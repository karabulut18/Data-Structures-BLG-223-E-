/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 9/11/2021*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

void infix_to_postfix(string,string&);
bool higher_priority(char,char);
double eval_postfix(string);
double evaluate(double,double,char);

int main(){
    string infix;
    string postfix;
    bool is_exit = false;

    while(!is_exit)
    {
        cout<<"Input the expression in infix: ";
        cin>>infix;

        if (infix == "E" || infix == "e") 
            is_exit = true;

        else
        {
            infix_to_postfix(infix, postfix);
            cout<<postfix<<endl;
            cout<<setprecision(2)<<fixed<<eval_postfix(postfix)<<endl;
        }
        
        cin.clear();
        cin.ignore();
        infix.clear();
        postfix.clear();

    }
    return EXIT_SUCCESS;
}

void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;
    // *********************Fill this method
    int i = 0; 
    while (infix[i])
    {
        if(infix[i]>='0' && infix[i]<='9'){

            postfix.push_back(infix[i]);
        }else{
            if(!s.empty()){
                if(higher_priority(infix[i],s.top())){
                    s.push(infix[i]);
                }
                else{ 
                    while(!higher_priority(infix[i],s.top()))
                    {
                        postfix.push_back(s.top());
                        s.pop();
                        if (s.empty()) break;
                    }
                    s.push(infix[i]);
                } 
            }
            else{
                s.push(infix[i]);
            }
        }
        i++;
    }

    while (!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }
};




bool higher_priority(char first,char second){
    /*
    if(first=='*' || first=='/')
        return true;
    else if(second=='+' || second=='-')
        return true;
    else return false;
*/
    if ((first=='*' || first=='/')&&(second=='+' || second=='-'))
    {
        return true;
    }
    else return false;

}

double eval_postfix(string expr){
    stack<double> s;
    double first, second;
    // *********************Fill this method 
    int i = 0;
    while (expr[i])
    {
        if (expr[i]>='0' && expr[i]<='9')
        {   
            double a = expr[i]-48;
            cout<<a<<" ";
            s.push(a);
        }
        else{
            first = s.top();
            s.pop();
            second = s.top();
            s.pop();
            s.push(evaluate(second,first, expr[i]));
        }
        i++;
    }
    
    return s.top();
}

double evaluate(double first,double second,char c){
    switch(c){
        case '*':
            return first*second;
        case '+':
            return first+second;
        case '-':
            return first-second;
        case '/':
            return first/second;
        default:
            return 0;
    }
}
