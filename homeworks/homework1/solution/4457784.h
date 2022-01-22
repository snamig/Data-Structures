/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 10.11.2021 */

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
        materialNode* prev;
        materialNode(char id, int weight){
            this->id = id;
            this->weight = weight;
            this->next = NULL;
            this->prev = NULL;
        }; 
};

class wagonNode{ 
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
        wagonNode* prev;
        wagonNode(int wagonId, materialNode *material){
            this->wagonId = wagonId;
            this->material = material;
            this->next = NULL;
            this->prev = NULL;
        };
};

class Train{  

    wagonNode* head;
    wagonNode* tail;
    
    public:
        void create();
        void sort_material(wagonNode *);
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
};

#endif