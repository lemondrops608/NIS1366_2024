#include"head.h"
#include<thread>
#include<mutex>//the library which contains lock
#include<iostream>
#include<cstring>
#include<openssl/md5.h>
#include<fstream>
#include<chrono>
using namespace std;
mutex mtx;
user me;
int id;
vector<task> task_list;//Read events into an array
bool unstopped1 = true;
bool unstopped2 = true;
char command[50];
task *tixing;
void thread_function1(user me)//check commands regularly
{
	cout << "Type \"addtask\" to add a task.\n";
	cout << "Type \"showtask\" to show tasks.\n";
	cout << "Type \"deltask\" to delete a task.\n";
	while (unstopped1)
	{
		cin >> command;
		lock_guard<mutex> lock(mtx);//Automatic locking and unlocking
		if (strcmp(command, "addtask") == 0)
		{
			addtask(me, task_list, id);
			cout << "\n\t\033[43maddtask successed!\033[49m\n";
		}
		else if (strcmp(command, "showtask") == 0)
		{
			showtask(task_list);
			cout << "\n\t\033[43mshowtask successed!\033[49m\n";
		}
		else if (strcmp(command, "deltask") == 0)
		{
			deltask(me, task_list);
			cout << "\n\t\033[43mdeltask successed!\033[49m\n";
		}
		else if (strcmp(command, "help") == 0)
		{
			cout << "Type \"addtask\" to add a task.\n";
			cout << "Type \"showtask\" to show tasks.\n";
			cout << "Type \"deltask\" to delete a task.\n";
		}
		else if (strcmp(command, "quit") == 0)
		{
			unstopped1 = false;
			unstopped2 = false;
		}
		else if (strcmp(command, "ok") == 0)
		{
			tixing->is_reminded = true;
		}
		else
		{
			cout << "Type \"help\" to get help.\n";
		}
	}
}
void thread_function2(user me)//check time table regularly
{
	//lock_guard<mutex> lock(mtx);//Automatic locking and unlocking

	while (unstopped2)
	{
		if(check(task_list,tixing)&&!tixing->is_reminded)
		{
			lock_guard<mutex> lock(mtx);
			remind(*tixing);
			cout << '\a' << '\a' << '\a' << '\a';
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if(!unstopped2)break;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if(!unstopped2)break;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if(!unstopped2)break;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if(!unstopped2)break;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if(!unstopped2)break;
	}
}
int main()
{
	ifstream infile("../data/id.txt");
	infile >> id;
	infile.close();
	char firstcommand[50];
	cout<<"Type \"run\" to run the executable\n";
	while (cin >> firstcommand)
	{
		if (strcmp(firstcommand, "help") == 0)cout << "Type \"run\" to run the executable\n";
		else if (strcmp(firstcommand, "run") == 0)break;
		else cout << "Type \"help\" to get help.\n";
	}//run to get the program started


	vector<user> user_list;
	const char* fileName = "../data/user.txt";
	user_readFile(user_list, fileName);
	while (!menu(user_list, me)) { user_list.clear();user_readFile(user_list, fileName); };//login process

	task_readFile(task_list, me.getFilename().c_str());



	thread t1(thread_function1, me);
	thread t2(thread_function2, me);//Setting up two threads
	if (!t1.joinable())
	{
		cout << "Thread 1 creation failed\n";
		return -1;
	}
	if (!t2.joinable())
	{
		cout << "Thread 2 creation failed\n";
		return -1;
	}


	t1.join();
	t2.join();//Returning resources occupied by threads


	ofstream outfile("../data/id.txt");
	outfile << id;
	outfile.close();

	outfile.open(me.getFilename(), ios::out | ios::trunc);
	for (auto& elem : task_list)
	{
		outfile << elem.getname() << ' ' << elem.getstart_time().getstr() << ' '
			<< elem.get_priority() << ' ' << elem.get_classification() << ' ' <<
			elem.get_reminding_time().getstr() << ' ' << elem.getID() << endl;
	}
	return 0;
}
