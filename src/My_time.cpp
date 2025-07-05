#include"head.h"
#include<openssl/md5.h>
#include<iomanip>
#include<string>
#include <cstdlib>

My_time::My_time(int y, int m, int d, string hm1)
{
	year = y; month = m; day = d; hm = hm1;
	str = to_string(year) + '-' + to_string(month) + '-' + to_string(day) + '-' + hm;
}

My_time::My_time(string st)
{
	istringstream iss(st);
	string tmp;
	iss >> tmp;
	year = stoi(tmp);
	iss >> tmp;
	month = stoi(tmp);
	iss >> tmp;
	day = stoi(tmp);
	iss >> this->hm;
	str = to_string(year) + '-' + to_string(month) + '-' + to_string(day) + '-' + hm;
}

bool My_time::operator==(My_time t)
{
	if (year == t.year && month == t.month && day == t.day && hm == t.hm)
		return true;
	return false;
}

bool My_time::operator>(My_time t)
{
	if (year > t.year)return true;
	else if (year < t.year)return false;
	else
	{
		if (month > t.month)return true;
		else if (month < t.month)return false;
		else
		{
			if (day > t.day)return true;
			else if (day < t.day)return false;
			else
			{
				for (int i = 0;;)
				{
					if (hm[i] > t.hm[i])return true;
					else if (hm[i] < t.hm[i])return false;
					else
					{
						if (i != 1)i++;
						else i += 2;
					}
				}
			}
		}
	}
}

bool My_time::operator<(My_time t)
{
	if (year < t.year)return true;
	else if (year > t.year)return false;
	else
	{
		if (month < t.month)return true;
		else if (month > t.month)return false;
		else
		{
			if (day < t.day)return true;
			else if (day > t.day)return false;
			else
			{
				for (int i = 0;;)
				{
					if (hm[i] < t.hm[i])return true;
					else if (hm[i] > t.hm[i])return false;
					else
					{
						if (i != 1)i++;
						else i += 2;
					}
				}
			}
		}
	}
}