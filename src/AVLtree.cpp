#include <iostream>
#include <vector>
#include "AVLtree.h"

//Parsing Method
//Ufid Valid method
bool AVLTree::ufid_valid(std::string ufid) {
    //Check ufid is 8 digits and is ONLY digits
    int count = 0;
    for (char c: ufid) {
        if (!isdigit(c)) {
            return false;
        }
        count++;
    }
    if (count != 8) {
        return false;
    }
    return true;
}
//Name Valid Method
bool AVLTree::name_valid(std::string name) {
    for(char c: name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}
//Rotate Left helper method
//Cited from the Stepik Module 5
Node* AVLTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    //Update height
    node->height = 1 + std::max(node->left ? node->left->height : 0,
        node->right ? node->right->height : 0);
    rightChild->height = 1 + std::max(rightChild->left ? rightChild->left->height : 0,
        rightChild->right ? rightChild->right->height : 0);
    return rightChild;
}
//Rotate Right helper method
//Cited from the Stepik Module 5
Node* AVLTree::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    //Update Height
    node->height = 1 + std::max(node->left ? node->left->height : 0,
        node->right ? node->right->height : 0);
    leftChild->height = 1 + std::max(leftChild->left ? leftChild->left->height : 0,
        leftChild->right ? leftChild->right->height : 0);
    return leftChild;
}
//Traversals
//Pre Order Traversal
void AVLTree::preOrder() {
    std::vector<std::string> name;
    preOrderHelper(this->root, name);
    for (int i = 0; i < name.size(); i++) {
        std::cout << name[i];
        if (i != name.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
}
void AVLTree::preOrderHelper(Node* node, std::vector<std::string> name) {
    if (node != nullptr) {
        name.push_back(node->name);
        preOrderHelper(node->left, name);
        preOrderHelper(node->right, name);
    }
}
//In Order Traversal
void AVLTree::inOrder() {
    std::vector<std::string> name;
    inOrderHelper(this->root, name);
    for (int i = 0; i < name.size(); i++) {
        std::cout << name[i];
        if (i != name.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
}
void AVLTree::inOrderHelper(Node* node,  std::vector<std::string> name) {
    if (node != nullptr) {
        inOrderHelper(node->left, name);
        name.push_back(node->name);
        inOrderHelper(node->right, name);
    }
}
//Post Order Traversal
void AVLTree::postOrder() {
    std::vector<std::string> name;
    postOrderHelper(this->root, name);
    for (int i = 0; i < name.size(); i++) {
        std::cout << name[i];
        if (i != name.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
void AVLTree::postOrderHelper(Node* node,  std::vector<std::string> name) {
    if (node != nullptr) {
        postOrderHelper(node->left, name);
        postOrderHelper(node->right, name);
        name.push_back(node->name);
    }
}
//Level Order Traversal
void AVLTree::levelCount() {
    levelCountHelper(this->root);
}
void AVLTree::levelCountHelper(Node* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->height << std::endl;
}
//Code from Jackie Wang's video
//This will call an insert method that is private, so it is not visible to the user
void AVLTree::insert(std::string name, std::string ufid) {
    //Check if ufid is valid
    bool valid_ufid = ufid_valid(ufid);
    if (!valid_ufid) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    //Check if name is valid
    bool valid_name = name_valid(name);
    if (!valid_name) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    //Call InsertHelper from the insert method so memory is not exposed to the public
    this->root = insertHelper(this->root, name, ufid);
}
//Insert Helper method
Node* AVLTree::insertHelper(Node* node, std::string name, std::string ufid) {
    //Check where to insert the node
    if (node == nullptr) {
        std::cout << "successful" << std::endl;
        return new Node(name,ufid);
    }
    //Check if there are duplicates of ufid
    if (ufid == node->ufid) {
        std::cout << "unsuccessful" << std::endl;
        return node;
    }
    //Check whether ufid should be on the left or right
    if (ufid > node->ufid) {
        node->right = insertHelper(node->right, name, ufid);
    }
    else {
        node->left = insertHelper(node->left, name, ufid);
    }

    //Check height of node for balancing purposes
    node->height = 1 + std::max(node->left ? node->left->height : 0,
        node->right ? node->right->height : 0);

    //Find balance factor
    if (node->left != nullptr && node->right != nullptr) {
        node->balance = node->left->height - node->right->height;
    }
    else if (node->left != nullptr && node->right == nullptr) {
        node->balance = node->left->height;
    }
    else if (node->left == nullptr && node->right != nullptr) {
        node->balance = -(node->right->height);
    }

    //Do rotations based off of balance
    //If root (current node) is Left heavy
    if (node->balance > 1) {
        //If left's subtree is right heavy - Left Right rotation
        if (node->left && node->left->balance == -1) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        //If left's subtree is left heavy - Right rotation
        else {
            return rotateRight(node);
        }

    }
    //If root (current node) is right heavy
    else if (node->balance < -1) {
        //If right's subtree is left heavy - Right Left Rotation
        if (node->right && node->right->balance == 1) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        //right's subtree is right heavy - Left Rotation
        else {
            return rotateLeft(node);
        }
    }
    //return the current node if no rotations were to happen
    return node;
}

void AVLTree::searchId( std::string ufid) {
    //Check if ufid is valid
    bool valid_ufid = ufid_valid(ufid);
    if (!valid_ufid) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    searchIdHelper(this->root, ufid);
}
//Search ID Helper
void AVLTree::searchIdHelper(Node* node, std::string ufid) {
    if (node == nullptr) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    if (node->ufid == ufid) {
        std::cout << node->name << std::endl;
        return;
    }
    else if (ufid > node->ufid) {
        searchIdHelper(node->right,ufid);
    }
    else {
        searchIdHelper(node->left, ufid);
    }
}

void AVLTree::searchName(std::string name) {
    //Check if name is valid
    bool valid_name = name_valid(name);
    if (!valid_name) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    //Hold all ufids with duplicate names
    std::vector<std::string> ufids;
    searchNameHelper(this->root, name, ufids);
    //Print "unsuccessful" is there are no names that match
    if (ufids.size() == 0) {
        std::cout << "unsuccessful" << std::endl;
    }
    else {
        for (size_t i = 0; i < ufids.size(); i++) {
            std::cout << ufids[i] << std::endl;
        }
    }
}
//Search name helper
//FIX THIS AFTER DOING THE TRAVERSAL METHODS
void AVLTree::searchNameHelper(Node* node, std::string name, std::vector<std::string>& ufids) {
    if (node == nullptr) {
        return;
    }
    if (node->name == name) {
        ufids.push_back(node->ufid);
    }
    //Traverse with preorder traversal
    searchNameHelper(node->left,name,ufids);
    searchNameHelper(node->right,name,ufids);
}
//Remove Method
void AVLTree::removeId(std::string ufid) {
    //Check if ufid is valid
    bool valid_ufid = ufid_valid(ufid);
    if (!valid_ufid) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    this->root = removeIdHelper(this->root, ufid);
    std::cout << "successful" << std::endl;
}
Node* AVLTree::removeIdHelper(Node* node, std::string ufid) {
    if (node == nullptr) {
        return node;
    }
    if (ufid > node->ufid) {
        node->right = removeIdHelper(node->right, ufid);
    }
    else if (ufid < node->ufid) {
        node->left = removeIdHelper(node->left, ufid);
    }
    //Found node that has to be deleted
    //Node has no children
    if (node->ufid == ufid && !node->left && !node->right) {
        delete node;
        return nullptr;
    }
    //Node has only the left child
    if (node->ufid == ufid && node->left && !node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
    }
    //Node has only the right child
    if (node->ufid == ufid && !node->left && node->right) {
        Node* temp = node->right;
        delete node;
        return temp;
    }
    //Node has both children
    if (node->ufid == ufid && node->left && node->right) {
        //Find the inorder successor
        Node* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        //Swap the node and the inorder successor
        node->ufid = temp->ufid;
        node->name = temp->name;
        //Delete temp node recursively
        node->right = removeIdHelper(node->right, temp->ufid);
        return node;
    }
    return node;
}
void AVLTree::removeInorderN(int n) {
    std::vector<Node*> node_inorder;
    this->root = removeInorderNHelper(this->root, n, node_inorder);
    //Check if n is valid
    if (node_inorder.size() <= (size_t)n || n < 0) {
        std::cout << "unsuccessful" << std::endl;
    }
    else {
        //Remove nth node
        for (size_t i = 0; i < node_inorder.size(); i++) {
            if (i == (size_t)n) {
                std::cout << "successful" << std::endl;
                removeId(node_inorder[i]->ufid);
            }
        }
    }
}
Node* AVLTree::removeInorderNHelper(Node* node, int n, std::vector<Node*>& node_inorder) {
    if (node == nullptr) {
        return node;
    }
    removeInorderNHelper(node->left, n, node_inorder);
    node_inorder.push_back(node);
    removeInorderNHelper(node->right, n, node_inorder);

    return node;
}
