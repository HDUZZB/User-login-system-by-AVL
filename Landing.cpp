#include "Landing.h"

void Landing::graph()
{
	user.graph(cout);
}
Landing::Landing() // 构造函数
{
	nowuser.clear();
}
bool Landing::welcome(int fst)   // 首页
{
	if(!fst) readfile();
	// 错误4：每次回到这个函数都会读一遍文件
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t欢迎进入用户登录系统*^_^*\n\n");
	printf("\t\t\t1.注册用户\n");
	printf("\t\t\t2.删除用户\n");
	printf("\t\t\t3.用户登录\n");
	printf("\t\t\t4.退出\n");
	printf("\t\t\t5.查看用户AVL树\n");
	printf("\t\t\t请选择相应的序号 : ");
	int k,tmp;
	scanf("%d",&k);
	if(k == 1)
	{
		while(!insertuser()); // 调用添加用户函数
	}
	else if(k == 2)
	{
		while(!deleteuser()); // 调用删除用户函数
	}
	else if(k == 3)
	{
		while((tmp = landing()) == 0); // 调用登录函数
		if(tmp == 1) while(!Use());
		nowuser.clear();
	}
	else if(k == 4)
	{
		writefile(); // 调用写入文件函数
		return true;
	}
	else if(k == 5)
	{
		graph();
		Sleep(4000);
	}
	else
	{
		printf("\n\t\t\t请输入正确的编号！\n");
		Sleep(1000); // 停留 1s
	}
	return false;
}
void Landing::readfile()   // 从文件中读入信息
{
	string id,pass;
	ifstream uin("user.txt");
	while(uin>>id)
	{
		if(id == "End") break;
		uin>>pass;
		decode(pass); // 信息解密
		User us(id,pass); // 创建新的对象
		user.insert(us); // 插入节点
	}
}
void Landing::writefile()  // 将用户信息写入文件中，以 End 结尾
{
	ofstream uout("user.txt");
	vector<User> cnt;
	user.display(user.myRoot,cnt);
	for(int i=0; i<cnt.size(); i++)
	{
		encode(cnt[i].pass); // 信息加密
		uout<<cnt[i].id<<" "<<cnt[i].pass<<"\n";
	}
	uout<<"End";
}
int Landing::landing()  // 登陆界面
{
	system("cls");
	printf("\n\n\n");
	string id,pass;
	char ch;
	int times;
	bool flag;
	printf("\t\t\t欢迎进入用户登陆界面！！(按0退出)\n\n");
	printf("\t\t\t请输入用户名 ：");
	cin>>id;
	if(id == "0") return -1;
	User us(id);
	if(!user.search(us))  // 如果找不到该用户
	{
		printf("\n\t\t\t不存在该用户名！！");
		Sleep(700);
		return 0;
	}
	times = 3;
	flag = false;
	while(times--)  // 密码最多错 3 次
	{
		pass.clear();
		printf("\n\t\t\t请输入密码 ：");
		pass = getpass(); // 调用获取密码函数
		if(us.pass != pass) printf("\n\t\t\t密码错误！请重试！\n");
		else
		{
			flag = true;
			break;
		}
	}
	if(!flag)
	{
		printf("\n\t\t\t请确认用户名是否正确！！\n");
		Sleep(1000);
		return -1;
	}
	else nowuser = id;
	return 1;
}
bool Landing::Use()   // 用户界面
{
	system("cls");
	int k;
	bool flag = true;
	printf("\n\n\n");
	printf("\t\t\t欢迎进入用户界面！！\n\n");
	printf("\t\t\t1.修改密码\n");
	printf("\t\t\t2.返回上一层\n");
	printf("\t\t\t请输入操作对应的编号 : ");
	scanf("%d",&k);
	switch(k)
	{
	case 1:
		while(!change())
		{
			printf("\n\t\t\t是否重新修改？（Y or N）：");
			char ch;
			scanf(" %c",&ch);
			if(ch == 'N' || ch == 'n') break;
		};
		return false;
	case 2:
		return true;
	default:
		flag = false;
		break;
	}
	if(!flag)
	{
		printf("\n\t\t\t请输入正确的操作！\n");
		Sleep(800);
		return false;
	}
}
bool Landing::insertuser()  // 增加用户
{
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t欢迎进入增加用户界面！(按0退出)\n\n");
	string id,pass,repass;
	vector<string> cnt;
	char ch;
	printf("\n\t\t请输入新增的用户名(由字母、数字组成) ：");
	cin>>id;
	if(id == "0") return true;
	// 若包含非字母或数字字符，视为非法
	for(int i=0; i<id.length(); i++)if(!isalpha(id[i]) && !isdigit(id[i]))
		{
			printf("\n\t\t\t用户名包含非法字符！！\n");
			Sleep(700);
			return false;
		}
	User us(id);
	if(user.search(us))  // 查找树中是否已经存在此用户名
	{
		printf("\n\t\t\t该用户名已存在！\n");
	}
	else
	{
		printf("\n\t\t\t请输入密码 ：");
		pass = getpass();
		printf("\n\t\t\t请再次输入密码：");
		repass = getpass();
		if(repass != pass)
		{
			printf("\n\t\t\t密码不一致！ 注册失败！\n");
		}
		else
		{
			user.insert(User(id,pass)); // 插入新节点
			printf("\n\t\t\t注册成功！\n");
		}
	}
	printf("\n\t\t是否继续增加读者？（Y or N）: ");
	scanf(" %c",&ch);
	if(ch == 'Y' || ch == 'y') return false;
	return true;
}
bool Landing::deleteuser()   // 删除用户
{
	system("cls");
	printf("\n\n\n");
	printf("\n\t\t\t欢迎进入删除用户界面！(按0退出)\n\n");
	string id;
	printf("\n\t\t\t请输入要删除的用户名 ：");
	cin>>id;
	if(id == "0") return true;
	User r(id);
	if(!user.search(r)) printf("\n\t\t\t该读者不存在！\n");
	else
	{
		printf("\n\t\t\t请输入密码：");
		string pass = getpass();
		if(pass != r.pass)
		{
			printf("\n\t\t\t密码错误！！\n");
		}
		else
		{
			printf("\n\t\t您确定要删除此用户？（Y or N）：");
			char ch;
			scanf(" %c",&ch);
			if(ch == 'Y' || ch == 'y')
			{
				user.remove(r);
				printf("\n\t\t\t删除成功！\n");
			}
		}
	}
	char ch;
	printf("\n\t\t是否继续删除读者？（Y or N）: ");
	scanf(" %c",&ch);
	if(ch == 'Y' || ch == 'y') return false;
	return true;
}
bool Landing::change()   // 修改密码
{
	system("cls");
	User r(nowuser);
	user.search(r);
	string newpass;
	printf("\n\n\n\t\t\t请输入新密码 ：");
	newpass = getpass();
	if(r.pass == newpass)
	{
		printf("\n\t\t\t新密码和原密码相同！！\n");
		return false;
	}
	r.pass = newpass;
	user.update(r);
	printf("\n\t\t\t修改成功！！\n");
	Sleep(700);
	return true;
}
string Landing::getpass()
{
	char ch;
	string pass;
	while((ch=getch())!=13) // 当读入的不是回车
	{
		if(ch == '\b')  // 若读入退格键
		{
			if(pass.length() != 0)
			{
				printf("\b \b");
				pass = pass.substr(0,pass.length()-1);
			}
			continue;
		}
		// 否则输出一个星号
		printf("*");
		pass += ch;
	}
	printf("\n");
	return pass;
}
void Landing::encode(string& str)  // 简单的加密
{
	for(int i=0; i<str.length(); i++)
	{
		str[i] -= i;
	}
}
void Landing::decode(string& str)
{
	for(int i=0; i<str.length(); i++)
	{
		str[i] += i;
	}
}

