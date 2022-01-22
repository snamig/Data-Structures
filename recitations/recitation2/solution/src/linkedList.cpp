/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 26.10.2021 */
#include <iostream>
#include <stdio.h>
#include "linkedList.h"

using namespace std;

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
};
LinkedList::~LinkedList(){
    if(head!=NULL) delete head;
};

// Here we made our Linked list by reading inputs from given txt file
void LinkedList::add_element(char ch){
    Node* new_node = new Node();

    new_node->letter = ch;

    if(head == NULL){
        head = new_node;
        tail = new_node;
    }
    else{
        tail->next = new_node;
        tail = new_node;
    }
};

// I needed to use count several times while doing this homework 
// so I made it as a seperate function to prevent DRY principle
// This function counts letters in the Linked list
int LinkedList::count_letters(){
    int count = 0;

    Node* new_node = head;

    while(new_node != NULL){
        count++;
        new_node = new_node->next;
    }

    return count;
}

void LinkedList::reorderList(){
    //FILL THIS FUNCTION ACCORDINGLY

    int count = this->count_letters();


    
    for(int i = 0; i < count; i++){
        // First we take our reference node
        Node* temp_node_i = head;
        for(int k = 0; k < i; k++){
            temp_node_i = temp_node_i->next;
        }
        //And here we compare it with other nodes
        for(int j = i+1; j < count; j++){
            Node* temp_node_j = head;
            for(int k = 0; k < j; k++){
                temp_node_j = temp_node_j->next;
            }
            if(temp_node_i->letter > temp_node_j->letter){
                char temp;
                temp = temp_node_i->letter; 
                temp_node_i->letter = temp_node_j->letter;
                temp_node_j->letter = temp;
            }
        }
    }
};

void LinkedList::removeDublicates(){
    //FILL THIS FUNCTION ACCORDINGLY

    int count = this->count_letters();

    for(int i = 0; i < count; i++){
        Node* temp_node_i = head;
        
        for(int k = 0; k < i; k++){
            temp_node_i = temp_node_i->next;
        }
        if(temp_node_i->next != NULL){
            // Here we compared our letters, by comparing their 
            //ASCII values. If they are equal we change the pointer that
            //points to repeated one to next one.
            while(temp_node_i->letter == temp_node_i->next->letter){
                temp_node_i->next = temp_node_i->next->next;
                count--;
            }
        }
    }


};

void LinkedList::reverseList(){
    //FILL THIS FUNCTION ACCORDINGLY  

    Node* current = head;
    Node* previous = NULL;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        // Reverse current node pointer.
        current->next = previous;
        // Move pointers ahead.
        previous = current;
        current = next;
    }
    head = previous;
};


void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};