#include"head.h"
#include<openssl/md5.h>
#include<iomanip>
#include<string>
#include <cstdlib>

string user::encryptPassword(const string& password) const
{
	unsigned char digest[MD5_DIGEST_LENGTH];
	MD5(reinterpret_cast<const unsigned char*>(password.c_str()), password.length(), digest);
	std::stringstream ss;
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
		ss << hex << setw(2) << setfill('0') << static_cast<int>(digest[i]);
	}
	return ss.str();
}

bool user::checkPassword(const string& password) const
{
	return encrypted_key == encryptPassword(password);
}

user::user(string uname, string k)
{
	user_name = uname;
	encrypted_key = k;
	filename = "../data/" + uname + ".txt";//for example: your user_name is nmt, then the filename is "nmt.txt"
}