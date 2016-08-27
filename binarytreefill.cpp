//
//  Binary Tree Class
//
//  Created by Caitlin Sikora on 3/6/16.
//  Copyright © 2016 Caitlin Sikora. All rights reserved.
//


#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <math.h>
using namespace std;

// struct definition
template <class Item>
struct TreeNode {
    Item data;
    TreeNode<Item>* right;
    TreeNode<Item>* left;
};

// class definition
template <class Item>
class BinaryTree
{
public:
    
    BinaryTree(int size, char order, int dataIn[]); // Constructor
    
    int numNodes();
    TreeNode<Item>* createNode(const Item& entry, TreeNode <Item>* left_ptr=NULL, TreeNode <Item>* right_ptr=NULL);
    TreeNode<Item>* emptyTree(int count);
    void printSwitch(char order);
    void preorder_print(const TreeNode <Item>* node_ptr);
    void inorder_print(const TreeNode <Item>* node_ptr);
    void postorder_print(const TreeNode <Item>* node_ptr);
    void PreFillTree(TreeNode <Item>* node_ptr, int& entry, int dataIn[]);
    void InFillTree(TreeNode <Item>* node_ptr, int& entry, int dataIn[]);
    void PostFillTree(TreeNode <Item>* node_ptr, int& entry, int dataIn[]);
    
private:
    int numnodes;
    TreeNode<Item>* root_ptr;
};

// non-member function prototype to tokenize and interpret user data
string getCommand(string& input, int& size, int dataIn[]);

// user creates a tree by providing input, then user prints tree in desired order multiple times
int main() {
    // track if tree has been created and loop printing
    bool treeExists = false;
    bool repeat = true;
    // create array, size of array, and string to send user input
    string input;
    int dataIn[100];
    int size=0;
    
    // get user input
    cout << "You can create (C), print (P), or end (E) with the traversal order you choose (PRE, IN, POST).\n\n";
    cout << "Enter your command and list to create a tree:\n";
    getline(cin, input);
    
    // call getCommand to tokenize the user input
    string command = getCommand(input, size, dataIn);
    
    // create tree if appropriate input has been provided
    if (!treeExists && command[0]=='C'){
        BinaryTree<int> Tree1(size, command[3], dataIn);
        treeExists=true;
        
        // loop to print tree
        while (repeat){
            command = "";
            cout << "Enter another command to print the tree:\n";
            getline(cin, command);
            
            // if user commands to print tree and tree exists, print, otherwise, print an error message
            if (command[0]=='P') {
                if (treeExists){
                    cout << "Your command prints: ";
                    Tree1.printSwitch(command[3]);
                    cout << endl;
                } else {
                    cout << "You must create a tree in order to print a tree." << endl;
                }
            } else if (command[0]=='E') {
                repeat=false;
            } else {
                cout << "That is not a valid command." << endl;
            }
        }
        
    } else {
        cout << "You must restart to create a tree." << endl;
    }
    
    return 0;
}

// --------------------------------------all of the functions-------------------------------------

// constructor for a binary tree given user input
template <class Item>
BinaryTree<Item>::BinaryTree(int size, char order, int dataIn[]){
    root_ptr = emptyTree(size);
    int entry = 0;
    switch(order){
        case 'R':
            PreFillTree(root_ptr, entry, dataIn);
            break;
        case 'N':
            InFillTree(root_ptr, entry, dataIn);
            break;
        case 'O':
            PostFillTree(root_ptr, entry, dataIn);
            break;
        default:
            cout << "This is not a valid order." << endl;
            break;
    }

}

// create a node
template <class Item>
TreeNode<Item>* BinaryTree<Item>::createNode(const Item& entry, TreeNode <Item>* left_ptr, TreeNode <Item>* right_ptr){
    TreeNode<Item> *new_ptr = new TreeNode<Item>;
    new_ptr->data = entry;
    new_ptr->left = left_ptr;
    new_ptr->right = right_ptr;
    return new_ptr;
}

// create an empty tree with the correct number of nodes
template <class Item>
TreeNode<Item>* BinaryTree<Item>::emptyTree(int count){
    if (count > 0){
        count--;
        TreeNode<Item>* node_ptr;
        int rightNum = count/2;
        int leftNum = count - rightNum;
        node_ptr = createNode(0,emptyTree(leftNum),emptyTree(rightNum));
        return node_ptr;
    } else {
        return NULL;
    }
}


// fill the empty tree with an pre-order traversal
template <class Item>
void BinaryTree<Item>::PreFillTree(TreeNode <Item>* node_ptr, int& entry, int dataIn[]){
    if (node_ptr != NULL){
        node_ptr->data = dataIn[entry];
        entry++;
        PreFillTree(node_ptr->left, entry, dataIn);
        PreFillTree(node_ptr->right, entry, dataIn);
    }
}

// fill the empty tree with an in-order traversal
template <class Item>
void BinaryTree<Item>::InFillTree(TreeNode <Item>* node_ptr, int& entry, int dataIn[]){
    if (node_ptr != NULL){
        InFillTree(node_ptr->left, entry, dataIn);
        node_ptr->data = dataIn[entry];
        entry++;
        InFillTree(node_ptr->right, entry, dataIn);
    }
}

// fill the empty tree with a post-order traversal
template <class Item>
void BinaryTree<Item>::PostFillTree(TreeNode <Item>* node_ptr, int& entry, int dataIn[]){
    if (node_ptr != NULL){
        PostFillTree(node_ptr->left, entry, dataIn);
        PostFillTree(node_ptr->right, entry, dataIn);
        node_ptr->data = dataIn[entry];
        entry++;
    }
}

// print switch the choose the appropriate print function
template <class Item>
void BinaryTree<Item>::printSwitch(char order){
    switch(order){
        case 'R':
            preorder_print(root_ptr);
            break;
        case 'N':
            inorder_print(root_ptr);
            break;
        case 'O':
            postorder_print(root_ptr);
            break;
        default:
            cout << "This is not a valid order." << endl;
            break;
    }

}

// print tree preorder
template <class Item>
void BinaryTree<Item>::preorder_print(const TreeNode <Item>* node_ptr){
    if (node_ptr != NULL){
        cout << node_ptr->data << " ";
        preorder_print(node_ptr->left);
        preorder_print(node_ptr->right);
    }
}

// print tree inorder
template <class Item>
void BinaryTree<Item>::inorder_print(const TreeNode <Item>* node_ptr){
    if (node_ptr != NULL){
        inorder_print(node_ptr->left);
        cout << node_ptr->data << " ";
        inorder_print(node_ptr->right);
    }
}

// print tree postorder
template <class Item>
void BinaryTree<Item>::postorder_print(const TreeNode <Item>* node_ptr){
    if (node_ptr != NULL){
        postorder_print(node_ptr->left);
        postorder_print(node_ptr->right);
        cout << node_ptr->data << " ";
    }
}

// tokenize user input, send data for tree to an array that can be used to fill tree
string getCommand(string& input, int& size, int dataIn[]){
    string command;
    command = input.substr(0,2);
    string dumVar;
    bool first=true;
    int i = 2;
    int arrayInd = 0;
    int begin=0;
    while(i<input.length()){
        while (input[i]!=' '&& i<input.length()){
            dumVar += input[i];
            i++;
        }
        if (first==true){
            command += dumVar;
            begin = i+1;
            first=false;
        } else {
            size++;
            dataIn[arrayInd]=stoi(dumVar);
            arrayInd++;
        }
        i++;
        dumVar="";
    }
    input = input.substr(begin,input.length());
    return command;
}