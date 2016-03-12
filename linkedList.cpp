//
//  hw2-sikora.cpp
//  hw2

//  Data Structures and Algorithms CS 5403
//
//  Created by Caitlin Sikora on 2/24/16.
//  Copyright © 2016 Caitlin Sikora. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct Node {
    typedef int Item;
    Item data;
    Node* link;
};



// initialize the first node
void initializeNode(struct Node *head_ptr, int n){
    head_ptr->data = n;
    head_ptr->link = NULL;
}

// add other nodes
void addNode(struct Node *head_ptr, int n) {
    Node *newNode = new Node;
    newNode->data = n;
    newNode->link = NULL;
    
    Node *cursor = head_ptr;
    while(cursor!=NULL) {
        if(cursor->link == NULL) {
            cursor->link = newNode;
            return;
        }
        cursor = cursor->link;
    }
}

// build the list by tokenizing the string and calling initializeNode once and addNode for the other values
void buildList(string list, struct Node *head_ptr){
    int dumInt;
    bool first=true;
    string dummyString = "";
    int i = 0;
    while(i<list.length()){
            while (list[i]!=' '){
                dummyString += list[i];
                ++i;
            }
            dumInt = stoi(dummyString);
            dummyString ="";
            ++i;
            if (first==true){
                initializeNode(head_ptr,dumInt);
                first = false;
            } else {
                addNode(head_ptr, dumInt);
            }
        }
        i++;

}

// concatenate two linked lists
void concatenate(struct Node *head_ptr1, struct Node *head_ptr2){
    Node *list1 = head_ptr1;
    Node *list2 = head_ptr2;
    while(list1!=NULL) {
        if(list1->link == NULL) {
            list1->link = list2;
            return;
        }
        list1 = list1->link;
    }
}

// insert an int in the appropriate place in a sorted linked list
void insert(struct Node*& head_ptr, int n){
    Node *newNode = new Node;
    newNode->data = n;
    newNode->link = NULL;
    
    Node *cursor = head_ptr;
    Node *trail = NULL;
    if(n<=cursor->data) {
        newNode->link = head_ptr;
        head_ptr = newNode;
        return;
    } else {
        trail = cursor;
        cursor = cursor->link;
    }
    while(cursor!=NULL) {
        if(n<=cursor->data) {
            trail->link = newNode;
            newNode->link = cursor;
            return;
        }
        trail = cursor;
        cursor = cursor->link;
    }
    trail->link = newNode;
    newNode->link = cursor;
}

void remove(struct Node*& head_ptr, int n){
    Node *remove_ptr = head_ptr;
    Node *cursor = head_ptr;
    Node *trail = NULL;
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

// return the median of a linked list
double median(struct Node *head_ptr) {
    Node *list = head_ptr;
    int count=0;
    double median;
    double first, second;
    while(list) {
        list = list->link;
        count ++;
    }
    list = head_ptr;
    if (count%2==0){
        for (int i=0;i<((count/2)-1);i++) {
            list = list->link;
        }
        first = list->data;
        list = list->link;
        second = list->data;
        median = ((double)first + second) / 2;
    } else if (count%2!=0) {
        for (int i=0;i<(count/2);i++) {
            list = list->link;
        }
        median = list->data;
    }
    return median;
}

// reverse the nodes in the linked list by changing the links to point in the opposite direction
void reverse(struct Node*& head_ptr) {
    // check that there are at least 2 nodes. If not, return.
    if(head_ptr == NULL || head_ptr->link == NULL) return;
    
    // create 3 pointers to go through the elements of the linked list.
    Node *trail = head_ptr;
    Node *cursor = head_ptr->link;
    Node *lead = cursor->link;
    
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

void display(struct Node *head_ptr) {
    Node *list = head_ptr;
    while(list) {
        cout << list->data << " ";
        list = list->link;
    }
    cout << endl;
}

int main() {
    bool repeat = true;
    string opCode;
    while (repeat == true) {
        cout << "Please tell me what to do: concatenate(C), insert(I), median(M), reverse(R), end(E), remove(D)? \n";
        getline(cin, opCode);
    
    
        if ((char) opCode[0]=='C'){
            struct Node *head_ptr1 = new Node;
            struct Node *head_ptr2 = new Node;
            string l1;
            string l2;
            cout << "Please input the list1:\n";
            getline(cin, l1);
            cout << "Please input the list2:\n";
            getline(cin, l2);
            
            buildList(l1, head_ptr1);
            buildList(l2, head_ptr2);
            concatenate(head_ptr1, head_ptr2);
            cout << "The outcome is: " << endl;
            display(head_ptr1);
        
        } else if ((char) opCode[0]=='I'){
            struct Node *head_ptr = new Node;
            int n;
            string input;
            string list;
            cout << "Please input the list:\n";
            getline(cin, list);
            cout << "Please input the value:\n";
            getline(cin, input);
            n = stoi(input);
            
            buildList(list, head_ptr);
            insert(head_ptr, n);
            cout << "The outcome is: " << endl;
            display(head_ptr);
            
        } else if ((char) opCode[0]=='M'){
            struct Node *head_ptr = new Node;
            string input;
            string list;
            cout << "Please input the list:\n";
            getline(cin, list);
            
            buildList(list, head_ptr);
            cout << "The outcome is: " << endl;
            cout << median(head_ptr) << endl;

        } else if ((char) opCode[0]=='R'){
            struct Node *head_ptr = new Node;
            string input;
            string list;
            cout << "Please input the list:\n";
            getline(cin, list);
            
            buildList(list, head_ptr);
            reverse(head_ptr);
            cout << "The outcome is: " << endl;
            display(head_ptr);
            
        } else if ((char) opCode[0]=='E'){
            repeat = false;
            
        } else if ((char) opCode[0]=='D'){
                struct Node *head_ptr = new Node;
                int n;
                string input;
                string list;
                cout << "Please input the list:\n";
                getline(cin, list);
                cout << "Please input the value:\n";
                getline(cin, input);
                n = stoi(input);
            
                buildList(list, head_ptr);
                remove(head_ptr, n);
                cout << "The outcome is: " << endl;
                display(head_ptr);
            
        } else {
            cout << "This is not a valid instruction. Please try again." << endl;
            
        }
    }
    return 0;
}