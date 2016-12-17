#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>
template<class T>
class MyTree
{
private:
	class Elem
	{
	private:
		Elem * left;			//���������� ��� �������� ��������� �� ����� �������
		Elem * right;			//���������� ��� �������� ��������� �� ������ �������
		T * node;				//���������� ��� �������� ��������� �� ������ ��������
		const int key;				//���������� ��� �������� ����� (�������������)
	public:
		Elem(int, T*);			//�����������
		~Elem();				//����������
		T& getData();			//����� ��� ������ � ������� ������ �� ������
		int getKey();			//����� ��� ������ � ������� ������ �� ������
		void setLeft(Elem *);	//����� ��� ��������� ������ ���� � ������ (������������ ��������)
		void setRight(Elem *);	//����� ��� ��������� ������� ���� � ������ (���.��������)
		Elem* getLeft();		//����� ��� ��������� ������ ���� ������
		Elem* getRight();		//����� ��� ��������� ������� ���� ������
};
private:
	int count;					//���������� ��� �������� ���������� ���������
	Elem * rootPtr;				//���������� ��� �������� ��������� �� ������ ������
	
	void clearTree(Elem *);		//��������� ����������� ������� ������� ������
	Elem * remove(Elem *, int key, Elem *(& ret));	//��������� ������� �������� �������� �� �����
	int getMaxLevel(Elem *);	//������� ���������� ������������ �������� ������
	void showLevel(Elem *, int, int, int);		//������� ������� �� ����� ������� ������
	void printEmpty(int, int, int);		//�������� ������ ���� ��� ����
public:
	MyTree();					//����������� �� ���������
	~MyTree();					//���������� (� ��� ���������� ������� ������� ������)
	void insert(int key,T *);	//����� ��� ������� � ������
	T& getByKey(int key);		//����� ��� ��������� ������� �������� �� ������ �� �����
	T& removeByKey(int key);	//�������� �� ����� ���������� ������ ������� �������� �� ����� �����
	int getCount();				//�������� �������� ���������� count
	void showKey();				//����� �� ����� ������ � ���� ������
	void showMaxLevel();		//����� �� ����� �������� ������������� �������� �������(level)
};


///////////////////////////////////////////////////////////
//����������� (��������)
template<class T>
MyTree<T>::Elem::Elem(int k, T * t):key(k), node(t), left(NULL), right(NULL)
{
}

//���������� (��������)
template<class T>
MyTree<T>::Elem::~Elem()
{
	//key = 0;
	node = NULL;
	left = NULL;
	right = NULL;
}

//����� ��� ��������� �����������
template<class T>
T & MyTree<T>::Elem::getData()
{
	return *(node);
}

template<class T>
int MyTree<T>::Elem::getKey()
{
	return key;
}

template<class T>
void MyTree<T>::Elem::setLeft(Elem *l)
{
	left = l;
}

template<class T>
void MyTree<T>::Elem::setRight(Elem *r)
{
	right = r;
}

template<class T>
typename MyTree<T>::Elem * MyTree<T>::Elem::getLeft()
{
	return left;
}

template<class T>
typename MyTree<T>::Elem * MyTree<T>::Elem::getRight()
{
	return right;
}

template<class T>
void MyTree<T>::clearTree(typename MyTree<T>::Elem * currentRoot)
{
	//����� �����������
	MyTree<T>::Elem * start = currentRoot;	//������� ��������� �� ������� ���������
	if (start->getLeft() != NULL)				//���� ���������� ����� ���������
	{
		clearTree(start->getLeft());		//������� ���
	}
	if (start->getRight() != NULL)			//���� ���������� ������ ���������
	{
		clearTree(start->getRight());		//������� ���
	}
	
	delete start;							//������� ������� �������
	count--;
}

template<class T>
typename MyTree<T>::Elem * MyTree<T>::remove(typename MyTree<T>::Elem * root, int key, typename MyTree<T>::Elem * (& ret))
{
	if (root == NULL)		//���� ������ ������
		return NULL;
	else
	{
		//��������� 3 ������
		//���� ���������� ���� ������ ��� � �������� ���� ���������� ������� � ������ �����
		if (key > root->getKey())				
		{
			root->setRight(remove(root->getRight(),key, ret));	//������������� ������ ����� (� �����) ��������� ������ ���� �� ������� ������ ��� ������ ���������
		}
		//���� ���������� ���� ������ ��� � �������� ���� ���������� ������� � ����� �����
		if (key < root->getKey())
		{
			root->setLeft(remove(root->getLeft(),key, ret));	//������������� ������ ����� (� �����) ��������� ������ ���� �� ������� ������ ��� ������ ���������
		}
		//���� ����� ����������� ��������
		if (key == root->getKey())
		{
			//���� � ������� ��� ��������...
			if (root->getLeft() == NULL&&root->getRight() == NULL)
			{
				ret=root;	//�������� ���������� ��������� ����� ������� ����� �� �������� �� ���������
				count--;	//��������� �������
				if (root == rootPtr)		//��������� �� ������ ����� ��������� ������ (��������� �������)
				{
					rootPtr = NULL;	//������������� ��������� ��������� �����
				}
				//rootPtr = NULL;
				return NULL;
			}
			//���� � �������� ���� ������� (�����)
			if (root->getLeft() != NULL&&root->getRight() == NULL)
			{
				Elem * tmp = root->getLeft();	//������� ��������� ���������� ��� �������� ��������� �� ����� ����
				if (root == rootPtr)		//��������� �� ������ ����� ��������� ������ (��������� �������)
				{
					rootPtr = root->getLeft();	//������������� ��������� �� ������ ������ �� ����� �������
				}
				count--;					//��������� ������� ���������� �����
				ret=root;					//�������� ���������� ��������� ����� ������� ����� �� �������� �� ���������
				return tmp;					//���������� ����� ����
			}
			//���� � �������� �������� ���� ������� (������)
			if (root->getLeft() == NULL&&root->getRight() != NULL)
			{
				Elem * tmp = root->getRight();	//������� ��������� ���������� ��� �������� ��������� �� ������ ����
				if (root == rootPtr)			//��������� �� ������ ����� ��������� ������ (��������� �������)
				{
					rootPtr = root->getRight();	//������������� ��������� �� ������ ������ �� ������ �������
				}
				count--;					//��������� ������� ���������� �����
				ret=root;					//�������� ���������� ��������� ����� ������� ����� �� �������� �� ���������
				return tmp;					//���������� ����� ����
			}

			//���� � �������� �������� ���� ��� �������
			if (root->getLeft() != NULL&&root->getRight() != NULL)
			{
				//�������� �� ����� ����� � �������
				Elem * tmp1 = root->getRight();	//������� ���������� ��� �������� ��������� �� ������
				if (tmp1->getLeft() != NULL)	//��� ����� ���� ����������
				{
					Elem * tmp2 = tmp1->getLeft();	//������������� ��������� tmp2 �� ����� ����� ����
					while (tmp2->getLeft() != NULL)	//���� ����� ����� ������� ���������� �������� �� ����� ���� �� ����� ����� (����� �����)
					{
						tmp1 = tmp2;				//���������� ���������� �� �������
						tmp2 = tmp2->getLeft();		//������� ������������ �� ��������� �����
					}
					if (tmp2->getRight() != NULL)	//����� ����� ���� � ����� ������ ������ �������� ���� ������ �������
					{
						tmp1->setLeft(tmp2->getRight());	//������������� ���� ������ ������� ��� ����� � �����������
					}
					else
					{
						tmp1->setLeft(NULL);			//����� ������ ������� ������
					}
					tmp2->setLeft(root->getLeft());		//�������� � ������������ ��������� � ��������������� �������� ����������
					tmp2->setRight(root->getRight());
					if (root == rootPtr)				//���� ������� ��������� �������
					{
						ret = rootPtr;					//�������� ���������� ��������� ����� ������� ����� �� �������� �� ��������� (�� ���� �� ������ ������� �� �������)
						rootPtr = tmp2;					//������������� ����� ������ ��������� �������� (����� ����� � �������)
					}
					ret = root;							//������������� ��������� �� ��������� �������
					count--;							//��������� ������� ���������� �����
					return tmp2;						//���������� ��������� ����
				}
				else
				{
					//���� ������ ���� ���
					tmp1->setLeft(root->getLeft());		//�������� � ������������ ��������� � ������� ������� � ��� ������� �������	
					if (root == rootPtr)				//���� ������� ������
					{
						ret = rootPtr;					//�������� ���������� ��������� ����� ������� ����� �� �������� �� ��������� (�� ���� �� ������ ������� �� �������)
						rootPtr = tmp1;					//������������� ����� ������ ��������� �������� (�� ������)
					}
					ret = root;							//������������� ��������� �� ��������� �������
					count--;							//��������� ������� ���������� �����
					return tmp1;						//���������� ��������� ����
				}
			}	
		}
		return root;
	}
}

template<class T>
int MyTree<T>::getMaxLevel(Elem * root)
{
	int level = 1;
	int maxLeft = 0;	//������� ���������� ��� �������� �������� ������� � ����� ���������
	int maxRight = 0;	//������� ���������� ��� �������� �������� ������� � ������ ���������
	int max;			//���������� ��� �������� ������������� �� ���� ������
	if (root->getLeft() != NULL)				//���� ����� ��������� ����������
	{
		maxLeft = getMaxLevel(root->getLeft());	//������� ������� ������ ���������
	}
	if (root->getRight() != NULL)					//���� ������ ��������� ����������
	{
		maxRight = getMaxLevel(root->getRight());	//������� ������� ������� ���������
	}
	max = maxLeft > maxRight ? maxLeft : maxRight;	//���������� ������������ �� ����
	return level+max;								//���������� 1 + ���������� ������� (�� ����� � ������) 
}

template<class T>
void MyTree<T>::showLevel(Elem * root,int maxLevel, int curLvl, int showLvl)
{
	if ((curLvl + 1) <= showLvl)	//���� ������� ������� ����������� �� 1 ������ ��� ������ ��� ������������
	{
		if (root->getLeft() != NULL)			//��� ���� ���� ����� ��������� ���������� �� ������� ���
		{
			showLevel(root->getLeft(), maxLevel, curLvl + 1, showLvl);	
		}
		else
		{
			int difference = showLvl - curLvl;	//������� ���������� ��� �������� ������� ����� ������� � ������������ ��������
			int x = pow(2, difference-1);		//��������� ������� ������ ����� ���������� ����������
			printEmpty(x,maxLevel, showLvl);	//�������� ������ ����
		}
		if (root->getRight() != NULL)			//��� ���� ��� ���� ������ ���������� �� ������� ���
		{
			showLevel(root->getRight(), maxLevel, curLvl + 1, showLvl);
		}
		else
		{
			int difference = showLvl - curLvl;	//������� ���������� ��� �������� ������� ����� ������� � ������������ ��������
			int x = pow(2, difference - 1);		//��������� ������� ������ ����� ���������� ����������
			printEmpty(x, maxLevel, showLvl);	//�������� ������ ����
		}
	}
	if (curLvl == showLvl)						//���� ������� ������� � ��������� ��������� (�� ���� �� �� ������ ������)
	{
		if (showLvl == maxLevel)				//������� ��� ������ ������ ������� ������
		{
			std::cout <<std::setw(2)<< root->getKey();	//�������� ���� �������������� ������� ��� ���� ���� �� ���� ������
			std::cout << "  ";					//�������� �������������� ������ �� ���� ��������
		}
		else
			//���� �������� �� ����� ������ �������
		{
			int widtdSpace = pow(2, (maxLevel - showLvl+1))-2;	//��������� ������ ������� ���� �� ����
			
			std::cout << std::setw(widtdSpace) << "" << std::setw(2) << root->getKey()	//�������� ������ ����, �������� �������� key � ����
				<< std::setw(widtdSpace) << "";											//�������� ����� ����� ������ ����
			std::cout << "  ";															//�������� �������������� ������
		}
	}
}

template<class T>
void MyTree<T>::printEmpty(int count, int maxLvl, int showLvl)
{
	if (showLvl == maxLvl)					//���� �������� ����� ������ �������
	{
		for (int i = 0; i < count; i++)		//������ ������� ��� ������� ������� � ���������� �������
		{
			std::cout<<std::setw(2) << "";	//��� ��� ������ ���� ��������� ������ ��������������� ��������� �������� ����� ��� ������ ����
			std::cout << "  ";				//�������� "������"
		}
	}
	else
	{
		for (int i = 0; i < count; i++)		//������ ������� ��� ������� ������� � ���������� �������
		{
			int widthSpace = pow(2, (maxLvl - showLvl + 1)) - 2;	//��������� ������ ������� ����
			std::cout << std::setw(widthSpace)<<""<<std::setw(2) << ""	//�������� ������ ���� �������� ����� ��� ������ ��������
				<<std::setw(widthSpace)<<"";						//�������� ������ ���� �����
			std::cout << "  ";										//�������� "������"
		}
	}
}

template<class T>
MyTree<T>::MyTree(): rootPtr(NULL), count(0)
{
}

template<class T>
MyTree<T>::~MyTree()
{
	if (count > 0)
	{
		clearTree(rootPtr);
		rootPtr = NULL;
		count = 0;
	}
}

template<class T>
void MyTree<T>::insert(int key, T * t)
{
	//�������� ������� �������� �����
	Elem * tmp = new Elem(key, t);
	
	if (count == 0)	//���� ������ ������
	{
		
		rootPtr = tmp;
		count++;
	}
	else
	{
		Elem * start = rootPtr;
		while (true)
		{
			if (key > start->getKey())
			{
				if (start->getRight() != NULL)
				{
					start = start->getRight();
				}
				else
				{
					start->setRight(tmp);
					count++;
					break;
				}
			}
			else if(key < start->getKey())
			{
				if (start->getLeft() != NULL)
				{
					start = start->getLeft();
				}
				else
				{
					start->setLeft(tmp);
					count++;
					break;
				}
			}
		}
	}
}

template<class T>
T & MyTree<T>::getByKey(int key)
{
	Elem *start = rootPtr;					//�������������� ��������� �������� ��������� �� ���������
	while (true)							
	{
		int tmpKey = start->getKey();		//������� ���������� ��� �������� �������� �����

		if (key == tmpKey)					//���� ���������� ���� ������ 
		{
			return	start->getData();		//���������� ����������
		}
		else if (key > tmpKey)				//����� ���� ���������� ���� ������
		{
			if (start->getRight() != NULL)	//���� ���������� ������ �����
				start = start->getRight();	//������������ � ������ �����
			else
				break;						//���� �� ���������� ������ ����� �� �������� ����
		}
		else //���� ������������ ���� ������ ��� ��� ������� (key < tmpKey)
		{
			if (start->getLeft() != NULL)	//���� ���������� ����� �����
				start = start->getLeft();	//������������ � ����� �����
			else
				break;						//���� ����� ����� �� ���������� ��������� ����
		}

	}
	return NULL;							//�� ���� ������� ����� �� ����� ������������ �������� ���������� NULL
}

template<class T>
T & MyTree<T>::removeByKey(int key)
{
	Elem * tmp;							//������� ���������� ��� �������� �������� ���������� ����
	this->remove(rootPtr, key, tmp);	//�������� ����������� ������� �������� �� �����
	T* ret;								//������� ���������� ��� �������� ������������� ��������
	ret = &(tmp->getData());			//������������� ������������ ��������
	delete tmp;							//����������� ������ �� ��� ���������� ����
	return *ret;						//���������� ���������
}

template<class T>
inline int MyTree<T>::getCount()
{
	return count;
}

template<class T>
void MyTree<T>::showKey()
{
	if (count == 0)	//���� ������ ������ ��������� ���������� �������
	{
		std::cout<<"Tree is EMPTY!\n";
	}
	else
	{
		int maxLevel = getMaxLevel(rootPtr);
		for (int i = 1; i <= maxLevel; i++)
		{
			//int alreadyPrint = 0;
			showLevel(rootPtr, maxLevel, 1, i);
			std::cout << "\n";
		}
	}
}

template<class T>
void MyTree<T>::showMaxLevel()
{
	int level = getMaxLevel(rootPtr);
	std::cout << "Max level = " << level << std::endl;
}
