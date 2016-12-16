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
		Elem * left;			//Переменная для хранения указателя на левый элемент
		Elem * right;			//Переменная для хранения указателя на правый элемент
		T * node;				//Переменная для хранения указателя на объект хранения
		int key;				//Переменная для хранения ключа (целочисленный)
	public:
		Elem(int, T*);			//конструктор
		Elem(const Elem &);		//Конструктор копирования
		~Elem();				//Деструктор
		T& getData();			//Метод для работы с данными класса по чтению
		int getKey();			//Метод для работы с данными класса по чтению
		void setLeft(Elem *);	//Метод для установки левого узла в дереве (относительно текущего)
		void setRight(Elem *);	//Метод для установки правого узла в дереве (отн.текущего)
		Elem* getLeft();		//Метод для получения левого узла дерева
		Elem* getRight();		//Метод для получения правого узла дерева
		
	};
private:
	
	int count;					//Переменная для подсчета количества элементов

	void clearTree(Elem *);		//Служебная функция очистки дерева
	Elem * remove(Elem *, int key, Elem *(& ret));	//служебная функция удаления элемента по ключу

	Elem * rootPtr;				//Переменная для хранения указателя на корень дерева
	int getMaxLevel(Elem *);	//функция возвращает максимальное значение уровня
	void showLevel(Elem *, int, int, int);		//Функция выводит на экран уровень дерева
	void printEmpty(int, int, int);		//печатает пустой слот под узел
public:
	MyTree();					//Конструктор по умолчанию
	MyTree(MyTree *);			//Конструктор копирования
	~MyTree();					//Деструктор
	void insert(int key,T *);	//Метод для вставки в дерево
	T& getByKey(int key);		//Метод для получения объекта хранения из дерева по ключу
	T& removeByKey(int key);	//Удаление по ключу возвращает объект который хранился по этому ключу
	int getCount();				//Получить значение переменной count
	void showKey();				//Вывод на экран ключей в виде дерева
	void showMaxLevel();		//Вывод на экран значения максимального значения глубины(level)
};


///////////////////////////////////////////////////////////
//Конструктор (элемента)
template<class T>
MyTree<T>::Elem::Elem(int k, T * t)//:key(k), node(t), left(NULL), right(NULL)
{
	key = k;
	node = t;
	left = NULL;
	right = NULL;
}

//конструктор копирования (элемента)
template<class T>
MyTree<T>::Elem::Elem(const typename MyTree<T>::Elem &t)
{
	key = t.key;
	node = t.node;
	left = t.left;
	right = t.right;
}

//деструктор (элемента)
template<class T>
MyTree<T>::Elem::~Elem()
{
	key = 0;
	node = NULL;
	left = NULL;
	right = NULL;
}

//Метод для получения содержимого
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
	MyTree<T>::Elem * start = currentRoot;
	if (start->getLeft != NULL)
	{
		clearTree(start->getLeft());
	}
	if (start->getRight() != NULL)
	{
		clearTree(start->getRight());
	}
	delete start;
}

template<class T>
typename MyTree<T>::Elem * MyTree<T>::remove(typename MyTree<T>::Elem * root, int key, typename MyTree<T>::Elem * (& ret))
{
	if (root == NULL)		//если дерево пустое
		return NULL;
	else
	{
		//проверяем 3 случая
		//если переданный ключ больше чем у текущего узла необходимо перейти в правую ветку
		if (key > root->getKey())				
		{
			root->setRight(remove(root->getRight(),key, ret));	//устанавливаем
		}
		if (key < root->getKey())
		{
			root->setLeft(remove(root->getLeft(),key, ret));
		}
		if (key == root->getKey())
		{
			//если у текщего нет потомков...
			if (root->getLeft() == NULL&&root->getRight() == NULL)
			{
				ret=root;
				count--;
				if (root == rootPtr)
				{
					rootPtr = root->getLeft();
				}
				//rootPtr = NULL;
				return NULL;
			}
			//если у текущего один потомок (левый)
			if (root->getLeft() != NULL&&root->getRight() == NULL)
			{
				Elem * tmp = root->getLeft();
				if (root == rootPtr)
				{
					rootPtr = root->getLeft();
				}
				count--;
				ret=root;
				return tmp;
			}
			//если у текущего элемента один потомок (правый)
			if (root->getLeft() == NULL&&root->getRight() != NULL)
			{
				Elem * tmp = root->getRight();
				if (root == rootPtr)
				{
					rootPtr = root->getRight();
				}
				count--;
				ret=root;
				return tmp;
			}

			//если у текущего элемента есть два потомка
			if (root->getLeft() != NULL&&root->getRight() != NULL)
			{
				Elem * tmp1 = root->getRight();	//заводим переменную для хранения указателя на предыдущий узел
				if (tmp1->getLeft() != NULL)
				{
					Elem * tmp2 = tmp1->getLeft();	//устанавливаем указатель tmp2 на самый левый узел
					while (tmp2->getLeft() != NULL)
					{
						tmp1 = tmp2;
						tmp2 = tmp2->getLeft();		
					}
					if (tmp2->getRight() != NULL)
					{
						tmp1->setLeft(tmp2->getRight());
					}
					else
					{
						tmp1->setLeft(NULL);
					}
					tmp2->setLeft(root->getLeft());
					tmp2->setRight(root->getRight());
					if (root == rootPtr)
					{
						ret = rootPtr;
						rootPtr = tmp2;
					}
					ret = root;
					count--;
					return tmp2;
				}
				else
				{
					tmp1->setLeft(root->getLeft());
					if (root == rootPtr)
					{
						ret = rootPtr;
						rootPtr = tmp1;
					}
					
					count--;
					return tmp1;
				}
			}
				
		}
		return root;
	}
	//Не уверен
}

template<class T>
int MyTree<T>::getMaxLevel(Elem * root)
{
	int level = 1;
	int maxLeft = 0;
	int maxRight = 0;
	int max;
	if (root->getLeft() != NULL)
	{
		maxLeft = getMaxLevel(root->getLeft());
	}
	if (root->getRight() != NULL)
	{
		maxRight = getMaxLevel(root->getRight());
	}
	max = maxLeft > maxRight ? maxLeft : maxRight;
	return level+max;
}

template<class T>
void MyTree<T>::showLevel(Elem * root,int maxLevel, int curLvl, int showLvl)
{
	if ((curLvl + 1) <= showLvl)
	{
		if (root->getLeft() != NULL)
		{
			showLevel(root->getLeft(), maxLevel, curLvl + 1, showLvl);
		}
		else
		{
			int difference = showLvl - curLvl;
			int x = pow(2, difference-1);
			printEmpty(x,maxLevel, showLvl);
		}
		if (root->getRight() != NULL)
		{
			showLevel(root->getRight(), maxLevel, curLvl + 1, showLvl);
		}
		else
		{
			int difference = showLvl - curLvl;
			int x = pow(2, difference - 1);
			printEmpty(x, maxLevel, showLvl);
		}
	}
	if (curLvl == showLvl)
	{
		if (showLvl == maxLevel)
		{
			std::cout <<std::setw(2)<< root->getKey();
			std::cout << "  ";
		}
		else
		{
			int widtdSpace = pow(2, (maxLevel - showLvl+1))-2;
			
			std::cout << std::setw(widtdSpace) << "" << std::setw(2) << root->getKey()
				<< std::setw(widtdSpace) << "";
			std::cout << "  ";
		}
		/*std::cout.setw(2);
		std::cout << root->key << "  ";*/
	}
}

template<class T>
void MyTree<T>::printEmpty(int count, int maxLvl, int showLvl)
{
	if (showLvl == maxLvl)
	{
		for (int i = 0; i < count; i++)
		{
			std::cout<<std::setw(2) << "";
			std::cout << "  ";
		}
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			int widthSpace = pow(2, (maxLvl - showLvl + 1)) - 2;
			std::cout << std::setw(widthSpace)<<""<<std::setw(2) << ""
				<<std::setw(widthSpace)<<"";
			std::cout << "  ";
		}
	}
}

template<class T>
MyTree<T>::MyTree(): rootPtr(NULL), count(0)
{
}

template<class T>
MyTree<T>::MyTree(MyTree *)
{
	//MyTree<T>::Elem *tmp = new MyTree<T>::Elem();
	//не реализовано
}

template<class T>
MyTree<T>::~MyTree()
{
}

template<class T>
void MyTree<T>::insert(int key, T * t)
{
	//вставить условие проверки ключа
	Elem * tmp = new Elem(key, t);
	
	if (count == 0)	//если дерево пустое
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
	typename MyTree<T>::Elem *start = rootPtr;
	while (true)
	{
		int tmpKey = start->getKey();

		if (key == tmpKey)
		{
			return	start->getData();
		}
		else if (key > tmpKey)
		{
			if (start->getRight() != NULL)
				start = start->getRight();
			else
				break;
		}
		else //(key < tmpKey)
		{
			if (start->getLeft() != NULL)
				start = start->getLeft();
			else
				break;
		}

	}
	//return NULL;
}

template<class T>
T & MyTree<T>::removeByKey(int key)
{
	Elem * tmp=NULL;
	this->remove(rootPtr, key, tmp);
	return tmp->getData();
}

template<class T>
inline int MyTree<T>::getCount()
{
	return count;
}

template<class T>
void MyTree<T>::showKey()
{
	int maxLevel = getMaxLevel(rootPtr);
	for (int i = 1; i <= maxLevel; i++)
	{
		//int alreadyPrint = 0;
		showLevel(rootPtr, maxLevel, 1, i);
		std::cout << "\n";
	}
}

template<class T>
void MyTree<T>::showMaxLevel()
{
	int level = getMaxLevel(rootPtr);
	std::cout << "Max level = " << level << std::endl;
}
