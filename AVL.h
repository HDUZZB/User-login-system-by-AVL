#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;
#ifndef MYAVLCLASS
#define MYAVLCLASS
template <typename T>
class AVL
{
	class Node
	{
	public:
		T date;
		int balance,deep;
		Node * left;
		Node * right;
		Node():balance(0),left(NULL),right(NULL),deep(1) {}
		Node(T item):date(item),balance(0),left(NULL),right(NULL),deep(1) {}
	};
	typedef Node* NodePoint;
public:
	NodePoint myRoot;
	AVL();
	bool empty() const;
	bool search(T& item); // 找到 item 所在的节点，将所需信息复制到 key上
	void insert(const T& item);// 加入节点 item
	void remove(const T& item);// 删除节点 item
	void update(const T& item); // 更新 item 的节点
	void display(Node* st)const; // 输出全部信息
	void display(Node* st,vector<T>& cnt); // 遍历所有节点，将所需的信息存到 str中
	void graph(ostream& out) const; // 将整棵树以图的形式输出
	void LeftRotating(Node* pa , Node* pos); // 平衡树 左转
	void RightRotating(Node* pa , Node* pos);// 平衡树 右转
	void Left_RightRotating(Node* pa , Node* pos);// 平衡树 左右转
	void Right_LeftRotating(Node* pa , Node* pos);// 平衡树 右左转

private:
	void search2(const T& item,bool& found,NodePoint& locptr,NodePoint& parent,stack<NodePoint>& step) const; // 定位到 item 在的节点
	void update(Node* p);// 用于旋转后的更新
	void graphAux(ostream& out,int indent,NodePoint substrrRoot) const;
};
template <typename T>
AVL<T>::AVL()  // 树的根节点设置为空
{
	myRoot = NULL; 
}
template <typename T>
bool AVL<T>::empty() const  // 判断树的根节点是否为空
{
	return myRoot == NULL;  
}
template <typename T>
bool AVL<T>::search(T& item) // 找到与 item 的IP相同的节点，利用引用提取信息
{
	NodePoint sc = myRoot;
	while(sc != NULL)
	{
		if(sc->date == item)   // sc->date == item 说明关键词匹配，找到了目标
		{
			item = sc->date;  // 将所有的信息赋值给 item ，因为item是引用，外部也发生了变化
			return true;
		}
		if(sc->date < item) sc = sc->right; // 若目标关键词大于当前节点，说明在右子树
		else sc = sc->left; // 否则，说明在左子树
	}
	return false;
}
template <typename T>
void AVL<T>::update(Node* p) // 用于旋转后深度值的更新
{
	if(p->left == NULL && p->right == NULL) p->deep = 1; // 若无左右子树，深度为 1
	else if(p->left == NULL) p->deep = (p->right->deep)+1;
	else if(p->right == NULL) p->deep = (p->left->deep)+1; // 若只有一颗子树，深度为其子树深度+1
	else p->deep = max(p->left->deep,p->right->deep)+1; // 否则，深度为max(左，右)+1
	if(p->left == NULL && p->right == NULL) p->balance = 0; // 平衡值类似
	else if(p->left == NULL) p->balance = -(p->right->deep);
	else if(p->right == NULL) p->balance = p->left->deep;
	else p->balance = (p->left->deep)-(p->right->deep);
	// 调试错误1: 由于觉得形式相似，直接复制，导致 deep 没改成 balance

	//if(p->left != NULL) cout<<p->left->deep<<"   1111\n";
	//if(p->right != NULL) cout<<p->right->deep<<"   2222\n";
	//cout<<p->date<<"\n"<<p->deep<<" "<<p->balance<<"\n";
}
template <typename T>
void AVL<T>::update(const T& item)  // 更新目标的值
{
	NodePoint sc = myRoot;
	while(sc != NULL)
	{
		if(sc->date < item) sc = sc->right;
		else if(item < sc->date) sc = sc->left;
		else   // 找到目标后，赋值更新
		{
			sc->date = item;
			return;
		}
	}
}
template <typename T>
void AVL<T>::display(Node* st)const // 输出全部信息
{
	if(st->left != NULL) display(st->left);
	if(st != NULL) cout<<st->date<<"\n";
	if(st->right != NULL) display(st->right);
}
template <typename T>
void AVL<T>::display(Node* st,vector<T>& cnt) //遍历所有节点，将所需信息存到 str中
{
	if(st == NULL) return ;
	if(st->left != NULL) display(st->left,cnt);
	cnt.push_back(st->date); // 将节点信息放到向量 cnt 中
	if(st->right != NULL) display(st->right,cnt);
	// 错误3 ：递归调用display时忘加 str 参数
}
template <typename T>
void AVL<T>::graph(ostream& out) const // 将整棵树以图的形式输出
{
	graphAux(out,0,myRoot);
}
template <typename T>
void AVL<T>::graphAux(ostream& out,int indent,NodePoint subtreeRoot) const
{
	if(subtreeRoot != NULL)
	{
		graphAux(out,indent+7,subtreeRoot->right);
		out<<setw(indent)<<" "<<subtreeRoot->date<<"\n";
		graphAux(out,indent+7,subtreeRoot->left);
	}
}
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
template <typename T>
void AVL<T>::search2(const T& item,bool& found,NodePoint& sc,NodePoint& fa,stack<NodePoint>& step) const // 定位到 item 在的节点
{
	sc = myRoot;
	fa = NULL;
	found = false;
	while(sc != NULL)  // 找到sc节点，用fa记录其父节点，用step记录其路径
	{
		step.push(sc);
		if(item < sc->date)
		{
			fa = sc;
			sc = sc->left;
		}
		else if(sc->date < item)
		{
			fa = sc;
			sc = sc->right;
		}
		else
		{
			found = true;
			return;
		}
	}
}
template <typename T>
void AVL<T>::remove(const T& item) // 删除节点 item
{
	NodePoint sc,fa,tmp;
	bool found;
	stack<NodePoint> step;
	search2(item,found,sc,fa,step); // 先找到要删除节点的位置
	if(!found) return;
	// 接下来要让此节点与其右子树的最左边节点进行交换，有可能没有，也有可能就是其右节点
	if(sc->left != NULL && sc->right != NULL)
	{
		tmp = sc->right;
		step.push(tmp);
		fa = sc;
		while(tmp->left != NULL)   // 一直走到最左边
		{
			fa = tmp;
			tmp = tmp->left;
			step.push(tmp);
		}
		sc->date = tmp->date; // 交换
		sc = tmp;
	}
	// 连接sc的父节点与它的子树
	if(fa == NULL) // 若只有一个节点
		myRoot = NULL;
	else if(sc == fa->right)  // 若sc是右节点
	{
		if(sc->left != NULL)
			fa->right = sc->left;
		else
			fa->right = sc->right;
	}
	else
	{
		if(sc->left != NULL)
			fa->left = sc->left;
		else
			fa->left = sc->right;
	}
	if(sc == myRoot) myRoot = NULL;
	delete sc; // 删除节点
	if(step.size() <= 1) return;
	step.pop();
	int pre;
	NodePoint pa;
	while(!step.empty())  // 更新树，操作和插入时一样
	{
		tmp = step.top();
		step.pop();
		pre = tmp->balance;
		update(tmp);
		if(pre == tmp->balance) break;
		if(step.empty()) pa = NULL;
		else pa = step.top();
		if(tmp->balance == -2)
		{
			if(tmp->right->balance == 1) Right_LeftRotating(pa,tmp);
			else LeftRotating(pa,tmp);
		}
		else if(tmp->balance == 2)
		{
			if(tmp->left->balance == -1) Left_RightRotating(pa,tmp);
			else RightRotating(pa,tmp);
		}
	}

}
template <typename T>
void AVL<T>::LeftRotating(Node* pa , Node* pos) // 平衡树 左转
{
	Node* tmp = pos->right;
	if(pa == NULL)
		myRoot = tmp;
	// 当前节点的父节点连接其右节点
	else if(pa->left == pos)
		pa->left = tmp;
	else
		pa->right = tmp;
	// 其右节点的左子树变成当前节点的右子树
	pos->right = tmp->left;
	tmp->left = pos;
	update(pos);
	update(tmp);
}
template <typename T>
void AVL<T>::RightRotating(Node* pa , Node* pos) // 平衡树 右转
{
	Node* tmp = pos->left;
	if(pa == NULL)
		myRoot = tmp;
	// 当前节点的父节点连接其左节点
	else if(pa->right == pos)
		pa->right = tmp;
	else
		pa->left = tmp;
	// 其左节点的右子树变成当前节点的左子树
	pos->left = tmp->right;
	tmp->right = pos;
	update(pos);
	update(tmp);
}
template <typename T>
void AVL<T>::Left_RightRotating(Node* pa , Node* pos) // 平衡树 左右转
{
	NodePoint s,ss;
	s = pos->left;
	ss = s->right;
	pos->left = ss;
	s->right = ss->left;
	ss->left = s;
	update(s);
	update(ss); // 以上部分是左旋，以下是右旋
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
template <typename T>
void AVL<T>::Right_LeftRotating(Node* pa , Node* pos) // 平衡树 右左转
{
	NodePoint s,ss;
	s = pos->right;
	ss = s->left;
	pos->right = ss;
	s->left = ss->right;
	ss->right = s;
	update(s);
	update(ss); // 以上部分是右旋，以下是左旋
	if(pa == NULL)
		myRoot = ss;
	else if(pa->right == pos)
		pa->right = ss;
	else
		pa->left = ss;
	pos->right = ss->left;
	ss->left = pos;
	update(pos);
	update(ss);
}
#endif
