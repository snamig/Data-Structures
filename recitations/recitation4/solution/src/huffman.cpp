/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 14.12.2021 */
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

int Huffman::findindex(Token *arr,string elem){

	// YOU HAVE TO COMPLETE THIS PART
	// THIS FUNCTION RETURNS THE INDEX OF STRING ON TOKEN ARRAY, IF STRING IS NOT IN TOKEN ARRAY, RETURNS -1

    for(int i = 0; i < this->token_count; i++){
        if (arr[i].symbol == elem)   return i;
    }

    return -1;
}

void Huffman::find_frequencies(){
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }

    while (file_obj.get(symbol)) {
        string s;
        s.push_back(symbol);
        // YOU HAVE TO COMPLETE THIS PART

        index = this->findindex(this->token_array, s);
        if(index != -1)    this->token_array[index].count++;

        else{
            this->token_array[this->token_count].symbol = s;
            this->token_array[this->token_count].count = 1;
            this->token_count++;
        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue(){
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode){
	// YOU HAVE TO COMPLETE THIS PART
    Node *trav = this->head;
    Node *prev = this->head;
    if(trav == NULL){
        this->head = newnode;
        this->head->next = NULL;
    }
    else{
        while (trav->token.count > newnode->token.count){
            if(trav->next != NULL){
                prev = trav;
                trav = trav->next;
            }
            else break;
        }
        if(trav->token.count <= newnode->token.count){
            if(trav == this->head){
                newnode->next = trav;
                this->head = newnode;
            }
            else{
                newnode->next = trav;
                prev->next = newnode;
            }
        }
        else trav->next = newnode;
    }
    this->token_count++;
}

Node* PriorityQueue::pop(){
    // YOU HAVE TO COMPLETE THIS PART
    Node *trav = this->head;
    Node *prev = trav;

    while (trav->next != NULL){
        prev = trav;
        trav = trav->next;
    }
    prev->next = NULL;
    token_count--;
    return trav;

}

void Huffman::get_priority_queue(){
    // YOU HAVE TO COMPLETE THIS PART  
    for(int i = 0; i < this->token_count; i++){
        Node *node = new Node();
        node->token = token_array[i];  
        this->priority_queue.push(node);
    }
    // priority_queue.sort();
}

HuffmanBinaryTree::HuffmanBinaryTree(){
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2){
    // YOU HAVE TO COMPLETE THIS PART
    Node *node = new Node();
    node->token.symbol = node1->token.symbol + node2->token.symbol;
    node->token.count = node1->token.count + node2->token.count;
    node->left = node1;
    node->right = node2;
    return node;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal){
    if(traversal!=NULL) {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree(){
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree(){
    // YOU HAVE TO COMPLETE THIS PART 
    while(priority_queue.token_count > 1){
        Node *temp1 = priority_queue.pop();
        Node *temp2 = priority_queue.pop();
        priority_queue.push(huffman_binary_tree.merge(temp1, temp2));
    }
    huffman_binary_tree.root = priority_queue.head; 
}

void Huffman::get_codes(Node *traversal,string codepart){    
    // YOU HAVE TO COMPLETE THIS PART
    // A RECURSIVE FUNCTION APPENDS CODEPART STRING 1 OR 0 ACCORDING TO THE HUFFMAN BINARY TREE
    
    if(traversal->left == NULL && traversal->right == NULL){
        traversal->token.code = codepart;
        int index = findindex(token_array,traversal->token.symbol);
        token_array[index].code = codepart;
    }

    if(traversal->left != NULL) get_codes(traversal->left, codepart + "0");
    if(traversal->right != NULL) get_codes(traversal->right, codepart + "1");
}

string Huffman::return_code(string target){
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio(){
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
