#ifndef HEAD_H
#define HEAD_H
#include<iostream>
#include<string>
#include<cstring>
#include<ctime>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

class user
{
private:
	string user_name;
	string encrypted_key;
	string filename;
public:
	user(string uname, string k);
	user() = default;
	string encryptPassword(const string& password) const;
	bool checkPassword(const string& password) const;
	string getFilename(){ return filename; }
	string getusername(){return user_name;}
	friend bool menu(vector<user>& user_list, user& me);
};

class My_time
{
private:
	int year;
	int month;
	int day;
	string hm;
	string str;
public:
	bool operator==(My_time t);
	bool operator>(My_time t);
	bool operator<(My_time t);
	My_time(int y, int m, int d, string hm1);
	My_time(string st);
	My_time() = default;
	string getstr() { return str; }
	int getmonth(){ return month; }
	int getday(){ return day; }
};

class task
{
private:
	string task_name;
	My_time start_time;
	int priority;//0 minimum, larger values are more important
	int classification;//1��Study 2��Recreation 3��Life 4��Other
	My_time reminding_time;//Defaults to one hour before start_time
	int ID;
public:
	bool is_reminded;
	task(string tname, My_time stime, int prio, int clas, My_time rtime, int& id);
	task() = default;
	My_time getstart_time(){ return start_time; }
	void output();
	My_time& get_reminding_time();
	string getname() { return task_name; }
	int getID(){ return ID; }
	int get_priority() { return priority; }
	int get_classification() { return classification; }
};

void user_readFile(vector<user>& u, const char* fileName);
void task_readFile(vector<task>& t, const char* fileName);
bool menu(vector<user>& user_list, user& me);
void get_time(My_time& current_time);
void addtask(user u, vector<task>& task_list, int& id);
void showtask(vector<task>& task_list);
void deltask(user& me, vector<task>& task_list);
void remind(task t);
bool check(vector<task>& task_list,task *&tixing);
My_time strtotime(string& str);
bool is_correcttime(string st);
#endif
