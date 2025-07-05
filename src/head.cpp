#include"head.h"
#include<openssl/md5.h>
#include<iomanip>
#include<string>
#include <cstdlib>
using namespace std;

void user_readFile(vector<user>& u, const char* fileName)
{
	ifstream file(fileName);
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);
			string user_name;
			iss >> user_name;
			string encrtpted_key;
			iss >> encrtpted_key;
			user tmp(user_name, encrtpted_key);
			u.push_back(tmp);
		}
		file.close();
	}
}

My_time strtotime(string& str)
{
	int i = 0;
	int year = 0, month = 0, day = 0;
	string hm;
	while (str[i] != '-')
	{
		year = year * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (str[i] != '-')
	{
		month = month * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (str[i] != '-')
	{
		day = day * 10 + str[i] - '0';
		i++;
	}
	i++;
	hm = str.substr(i, 5);
	My_time result(year, month, day, hm);
	return result;
}

void task_readFile(vector<task>& t, const char* fileName)
{
	ifstream file(fileName);
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);
			string task_name;
			iss >> task_name;
			string s_time;
			iss >> s_time;
			string pt;
			iss >> pt;
			int priority = stoi(pt);
			string cl;
			iss >> cl;
			int classification = stoi(cl);
			string r_time;
			iss >> r_time;
			My_time start_time, reminding_time;
			start_time = strtotime(s_time);
			reminding_time = strtotime(r_time);
			int ID;
			iss >> ID;
			//My_time reminding_time;//save My_time in a proper way
			task tmp(task_name, start_time, priority, classification, reminding_time, ID);
			t.push_back(tmp);
		}
		file.close();
	}
	else
	{
		ofstream file1(fileName);
	}
}

bool is_correcttime(string st)
{
	int year, month, day;
	string hm;
	istringstream iss(st);
	string tmp;
	iss >> tmp;
	year = stoi(tmp);
	iss >> tmp;
	month = stoi(tmp);
	if (month < 1 || month>12)
	{
		return false;
	}
	iss >> tmp;
	day = stoi(tmp);
	if (day < 1)return false;
	bool isleapyear;
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)isleapyear = true;
	if (month == 2)
	{
		if (isleapyear)
		{
			if (day > 29)
				return false;
		}
		else if (day > 28)return false;
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day > 31)return false;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)return false;
	}
	else return false;
	iss >> hm;
	string sub;
	sub = hm.substr(0, 2);
	int t;
	t = stoi(sub);
	if (t < 0 || t > 23)return false;
	sub = hm.substr(3, 2);
	t = stoi(sub);
	if (t < 0 || t>59)return false;
	return true;
}

void addtask(user u, vector<task>& task_list, int& id)
{
	ofstream outfile;
	outfile.open(u.getFilename(), std::ios::app);
	if (outfile.is_open())
	{
		cout << "please input:\ntask name:";
		string taskname;
		cin >> taskname;
		cin.get();
		cout << "\nstart time:(eg: 2024 7 18 04:00)\n";
		string stime;
		getline(cin, stime);
		while (!is_correcttime(stime))
		{
			cout << "\t\033[41mWRONG INPUT\033[49m" << endl;
			cout << "You had just input a wrong time,please input again" << endl;
			cout << "\nstart time:(eg: 2024 7 18 15:00)\n";
			cin.get();
			getline(cin, stime);
		}
		My_time s_time(stime);
		cout << "\npriority:\n1 means the most important and 2 is on it's heels\n[input -1 if the priority doesn't matter]\n";
		int prio;
		cin >> prio;
		cout << "\nclassification:\n1-learning\t2-entertaining\t3-living\n[input -1 if the classification doesn't matter]\n";
		int clas;
		cin >> clas;
		cout << "\nreminding time:(eg: 2024 7 18 03:00)\n";
		string rtime;
		cin.get();
		getline(cin, rtime);
		while (!is_correcttime(rtime))
		{
			cout << "\t\033[41mWRONG INPUT\033[49m" << endl;
			cout << "You had just input a wrong time,please input again" << endl;
			cout << "\nstart time:(eg: 2024 7 18 15:00)\n";
			cin.get();
			getline(cin, rtime);
		}
		My_time r_time(rtime);
		//outfile << taskname<<" "<<s_time.getstr()<<" "<<prio<<" "<<clas<<" "<<r_time.getstr()<<endl;	
		task_list.push_back(task(taskname, s_time, prio, clas, r_time, id));
	}
	//task_readFile(task_list,u.getFilename().c_str());
}

bool menu(vector<user>& user_list, user& me)
{
	string str;
	int order;
	cout << "1.Login\n2.Register\nPlease enter the command.\n";
	cin >> str;
	if (str != "1" && str != "2")order = 3;
	else order = stoi(str);
	switch (order)
	{
	case 1:
	{
		string user_name;
		string key;
		cout << "Please enter a user name:";
		cin >> user_name;
		cout << "Please enter your password:";
		cin >> key;
		//comparison
		bool flag = false;
		for (auto& elem : user_list)
		{
			if (elem.user_name == user_name)
			{
				flag = true;
				me = elem;
				break;
			}
		}
		if (flag)
		{
			if (me.encrypted_key == me.encryptPassword(key))
			{
				system("clear");
				cout << "log in successfully" << endl;
				return true;
			}
			else
			{
				system("clear");
				cout << "wrong password" << endl;
				return false;
			}
		}
		else
		{
			system("clear");
			cout << "user not found" << endl;
			return false;
		}
		break;
	}
	case 2:
	{
		string user_name;
		string key;
		string key_retyped;
		cout << "Please create a username:";
		cin >> user_name;
		for (auto& elem : user_list)
		{
			if (elem.getusername() == user_name)
			{
				system("clear");
				cout << "This username has been registered\n";//#########################################################
				return false;
			}
		}
		cout << "Please set a password:";
		cin >> key;
		cout << "Please confirm the password:";
		cin >> key_retyped;
		if (key != key_retyped)
		{
			do
			{
				cout << "The passwords entered do not match, please reset the passwords:\n";
				cin >> key;
				cout << "Please reconfirm the password:\n";
				cin >> key_retyped;
			} while (key != key_retyped);
		}
		//Create users and store their passwords encrypted
		ofstream outfile;
		outfile.open("../data/user.txt", std::ios::app);
		if (outfile.is_open())
		{
			outfile << user_name << " " << me.encryptPassword(key) << endl;
		}
		system("clear");
		cout << "registered successfully, please log in again" << endl;
		return false;
		break;
	}
	default:
	{
		system("clear");//linux system("clear");
		cout << "Input error! \n";
		return false;
	}
	}
	return true;
}

void get_time(My_time& current_time)
{
	time_t now;
	string time_str;
	time(&now);

	time_str = ctime(&now);
	istringstream iss(time_str);
	int year;
	int month;
	int day;
	string hm;
	string tmp;
	iss >> tmp;
	iss >> tmp;
	tmp = tmp.substr(0, 3);
	if (tmp == "Jan")month = 1;
	else if (tmp == "Feb")month = 2;
	else if (tmp == "Mar")month = 3;
	else if (tmp == "Apr")month = 4;
	else if (tmp == "May")month = 5;
	else if (tmp == "Jun")month = 6;
	else if (tmp == "Jul")month = 7;
	else if (tmp == "Aug")month = 8;
	else if (tmp == "Sep")month = 9;//Sep?
	else if (tmp == "Oct")month = 10;
	else if (tmp == "Nov")month = 11;
	else if (tmp == "Dec")month = 12;
	else  cout << "WRONG INPUT!" << endl;
	iss >> tmp;
	day = stoi(tmp);
	iss >> tmp;
	hm = tmp.substr(0, 5);
	iss >> tmp;
	year = stoi(tmp);
	My_time t(year, month, day, hm);
	current_time = t;
	return;
}

void showtask(vector<task>& task_list)
{
	int num = task_list.size();
	for (int i = 0; i < num; i++)
	{
		bool switchflag = false;
		for (int j = 0; j < num - i - 1; j++)
		{
			if (task_list[j].getstart_time() > task_list[j + 1].getstart_time())
			{
				task tem = task_list[j];
				task_list[j] = task_list[j + 1];
				task_list[j + 1] = tem;
				switchflag = true;
			}
		}
		if (!switchflag)break;
	}
	cout << "You want to print events within a whole day or a month?\n1. in a whole day\n2. in a whole month\n3. All\n";
	int choice;
	cin >> choice;
	int yearnum, monthnum, daynum;
	switch (choice)
	{
	case 1:
		cout << "input the date:  eg:2024(year) 10(month) 20(day)\n";
		cin >> yearnum >> monthnum >> daynum;
		cout <<left<<setw(10)<< "name" <<setw(20)<< "start_time" <<setw(10)<< "priority" <<setw(15)<< "classification"
		 <<left<<setw(20)<< "reminding_time" <<setw(3) << "ID"  << endl;
		for (int i = 0; i < num; i++)
		{
			if (task_list[i].getstart_time().getmonth() == monthnum && task_list[i].getstart_time().getday() == daynum)
			{
				task_list[i].output();
			}
		}
		break;
	case 2:
		cout << "input month:  eg:2024(year) 10(month)\n";
		cin >> yearnum >> monthnum;
		cout <<left<<setw(10)<< "name" <<setw(20)<< "start_time" <<setw(10)<< "priority" <<setw(15)<< "classification"
		 <<left<<setw(20)<< "reminding_time" <<setw(3) << "ID"  << endl;
		for (int i = 0; i < num; i++)
		{
			if (task_list[i].getstart_time().getmonth() == monthnum)
			{
				task_list[i].output();
			}
		}
		break;
	case 3:
		cout <<left<<setw(10)<< "name" <<setw(20)<< "start_time" <<setw(10)<< "priority" <<setw(15)<< "classification"
		 <<left<<setw(20)<< "reminding_time" <<setw(3) << "ID"  << endl;
		for (int i = 0; i < num; i++)
		{
			task_list[i].output();
		}
		break;
	default:
		cout << "input error\n";
		break;
	}

}

void deltask(user& me, vector<task>& task_list)
{
	cout << "input the task ID you want to delete:" << endl;
	int target;
	cin >> target;
	int num = task_list.size();
	for (int i = 0; i < num; i++)
	{
		if (task_list[i].getID() == target)
			task_list.erase(task_list.begin() + i);
	}
}

void remind(task t)
{
	cout << "\n\t\033[41mREMINDER\033[49m\n" << "It's time for the event:"
		<< t.getname() << endl;
}

bool check(vector<task>& task_list,task *&tixing)
{
	My_time current_time;
	get_time(current_time);
	for (auto& elem : task_list)
	{
		if (elem.get_reminding_time() == current_time)
		{
			tixing=&elem;
			return true;
		}
	}
	return false;
}