#ifndef MYUSER
#define MYUSER
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class User
{
public:
	string id; // 用户名
	string pass; // 密码
	User();
	User(string a,string b = "");
	friend bool operator < (const User & t1,const User & t2); // 按 id 比较大小
	friend bool operator == (const User & t1,const User & t2); // id 相等，就算相等
	friend ostream& operator<<(ostream& out,const User& us); //重定义输出流
};
#endif
