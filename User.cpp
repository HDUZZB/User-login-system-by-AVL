
#include "User.h"

User::User() {}
User::User(string a,string b)
{
	id = a;
	pass = b;
}
bool operator < (const User & t1,const User & t2) // 按 id 比较大小
{
	return t1.id < t2.id;
}
bool operator == (const User & t1,const User & t2) // id 相等，就算相等
{
	return t1.id == t2.id;
}
ostream& operator<<(ostream& out,const User& us)
{
	return out<<us.id;
}



