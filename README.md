基于AVL的用户登录系统
===========================
该项目模拟了一个用户登录系统。可用在登录服务器系统时验证用户名和密码(如`telnet`远程登录服务器)。

****
	
|Author|HDUZZB|
|---|---
|E-mail|hduzzb@126.com


****
## 目录
* [系统功能](#系统功能)
* [文件组成](#文件组成)
* [设计思路](#设计思路)
    * [基本数据结构](#基本数据结构)
    * [程序流程](#程序流程)
    * [类间关系](#类间关系)
* [测试](#测试)
    * [输入形式](#输入形式)
    * [功能测试](#功能测试)
    * [异常测试](#异常测试)
    * [验证AVL树](#验证AVL树)
* [项目重难点](#项目重难点) 

系统功能
-----------
该用户登录系统功能包括用户登录、用户密码更新、用户添加和用户删除4大功能。另外，系统也会经常添加新用户、删除老用户和更新用户密码等操作。由于用户信息的验证频率很高，系统有必要有效地组织这些用户信息，从而快速查找和验证用户。

文件组成
-----------
|文件名|文件功能|
|----|-----|
|[AVL.h](./AVL.h)|AVL树的声明和实现|
|[Landing.cpp](./Landing.cpp)|登录类的实现|
|[Landing.h](./Landing.h)|登录类的声明|
|[User.cpp](./User.cpp)|用户类的实现|
|[User.h](./User.h)|用户类的声明|
|[main.cpp](./main.cpp)|主函数|
|[user.txt](./user.txt)|测试数据|

设计思路
-----------

### 基本数据结构
采用二叉平衡查找树（AVL），采用了模板类，以用户名（IP）作为比较的关键词进行插入。二叉平衡查找树是在二叉搜索树（BST）的基础上进行了优化，使得树基本达到平衡。定义内部类Node来存储AVL树的节点信息。
```cpp
class Node{
	public:
		T date; // 记录节点的值
		int balance,deep; // 表示节点的平衡值和它向下的最大深度
		Node * left;  // 指向左节点
		Node * right;  // 指向右节点
		Node():balance(0),left(NULL),right(NULL),deep(1){}
		Node(T item):date(item),balance(0),left(NULL),right(NULL),deep(1){}
	};
```
要创建一颗包含用户信息的树，要能适应频繁的查找，想到生活中登陆时都是先输入用户名，且每个人的用户名是唯一的，因此在实现时将用户名（string类型）作为AVL树的比较参数，这样就可以实现快速的插入、删除和查找，重定义User类的比较函数
```cpp
bool operator < (const User & t1,const User & t2) // 按 id 比较大小
{
		return t1.id < t2.id;
}
```
AVL树是用模板类实现的，这样就可以直接比较两个用户类，方便了很多。

###程序流程

###类间关系


测试
----------

###输入形式
基本以 string 串的形式输入输出，用户名应该只包含字母以及数字

###功能测试
####添加用户
注意：输入用户名时，输入0，才会退出。 用户名要只有字母或数字

####删除用户
注意：删除用户是也需要密码

####用户登陆
注意：密码错误三次会自动跳到上一层

####修改密码


###异常测试
####用户名不能重复

####用户名不能包含非法字符

####注册新用户，两次密码要相同

####只能删除存在的用户

####删除用户是也要输入密码

####登录时，用户名要合法

####登陆时密码要正确

####修改密码时要和原密码不相同


###验证AVL树
####初始阶段

####加入节点 a 右旋

####加入节点 x , y 左旋

####加入节点 q 右左旋

####加入节点 d ，k 左右旋

####删除节点 c


项目重难点
----------

###AVL树的实现
二叉查找树（BST）是一种很好的数据结构，它的特点是，对其任一节点，都满足该节点的左子树的所有点的值都小于该节点，而右子树则是大于。因此采用链表来实现它，创建关于节点的一个类 Node ，内含描述该节点的值，及左右指针。定义 insert() 函数来实现新节点的插入。
```cpp
template <typename T>
void AVL<T>::insert(const T& item) // 加入节点 item
{
	NodePoint sc = myRoot;
	if(sc == NULL)  // 若当前树为空，直接创建根节点
	{
		myRoot = new Node(item);
		return;
	}
	stack<NodePoint> step; // 用于记录从根节点走到目标节点的路径
	int s,gs;
	while(1)
	{
		step.push(sc);
		//cout<<item<<" "<<sc->date<<"\n";
		if(item < sc->date)  // 如果新节点的值小于当前节点，则跳到左子树
		{
			if(sc->left == NULL)
			{
				sc->left = new Node(item);
				s = 0;
				sc->balance++;
				sc->deep = max(sc->deep,2);
				break;
			}
			else sc = sc->left;
		}
		else if(sc->date < item)   // 如果新节点的值大于当前节点，则跳到右子树
		{
			if(sc->right == NULL)
			{
				sc->right = new Node(item);
				s = 1;
				sc->balance--;
				sc->deep = max(sc->deep,2);
				break;
			}
			else sc = sc->right;
		}
		else return ;
	}
	if(step.size() <= 1) return; // 不然，说明该节点已经存在，直接结束
	step.pop();
	int pre;
	NodePoint pa,tmp;
	while(!step.empty())
	{
		gs = s; // s表示的是当前节点子节点，gs表示当前节点的孙子节点
		tmp = step.top();
		step.pop();
		if(tmp->left == sc) s = 0;
		else s = 1; // 0表示在左子树，1表示在右子树
		pre = tmp->balance;
		update(tmp); // 更新 tmp 节点的balance和deep
		if(pre == tmp->balance) break; // 若 tmp 节点的balance值未发生变化，则其祖先也不会变化
		if(abs(tmp->balance) > 1)   // 如果平衡被打破
		{
			if(step.empty()) pa = NULL;
			else pa = step.top();
			if(!s && !gs) RightRotating(pa,tmp); // 当新节点位于左子树的左子树
			else if(s && gs) LeftRotating(pa,tmp); // 当新节点位于右子树的右子树
			else if(!s && gs) Left_RightRotating(pa,tmp); // 当新节点位于左子树的右子树
			else Right_LeftRotating(pa,tmp); // 当新节点位于右子树的左子树
		}
	}
}
```
查找、删除函数也是类似的步骤。

###AVL树的旋转
AVL树相对于BST树，多了平衡两字，树都有高度，而AVL树就是要求每一个节点的左子树和右子树的高度差不超过1，这样就能使其尽可能的减小整棵树的高度，使时间复杂度能稳定在O(logN), 但我们不可能去约束用户的输入，因此，引入了四种旋转：左旋、右旋、先右旋再左旋、先左旋后右旋。
***
####左旋

####右旋

####先右旋再左旋

####先左旋后右旋
***
以下是左-右旋的代码：
```cpp
template <typename T>
void AVL<T>::Left_RightRotating(Node* pa , Node* pos){
	NodePoint s,ss; // s 记录的是 ss 的父节点
	s = pos->left;ss = s->right;
	pos->left = ss;
	s->right = ss->left;
	ss->left = s;
	update(s);
	update(ss); // 以上部分是左旋
	if(pa == NULL) 
		myRoot = ss;
	else if(pa->left == pos)
		pa->left = ss;
	else 
		pa->right = ss;
	pos->left = ss->right;
	ss->right = pos;
	update(pos);
	update(ss);
}
```
还有一个重要的部分是选择何种旋转，以下例举插入函数中的部分代码：
```cpp
int pre;
NodePoint pa,tmp;
while(!step.empty()){ // step 内存的是从根节点到当前节点的路径，由于stack的特性，离栈顶越近，深度越深
	gs = s;  // gs 记录当前节点的父节点是祖父节点的左节点（0）还是右节点（1）
	tmp = step.top(); // 不断弹出元素，并更新balance值和deep值
	step.pop();
	if(tmp->left == sc) s = 0; 
	else s = 1;   // s 记录当前节点是父节点的左节点（0）还是右节点（1）
	pre = tmp->balance;
	update(tmp);
	if(pre == tmp->balance) break;
	if(abs(tmp->balance) > 1){ // 如果平衡被打破
		if(step.empty()) pa = NULL;
		else pa = step.top();
		if(!s && !gs) RightRotating(pa,tmp);
		else if(s && gs) LeftRotating(pa,tmp);
		else if(!s && gs) Left_RightRotating(pa,tmp);
		else Right_LeftRotating(pa,tmp);
	}
}
```
###查询操作时，怎么能找到相应用户的节点？
考虑到用户名的唯一性，所以将用户名作为AVL树的关键词，以字符串来比较大小，进行排序，重定义User类的比较操作符，只比较IP,因此，在查询的时候，新建一个User的对象，其IP赋值为所要查询的IP，然后调用查找函数，可找到对应的点