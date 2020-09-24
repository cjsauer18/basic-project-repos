#include "AdjacencyList.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//Program Name: Project 3: Dynamic Minimum Spanning Trees
//Programmer Name: Chris Sauer
//Description: Design a program that reads in a list of nodes and edges that make up a connected, undirected graph and construct an adjacency list. The graph must be checked for completion and proper edge insertion, as well as provide user editing ability which the program must verify as correct, after which a minimum spanning tree and corresponding adjacency list is calculated and displayed.
//Date Created: July 27th, 2020


void menu(){
    cout << "--------MENU----------" << endl;
    cout << "(1) Edit Current Graph" << endl;
    cout << "(2) Finish " << endl;
    cout << "----------------------" << endl;
    cout << "Selection: ";
}

//Description: Main function acts as program flow. Prompts user to enter initial file inputs and stops program if valid conditions are not met. Displays action menu to user if more additions to the graph are to be made.
//Pre-condition: User must supply file names.
//Post-condition: Initializes program, and halts upon user input.
int main() {

    cout << "MST Grapher, Welcome!" << endl << endl;
    string input, output, selection;
    AdjacencyList graph;
    cout << "Enter filename to open: ";
    cin >> input;
    cout << endl;
    cout << "Enter filename to output: ";
    cin >> output;
    cout << endl;
    graph.setFileNames(input, output);
    cout << "Initializing Graph" << endl;
    if(graph.readInInitial() == false){
        cout << "Invalid filename" << endl << "Halting program" << endl;
        return 0;
    }

    while(true){
        menu();
        cin >> selection;
        if(selection == "1"){
            int status = graph.readInUserChanges();
            if(status == AdjacencyList::valid){
                graph.outputCurrentState();
            }else if(status == AdjacencyList::shortestPath){
                continue;
            }
            else {
                cout << "There was a problem with your input!" << endl;
            }
        }else if(selection == "2"){
            break;
        }else{
            cin.ignore();
            cin.clear();
            cout << endl << "Invalid option!" << endl << endl;
        }
    }
}
