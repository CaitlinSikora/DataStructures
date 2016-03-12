//
//  Linked List Class
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

template <class Item>
struct Node {
    Item data;
    Node<Item>* link;
};

template <class Item>
class LinkedList
{
public:
    
    LinkedList(string list); // Constructor for list
    LinkedList(Item); // Constructor for Item
    
    int Length();
    void insertTail(Item n);
    void insertHead(Item n);
    void remove(Item n);
    void display();
    void reverse();
    
private:
    Node<Item>* head_ptr;
    Node<Item>* tail_ptr;
    int length;
    
};

// Constructor that takes in a single Item
template <class Item>
LinkedList<Item>::LinkedList(Item n){
    Node<Item> *newNode = new Node<Item>;
    newNode->data = n;
    newNode->link = NULL;
    
    head_ptr=newNode;
    tail_ptr=newNode;
}

// Constructor that takes in a list
template <class Item>
LinkedList<Item>::LinkedList(string list){
    Item dumVar;
    bool first=true;
    int i = 0;
    while(i<list.length()){
        dumVar = list[i];
        i++;
        if (first==true){
            Node<Item> *newNode = new Node<Item>;
            newNode->data = dumVar;
            newNode->link = NULL;
            
            head_ptr=newNode;
            tail_ptr=newNode;
            first=false;
        } else {
            insertTail(dumVar);
        }
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
            tail_ptr = newNode;
            return;
        }
        cursor = cursor->link;
    }
}

// print a linked list
template <class Item>
void LinkedList<Item>::display() {
    Node<Item> *list = head_ptr;
    while(list) {
        cout << list->data;
        list = list->link;
    }
    cout << endl;
}

// insert an item at the beginning of the linked list
template <class Item>
void LinkedList<Item>::insertHead(Item n){
    Node<Item> *newNode = new Node<Item>;
    newNode->data = n;
    newNode->link = NULL;
    
    newNode->link = head_ptr;
    head_ptr = newNode;
    return;
}

// remove an item from the top of the list
template <class Item>
void LinkedList<Item>::remove(Item n){
    Node<Item> *remove_ptr = head_ptr;
    Node<Item> *cursor = head_ptr;
    Node<Item> *trail = NULL;
    if(n==cursor->data) {
        cursor = cursor->link;
        delete remove_ptr;
        head_ptr = cursor;
        return;
    } else {
        trail = cursor;
        cursor = cursor->link;
        remove_ptr= remove_ptr->link;
    }
    while(cursor!=NULL) {
        if(n==cursor->data) {
            cursor = cursor->link;
            delete remove_ptr;
            trail->link = cursor;
            return;
        }
        trail = cursor;
        cursor = cursor->link;
    }
    cout << "Data not found." << endl;
}

// reverse the nodes in the linked list by changing the links to point in the opposite direction
template <class Item>
void LinkedList<Item>::reverse() {
    // check that there are at least 2 nodes. If not, return.
    if(head_ptr == NULL || head_ptr->link == NULL) return;
    
    // create 3 pointers to go through the elements of the linked list.
    Node<Item> *trail = head_ptr;
    Node<Item> *cursor = head_ptr->link;
    Node<Item> *lead = cursor->link;
    
    // make the original head pointer point to NULL
    trail->link = NULL;
    
    while(lead != NULL){
        cursor->link = trail;
        trail = cursor;
        cursor = lead;
        lead = lead->link;
    }
    // change the head pointer to the former end of the list
    
    cursor->link = trail;
    head_ptr = cursor;
}


int main() {
    string l1;
    cout << "Please input the list:\n";
    getline(cin, l1);
    LinkedList<char> List1(l1);
    cout << "Your list reads: ";
    List1.display();
    List1.insertHead('a');
    cout << "Insert 'a' at head: ";
    List1.display();
    List1.insertTail('k');
    cout << "Insert 'k' at tail: ";
    List1.display();
    List1.remove('c');
    cout << "Remove 'c': ";
    List1.display();
    List1.reverse();
    cout << "Reverse your list: ";
    List1.display();
    return 0;
}