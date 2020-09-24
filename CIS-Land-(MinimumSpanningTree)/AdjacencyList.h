#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <ostream>
#include <map>
using namespace std;
class AdjacencyList{
    
private:
    
    struct Edge{
        int primaryNode;
        int correspondingNode;
        int weight;
        Edge(int first, int second, int weight){
            primaryNode = first;
            correspondingNode = second;
            this->weight = weight;
        }
        bool operator() (Edge const &a, Edge const &b)  {return a.weight > b.weight;}
        bool operator>(Edge const &a) const  {return a.weight > weight;}
        bool operator<(Edge const &a) const  {return a.weight < weight;}
        bool operator==(const Edge &a)const{
            return ((a.primaryNode == correspondingNode && a.correspondingNode == primaryNode) || (a.primaryNode == primaryNode && a.correspondingNode == correspondingNode));
        }
    };
    struct Vertex {
        vector<Edge>correspondingEdges;
        int ID;
        Vertex(Edge& e, int ID){
            correspondingEdges.push_back(e);
            this->ID = ID;
        }
        Vertex(){}
    };
    
  
    string outputFilename;
    string inputFilename;
    ifstream input;
    ofstream output;
    
    map<int, Vertex>MSTmap;
    map<int, Vertex>mapOfVertices;
    vector<pair<int, Edge>>spanningTree;
    
    int minSpanTreeVertices;
    int minSpanTreeEdges;
    int numberOfVertices;
    int numberOfEdges;
    int sumOfMinSpanningTree = 0;
    
public:
    void constructAdjacentList();
    
    int addEdge(Edge);
    int incrementEdge(int, int, int);
    int decrementEdge(int, int, int);
    
    void setFileNames(string, string);
    int checkValidity(Edge, int);
    bool verticeIsVisited(int vertex);
    void writeErrorDescriptionToFile(int, Edge);
    AdjacencyList();
    void outputCurrentState();
    bool readInInitial();
    int readInUserChanges();
    void calculateMST();//prims algorithm
    
    bool checkGraphIsConnected();
    void traverse(int, bool isVisited[]);
    int calculateShortestPath(int A, int B);
   
    

    friend ostream& operator<<(ostream&out, Edge group){
        out << "(" << group.primaryNode << ", " << group.correspondingNode << ", " << group.weight << ")";
        return out;
    }
    friend ofstream& operator<<(ofstream&out, Edge group){
       out << "(" << group.primaryNode << ", " << group.correspondingNode << ", " << group.weight << ")";
           return out;
    }
    enum ValidState {
            valid,
            negativeWeight,
            invalidVertex,
            edgeNotFound,
            duplicateFound,
            invalidCommand,
            shortestPath
        };
    enum editMode{
        increment,
        decrement,
        addNew
    };
};
