//
// Created by Kush P on 2/17/2026.
//

#ifndef PROJECT_1_DSA_AVL_TREES_AVLTREE_H
#define PROJECT_1_DSA_AVL_TREES_AVLTREE_H

#endif //PROJECT_1_DSA_AVL_TREES_AVLTREE_H

#include <iostream>
#include <vector>
#include <string>
//Code from Jackie Wang's video
struct Node{
    //Node Attributes
    std::string name;
    std::string ufid;
    int height = 1;
    int balance = 0;
    Node* left;
    Node* right;
    Node(std::string name, std::string ufid) {
        this->name = name;
        this->ufid = ufid;
        this->left = nullptr;
        this->right = nullptr;
    }
};
//Function prototypes
class AVLTree {
    Node* root = nullptr;
    //Private Helper Methods
    Node* insertHelper(Node* node, std::string name, std::string ufid);
    void searchIdHelper(Node* node, std::string ufid);
    void searchNameHelper(Node* node, std::string name, std::vector<std::string>& ufids);
    Node* removeIdHelper(Node* node, std::string ufid);
    Node* removeInorderNHelper(Node* node, int n, std::vector<Node*>& node_inorder);
    void preOrderHelper(Node* node);
    void inOrderHelper(Node* node);
    void postOrderHelper(Node* node);
    void levelCountHelper(Node* node);
    //Rotations
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
public:
    //Insertion Method
    void insert(std::string name, std::string ufid);
    //Search Methods
    void searchId(std::string ufid);
    void searchName(std::string name);
    //Remove Methods
    void removeId(std::string ufid);
    void removeInorderN(int n);
    //Traversal Methods
    void preOrder();
    void inOrder();
    void postOrder();
    void levelCount();

    //UF ID Valid
    bool ufid_valid(std::string ufid);
    //Name Valid
    bool name_valid(std::string name);

    //Destructor
    ~AVLTree() {
        //postorder traversal//
    }
};


