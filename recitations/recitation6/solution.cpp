/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 11.01.2022
*/


// Even though everything is correct after compiling on listDay function it did not passed calico test 
// Can you please double check my code

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <vector>
#include <bits/stdc++.h>   
#define MAX_SIZE 10000

// orders.txt should be opened

using namespace std;

string file_path;

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


// Did some research on internet to write compare and sort function
bool compare(pair<string, double>& x, pair<string, double>& y){
    return x.second > y.second;
}

void sort(map<string, double>& Map){

    // Declare vector of pairs
    vector<pair<string, double> > sortedMap;
  
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : Map) {
        sortedMap.push_back(it);
    }
  
    // Sort using comparator function
    sort(sortedMap.begin(), sortedMap.end(), compare);
  
    // Print the sorted value
    int i = 0;
    for (auto& it : sortedMap) {
        if(i > 4) break;
  
        cout << it.first << ' '
             << fixed << setprecision(2) << it.second;

        if(i <= 4) cout << endl;     

        // cout << "i = " << i << endl;
        i++;     
    }
}

void print_days(string day){
    cout << "5 products with the highest revenue for " << day << " are:" << endl;
}

void listProducts()
{
// *********************Fill this method 
    fstream infile;
    infile.open("orders.txt", ios::in);
    if(!infile.is_open()){
        cout << "File cannot be opened" << endl;
        return;
    }
    
    int count = 0;
    string product;
    double price, revenue, previous_revenue;
    int quantity;
    map<string ,double> mymap;

    string productArr[MAX_SIZE];

    // It is better to hold products in an array in order to find their revenues correctly according to the keys of map

    for(string data; infile >> data;){
        if(count > 3){         
            // Dealing with products here
            if(count %4 == 0){
                product = data;
                int iter = 0;

                if(productArr[0] == "") productArr[0] = product;

                while(productArr[iter] != ""){
                    if(productArr[iter] != product) iter++;
                    if(productArr[iter] == "") productArr[iter] = product;
                    if(productArr[iter] == product){
                        auto elem = mymap.find(product);
                        previous_revenue = elem->second;
                        break;
                    }
                }

            }
            // Dealing with prices here
            if(count %4 == 1){
                price = stod(data);
            }
            // Dealing with quantities here
            if(count %4 == 2){
                quantity = stoi(data);
                revenue = price * quantity;
                mymap[product] = revenue + previous_revenue;
                previous_revenue = 0;
            }
            // No need to deal with days on this part of the code
            // if(count %4 == 3){

            // }
        }
        count++;
    }

    cout<<"5 products with the highest revenue for total are:"<<endl;
    sort(mymap);

}


void listDay()
{
// *********************Fill this method 
    
    fstream infile;
    infile.open("orders.txt", ios::in);
    if(!infile.is_open()){
        cout << "File cannot be opened" << endl;
        return;
    }

    string dayArr[MAX_SIZE];
    int count = 0;
    int otherCounter = 0;
    string day, product;
    int quantity;
    double price, revenue;

    map<string, map<string, double>*> mymap;


    for(string data; infile >> data;){
        int tempCount = otherCounter;
        if(count > 3){
            if(count %4 == 0){
                product = data;
            }
            if(count %4 == 1){
                price = stod(data);
            }
            if(count %4 == 2){
                quantity = stoi(data);
            }
            if(count %4 == 3){
                day = data;
                otherCounter++;
            }
            
        }

        if(otherCounter != tempCount){
            revenue = quantity * price;
            if(mymap.find(day) != mymap.end()){
                map<string, double> *tempMap = mymap[day];
                if(tempMap->find(product) != tempMap->end()){
                    tempMap->at(product) += revenue;
                }
                else{
                    tempMap->insert(pair<string, double>(product, revenue));
                }
            }
            else{
                map<string, double> *tempMap = new map<string, double>;
                mymap.insert(pair<string, map<string, double>*>(day, tempMap));
                tempMap->insert(pair<string, double>(product, revenue));
            }
        }


        count++;
    }
    map<string, double> *tempMap = mymap["Monday"];
    print_days("Monday");
    sort(*tempMap);

    tempMap = mymap["Sunday"];
    print_days("Sunday");
    sort(*tempMap);

    tempMap = mymap["Tuesday"];
    print_days("Tuesday");
    sort(*tempMap);

    tempMap = mymap["Wednesday"];
    print_days("Wednesday");
    sort(*tempMap);

    tempMap = mymap["Thursday"];
    print_days("Thursday");
    sort(*tempMap);

    tempMap = mymap["Friday"];
    print_days("Friday");
    sort(*tempMap);

    tempMap = mymap["Saturday"];
    print_days("Saturday");
    sort(*tempMap);
  
}