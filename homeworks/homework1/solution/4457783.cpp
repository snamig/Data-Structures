/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 10.11.2021 */
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../include/linkedList.h"

using namespace std;

const int LIMIT = 2000;

void Train::create()
{  
    head = NULL;
    tail = NULL;
};

void Train::sort_material(wagonNode* wagon){
    int count = 0;
    materialNode * tempMaterialNode = wagon->material;
    while(tempMaterialNode){
        count++;
        tempMaterialNode = tempMaterialNode->next;
    }
    
    for(int i = 0; i < count; i++){
        // First we take our reference node
        materialNode* temp_node_i = wagon->material;
        for(int k = 0; k < i; k++){
            temp_node_i = temp_node_i->next;
        }
        //And here we compare it with other nodes
        for(int j = i+1; j < count; j++){
            materialNode* temp_node_j = wagon->material;
            for(int k = 0; k < j; k++){
                temp_node_j = temp_node_j->next;
            }
            if(temp_node_i->id > temp_node_j->id){
                char temp;
                int tempWeight;

                temp = temp_node_i->id;
                tempWeight = temp_node_i->weight; 

                temp_node_i->id = temp_node_j->id;
                temp_node_i->weight = temp_node_j->weight;

                temp_node_j->id = temp;
                temp_node_j->weight = tempWeight;

            }
        }
    }
}

void Train::addMaterial(char material, int weight)
{
    int toBeAdded = weight;
    bool isMaterialFound = false;

    wagonNode *traverse = this->head;

    if (!this->head)
    {
        int count = 0;
        if (toBeAdded <= LIMIT)
        {
            materialNode *newMaterial = new materialNode(material, weight);
            wagonNode *newWagon = new wagonNode(count+1, newMaterial);
            this->head = newWagon; 
            this->tail = newWagon;
            sort_material(newWagon);
                 
            newWagon->prev = NULL;
        }
        else
        {
            while (toBeAdded != 0)
            {
                if (toBeAdded < LIMIT)
                {   
                    materialNode *newMaterial = new materialNode(material, toBeAdded);
                    wagonNode *newWagon = new wagonNode(count+1, newMaterial);
                    sort_material(newWagon);
                    if (count == 0)
                    {
                        this->head = newWagon;
                        this->tail = newWagon;
                        traverse = this->head;
                        newWagon->prev = NULL;
                    }
                    else
                    {
                        traverse->next = newWagon;
                        newWagon->prev = traverse;
                        this->tail = newWagon;

                    }
                    toBeAdded = 0;
                }
                else
                {
                    materialNode *newMaterial = new materialNode(material, LIMIT);
                    wagonNode *newWagon = new wagonNode(count+1, newMaterial);
                    sort_material(newWagon);
                    toBeAdded -= LIMIT;
                    if (count == 0)
                    {
                        this->head = newWagon;
                        newWagon->prev = NULL;
                        traverse = this->head;
                    }
                    else
                    {
                        traverse->next = newWagon;
                        newWagon->prev = traverse;
                        this->tail = newWagon;
                        traverse = traverse->next;
                    }
                    count++;
                }
            }
        }
    }

    else
    {
        materialNode *materialTraverse = traverse->material;
        wagonNode *prev = traverse;

        while (materialTraverse)
        {
            if (materialTraverse->weight == LIMIT && materialTraverse->id == material)
            {
                prev = traverse;
                traverse = traverse->next;
                materialTraverse = traverse->material;
            }
            else
            {
                materialTraverse = materialTraverse->next;
            }
        }
        if (!traverse)
        {
            // add new wagon until toBeAdded is 0
            while (weight > LIMIT)
            {
                if (toBeAdded <= LIMIT)
                {
                    toBeAdded = weight;
                }
                else
                {
                    toBeAdded = LIMIT;
                    weight -= 2000;
                }
            }
        }
        else
        {
            materialNode *materialTraverse = traverse->material;
            while (materialTraverse)
            {
                if (materialTraverse->id == material)
                {
                    isMaterialFound = true;
                    if (materialTraverse->weight + weight > LIMIT)
                    {
                        while (toBeAdded != 0)
                        {
                            cout << materialTraverse->id << endl;
                            int wagonId = traverse->wagonId;
                            if (toBeAdded >= LIMIT)
                            {
                                toBeAdded -= (LIMIT - materialTraverse->weight);
                                materialTraverse->weight = LIMIT;
                                while (toBeAdded != 0)
                                {
                                    wagonId++;
                                    if (toBeAdded >= LIMIT)
                                    {
                                        materialNode *newMaterial = new materialNode(material, LIMIT);
                                        wagonNode *newWagon = new wagonNode(wagonId, newMaterial);
                                        sort_material(newWagon);
                                        traverse->next = newWagon;
                                        newWagon->prev = traverse;
                                        this->tail = newWagon;
                                        traverse = traverse->next;
                                        toBeAdded = toBeAdded - LIMIT;
                                    }
                                    else
                                    {
                                        materialNode *newMaterial = new materialNode(material, toBeAdded);
                                        wagonNode *newWagon = new wagonNode(wagonId, newMaterial);
                                        sort_material(newWagon);
                                        if (traverse->next)
                                        {
                                            traverse = traverse->next;
                                            materialNode *newMaterialTraverse = traverse->material;
                                            materialNode *prevMaterial = traverse->material;

                                            while (newMaterialTraverse)
                                            {
                                                prevMaterial = newMaterialTraverse;
                                                newMaterialTraverse = newMaterialTraverse->next;
                                            }

                                            materialNode *newMaterial = new materialNode(material, toBeAdded);
                                            prevMaterial->next = newMaterial;
                                            newMaterial->prev = prevMaterial;
                                            sort_material(newWagon);
                                            toBeAdded = 0;
                                        }
                                        else
                                        {
                                            traverse->next = newWagon;
                                            this->tail = newWagon;
                                            newWagon->prev = traverse;
                                            traverse = traverse->next;
                                            toBeAdded = 0;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                toBeAdded = materialTraverse->weight - (LIMIT - weight);
                                materialTraverse->weight = LIMIT;
                                wagonId++;
                                materialNode *newMaterial = new materialNode(material, toBeAdded);
                                wagonNode *newWagon = new wagonNode(wagonId, newMaterial);
                                sort_material(newWagon);

                                traverse->next = newWagon;
                                newWagon->prev = traverse;
                                this->tail = newWagon;
                                toBeAdded = 0;
                            }
                        }
                    }
                    else
                    {
                        materialTraverse->weight += weight;
                    }
                }
                materialTraverse = materialTraverse->next;
            }

            if (!isMaterialFound)
            {
                wagonNode *previous = this->head;
                traverse = this->head;
                if (toBeAdded < LIMIT)
                {
                    materialNode *materialTraverse = traverse->material;
                    materialNode *prevMaterial = traverse->material;

                    while (materialTraverse)
                    {
                        prevMaterial = materialTraverse;
                        materialTraverse = materialTraverse->next;
                    }
                    materialNode *newMaterial = new materialNode(material, toBeAdded);
                    prevMaterial->next = newMaterial;
                    newMaterial->prev = prevMaterial;
                    sort_material(previous);
                }
                else
                {
                    int count = 0;
                    while (toBeAdded != 0)
                    {
                        if (traverse)
                        {
                            if (toBeAdded > LIMIT)
                            {
                                materialNode *newMaterialTraverse = traverse->material;
                                materialNode *prevMaterial = traverse->material;

                                while (newMaterialTraverse)
                                {
                                    prevMaterial = newMaterialTraverse;
                                    newMaterialTraverse = newMaterialTraverse->next;
                                }
                                materialNode *newMaterial = new materialNode(material, LIMIT);
                                prevMaterial->next = newMaterial;
                                newMaterial->prev = prevMaterial;
                                sort_material(traverse);
                                toBeAdded -= LIMIT;
                            }
                            else
                            {
                                materialNode *newMaterialTraverse = traverse->material;
                                materialNode *prevMaterial = traverse->material;

                                while (newMaterialTraverse)
                                {
                                    prevMaterial = newMaterialTraverse;
                                    newMaterialTraverse = newMaterialTraverse->next;
                                }
                                materialNode *newMaterial = new materialNode(material, toBeAdded);
                                prevMaterial->next = newMaterial;
                                newMaterial->prev = prevMaterial;
                                sort_material(traverse);
                                toBeAdded = 0;
                            }
                            previous = traverse;
                            count++;
                            traverse = traverse->next;
                        }
                        else
                        {
                            if (toBeAdded > LIMIT)
                            {
                                materialNode *newMaterial = new materialNode(material, LIMIT);
                                wagonNode *newWagon = new wagonNode(count+1, newMaterial);


                                previous->next = newWagon;
                                this->tail = newWagon;
                                sort_material(newWagon);
                                toBeAdded -= LIMIT;
                            }
                            else
                            {
                                materialNode *newMaterial = new materialNode(material, toBeAdded);
                                wagonNode *newWagon = new wagonNode(count+1, newMaterial);

                                previous->next = newWagon;
                                newWagon->prev = previous;
                                this->tail = newWagon;
                                sort_material(newWagon);
                                toBeAdded = 0;
                            }
                        }
                    }
                }
            }
        }
    };
};

void Train::deleteFromWagon(char material, int weight){
    //FILL THIS FUNCTION ACCORDINGLY

    int toBeRemoved = weight;
    wagonNode *traverse = this->tail;
    materialNode *traverseMaterial = traverse->material;
    
    while(toBeRemoved!=0){
        if(traverse->material == NULL){
            wagonNode* temp = traverse->prev;
            traverse->prev->next = NULL;
            delete traverse;
            traverse = temp;
            traverseMaterial = traverse->material;
        }
        else if(traverseMaterial == NULL){
            traverse = traverse->prev;
            traverseMaterial = traverse->material;
        }
        else if(traverseMaterial->id == material){
            if(toBeRemoved > traverseMaterial->weight){
                toBeRemoved -= traverseMaterial->weight;
                traverseMaterial->weight = 0;
                
                if(traverseMaterial->prev != NULL){
                    traverseMaterial->prev->next = NULL;
                    delete traverseMaterial;
                }
                else{
                    traverse->material = NULL;
                    delete traverseMaterial;
                }
            }
            else{
                traverseMaterial->weight -= toBeRemoved;
                toBeRemoved = 0;

                if(traverseMaterial->weight == 0){
                    if(traverseMaterial->prev != NULL){
                        traverseMaterial->prev->next = NULL;
                        delete traverseMaterial;
                    }
                    else{
                        traverse->material = NULL;
                        delete traverseMaterial;
                    }
                }
            }
        }
        else{
            traverseMaterial = traverseMaterial->next;
        }
    }

    if (traverse->material == NULL){
        if(traverse->prev != NULL){
            traverse->prev->next = NULL;
            wagonNode* temp = traverse->prev;
            delete traverse;
            traverse = temp;
        }else{
            this->head = NULL;
            delete traverse;
        }
    }
    
};

void Train::printWagon()
{
    wagonNode *tempWagon = head;

    if (tempWagon == NULL) 
    {
        cout << "Train is empty!!!" << endl;
        return;
    }

    while (tempWagon != NULL)
    {
        materialNode *tempMat = tempWagon->material;
        cout << tempWagon->wagonId << ". Wagon:" << endl;
        while (tempMat != NULL)
        {
            cout << tempMat->id << ": " << tempMat->weight << "KG, ";
            tempMat = tempMat->next;
        }
        cout << endl;
        tempWagon = tempWagon->next;
    }
    cout << endl;
};
