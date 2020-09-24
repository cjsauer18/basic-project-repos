#include <string>
#include "AdjacencyList.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;




//HELPERS

//Description: User input helper functions. Each is overloaded when called for different inputs. Provide cin error checking and handling.
//Pre-condition: Must be called from a method and supply a reference to a variable to set with values.
//Post-condition: Returns value(s) to varaible parameter(s) via reference.
void userChoice(char& selection){
    char inputLine[10];
    string choice;
       while(true){
           cin.ignore();
           cin.clear();
           cout << "Enter selection: ";
           cin.get(inputLine, 5);
           stringstream buffer(inputLine);
           buffer >> choice;
           if(buffer.fail() || !buffer.eof()){
               cout << "Error, try entering that again" << endl;
               buffer.ignore();
               buffer.clear();
           }else{
               selection = choice[0];
               selection = toupper(selection);//case sensitive
               
               break;
           }
       }
}
void userInput(int& A, int& B){
    char inputLine[5];
    int a, b;
    while(true){
        cin.ignore();
        cin.clear();
        cout << "Enter vertices to calculate shortest path: " << endl;
        cin.get(inputLine, 5);
        
        stringstream buffer(inputLine);
        buffer >> a >> b;
        if(buffer.fail() || !buffer.eof()){
            cout << "Error, try entering that again" << endl;
            buffer.ignore();
            buffer.clear();
        }else{
            A = a;
            B = b;
            break;
        }
    }
}
void userInput(int& A, int& B, int& W){
    char inputLine[10];
    int a, b, w;
    
    while(true){
        cin.ignore();
        cin.clear();
        cout << "Enter edge (vertexA vertexB Weight): ";
        cin.get(inputLine, 6);
        stringstream buffer(inputLine);
        buffer >> a >> b >> w;
        if(buffer.fail() || !buffer.eof()){
            cout << "Error, try entering that again" << endl;
            buffer.ignore();
            buffer.clear();
        }else{
            A = a;
            B = b;
            W = w;
            break;
        }
    }
}


//Description: Filename setter.
//Pre-condition: User must provide input in main
//Post-condition: Sets private filename variables.
void AdjacencyList::setFileNames(string inputFile, string outputFile){
    inputFilename = inputFile;
    outputFilename = outputFile;
}


AdjacencyList::AdjacencyList(){}//default constructor


//Description: Recursive helper function to checkGraphIsConnected method.
//Pre-condition: checkGraphIsConnected must be called. Graph must exist.
//Post-condition: Sets values in boolean array to be used in parent function.
void AdjacencyList::traverse(int currentIndex, bool isVisited[]){
    isVisited[currentIndex] = true;
    const Vertex& currentVertex = mapOfVertices[currentIndex];
    for(int i = 0; i < currentVertex.correspondingEdges.size(); ++i){
        int nextAdjacentVertex = currentVertex.correspondingEdges[i].correspondingNode;
        if(isVisited[nextAdjacentVertex] == false){
            traverse(nextAdjacentVertex, isVisited);
        }
    }
}

//Description: Helper function to check if the graph is connected (all vertices can be reached)
//Pre-condition: Graph must be initialized with values in vertex map.
//Post-condition: Returns boolean status of connection state.
bool AdjacencyList::checkGraphIsConnected(){
    bool isVisited[numberOfVertices];
    for(int i = 0; i < numberOfVertices; ++i){
        isVisited[i] = false;
    }
    traverse(0, isVisited);
    for(int k = 0; k < numberOfVertices; ++k){
        if(isVisited[k] == false){
            return false;
        }
    }
    return true;
}


//Description: Method opens file provided by user and parses into respective variables. Method tests if the file name is correct, if the number of edges is maintained, and if the graph is connected. If all three cases prove true, function calls output helper function and displays initial list data, and MST data.
//Pre-condition: File format must be correct (if existing => first line must exist).
//Post-condition: Populates vertex map (adjacency list) and fixes any errors in the graph by prompting user to complete graph where needed.
bool AdjacencyList::readInInitial(){
    output.open(outputFilename);
    output << "Creating file from " + inputFilename << endl;
    output.close();
    string line; int nodeA; int nodeB; int weight; int count = -1;
    input.open(inputFilename);
    if(input.is_open()){
        cout << "file opened successfully!" << endl << endl;
    }else{
        output.open(outputFilename, ios::app);
        output << "Input file does not exist" << endl;
        output.close();
        input.close();
        return false;
    }
    while(getline(input, line)){
        stringstream buffer(line);
        if(count == -1){
            if(line[0] == ' ' || (!isdigit(line[0]))){
                cout << "Incorrect file format" << endl;
                output.open(outputFilename, ios::app);
                output << "Incorrect file format" << endl;
                output.close();
                return false;
            }
            count++;
            buffer >> numberOfVertices >> numberOfEdges;
            cout << numberOfVertices << " vertices, " << numberOfEdges << " edges" << endl;
            output.open(outputFilename, ios::app);
            output << numberOfVertices << " vertices, " << numberOfEdges << " edges" << endl;
            output << endl;
            output << "Edges: " << endl;
            output.close();
            cout << endl;
        }else{
            buffer >> nodeA; buffer >> nodeB; buffer >> weight;
            if(buffer.fail() || !buffer.eof()){
                output.open(outputFilename, ios::app);
                output << "Invalid data on line: " << count << endl;
                cout << "Invalid data on line: " << count << endl;
                output.close();
                buffer.clear();
                buffer.ignore();
                count++;
                continue;
            }
            output.open(outputFilename, ios::app);
            output << nodeA << " " << nodeB << " " << weight << " " << setw(5);
            output.close();
            cout << nodeA << " " << nodeB << " " << weight << " " << setw(5);
           
            int edgeStatus = addEdge(Edge(nodeA, nodeB, weight));
            if(edgeStatus != valid){
                numberOfEdges--;//must retract edge count from file when an edge is invalid and discarded
                writeErrorDescriptionToFile(edgeStatus, Edge(nodeA, nodeB, weight));//display error present in edge
            }else{
                count++;
            }
        }
    }
    //check complete (number of edges satisfied)
    if(count < numberOfEdges){
        
        cout << "Graph incomplete, enter edges to complete graph" << endl;
        output << "Graph incomplete, enter edges to complete graph" << endl;
        
          while(count < numberOfEdges){
              userInput(nodeA, nodeB, weight);//recieve input from user
              int edgeStatus = addEdge(Edge(nodeA, nodeB, weight));//add edge
              
              if(edgeStatus == valid){
                  count++;
              }else{
                  writeErrorDescriptionToFile(edgeStatus, Edge(nodeA, nodeB, weight));
              }
          }
    }
    //indicate initial file read is complete.
    output.open(outputFilename, ios::app);
    output << endl << "Initial Input Complete" << endl << endl << endl;
    output.close();
    cout << endl << "Initial Input Complete" << endl << endl << endl;
    input.close();
   // output.close();
    outputCurrentState();//output graph
    
    if(!checkGraphIsConnected()){//check if connected
        cout << "-----------------------" << endl;
        cout << "Graph is not connected" << endl;
        cout << "-----------------------" << endl;
        while(checkGraphIsConnected() != true){
            cout << "Add more edges until graph becomes connected"<< endl;
            userInput(nodeA, nodeB, weight);
            int edgeStatus = addEdge(Edge(nodeA, nodeB, weight));
            if(edgeStatus == valid){
                numberOfEdges++;
            }else{
                writeErrorDescriptionToFile(edgeStatus, Edge(nodeA, nodeB, weight));
            }
        }
        if(checkGraphIsConnected()){//confirm that graph is now connected before continuing.
            cout << "Graph is connected" << endl;
            output.open(outputFilename, ios::app);
            output << "Graph is connected" << endl;
            output.close();
        }
        outputCurrentState();//output current state
    }
    return true;
}

//Description: Helper method formats the graph output, and the MST output to the console and file. Method checks if MST can be calculated by verifying if the graph is connected. If so, MST data is also outputted.
//Pre-condition: Graph should be populated and connection state does not matter.
//Post-condition: Output to file and console the adajcency list(s) depending on if the graph is connected.
void AdjacencyList::outputCurrentState(){
    
    //this should handle the mst being less than 10, printing multiple iterations... etc.
    
    
    output.open(outputFilename, ios::app);
    output << endl;
    cout << endl;
    output << "Full graph has " << numberOfVertices << " vertices and " << numberOfEdges << " edges" << endl;
    output << "Adjacency List:" << endl << endl;
    cout << "Full graph has " << numberOfVertices << " vertices and " << numberOfEdges << " edges" << endl << endl;
    cout << "Adjacency List:" << endl << endl;
    for(int i = 0; i < mapOfVertices.size(); i++){
        output << "Node " << i << ": ";
        cout << "Node " << i << ": ";
        for(int j = 0; j < mapOfVertices[i].correspondingEdges.size(); j++){
            output << mapOfVertices[i].correspondingEdges[j];
            cout << mapOfVertices[i].correspondingEdges[j];
        }
        output << endl;
        cout << endl;
    }
    if(checkGraphIsConnected()){
        calculateMST();
        output << endl;
        cout << endl;
        output << "Minimum spanning tree graph has " << minSpanTreeVertices << " vertices and " << minSpanTreeEdges << " edges" << endl;
         cout << "Minimum spanning tree graph has " << minSpanTreeVertices << " vertices and " << minSpanTreeEdges << " edges" << endl;
        output << "Sum of MST: " << sumOfMinSpanningTree << endl << endl;
        output << "Minimum Spanning Tree Adjacency List: " << endl << endl;
        
        cout  << "Minimum Spanning Tree Adjacency List: " << endl << endl;
        for(int i = 0; i < MSTmap.size(); i++){
               output << "Node " << i << ": ";
           cout << "Node " << i << ": ";
            for(int j = 0; j < MSTmap[i].correspondingEdges.size(); j++){
                output << MSTmap[i].correspondingEdges[j];
                cout << MSTmap[i].correspondingEdges[j];
               }
               output << endl;
            cout << endl;
           }
        output << endl << endl;
        cout << endl << endl;
        cout << "Sum of MST: " << sumOfMinSpanningTree << endl << endl;
        if(numberOfVertices < 10){//displays iterations only if number of vertices is less than 10.
            for(int i = 0; i < spanningTree.size(); ++i){
                output << "Add Edge: " << spanningTree[i].second << " +"<< spanningTree[i].second.weight << " | Cumulative Sum: "<< spanningTree[i].first << endl;
                cout << "Add Edge: " << spanningTree[i].second << " +"<< spanningTree[i].second.weight << " | Cumulative Sum: "<< spanningTree[i].first << endl;
            }
        }
        cout << endl << endl;
        output << endl << endl;
        
    }
    
    output.close();
    output.clear();
}




//Description: Main edge check auxiliary function. Function takes in edge candidates supplied by user and input file and checks if the edges meet the requirements to be inserted.
//Pre-condition: Edge must be supplied, along with what type operation is being called (add, increment, decrement)
//Post-condition: Returns enumerated value corresponding to what error was detected (if any).
int AdjacencyList::checkValidity(Edge candidateEdge, int operation) {
    if((candidateEdge.primaryNode >= numberOfVertices || candidateEdge.primaryNode < 0) || (candidateEdge.correspondingNode >= numberOfVertices || candidateEdge.correspondingNode < 0) ){//if at least one vertex is not valid (exists)
        return invalidVertex;
    }
    if(candidateEdge.primaryNode == candidateEdge.correspondingNode){//use of edge comparator for increment/decrement methods to check if edge exists.
        return edgeNotFound;
    }
    if(candidateEdge.weight <= 0){//general negative weight check
        return negativeWeight;
    }
    if(operation != increment){
        for(int i = 0; i < mapOfVertices[candidateEdge.primaryNode].correspondingEdges.size(); i++){
               if(mapOfVertices[candidateEdge.primaryNode].correspondingEdges[i] == candidateEdge){//existing edge is found.
                   if(operation == addNew){//if addEdge calls this function
                       return duplicateFound;//existing edge is already present
                   }else{
                       //if an edge is being decremented, check if weight change is valid.
                       int currentWeight = mapOfVertices[candidateEdge.primaryNode].correspondingEdges[i].weight;
                       if(currentWeight - candidateEdge.weight <= 0){
                            return negativeWeight;
                        }else{
                            return valid;
                        }
                   }
               }
           }
    }
    return valid;
}


//Description: Method maintains the user interface by prompting the edit menu, and processes user input and distributes input to appropriate methods.
//Pre-condition: Input must be supplied from user. Graph must be initialized and certified valid, as well as connected.
//Post-condition: If user input passes the check function, a value is returned corresponding to success or failure. Edge is added/modified.
int AdjacencyList::readInUserChanges(){
    char selection;
    int nodeA; int nodeB; int weight;
    int status = valid;
    //menu
    cout << "---------------------------" << endl;
    cout << "(E) to add an edge" << endl;
    cout << "(I) to increment an edge" << endl;
    cout << "(D) to decrement an edge" << endl;
    cout << "(S) to find shortest path" << endl;
    cout << "---------------------------" << endl;
    
    userChoice(selection);//receive input for action selection.
    //echo all user inputs to output
    output.open(outputFilename, ios::app);
    if(selection != 'S'){
        userInput(nodeA, nodeB, weight);//receive input for edge selection
        output << selection << " " <<  nodeA << " " << nodeB << " " << weight << " " << setw(5);
    }else{
        userInput(nodeA, nodeB);//recieve input for shortest path selection
        output << selection << " " <<  nodeA << " " << nodeB << " " << setw(5);
        output << "Determine shortest path from "<< nodeA << " to " << nodeB << endl;
    }
    output.close();
    while(true){
        //call approprate methods
        if(selection == 'I'){
            status = incrementEdge(nodeA, nodeB, weight);
        }else if(selection == 'D'){
            status = decrementEdge(nodeA, nodeB, weight);
        }else if(selection == 'E'){
            status = addEdge(Edge(nodeA, nodeB, weight));
            if(status == valid){
                numberOfEdges++;
            }
        }else if(selection == 'S'){
            if(!(nodeA >= 0 && nodeA < numberOfVertices) && (nodeB >= 0 && nodeB < numberOfVertices)){
                output.open(outputFilename, ios::app);
                output << "Error, enter valid vertices to determine shortest path" << endl;
                cout << "Error, enter valid vertices to determine shortest path" << endl;
                output.close();
            }else{
                int distance = calculateShortestPath(nodeA, nodeB);
                output.open(outputFilename, ios::app);
                output << "Shortest distance from vertex " << nodeA << " to vertex " << nodeB << " is " << distance << endl;
                output.close();
                cout << "Shortest distance from vertex " << nodeA << " to vertex " << nodeB << " is " << distance << endl;
            }
        }else{
            status = invalidCommand;//command not recognized.
        }
    
        writeErrorDescriptionToFile(status, Edge(nodeA, nodeB, weight));//output proper action statement
        
        //if incrementing/decrementing and the action resulted in invalid vertices, reprompt user to enter valid vertices.
        if((status == invalidVertex || status == edgeNotFound) && selection == 'I'){
            cout << "Re-Enter valid edge vertices and weight to increment" << endl;
            userInput(nodeA, nodeB, weight);
        }else if((status == invalidVertex || status == edgeNotFound) && selection == 'D'){
            cout << "Re-Enter valid edge vertices and weight to decrement" << endl;
            userInput(nodeA, nodeB, weight);
        }else{
            break;
        }
        
    }
    return status;
}
//Description: Main edge add method. Takes in edge candidate and echos input to file. If edge is valid, edge is added to the map of vertices.
//Pre-condition: Candidate edge must be taken from user input.
//Post-condition: Returns error state from checkValid. If valid, edge is added and a status of 'valid' is returned.

int AdjacencyList::addEdge(Edge candidateEdge){
    //output action to screen
    cout << "add edge " << candidateEdge.primaryNode << " " << candidateEdge.correspondingNode << " with weight " << candidateEdge.weight << endl;
    output.open(outputFilename, ios::app);
    output << "add edge " << candidateEdge.primaryNode << " " << candidateEdge.correspondingNode << " with weight " << candidateEdge.weight << endl;
    output.close();
    
    int validStatus = checkValidity(candidateEdge, addNew);//depending on status, add edge to both respective vertices
    if(validStatus == valid){
        Edge correspondingEdge(candidateEdge.correspondingNode, candidateEdge.primaryNode, candidateEdge.weight);
        if(mapOfVertices.count(candidateEdge.primaryNode) == 0){
            //if vertex did not exist initially
            mapOfVertices[candidateEdge.primaryNode] = Vertex(candidateEdge, candidateEdge.primaryNode);//edge, vertex id
        }else{
            mapOfVertices[candidateEdge.primaryNode].correspondingEdges.push_back(candidateEdge);
        }
        //subsequent, equivalent vertex.
        if(mapOfVertices.count(correspondingEdge.primaryNode) == 0){
            mapOfVertices[correspondingEdge.primaryNode] = Vertex(correspondingEdge, correspondingEdge.primaryNode);
        }else{
            mapOfVertices[correspondingEdge.primaryNode].correspondingEdges.push_back(correspondingEdge);
        }
    }
    return validStatus;
}

//Description: Incrememnt method takes in an edge and echos output. If edge is valid, edge weight is incremented.
//Pre-condition: Graph must be initialized and verified. User must provide input.
//Post-condition: Returns enum status from checkValid. If valid, weight is incremented, otherwise no change.

int AdjacencyList::incrementEdge(int primaryVertex, int correspondingVertex, int weight){
    output.open(outputFilename, ios::app);
    output << "Increment edge " << primaryVertex << " " << correspondingVertex << " weight by " << weight << endl;//output action
    output.close();
    
    Edge candidateEdge(primaryVertex, correspondingVertex, weight);
    int validStatus = checkValidity(candidateEdge, increment);//depending on status, if valid loop through both edges (A,B and B,A) and set weight to new value.
    if(validStatus == valid){
        for(int i = 0; i < mapOfVertices[primaryVertex].correspondingEdges.size(); ++i){
            if(mapOfVertices[primaryVertex].correspondingEdges[i].correspondingNode == correspondingVertex){
                mapOfVertices[primaryVertex].correspondingEdges[i].weight += weight;
                break;
            }
        }
        for(int i = 0; i < mapOfVertices[correspondingVertex].correspondingEdges.size(); ++i){
            if(mapOfVertices[correspondingVertex].correspondingEdges[i].correspondingNode == primaryVertex){
                mapOfVertices[correspondingVertex].correspondingEdges[i].weight += weight;
                break;
            }
        }
    }
    return validStatus;
}
//Description: Decrement method takes in an edge and echos output. If edge is valid, edge weight is decremented.
//Pre-condition: Graph must be initialized and verified. User must provide input.
//Post-condition: Returns enum status from checkValid. If valid, weight is decremented, otherwise no change.
int AdjacencyList::decrementEdge(int primaryVertex, int correspondingVertex, int weight) {
    output.open(outputFilename, ios::app);
    output << "Decrement edge " << primaryVertex << " " << correspondingVertex << " weight by " << weight << endl;//output action
    output.close();
    
    Edge candidateEdge(primaryVertex, correspondingVertex, weight);
    //check if candidate edge is valid
    int validStatus = checkValidity(candidateEdge, decrement);
    if(validStatus == valid){//depending on status, if valid loop through both edges (A,B and B,A) and set weight to new value.
           for(int i = 0; i < mapOfVertices[primaryVertex].correspondingEdges.size(); ++i){
               if(mapOfVertices[primaryVertex].correspondingEdges[i].correspondingNode == correspondingVertex){
                   mapOfVertices[primaryVertex].correspondingEdges[i].weight -= weight;
                   break;
               }
           }
           for(int i = 0; i < mapOfVertices[correspondingVertex].correspondingEdges.size(); ++i){
               if(mapOfVertices[correspondingVertex].correspondingEdges[i].correspondingNode == primaryVertex){
                   mapOfVertices[correspondingVertex].correspondingEdges[i].weight -= weight;
                   break;
               }
           }
    }
    return validStatus;
}

//Description: Error description auxiliary method takes in enum error number and a user inputted edge candidate. Formats appropriate output from error number.
//Pre-condition: An edge must be inputted by user. Function is only called when edges are being added/modified.
//Post-condition: Formats approriate output corresponding to error type.
void AdjacencyList::writeErrorDescriptionToFile(int error, Edge candidateEdge){
    output.open(outputFilename, ios::app);
    if(error == valid){//valid
        output << endl;
    }else if(error == negativeWeight){//negative weight
        output << "Error invalid weight (<= 0): " << candidateEdge.weight << " is not a valid weight" << endl;
        cout << "Error invalid weight (<= 0): " << candidateEdge.weight << " is not a valid weight" << endl;

    }
    else if(error == invalidVertex){//invalid vertice
        output << "Vertex does not exist: ";
        cout << "Vertex does not exist: ";
        if(candidateEdge.primaryNode >= numberOfVertices){
            output << candidateEdge.primaryNode;
            cout << candidateEdge.primaryNode;
        }else{
            output << candidateEdge.correspondingNode;
            cout << candidateEdge.correspondingNode;
        }
        output << " is not a valid vertex" << endl;
        cout << " is not a valid vertex" << endl;

    }
    else if(error == edgeNotFound){//edge not found
        cout << "not a valid edge" << endl;
        output << "Not a valid edge: " << candidateEdge << endl;
    }
    else if(error == duplicateFound){//duplicate found
        output << "Duplicate edge detected: " << candidateEdge <<  endl;
        cout << "Duplicate edge detected: " << candidateEdge <<  endl;
    }
    else if(error == invalidCommand){//invalid command
        output << "Invalid command" << endl;
        cout << "invalid command" << endl;
    }
    output.close();
    output.clear();
}

//Description: MST function calculates the minimum spanning tree using prims algorithm and a priority queue.
//Pre-condition: checkGraphIsConnected must return true (graph must be connected).
//Post-condition: Returns adjacencyList of the minimum spanning tree, along with the sum and sets vertex/edge count.

//we need to make sure that an edge is not
void AdjacencyList::calculateMST(){
    MSTmap.clear();//reset containers when recalculating
    vector<pair<Edge, int>>iterations;
    minSpanTreeEdges = 0;
    spanningTree = {};
    sumOfMinSpanningTree = 0;
    minSpanTreeVertices = numberOfVertices;
    map<int, bool>visitStatus;//visit map to reference
    
    for(int i = 0; i < numberOfVertices; i++){
        visitStatus[i] = false;
    }
    
    int newestVertexIndex = 0;//start at 0
    priority_queue<Edge, vector<Edge>, less<Edge>>pq;
    int j = 0;

    while(j < mapOfVertices.size()-1){
        for(int k = 0; k < mapOfVertices[newestVertexIndex].correspondingEdges.size(); ++k){
            pq.push(mapOfVertices[newestVertexIndex].correspondingEdges[k]);//add newest batch
        }
        //if vertice of this primary node in the edge has been visited, discard the edge.
        while(!pq.empty()){
            if(visitStatus[pq.top().correspondingNode] == false){
                //has not been visited, add to spanning tree
                sumOfMinSpanningTree += pq.top().weight;
                visitStatus[pq.top().primaryNode] = true;
                visitStatus[pq.top().correspondingNode] = true;
                spanningTree.push_back(make_pair(sumOfMinSpanningTree, pq.top()));
                //if not in MSTmap, push back vertex, if in vector, push back to vector of edges iwthin vertice
                
                if(MSTmap.count(pq.top().primaryNode) == 0){
                    Edge newEdge(pq.top());
                    MSTmap[pq.top().primaryNode] = Vertex(newEdge, pq.top().primaryNode);
                }else{
                    MSTmap[pq.top().primaryNode].correspondingEdges.push_back(pq.top());
                }
                //subsequent node
                if(MSTmap.count(pq.top().correspondingNode) == 0){
                    Edge newEdge(pq.top().correspondingNode, pq.top().primaryNode, pq.top().weight);
                    MSTmap[pq.top().correspondingNode] = Vertex(newEdge, pq.top().correspondingNode);
                }else{
                    //push back edge to existing vertex
                    MSTmap[pq.top().correspondingNode].correspondingEdges.push_back(Edge(pq.top().correspondingNode, pq.top().primaryNode, pq.top().weight));
                }
              
                newestVertexIndex = pq.top().correspondingNode;//set next vertex index so new adjacent vertices can be added to queue.
                pq.pop();//remove from queue
                minSpanTreeEdges++;
                
                                
                
                break;//end loop while keeping candidate edges in queue
            }else{
                pq.pop();//get next possible edge
            }
        }
        j++;
    }
}


//Description: Dijkstra's shortest path algorithm implementation. Takes in a starting node and finish node and searches for the shortest (minimal weight) path to the finish node.
//Pre-condition: Graph must be connected and complete, and start/finish nodes must be supplied by user.
//Post-condition: Outputs a formatted display of iterations as well returns the distance from start to finish.
int AdjacencyList::calculateShortestPath(int A, int B){
   
    //requires a comparison operator for priority queue to work with pairs
    struct Compare{
        bool operator()(pair<int, int>*const&a, pair<int, int>*const&b)
        {
            return a->second > b->second;
        }
    };
    //PQ uses pointers so respective values can be uptaed when referenced outside of the queue.
    priority_queue<pair<int, int>*, vector<pair<int, int>*>, Compare>pq;
    vector<pair<int, int>>distance;//pair of vertex, distance
    vector<string>iterations;
    distance.reserve(numberOfVertices);
    for(int i = 0; i < numberOfVertices; ++i){
        if(i != A){
            distance.push_back(make_pair(i, INT_MAX));//if not the start node, set distance to infinity.
        }else{
              distance.push_back(make_pair(i, 0));
        }
        pq.push(&distance[i]);//push address of distance to priority queue
    }
        while(!pq.empty()){
            pair<int, int>*vertex = pq.top(); //pop item with shortest distance
            int index = vertex->first;
            int length = vertex->second;
            pq.pop();//remove from queue
            
            //for each adjacent vertex from popped vertex, check if the distance (weight) of the each adjacent node and compare to previous set distance of infinity.
            
            for(int j = 0; j < mapOfVertices[index].correspondingEdges.size(); ++j){
                int alternateDistance = length + mapOfVertices[index].correspondingEdges[j].weight;
                if(alternateDistance < distance[mapOfVertices[index].correspondingEdges[j].correspondingNode].second){
                    if(numberOfVertices < 10){
                        int node = mapOfVertices[index].correspondingEdges[j].correspondingNode;
                        string iter = "From: " + to_string(index) + " to " + to_string(node) + " | Cumulative distance: " + to_string(alternateDistance);
                        iterations.push_back(iter);
                    }
                    //set distance to newly calculated value.
                    distance[mapOfVertices[index].correspondingEdges[j].correspondingNode].second = alternateDistance;
                }
            }
        }
    //if the number of vertices is less than 10, compile each iteration of the algorithm and display to output.
    if(numberOfVertices < 10){
        output.open(outputFilename, ios::app);
        for(int i = 0; i < numberOfVertices; ++i){
            cout << iterations[i] << endl;
            output << iterations[i] << endl;
        }
        output.close();
    }
    return distance[B].second;
}


