#include <iostream>
#include <string>
#include "AVLtree.h"

using namespace std;

int main(){
	AVLTree tree;
	std::string numCommands;
	//Node* one;
	std::getline(std::cin, numCommands);
	for (int i = 0; i < std::stoi(numCommands); i++) {
		tree.insert("Jackie", "00000000");
	}
	return 0;
}
