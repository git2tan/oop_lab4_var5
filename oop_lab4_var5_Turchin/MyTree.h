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
		const int key;				//Переменная для хранения ключа (целочисленный)
	public:
		Elem(int, T*);			//конструктор
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
	Elem * rootPtr;				//Переменная для хранения указателя на корень дерева
	
	void clearTree(Elem *);		//Служебная рекурсивная функция очистки дерева
	Elem * remove(Elem *, int key, Elem *(& ret));	//служебная функция удаления элемента по ключу
	int getMaxLevel(Elem *);	//функция возвращает максимальное значение уровня
	void showLevel(Elem *, int, int, int);		//Функция выводит на экран уровень дерева
	void printEmpty(int, int, int);		//печатает пустой слот под узел
public:
	MyTree();					//Конструктор по умолчанию
	~MyTree();					//Деструктор (в нем вызывается функция очистки дерева)
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
MyTree<T>::Elem::Elem(int k, T * t):key(k), node(t), left(NULL), right(NULL)
{
}

//деструктор (элемента)
template<class T>
MyTree<T>::Elem::~Elem()
{
	//key = 0;
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
	//метод рекурсивный
	MyTree<T>::Elem * start = currentRoot;	//заводим указатель на текущее поддерево
	if (start->getLeft() != NULL)				//если существует левое поддерево
	{
		clearTree(start->getLeft());		//очищаем его
	}
	if (start->getRight() != NULL)			//если существует правое поддерево
	{
		clearTree(start->getRight());		//очищаем его
	}
	
	delete start;							//удаляем текущий элемент
	count--;
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
			root->setRight(remove(root->getRight(),key, ret));	//устанавливаем правым узлом (у текущ) результат работы этой же функции только для правго поддерева
		}
		//если переданный ключ меньше чем у текущего узла необходимо перейти в левую ветку
		if (key < root->getKey())
		{
			root->setLeft(remove(root->getLeft(),key, ret));	//устанавливаем правым узлом (у текущ) результат работы этой же функции только для правго поддерева
		}
		//если нашли необходимое значение
		if (key == root->getKey())
		{
			//если у текщего нет потомков...
			if (root->getLeft() == NULL&&root->getRight() == NULL)
			{
				ret=root;	//изменяем переданный указатель таким образом чтобы он указывал на найденный
				count--;	//уменьшаем счетчик
				if (root == rootPtr)		//проверяем на случай когда удаляется корень (заглавный элемент)
				{
					rootPtr = NULL;	//устанавливаем заглавным элементом левый
				}
				//rootPtr = NULL;
				return NULL;
			}
			//если у текущего один потомок (левый)
			if (root->getLeft() != NULL&&root->getRight() == NULL)
			{
				Elem * tmp = root->getLeft();	//заводим временную переменную для хранения указателя на левый узел
				if (root == rootPtr)		//проверяем на случай когда удаляется корень (заглавный элемент)
				{
					rootPtr = root->getLeft();	//устанавливаем указатель на корень дерева на левый элемент
				}
				count--;					//уменьшаем счетчик количества узлов
				ret=root;					//изменяем переданный указатель таким образом чтобы он указывал на найденный
				return tmp;					//возвращаем левый узел
			}
			//если у текущего элемента один потомок (правый)
			if (root->getLeft() == NULL&&root->getRight() != NULL)
			{
				Elem * tmp = root->getRight();	//заводим временную переменную для хранения указателя на правый узел
				if (root == rootPtr)			//проверяем на случай когда удаляется корень (заглавный элемент)
				{
					rootPtr = root->getRight();	//устанавливаем указатель на корень дерева на правый элемент
				}
				count--;					//уменьшаем счетчик количества узлов
				ret=root;					//изменяем переданный указатель таким образом чтобы он указывал на найденный
				return tmp;					//возвращаем левый узел
			}

			//если у текущего элемента есть два потомка
			if (root->getLeft() != NULL&&root->getRight() != NULL)
			{
				//заменяем на самый левый у правого
				Elem * tmp1 = root->getRight();	//заводим переменную для хранения указателя на правый
				if (tmp1->getLeft() != NULL)	//еси левый узел существует
				{
					Elem * tmp2 = tmp1->getLeft();	//устанавливаем указатель tmp2 на самый левый узел
					while (tmp2->getLeft() != NULL)	//пока левый левый элемент существует проходим до самго низа по левой ветке (самый левый)
					{
						tmp1 = tmp2;				//перемещаем предыдущий на текущий
						tmp2 = tmp2->getLeft();		//текущий переставляем на следующий левый
					}
					if (tmp2->getRight() != NULL)	//после этого если у этого самого левого элемента есть правый элемент
					{
						tmp1->setLeft(tmp2->getRight());	//устанавливаем этот правый элемент как левый у предыдущего
					}
					else
					{
						tmp1->setLeft(NULL);			//иначе просто убираем ссылку
					}
					tmp2->setLeft(root->getLeft());		//приводим в соответствие указатели у переставляемого элемента удаляемому
					tmp2->setRight(root->getRight());
					if (root == rootPtr)				//если удалили заглавный элемент
					{
						ret = rootPtr;					//изменяем переданный указатель таким образом чтобы он указывал на найденный (то есть на корень который мы удаляем)
						rootPtr = tmp2;					//устанавливаем новым корнем найденное значение (самое левое у правого)
					}
					ret = root;							//устанавливаем указатель на удаляемый элемент
					count--;							//уменьшаем счетчик количества узлов
					return tmp2;						//возвращаем найденный узел
				}
				else
				{
					//если левого узла нет
					tmp1->setLeft(root->getLeft());		//приводим в соответствие указатели у правого элемнта с тем который удаляем	
					if (root == rootPtr)				//если удаляем корень
					{
						ret = rootPtr;					//изменяем переданный указатель таким образом чтобы он указывал на найденный (то есть на корень который мы удаляем)
						rootPtr = tmp1;					//устанавливаем новым корнем найденное значение (на правый)
					}
					ret = root;							//устанавливаем указатель на удаляемый элемент
					count--;							//уменьшаем счетчик количества узлов
					return tmp1;						//возвращаем найденный узел
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
	int maxLeft = 0;	//заводим переменную для хранения значения глубины в левом поддереве
	int maxRight = 0;	//заводим переменную для хранения значения глубины в правом поддереве
	int max;			//переменная для хранения максимального из двух глубин
	if (root->getLeft() != NULL)				//если левое поддерево существует
	{
		maxLeft = getMaxLevel(root->getLeft());	//считаем глубину левого поддерева
	}
	if (root->getRight() != NULL)					//если правое поддерево существует
	{
		maxRight = getMaxLevel(root->getRight());	//считаем глубину правого поддерева
	}
	max = maxLeft > maxRight ? maxLeft : maxRight;	//записываем максимальное из двух
	return level+max;								//возвращаем 1 + наибольшая глубина (из левой и правой) 
}

template<class T>
void MyTree<T>::showLevel(Elem * root,int maxLevel, int curLvl, int showLvl)
{
	if ((curLvl + 1) <= showLvl)	//если текущий уровень увеличенный на 1 меньше или равный чем показываемый
	{
		if (root->getLeft() != NULL)			//при этом если левое поддерево существует то выводим его
		{
			showLevel(root->getLeft(), maxLevel, curLvl + 1, showLvl);	
		}
		else
		{
			int difference = showLvl - curLvl;	//заводим переменную для хранения разницы между текущим и показываемым уровнями
			int x = pow(2, difference-1);		//вычисляем сколько пустых узлов необходимо напечатать
			printEmpty(x,maxLevel, showLvl);	//печатаем пустые узлы
		}
		if (root->getRight() != NULL)			//или если при этом правое существует то выводим его
		{
			showLevel(root->getRight(), maxLevel, curLvl + 1, showLvl);
		}
		else
		{
			int difference = showLvl - curLvl;	//заводим переменную для хранения разницы между текущим и показываемым уровнями
			int x = pow(2, difference - 1);		//вычисляем сколько пустых узлов необходимо напечатать
			printEmpty(x, maxLevel, showLvl);	//печатаем пустые узлы
		}
	}
	if (curLvl == showLvl)						//если текущий уровень и выводимый совпадают (то есть мы на нужном уровне)
	{
		if (showLvl == maxLevel)				//условия для печати самого нижнего уровня
		{
			std::cout <<std::setw(2)<< root->getKey();	//печатаем узел предварительно выдилив под узел поле из двух знаков
			std::cout << "  ";					//печатаем разделительный пробел из двух пробелов
		}
		else
			//если печатаем не самый нижний уровень
		{
			int widtdSpace = pow(2, (maxLevel - showLvl+1))-2;	//вычисляем ширину пустого поля до узла
			
			std::cout << std::setw(widtdSpace) << "" << std::setw(2) << root->getKey()	//печатаем пустое поле, печатаем значение key у узла
				<< std::setw(widtdSpace) << "";											//печатаем после этого пустое поле
			std::cout << "  ";															//печатаем разделительный пробел
		}
	}
}

template<class T>
void MyTree<T>::printEmpty(int count, int maxLvl, int showLvl)
{
	if (showLvl == maxLvl)					//если печатаем самый нижний уровень
	{
		for (int i = 0; i < count; i++)		//печаем столько раз сколько указано в параметрах функции
		{
			std::cout<<std::setw(2) << "";	//так как нижнее поле разделено только разделительными пробелами выделяем место под пустой узел
			std::cout << "  ";				//печатаем "пробел"
		}
	}
	else
	{
		for (int i = 0; i < count; i++)		//печаем столько раз сколько указано в параметрах функции
		{
			int widthSpace = pow(2, (maxLvl - showLvl + 1)) - 2;	//вычисляем ширину пустого поля
			std::cout << std::setw(widthSpace)<<""<<std::setw(2) << ""	//печатаем пустое поле печатаем место под пустое значение
				<<std::setw(widthSpace)<<"";						//печатаем пустое поле после
			std::cout << "  ";										//печатаем "пробел"
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
	Elem *start = rootPtr;					//инициализируем стартовое значение указателя на поддерево
	while (true)							
	{
		int tmpKey = start->getKey();		//заводим переменную под хранение значения ключа

		if (key == tmpKey)					//если переданный ключ совпал 
		{
			return	start->getData();		//возвращаем содержимое
		}
		else if (key > tmpKey)				//иначе если переданный ключ больше
		{
			if (start->getRight() != NULL)	//если существует правая ветка
				start = start->getRight();	//перемещаемся в правую ветку
			else
				break;						//если не существует правой ветки то обрываем цикл
		}
		else //если передаваемый ключ меньше чем чем текущий (key < tmpKey)
		{
			if (start->getLeft() != NULL)	//если существует левая ветка
				start = start->getLeft();	//перемещаемся в левую ветку
			else
				break;						//если левой ветки не существует прерываем цикл
		}

	}
	return NULL;							//во всех случаях когда не нашли необходимого значения возвращаем NULL
}

template<class T>
T & MyTree<T>::removeByKey(int key)
{
	Elem * tmp;							//заводим переменную для хранения значения удаляемого поля
	this->remove(rootPtr, key, tmp);	//вызываем рекурсивную функцию удаления по ключу
	T* ret;								//заводим переменную для хранения возвращаемого значения
	ret = &(tmp->getData());			//устанавливаем возвращаемое значение
	delete tmp;							//освобождаем память из под удаленного поля
	return *ret;						//возвращаем результат
}

template<class T>
inline int MyTree<T>::getCount()
{
	return count;
}

template<class T>
void MyTree<T>::showKey()
{
	if (count == 0)	//если дерево пустое прерываем выполнение функции
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
