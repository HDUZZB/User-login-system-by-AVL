#ifndef LANDING
#define LANDING
#include "AVL.h"
#include "User.cpp"
#include <conio.h>
#include <fstream>
#include <ctype.h>
#include <windows.h>

class Landing
{
	string nowuser;
	AVL<User> user;
public:
	void graph();
	Landing();// 构造函数
	bool welcome(int fst);// 首页
	void readfile(); // 从文件中读入信息
	void writefile(); // 将用户信息写入文件中，以 End 结尾
	int landing(); // 登陆界面
	bool Use();  // 用户界面
	bool insertuser(); // 增加用户
	bool deleteuser();  // 删除用户
	bool change();  // 修改密码
private:
	string getpass(); // 获取密码
	void encode(string& str); // 密码加密
	void decode(string& str); // 密码解密
};

#endif
