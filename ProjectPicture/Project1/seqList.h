#include<iostream>

using namespace std;

template <class T>
struct CircLinkNode       //循环链表结点类的定义
{
	T data;			          //数据域
	CircLinkNode<T> *link;      //指针域

	CircLinkNode()
	{
		link = NULL;
	}                       //构造函数1
	CircLinkNode(T d)
	{
		data = d;  link = NULL;
	}     //构造函数2

};


template <class T>
class CircList       //单链表类定义, 不用继承也可实现
{
protected:
	CircLinkNode<T> *head;	 //表头指针

public:
	CircList() { head = new CircLinkNode<T>;  }  //构造函数
	CircList(const T& x) { head = new CircLinkNode<T>(x);  }
	~CircList() { makeEmpty(); }	//析构函数

	void makeEmpty();		    //将链表置为空表
	int Length() const;		//计算链表的长度
	CircLinkNode<T> *getHead() const { return head; }
	CircLinkNode<T> *Search(T x);	 //搜索含x元素
	CircLinkNode<T> *Locate(int i);	 //定位第i个元素
	bool getData(int i, T& x); //取出第i元素值
	void setData(int i, T& x);		//更新第i元素值
	bool Insert(int i, T& x);		//在第i元素后插入
	bool Remove(int i, T& x);	         //删除第i个元素
	bool IsEmpty() const 	        //判表是否为空
	{
		return head->link == NULL ? true : false;
	}
	void inputFront(T endTag);
	void inputRear(T endTag);
	void output();
	CircList<T>& operator=(CircList<T>& L); //重载赋值运算符

	//Josephus(int n);
};



template <class T>
void CircList<T>::makeEmpty() 	//将链表置为空表
{
	CircLinkNode<T> *q;
	while (head->link != NULL)
	{
		q = head->link;              //q指向被删结点
		head->link = q->link;   //从链上删除该结点
		delete q;		            //释放结点空间
	}
}


template <class T>
int CircList<T>::Length() const		//计算链表的长度
{
	CircLinkNode<T> *p = head->link;
	int count = 0;
	while (p != NULL)
	{
		p = p->link;
		count++;
	}
	return count;
}


template <class T>
CircLinkNode<T> *CircList<T>::Search(T x)  //搜索x
{
	CircLinkNode<T> *current = head->link;
	while (current != NULL)
	{
		if (current->data == x)  break;
		else	current = current->link;
	}
	return current;
}


template <class T>
CircLinkNode<T> *CircList<T>::Locate(int i)
{  //返回表中第 i 个元素的地址
   //若i<0 或 i>表中结点个数，则返回NULL。

	if (i < 0)  return NULL;		// i值不合理
	CircLinkNode<T> *current = head;
	int k = 0;
	while (current->link != NULL && k < i)
	{
		current = current->link;	 k++;
	}
	if (k >= i)
		return current;    //返回第 i 个结点的地址或NULL
	else
		return NULL;
}



template <class T>
bool CircList<T>::getData(int i, T& x)  //取出第i元素值
{
	if (i <= 0)  return false;

	CircLinkNode<T> *current = Locate(i);

	if (current == NULL)
		return false;
	else
	{
		x = current->data;
		return true;
	}
}


template <class T>
void CircList<T>::setData(int i, T& x)		//更新第i元素值
{
	if (i <= 0)  return;

	CircLinkNode<T> *current = Locate(i);

	if (current == NULL)
		return;
	else
		current->data = x;
}


template <class T>
bool CircList<T>::Insert(int i, T& x)		//在第i元素后插入
{  //将新元素 x 插入在链表中第 i 个结点之后

	CircLinkNode<T> *current = Locate(i);

	if (current == NULL) return false;  //无插入位置
	CircLinkNode<T> *newNode = new  CircLinkNode<T>(x);   //创建新结点
	if (newNode == NULL)
	{
		cerr << "存储分配错误!" << endl;    exit(1);
	}
	newNode->link = current->link;    //插入
	current->link = newNode;
	return true;
}


template <class T>
bool CircList<T>::Remove(int i, T& x)  //删除第i个元素
{  //删除链表第i个元素, 通过引用参数x返回元素值

	CircLinkNode<T> *current = Locate(i - 1);

	if (current == NULL || current->link == NULL)
		return false; 	//删除不成功 	
	CircLinkNode<T> *del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}



template <class T>      //前插建立链表
void CircList<T>::inputFront(T endTag)
{
	makeEmpty();

	CircLinkNode<T> *newNode;
	T val;
	cin >> val;
	while (val != endTag)
	{
		newNode = new CircLinkNode<T>(val);
		if (newNode == NULL)
		{
			cerr << "存储分配错误!" << endl;   exit(1);
		}
		newNode->link = head->link;  //插在表前端
		head->link = newNode;
		cin >> val;
	}
}




template <class T>    //后插建立链表
void CircList<T>::inputRear(T val)
{
	CircLinkNode<T> *newNode, *last;
	last = head;
	while (last->link != NULL) {
		last = last->link;
	}
	newNode = new CircLinkNode<T>(val);
	if (newNode == NULL)
	{
		cerr << "存储分配错误!" << endl;   exit(1);
	}
	last->link = newNode;
	last = newNode;
}



template <class T>    //输出链表
void CircList<T>::output()
{
	CircLinkNode<T> *p = head->link;

	while (p != NULL)
	{
		cout << p->data << endl;
		p = p->link;
	}
	cout << endl;
}


template <class T>
CircList<T>& CircList<T>::operator=(CircList<T>& L) //重载赋值运算符
{
	T  value;
	CircLinkNode<T> *srcptr = L.getHead();
	CircLinkNode<T> *destptr = head = new CircLinkNode<T>;
	while (srcptr->link != NULL)
	{
		value = srcptr->link->data;
		destptr->link = new CircLinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	return *this;
}
