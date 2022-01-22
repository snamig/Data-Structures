/* @Author
Student Name: Namig Samadov
Student ID : 150190912
Date: 26.10.2021 */
#include <iostream> 
#include <stdlib.h>

#include "linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {



	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows

    LinkedList newLinkedList;

    // We need to read the data from input.txt first
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");

    char ch;
    while ((ch = fgetc(fp)) != EOF){
        if(ch!='\n') newLinkedList.add_element(ch);
    }
    fclose(fp);
 


    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();


    return EXIT_SUCCESS;
}