//
//  csikora-hw3.cpp
//  sikora-hw3
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

// create a struct called Node with a template class Item
template <class Item>
struct Node {
    Item data;
    Node<Item>* link;
};

// implement a stack class
template <class Item>
class Stack
{
public:
    
    Stack(); // Constructor
    void push(Item n);
    Item pop();
    int Length();
    
private:
    Node<Item>* head_ptr;
    int length;
};

// Stack constructor that creates a node with data 0 and a pointer to NULL
template <class Item>
Stack<Item>::Stack(){
    Node<Item> *newNode = new Node<Item>;
    newNode->data = 0;
    newNode->link = NULL;

    head_ptr=newNode;
    length = 0;
}


// insert an item at the top of the stack
template <class Item>
void Stack<Item>::push(Item n){
    Node<Item> *newNode = new Node<Item>;
    newNode->data = n;
    newNode->link = NULL;
        
    newNode->link = head_ptr;
    head_ptr = newNode;
    length++;
    return;
}

// remove an item from the top of the stack
template <class Item>
Item Stack<Item>::pop(){
    if (length > 0) {
        Item dumVar;
        Node<Item> *remove_ptr = head_ptr;
        Node<Item> *cursor = head_ptr;
        cursor = cursor->link;
        dumVar=remove_ptr->data;
        delete remove_ptr;
        head_ptr = cursor;
        length--;
        return dumVar;
    } else {
        cout << "No data to pop" << endl;
        return 0;
    }
}

template <class Item>
int Stack<Item>::Length(){
    return length;
}

// use a function to reverse print the string
template <class Item>
string reverseWords(string input){
    Stack<Item> theStack;
    Item dummy;
    string output;
    theStack.push(' '); // start with a space to go between the first and second words
    for (int i=0; i<input.length(); i++){
        dummy = input[i];
        if (dummy!= ' '){
            theStack.push(dummy); // push the first word into the stack
        } else if(dummy== ' '){ // pop the first word backwards and add to the output string
            while (theStack.Length()>0){
                output+=theStack.pop();
            }
            theStack.push(' '); // push a space to go in between the next two words
        }
    }
    while (theStack.Length()>1){ // pop the last word off without the space at the end
        output+=theStack.pop();
    }
    theStack.pop(); // pop off the last space to deallocate the memory for that space
    return output;
}

// implement a queue class
template <class Item>
class Queue
{
public:
    
    Queue();
    
    void insert(Item n);
    Item get_front();
    
private:
    Stack<Item> Stack1;
    Stack<Item> Stack2;
    int count;
};

// constructor
template <class Item>
Queue<Item>::Queue(){
    count = 0;
}


// insert an item to the end of the Queue
template <class Item>
void Queue<Item>::insert(Item n){
    Stack1.push(n);
    count++;
    return;
}

// remove an item from the top of the stack
template <class Item>
Item Queue<Item>::get_front(){
    if (count > 0) {
        Item dumVar;
        for (int i=0; i<count; i++){
            Stack2.push(Stack1.pop());
        }
        dumVar = Stack2.pop();
        count--;
        for (int i=0; i<count; i++){
            Stack1.push(Stack2.pop());
        }
        return dumVar;
    } else {
        cout << "No data to get" << endl;
        return 0;
    }
}


int main() {
    string l1;
    char dummy;
    // get a sentence from the user
    cout << "Please input a sentence:\n";
    getline(cin, l1);
    Stack<char> theStack;
    Queue<char> theQueue;
    // push each character in the sentence into the stack
    for (int i=0; i<l1.length(); i++){
        dummy = l1[i];
        theStack.push(dummy);
    }
    // pop and print each character in the stack
    cout << "The reverseWords function uses one stack to return: " << endl;
    cout << reverseWords<char>(l1);
    cout << endl;
    // insert each character in the sentence into the queue
    for (int i=0; i<l1.length(); i++){
        dummy = l1[i];
        theQueue.insert(dummy);
    }
    // get and print each character from the front of the queue one at a time
    cout << "Looping through the get_front function for the Queue gives: " << endl;
    for (int i=0; i<l1.length(); i++){
        dummy = theQueue.get_front();
        cout << dummy;
    }
    cout << endl;
    return 0;
}