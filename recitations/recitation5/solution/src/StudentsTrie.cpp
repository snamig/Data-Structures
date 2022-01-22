/* @Author
Student Name: Namig Samadov
Student ID: 150190912
E-mail: samadov19@itu.edu.tr
Date: 28.12.2021
*/
#include <fstream>
#include <iostream>

#include "../include/StudentsTrie.h"

using namespace std;

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};

// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for  input file
    string current_student_id;

    root = new TrieNode('r'); 

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

int TrieNode::search(char dgt){
   int i = 0;

   while(i < count && children[i]->digit != dgt)   i++;
   
   if(i >= count ) return -1;
   else return i;
}

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id ) {
   // IMPLEMENT THIS METHOD

   TrieNode* location = root;

   for(int i = 0; i < student_id.size(); i++){
      int index = location->search(student_id[i]);
      
      if(index == -1){
         TrieNode* newNode = new TrieNode(student_id[i]);
         int indexToInsert = 0;
         while (indexToInsert < location->count){
            if(location->children[indexToInsert]->digit > newNode->digit){
               break;
            }
            else{
               indexToInsert++;
            }
         }
         
         for (int j = location->count-1; j >= indexToInsert; j--){
            location->children[j+1] = location->children[j]; 
         }
         
         location->children[indexToInsert] = newNode;
         location->count++;
         location = location->children[indexToInsert];
      }

      else{
         location = location->children[index];
      }

   }
}; 

// Print Student IDs in Trie in ascending order 
void StudentsTrie::print_trie(){
   // IMPLEMENT THIS METHOD
   print_trie(this->root,"");
}

void StudentsTrie::print_trie(TrieNode* node, string s){
   for (int i = 0; i < node->count; i++){
      s.push_back(node->children[i]->digit);
      if(node->children[i]->count != 0){
         print_trie(node->children[i],s);
      }
      else{
         cout<<s<<" ";
      }
      s.pop_back();
   }
}

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};