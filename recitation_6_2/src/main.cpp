/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 10/01/2022 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>

using namespace std;

string file_path;

string days[7]={"Monday","Sunday","Tuesday","Wednesday","Thursday","Friday","Saturday"}; //days array

bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();



int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;


}


void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "D: List 5 products with the highest revenue for each day" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
            terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
// *********************Fill this method 
    fstream file;                       //create file object
    file.open(file_path,ios::in);       //open file
    
    string line;                        //create an empty sting to read file line by line
    
    bool first = true;
    
    double pro_price, quantity;
    string pro_name="", day="";

    map <string, double> lispro;

    while (getline(file,line))
    {
        stringstream input(line);                   
        input>>pro_name>>pro_price>>quantity>>day;  //read the values
        //map<string, double>::iterator is_there;
        if (first)
        {
            first = false;
            continue;
        }
        else
        {
            auto is_there = lispro.find(pro_name);           //check if it is already added
            if(!(is_there == lispro.end())){
                is_there->second = is_there->second + (pro_price*quantity); //if it is then, add the revenue
            }else{
                lispro.insert(pair<string, double>(pro_name,(pro_price*quantity)));  //if its not added, add the item
            }
        }
    }
    file.close();       //close the file
    
    map<string, double>::iterator iter;
    multimap<double, string> sorted_list;
    for (iter = lispro.begin(); iter != lispro.end(); iter++)
    {
        sorted_list.insert(pair<double, string>(iter->second, iter->first));
    }

    cout<<"5 products with the highest revenue for total are:"<<endl;
    
    map<double, string>::reverse_iterator it;
    int check = 0;
    for (it = sorted_list.rbegin(); it != sorted_list.rend(); it++)
    {
        cout<<it->second<<" ";
        cout<<fixed<<setprecision(2)<<it->first<<endl;

        check++;
        if (check == 5)break;
    }
    
}



void listDay()
{
// *********************Fill this method 
    fstream file;                       //create file object
    file.open(file_path,ios::in);       //open file
    
    string line;                        //create an empty sting to read file line by line
    
    bool first = true;
    
    double pro_price, quantity;
    string pro_name="", day="";

    map <string, double> list_withd[7];

    while (getline(file,line))
    {
        stringstream input(line);                   
        input>>pro_name>>pro_price>>quantity>>day;  //read the values
        //map<string, double>::iterator is_there;
        if (first)
        {
            first = false;
            continue;
        }
        else
        {
            int i = 0;
            for (; i <7; i++)
            {
                if(!days[i].compare(day)){
                    break;
                };
            }
    
            auto is_there = list_withd[i].find(pro_name);           //check if it is already added
            if(!(is_there == list_withd[i].end())){
                is_there->second = is_there->second + (pro_price*quantity); //if it is then, add the revenue
            }else{
                list_withd[i].insert(pair<string, double>(pro_name,(pro_price*quantity)));  //if its not added, add the item
            }                                                                 
        }
    }
    file.close();       //close the file

        
    map<string, double>::iterator iter;
    multimap<double, string> sor_list_withd[7];
    int a = 0;
    while (a<7)
    {        
        for (iter = list_withd[a].begin(); iter != list_withd[a].end(); iter++)
        {
            sor_list_withd[a].insert(pair<double, string>(iter->second, iter->first));
        }
        a++;
    }

    a = 0;
    map<double, string>::reverse_iterator it;
    
    while (a<7)
    {   
        
        cout<<"5 products with the highest revenue for "<<days[a]<<" are:"<<endl;
        int check = 0;
        for (it = sor_list_withd[a].rbegin(); it != sor_list_withd[a].rend(); it++)
        {
            cout<<it->second<<" ";
            cout<<fixed<<setprecision(2)<<it->first<<endl;

            check++;
            if (check == 5)break;
        }
        a++;
    }
}