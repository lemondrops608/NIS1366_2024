#include"head.h"
#include<openssl/md5.h>
#include<iomanip>
#include<string>
#include <cstdlib>

task::task(string tname, My_time stime, int prio, int clas, My_time rtime, int& id)
{
	task_name = tname;
	start_time = stime;
	priority = prio;
	classification = clas;
	reminding_time = rtime;
	ID = id++;
	is_reminded = false;
}

void task::output()
{
	switch (classification)
	{
	case 1:
		cout <<left<< "\033[34m" <<setw(10)<<task_name  <<setw(20)<< start_time.getstr() <<setw(10)<< priority  <<setw(15)<< "learning";
		break;
	case 2:
		cout <<left<< "\033[32m" <<setw(10)<< task_name  <<setw(20)<< start_time.getstr() <<setw(10)<< priority <<setw(15)<< "entertaining";
		break;
	case 3:
		cout <<left<< "\033[33m" <<setw(10)<< task_name  <<setw(20)<< start_time.getstr() <<setw(10)<< priority  <<setw(15)<< "dailylife";
		break;

	default:
		cout <<left<< "\033[37m" <<setw(10)<< task_name  <<setw(20)<< start_time.getstr() <<setw(10)<< priority  <<setw(15)<< "other_type";
		break;
	}
	cout <<left<<setw(20)<< reminding_time.getstr() << setw(3) << ID << "\033[0m" << endl;
}

My_time& task::get_reminding_time()
{
	return reminding_time;
}