#include<iostream>

using namespace std;

template <class T>
struct CircLinkNode       //ѭ����������Ķ���
{
	T data;			          //������
	CircLinkNode<T> *link;      //ָ����

	CircLinkNode()
	{
		link = NULL;
	}                       //���캯��1
	CircLinkNode(T d)
	{
		data = d;  link = NULL;
	}     //���캯��2

};


template <class T>
class CircList       //�������ඨ��, ���ü̳�Ҳ��ʵ��
{
protected:
	CircLinkNode<T> *head;	 //��ͷָ��

public:
	CircList() { head = new CircLinkNode<T>;  }  //���캯��
	CircList(const T& x) { head = new CircLinkNode<T>(x);  }
	~CircList() { makeEmpty(); }	//��������

	void makeEmpty();		    //��������Ϊ�ձ�
	int Length() const;		//��������ĳ���
	CircLinkNode<T> *getHead() const { return head; }
	CircLinkNode<T> *Search(T x);	 //������xԪ��
	CircLinkNode<T> *Locate(int i);	 //��λ��i��Ԫ��
	bool getData(int i, T& x); //ȡ����iԪ��ֵ
	void setData(int i, T& x);		//���µ�iԪ��ֵ
	bool Insert(int i, T& x);		//�ڵ�iԪ�غ����
	bool Remove(int i, T& x);	         //ɾ����i��Ԫ��
	bool IsEmpty() const 	        //�б��Ƿ�Ϊ��
	{
		return head->link == NULL ? true : false;
	}
	void inputFront(T endTag);
	void inputRear(T endTag);
	void output();
	CircList<T>& operator=(CircList<T>& L); //���ظ�ֵ�����

	//Josephus(int n);
};



template <class T>
void CircList<T>::makeEmpty() 	//��������Ϊ�ձ�
{
	CircLinkNode<T> *q;
	while (head->link != NULL)
	{
		q = head->link;              //qָ��ɾ���
		head->link = q->link;   //������ɾ���ý��
		delete q;		            //�ͷŽ��ռ�
	}
}


template <class T>
int CircList<T>::Length() const		//��������ĳ���
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
CircLinkNode<T> *CircList<T>::Search(T x)  //����x
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
{  //���ر��е� i ��Ԫ�صĵ�ַ
   //��i<0 �� i>���н��������򷵻�NULL��

	if (i < 0)  return NULL;		// iֵ������
	CircLinkNode<T> *current = head;
	int k = 0;
	while (current->link != NULL && k < i)
	{
		current = current->link;	 k++;
	}
	if (k >= i)
		return current;    //���ص� i �����ĵ�ַ��NULL
	else
		return NULL;
}



template <class T>
bool CircList<T>::getData(int i, T& x)  //ȡ����iԪ��ֵ
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
void CircList<T>::setData(int i, T& x)		//���µ�iԪ��ֵ
{
	if (i <= 0)  return;

	CircLinkNode<T> *current = Locate(i);

	if (current == NULL)
		return;
	else
		current->data = x;
}


template <class T>
bool CircList<T>::Insert(int i, T& x)		//�ڵ�iԪ�غ����
{  //����Ԫ�� x �����������е� i �����֮��

	CircLinkNode<T> *current = Locate(i);

	if (current == NULL) return false;  //�޲���λ��
	CircLinkNode<T> *newNode = new  CircLinkNode<T>(x);   //�����½��
	if (newNode == NULL)
	{
		cerr << "�洢�������!" << endl;    exit(1);
	}
	newNode->link = current->link;    //����
	current->link = newNode;
	return true;
}


template <class T>
bool CircList<T>::Remove(int i, T& x)  //ɾ����i��Ԫ��
{  //ɾ�������i��Ԫ��, ͨ�����ò���x����Ԫ��ֵ

	CircLinkNode<T> *current = Locate(i - 1);

	if (current == NULL || current->link == NULL)
		return false; 	//ɾ�����ɹ� 	
	CircLinkNode<T> *del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}



template <class T>      //ǰ�彨������
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
			cerr << "�洢�������!" << endl;   exit(1);
		}
		newNode->link = head->link;  //���ڱ�ǰ��
		head->link = newNode;
		cin >> val;
	}
}




template <class T>    //��彨������
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
		cerr << "�洢�������!" << endl;   exit(1);
	}
	last->link = newNode;
	last = newNode;
}



template <class T>    //�������
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
CircList<T>& CircList<T>::operator=(CircList<T>& L) //���ظ�ֵ�����
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
