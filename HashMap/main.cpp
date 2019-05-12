// HashMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HashNode.h"
#include "HashMap.h"

using namespace std;

void testHashNode() {
	HashNode<int, string> test(1,"test1");
	HashNode<int, string> temp(1, "test2");
	test.setNext(temp);
	HashNode<int, string> cpy = test;
	std::vector<string> v1 = test.getAllValues();
	std::vector<string> v2 = cpy.getAllValues();

	for (auto it : v1) cout << it << " ";
	cout << endl;

	for (auto it : v2) cout << it << " ";
	cout << endl;
    std::cout << "Hello World!\n"; 
}

struct MyKeyHash {
	unsigned long operator()(const int& k) const
	{
		return k % 10;
	}
};

int main(){
	HashMap<int, string, 10, MyKeyHash> hmap;
	HashMap<int, string, 10, MyKeyHash> cpy;
	
	//hmap.put(1, "1");
	hmap.put(2, "2");
	hmap.put(12, "3");
	hmap.put(22, "4");
	//hmap.put(3, "3");
	cpy = hmap;
	string value;
	cpy.get(2, value);
	value = cpy[2];
	//cout << value;
	cout << endl;
	vector<string> r = hmap.getAllValues(2);
	for (auto it : r) cout << it << " ";
	cout << endl;
	cout << hmap.distinctKeys();
	cout << hmap;
}

