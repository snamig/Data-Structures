/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 26.10.2021 */
#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    public:
        char letter;
        Node* next;

};


class LinkedList{
 
    Node* head;
    Node* tail;

    public:
        
        LinkedList();
        ~LinkedList();
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
        void add_element(char);
        int count_letters();
};

#endif