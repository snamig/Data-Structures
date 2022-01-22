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

    public:
       
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif