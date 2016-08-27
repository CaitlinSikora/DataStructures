//
//  Binary Search Tree Class
//
//  Created by Caitlin Sikora on 3/6/16.
//  Copyright © 2016 Caitlin Sikora. All rights reserved.
//


#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

// struct definition for TreeNode
template <class Item>
struct TreeNode {
    Item data;
    TreeNode<Item>* right;
    TreeNode<Item>* left;
};

// BinaryTree class definition
template <class Item>
class BinaryTree
{
public:
    
    BinaryTree(string& input); // Constructor
    BinaryTree(Item array[]); // Array constructor
    
    TreeNode<Item>* createNode(const Item& entry, TreeNode<Item>* left = NULL, TreeNode<Item>* right = NULL);
    void insert(TreeNode <Item>*& node_ptr, const Item& entry);
    void search(TreeNode<Item>*  root_ptr, const Item& target, bool& found, int& numNodes, TreeNode<Item>*& loc_ptr);
    void inorder_print(const TreeNode <Item>* node_ptr);
    TreeNode<Item>* getLoc();
    TreeNode<Item>* getRoot();
    
private:
    TreeNode<Item>* loc_ptr = NULL;
    TreeNode<Item>* root_ptr = NULL;
};

// struct definition for Node
template <class Item>
struct Node {
    Item data;
    Node<Item>* link;
};

// class definition for LinkedList
template <class Item>
class LinkedList
{
public:
    
    LinkedList(string list); // Constructor for list
    LinkedList(Item array[]); // Constructor for array
    
    int Length();
    void insertTail(Item n);
    void search(Node<Item>* head_ptr, Item look_data, bool& found, int& numNodes, Node<Item>*& loc_ptr);
    Node<Item>* getHeader();
    Node<Item>* getLoc();
    
private:
    int length;
    Node<Item>* head_ptr = NULL;
    Node<Item>* loc_ptr = NULL;
    
};

// non-member function prototypes:
void sortArray(int array[]);

// user creates a tree and linked list by providing input, then main searches for desired entry in both and reports nodes visited
int main() {
    string input;
    string value;
    int data;
    bool foundTree=false;
    bool foundList=false;
    int numTreeNodes=0;
    int numListNodes=0;
    
    // get user input
    cout << "Enter your list to create a tree and a linked list:\n";
    getline(cin, input);
    
    // call constructor to tokenize user data and insert into a binary search tree called Tree1
    BinaryTree<int> Tree1(input);
    LinkedList<int> List1(input);
    TreeNode<int>* locTree1_ptr = Tree1.getLoc();
    Node<int>* locList1_ptr = List1.getLoc();
    TreeNode<int>* root1_ptr = Tree1.getRoot();
    Node<int>* head1_ptr = List1.getHeader();
    
    cout << "Enter the value you'd like to search for:\n";
    getline(cin, value);
    data = stoi(value);
    
    Tree1.search(root1_ptr,data,foundTree,numTreeNodes,locTree1_ptr);
    List1.search(head1_ptr,data,foundList,numListNodes,locList1_ptr);
    if (foundTree==true){
        cout << data << " has been found in the tree." << endl;
    } else {
        cout << "Your data was not found." << endl;
    }
    cout << "Your Binary Search Tree has visited " << numTreeNodes << " nodes." <<endl;
    if (foundList==true){
        cout << data << " has been found in the list." << endl;
    }
    cout << "Your Linked List has visited " << numListNodes << " nodes." <<endl;
    
    cout << "For a randomly generated list..." << endl;
    // generate the random numbers
    srand (time(NULL));
    int randInts[1024];
    for (int i=0;i<1024;i++){
        randInts[i]=rand()%10000000;
    }
    
    // sort the array if desired
    sortArray(randInts);
    
    // reset the found and numNodes variables
    foundTree=false;
    foundList=false;
    numTreeNodes=0;
    numListNodes=0;
    
    // create the new tree and list and set pointers to the head pointer and loc pointers
    BinaryTree<int> Tree2(randInts);
    LinkedList<int> List2(randInts);
    TreeNode<int>* locTree2_ptr = Tree2.getLoc();
    Node<int>* locList2_ptr = List2.getLoc();
    TreeNode<int>* root2_ptr = Tree2.getRoot();
    Node<int>* head2_ptr = List2.getHeader();

    // search the tree for the intended value
    data = 9;
    Tree2.search(root2_ptr,data,foundTree,numTreeNodes,locTree2_ptr);
    List2.search(head2_ptr,data,foundList,numListNodes,locList2_ptr);
    if (foundTree==true){
        cout << data << " has been found in the tree." << endl;
    } else {
        cout << "Your data was not found." << endl;
    }
    cout << "Your Binary Search Tree has visited " << numTreeNodes << " nodes." <<endl;
    if (foundList==true){
        cout << data << " has been found in the list." << endl;
    }
    cout << "Your Linked List has visited " << numListNodes << " nodes." <<endl;
    
    return 0;
}

// --------------------------------------all of the functions-------------------------------------

// constructor for a binary tree given user input
template <class Item>
BinaryTree<Item>::BinaryTree(string& input){
    string dumVar;
    Item dum;
    int i = 0;
    while(i<input.length()){
        while (input[i]!=' '&& i<input.length()){
            dumVar += input[i];
            i++;
        }
        dum=stoi(dumVar);
        insert(root_ptr, dum);
        i++;
        dumVar="";
    }
    //inorder_print(root_ptr);
}

// constructor for binary tree from array
template <class Item>
BinaryTree<Item>::BinaryTree(Item array[]){
    int i = 0;
    while(i<1024){
        insert(root_ptr, array[i]);
        i++;
    }
    //inorder_print(root_ptr);
}

// get root
template <class Item>
TreeNode<Item>* BinaryTree<Item>::getRoot(){
    return root_ptr;
}

// get Loc
template <class Item>
TreeNode<Item>* BinaryTree<Item>::getLoc(){
    return loc_ptr;
}

// create a node
template <class Item>
TreeNode<Item>* BinaryTree<Item>::createNode(const Item& entry, TreeNode<Item>* left_ptr, TreeNode<Item>* right_ptr){
    TreeNode<Item> *new_ptr = new TreeNode<Item>;
    new_ptr->data = entry;
    new_ptr->left = left_ptr;
    new_ptr->right = right_ptr;
    return new_ptr;
}

// insert function
template <class Item>
void BinaryTree<Item>::insert(TreeNode <Item>*& root_ptr, const Item& entry) {
    if (root_ptr == NULL)
        root_ptr = createNode(entry);
    else if (entry <= root_ptr->data)
        insert(root_ptr->left, entry);
    else
        insert(root_ptr->right, entry);
}

// search function that keeps track of nodes visited
template<class Item>
void BinaryTree<Item>::search(TreeNode<Item>*  root_ptr, const Item& target, bool& found, int& numNodes, TreeNode<Item>*& loc_ptr){
    if (root_ptr == NULL)
    {
        loc_ptr = NULL;
        found = false;
    }
    else if (target == root_ptr-> data)
    {
        numNodes++;
        loc_ptr = root_ptr;
        found = true;
        return;
    }
    else if (target <= root_ptr ->data){
        numNodes++;
        search(root_ptr->left, target, found, numNodes, loc_ptr);
    }
    else{
        numNodes++;
        search(root_ptr->right, target, found, numNodes, loc_ptr);
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

// Constructor that takes in a string to build a linked list
template <class Item>
LinkedList<Item>::LinkedList(string list){
    string dumVar;
    bool first=true;
    int i = 0;
    while(i<list.length()){
        while (list[i]!=' '&& i<list.length()){
            dumVar += list[i];
            ++i;
        }
        if (first==true){
            Node<Item> *newNode = new Node<Item>;
            newNode->data = stoi(dumVar);
            newNode->link = NULL;
            
            head_ptr=newNode;
            first=false;
        } else {
            insertTail(stoi(dumVar));
        }
        i++;
        dumVar="";
    }
}

// constructor that takes in an array of items
template <class Item>
LinkedList<Item>::LinkedList(Item array[]){
    bool first=true;
    int i = 0;
    while(i<1024){
        if (first==true){
            Node<Item> *newNode = new Node<Item>;
            newNode->data = array[i];
            newNode->link = NULL;
            
            head_ptr=newNode;
            first=false;
        } else {
            insertTail(array[i]);
        }
        i++;
    }
}

// add other nodes
template <class Item>
void LinkedList<Item>::insertTail(Item n) {
    Node<Item> *newNode = new Node<Item>;
    newNode->data = n;
    newNode->link = NULL;
    
    Node<Item> *cursor = head_ptr;
    while(cursor!=NULL) {
        if(cursor->link == NULL) {
            cursor->link = newNode;
            return;
        }
        cursor = cursor->link;
    }
}

// get header
template <class Item>
Node<Item>* LinkedList<Item>::getHeader(){
    return head_ptr;
}

// get loc
template <class Item>
Node<Item>* LinkedList<Item>::getLoc(){
    return loc_ptr;
}

// search the linked list
template <class Item>
void LinkedList<Item>::search(Node<Item>* head_ptr, Item look_data, bool& found, int& numNodes, Node<Item>*& loc_ptr) {
    if (head_ptr == NULL){
        loc_ptr = NULL;
        found = false;
    } else if(head_ptr->data == look_data) {
        numNodes++;
        loc_ptr = head_ptr;
        found = true;
        return;
    } else {
        numNodes++;
        search(head_ptr->link,look_data,found,numNodes,loc_ptr);
    }
}

// sort the array
void sortArray(int array[]){
    
    std::vector<int> randVector (array, array+1024);
    
    // sort the elements of the vector:
    std::sort (randVector.begin(), randVector.end());
    int i=0;
    // refill the array
    for (std::vector<int>::iterator it=randVector.begin(); it!=randVector.end(); ++it){
        array[i]= *it;
        //cout << array[i] << endl;
        i++;
    }
}
