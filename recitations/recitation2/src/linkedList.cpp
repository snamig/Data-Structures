#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

void LinkedList::reorderList(){
    //FILL THIS FUNCTION ACCORDINGLY
};

void LinkedList::removeDublicates(){
    //FILL THIS FUNCTION ACCORDINGLY
};

void LinkedList::reverseList(){
    //FILL THIS FUNCTION ACCORDINGLY  
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};