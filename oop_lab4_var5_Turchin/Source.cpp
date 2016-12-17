#include "MyTree.h"
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

	std::cout << "Insert \"Str10\" with key = 10\n";
	tmp->insert(10, string10);
	std::cout << "Insert \"Str27\" with key = 27\n";
	tmp->insert(27, string27);
	std::cout << "Insert \"Str20\" with key = 20\n";
	tmp->insert(20, string20);
	std::cout << "Insert \"Str29\" with key = 29\n";
	tmp->insert(29, string29);
	std::cout << "Insert \"Str15\" with key = 15\n";
	tmp->insert(15, string15);
	std::cout << "Insert \"Str18\" with key = 18\n";
	tmp->insert(18, string18);
	std::cout << "Insert \"Str31\" with key = 31\n";
	tmp->insert(31, string31);
	std::cout << "Insert \"Str8\" with key = 8\n";
	tmp->insert(8, string8);
	std::cout << "Insert \"Str3\" with key = 3\n";
	tmp->insert(3, string3);
	std::cout << "Insert \"Str5\" with key = 5\n";
	tmp->insert(5, string5);
	std::cout << "Insert \"Str1\" with key = 1\n";
	tmp->insert(1, string1);
	
	tmp->showMaxLevel();
	tmp->showKey();
	
	std::cout << "removeByKey(10) and show data. Result:\n" << &(tmp->removeByKey(10)) << std::endl;
	tmp->showMaxLevel();
	tmp->showKey();
	std::cout << "removeByKey(27) and show data. Result:\n" << &(tmp->removeByKey(27)) << std::endl;
	tmp->showKey();

	std::cout << "removeByKey(18) and show data. Result:\n" << &(tmp->removeByKey(18)) << std::endl;
	tmp->showKey();
	std::cout << "removeByKey(15) and show data. Result:\n" << &(tmp->removeByKey(15)) << std::endl;
	std::cout << "removeByKey(31) and show data. Result:\n" << &(tmp->removeByKey(31)) << std::endl;
	std::cout << "removeByKey(1) and show data. Result:\n" << &(tmp->removeByKey(1)) << std::endl;
	std::cout << "removeByKey(8) and show data. Result:\n" << &(tmp->removeByKey(8)) << std::endl;
	std::cout << "removeByKey(29) and show data. Result:\n" << &(tmp->removeByKey(29)) << std::endl;
	std::cout << "removeByKey(3) and show data. Result:\n" << &(tmp->removeByKey(3)) << std::endl;
	std::cout << "Insert \"Str31\" with key = 31\n";
	tmp->insert(31, string31);
	tmp->showKey();
	std::cout << "removeByKey(20) and show data. Result:\n" << &(tmp->removeByKey(20)) << std::endl;
	tmp->showKey();
	std::cout << "removeByKey(31) and show data. Result:\n" << &(tmp->removeByKey(31)) << std::endl;
	tmp->showKey();
	system("pause");
	std::cout << "removeByKey(5) and show data. Result:\n" << &(tmp->removeByKey(5)) << std::endl;
	tmp->showKey();

	delete tmp;
	system("pause");
}