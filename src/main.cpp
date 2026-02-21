#include <iostream>
#include <string>
#include <sstream>
#include "AVLtree.h"

using namespace std;

int main(){
	AVLTree tree;
	std::string numCommands;
	std::getline(std::cin, numCommands);
	if (std::stoi(numCommands) <= 1001 || std::stoi(numCommands) >= 1) {
		for (int i = 0; i < std::stoi(numCommands); i++) {
			string line;
			std::getline(std::cin, line);
			//Put line in a string stream to allow for parsing
			istringstream is(line);
			//Extract command
			std::string command;
			is >> command;
			//Check if command is valid
			if (command.size() < 6 || command.size() > 1000 ) {
				std::cout << "unsuccessful" << std::endl;
				continue;
			}
			if (command == "insert"){
				//Extract name
				std::string name;
				std::getline(is, name, '"');
				std::getline(is, name, '"');
				//Extract ufid
				std::string ufid;
				is >> ufid;
				tree.insert(name,ufid);
			}
			else if (command == "remove") {
				//Extract ufid
				std::string ufid;
				is >> ufid;
				tree.removeId(ufid);
			}
			else if (command == "search") {
				//Extract ufid
				is >> std::ws;
				if (is.peek() == '"') {
					//Search name
					//Extract name
					std::string name;
					std::getline(is, name, '"');
					std::getline(is, name, '"');
					tree.searchName(name);
				}
				else {
					//search ufid
					std::string ufid;
					is >> ufid;
					tree.searchId(ufid);
				}
			}
			else if (command == "printInorder") {
				tree.inOrder();
			}
			else if (command == "printPreorder") {
				tree.preOrder();
			}
			else if (command == "printPostorder") {
				tree.postOrder();
			}
			else if (command == "printLevelCount") {
				tree.levelCount();
			}
			else if (command == "removeInorder") {
				std::string n;
				is >> n;
				bool n_valid = true;
				for (char c: n) {
					if (!isdigit(c)) {
						std::cout << "unsuccessful" << std::endl;
						n_valid = false;
						break;
					}
				}
				if (n_valid) {
					tree.removeInorderN(std::stoi(n));
				}
			}
			else {
				std::cout << "unsuccessful" << std::endl;
			}
		}
	}
	return 0;
}
