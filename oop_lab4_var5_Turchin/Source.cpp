#include "Header.h"
#include <Windows.h>
void main()
{
	MyTree<char> *tmp  = new MyTree<char>();
	char * string10 = "Str10";
	char * string27 = "Str27";
	char * string20 = "Str20";
	char * string15 = "Str15";
	char * string29 = "Str29";
	char * string18 = "Str18";
	char * string31 = "Str31";
	char * string17 = "Str17";
	char * string19 = "Str19";
	char * string8 = "Str8";
	char * string5 = "Str5";
	char * string3 = "Str3";
	char * string1 = "Str1";

	tmp->insert(10, string10);
	tmp->insert(27, string27);
	tmp->insert(20, string20);
	tmp->insert(29, string29);
	tmp->insert(15, string15);
	tmp->insert(18, string18);
	tmp->insert(31, string31);
	tmp->insert(8, string8);
	tmp->insert(3, string3);
	tmp->insert(5, string5);
	tmp->insert(1, string1);
	std::cout <<"cunt="<< tmp->getCount() << std::endl;
	tmp->showKey();
	tmp->showMaxLevel();
	std::cout << "removeByKey(10)" << &(tmp->removeByKey(10)) << std::endl;
	tmp->showKey();
	system("pause");
}