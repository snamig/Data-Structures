/* @Author
Student Name: Namig Samadov
Student ID : 15019012
Date: 08.11.2021 */
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
bool is_number(char);

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
// Here I added a new function to check if the character we get is an integer or not 
// We will need to use it while pushing to postfix and stack
bool is_number(char a){
    if(a != '/' && a != '*' && a != '+' && a != '-')    return true;
    return false;
}

// As all the instructions were clear as pseudocode I just followed the instructions

void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;
    // *********************Fill this method 
    int size = infix.length();
    for(int i = 0; i < size; i++){
        if(is_number(infix[i])){
            postfix.push_back(infix[i]);
        }
        else{
            if(s.empty()){
                s.push(infix[i]);
            }
            else{

                    // I have noticed a problem on higher priority function, as this function implemented as if(first=='*' || first=='/') it considers * has higher priority than /
                    // So I added another checker here in order to solve the problem.
                    bool temp = false;
                    if ((infix[i] == '*' && s.top() == '/') || (infix[i] == '/' && s.top() == '*')) temp = true;
                    else if((infix[i] == '+' && s.top() == '-') || (infix[i] == '-' && s.top() == '+')) temp = true;

                if(higher_priority(infix[i],s.top()) && !temp){
                    s.push(infix[i]);
                }
                else{
                    char temp = s.top();
                    while(higher_priority(temp,infix[i])){
                        s.pop();
                        postfix.push_back(temp);
                        if(s.empty()){
                            break;
                        }
                        temp = s.top();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }
    while(!s.empty()){
        char temp = s.top();
        postfix.push_back(temp);
        s.pop();
    }
}


bool higher_priority(char first,char second){
    if(first=='*' || first=='/')
        return true;
    else if(second=='+' || second=='-')
        return true;
    else return false;
}

double eval_postfix(string expr){
    stack<double> s;
    double first, second;
    // *********************Fill this method 
    int size = expr.length();
    for(int i = 0; i < size; i++){
        if(is_number(expr[i])){
            // it is for converting a character to a double there is a 48 difference between ASCII value of the integers and them
            s.push((int)expr[i] - 48);
        }
        else{
            first = s.top();
            s.pop();
            second = s.top();
            s.pop();
            // I could not understand why it did not work as expected like "evaluate(first, second, expr[i])" I just changed their places and it worked lol
            s.push(evaluate(second, first, expr[i]));
        }
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
