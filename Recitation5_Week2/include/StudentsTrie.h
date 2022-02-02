/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 28/12/2021 */
// PLEASE DO NOT REMOVE DECLARED VARIBLES AND FUNCTIONS OF CLASSES, 
// IF YOU PREFER, YOU CAN ADD NEW ONES
#ifndef _H
#define _H

#include <string>
using namespace std;

#define MAX_CHILDREN 10 // Each student ID consists of a sequence of digits: 0-9 

class TrieNode{
        char digit = '\0';   // Current Digit (initially null)
        TrieNode* children[MAX_CHILDREN];   // Next Digit(s) 
        friend class StudentsTrie;

    public:
        TrieNode(const char& digit);
};

class StudentsTrie{
        TrieNode *root;

    public:
        StudentsTrie     ( const string& file_name  ); // Construct a StudentsTrie using the records in 'file_name' 
        void insert_id   ( const string& student_id ); // Insert a student ID into the StudentsTrie 
        void print_trie  (                          ); // Print Student IDs in the StudentsTrie in ascending order
        void print_num   ( TrieNode*, string        ); // used in the print function
        ~StudentsTrie    (                          ); // StudentsTrie Destructor
};

#endif
