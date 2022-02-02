/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 14/12/2021 */
/*After the submitting hw, some parts that not working correctly and unneccessary are commented out*/

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
    int i = 0;                                                  //set i as 0 (counter)
    bool found = false;                                         //flag for the check that the wanted token is found or not
    while ( i < this->token_count && (!found))                                    //while arr[i] is not null and found is false
    {
        if (arr[i].symbol == elem)                              //if the symbol is equal to elem(wanted symbol) then 
        {
            found = true;                                       //set found true
            break;                                           //return the index
        }
        i++;                                                    // otherwise increment i
    }
    if (!found)                                                 //if the wanted token couldnt be found
    {
        return -1;                                              //return -1
    }
    return i;
}

void Huffman::find_frequencies()
{
    ifstream file_obj; //object to read file
    file_obj.open("../eval.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("eval.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }

    int i = 0;                                                  //iteretör for the while lopp


    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);
        // YOU HAVE TO COMPLETE THIS PART
        Token new_token;
        new_token.symbol = symbol;                                 //giving token's symbol 
        new_token.count = 1;                                       //initializing the count 
        bool flag_added = false;                                    //set a flag to false initially (to understand its added or not)
        if(i== 0){                                      //if token array is empty add the first element
            this->token_array[i].count = new_token.count;                           //set new token as first element of token array
            this->token_array[i].symbol = new_token.symbol;
            flag_added = true;                                      //set flag as true
            i++;
        }                                                           //otherwise
        int a = 0;
        while (!flag_added && !(this->token_array[a].symbol == ""))                     //go into loop until finding that token in the list
        {
            if(new_token.symbol==this->token_array[a].symbol){                //if token found then 
                this->token_array[a].count = token_array[a].count + 1;    //then increment count by 1(calculate frequency)
                flag_added = true;                                  //set flag as true
            }
            a++;                                                    //increment the loop counter
        }
        if(!flag_added){                                            //if its not in the list
            this->token_array[i].count = new_token.count;                           //add the token end of the list
            this->token_array[i].symbol= new_token.symbol;
            i++;
        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
	// YOU HAVE TO COMPLETE THIS PART
    /*
    Node* traverse = this->head;                     //initiliaze the traverse node
    Node* pre_traverse = this->head;                 //initiliaze the pre_traverse node

    bool pushed = false;                                            //create a flag, initialize with false

    if (!traverse)                                                  //if head is null
    {
        this->head  = newnode;                                   //add to beginning
        pushed = true;                                              // set flag to true
    }

    while (traverse && !pushed)                                     //if traverse is not null and pushed is false
    {
        if (traverse->token.count > newnode->token.count)          //then compare newnode token count with traverse token count 
        {
            
            if (traverse == pre_traverse)                           //if it suppose to be added at head 
            {
                newnode->next = this->head->next;                        //new node next
                this->head = newnode;                              //then set head
                pushed = true;                                          //set pushed true
            }else{
                newnode->next = traverse;                         //set newnode next to traverse next 
                pre_traverse->next = newnode;                           //set pretraverse next to newnode
                pushed = true;                                          //set pushed true
            }

        }else{
            pre_traverse = traverse;                              //move the pretraverse node
            traverse = traverse->next;                                  //move the traverse node
        }
    }

    if (!pushed && !traverse)                                       //if the traverse traversed the whole list and the node still is not added
    {
        pre_traverse->next = newnode;                                        //then add and of the list
        pushed = true;                                              //set pushed true
    }
    */
        if(head == NULL){      //if head does not exist
        head = newnode;
    }    
    else{
        if(newnode->token.count < this->head->token.count){
            newnode->next = head;
            head = newnode;
        }
        else{
            Node* iterator = head;
            while(iterator->next != NULL && iterator->next->token.count < newnode->token.count){
                iterator = iterator->next;
            }
            newnode->next = iterator->next;
            iterator->next = newnode;
        }
    }
}

Node* PriorityQueue::pop()
{
    // YOU HAVE TO COMPLETE THIS PART

    Node* temp = this->head;                         //initiliaze the temp node

    if (!this->head)                                 //if head is null
    {
        cerr<<"the token list is empty"<<endl;                      //send an error
    }
    
    this->head = this->head->next;                     //set head to second node
    temp->next = NULL;                                          //set temp next to null

    return temp;                           //if its not return first node 
}

void Huffman::get_priority_queue()
{
    // YOU HAVE TO COMPLETE THIS PART
    int i = 0;                                                      //loop counter
    while (!(this->token_array[i].symbol == ""))                                    //while token array [i] is not 0
    {
        Node* new_node = new Node;                                              //create new node
        new_node->token.count = this->token_array[i].count;                     //initialize with token array [i]
        new_node->token.symbol = this->token_array[i].symbol;
        new_node->token.code = '\0';
        this->priority_queue.push(new_node);                        //push into priority_queue
        i++;                                                        //increment i
    }
    this->token_count = i;                                          //update the token count
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    // YOU HAVE TO COMPLETE THIS PART
    Node* merged_node = new Node;                                           //create new node

    merged_node->token.symbol = node1->token.symbol + node2->token.symbol;    //set the merged node token symbol
    merged_node->token.count = node1->token.count + node2->token.count;     //set the merged node token count
    
    merged_node->left = node1;                                              //set the merged node left to node2
    merged_node->right = node2;                                             //set the merged node left to node1

    return merged_node;                                                     //return the merged node
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    // YOU HAVE TO COMPLETE THIS PART 

    while (this->priority_queue.head->next)                                 //while the head next is not null
    {
        Node* node1 = this->priority_queue.pop();                           //pop the first node
        Node* node2 = this->priority_queue.pop();                           //pop the second
        
        this->priority_queue.push(this->huffman_binary_tree.merge(node1,node2));                    //merge them and push back
    }

    this->huffman_binary_tree.root = this->priority_queue.head;             //finally after the last merge, head equals to root

}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    // YOU HAVE TO COMPLETE THIS PART
    // A RECURSIVE FUNCTION APPENDS CODEPART STRING 1 OR 0 ACCORDING TO THE HUFFMAN BINARY TREE
    
    string codepart_R = codepart;                                       //codepart_r goes for the right child
    if (!traversal->left)                                                   //Since this is a complete tree that every parent either has 2 child or none
    {                                                                       //then iff traversel left is null then return

        int index = this->findindex(this->token_array,traversal->token.symbol);
        this->token_array[index].code = codepart;

    }else{

        traversal->left->token.code = codepart + '0';                       //update the left token code
        codepart = traversal->left->token.code;                             //update tokencodepart

        this->get_codes(traversal->left, codepart);                         //send back to func

    
        traversal->right->token.code = codepart_R + '1';                      //update the left token code
        codepart_R = traversal->right->token.code;                            //update tokencodepart

        this->get_codes(traversal->right, codepart_R);                        //send back to func
    }

}
/*
void Huffman::updateTokkenArray(Node* start, int target){                   //take the starting node and (token array) index of symbol as arguments 

    string symbol = this->token_array[target].symbol;                       //to do post order search, take the symbol 
    if (start)                                                           //while start is not null
    {
        if(start->token.symbol == symbol){                                  //if the token's symbol in the huffman tree matches with the symbol wanted
            this->token_array[target].code = start->token.code;             //update the code of token in the token array
            return;                                                         // return
        }
        this->updateTokkenArray(start->left, target);                       //if not then search left child
        this->updateTokkenArray(start->right, target);                      //and right child afterwards
    }
    
}
*/

string Huffman::return_code(string target)
{

    int index = findindex(token_array,target);
    //if(token_array[index].code.empty()){                                      //check if the code of token that in the token array is updated or not
    //    this->updateTokkenArray(this->huffman_binary_tree.root, index);     //if its null then, set the code
    //}
    return token_array[index].code;                                         //return it
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++){
       // if(token_array[i].code.empty()){                                      //check if the code of token that in the token array is updated or not
        //    this->updateTokkenArray(this->huffman_binary_tree.root, i);     //if its null then, set the code
        //}
        bit_required_after += token_array[i].count * token_array[i].code.length();
    }
    return bit_required_before / bit_required_after;
}
