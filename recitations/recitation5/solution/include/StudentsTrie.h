/* @Author
Student Name: Namig Samadov
Student ID: 150190912
E-mail: samadov19@itu.edu.tr
Date: 28.12.2021
*/
// PLEASE DO NOT REMOVE DECLARED VARIBLES AND FUNCTIONS OF CLASSES, 
// IF YOU PREFER, YOU CAN ADD NEW ONES
#ifndef _H
#define _H

#include <string> 
using namespace std;

#define MAX_CHILDREN 10 // Each student ID consists of a sequence of digits: 0-9 

class TrieNode{
        char digit;   // Current Digit
        TrieNode* children[MAX_CHILDREN];   // Next Digit(s) 
        friend class StudentsTrie;
        int count = 0;

    public:
        TrieNode(const char& digit);
        int search(char);
};

class StudentsTrie{
        TrieNode *root;

    public: 

        StudentsTrie     ( const string& file_name  ); // Construct a StudentsTrie using the records in 'file_name' 
        void insert_id   ( const string& student_id ); // Insert a student ID into the StudentsTrie 
        void print_trie  (                          ); // Print Student IDs in the StudentsTrie in ascending order 
        void print_trie  ( TrieNode* node, string s);  // Print Student IDs in the StudentsTrie in ascending order
        ~StudentsTrie    (                          ); // StudentsTrie Destructor
};

#endif


