#ifndef TILES_H
#define TILES_H
#include <string>
#include <list>
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
#include <stack>
#include <stdlib.h>
using namespace std;

struct edge 
{
    pair<int, int> edgeNodes; 
    unsigned long edgeWeight; 
};

struct node 
{
    int nodeName; 
    int moveCost; 
    int dijkCost; 
    vector<int> puzzleVector; 
    list<pair<node, unsigned long> > adjList; 
};

class Puzzle
{
    private:
        int nodeName;
        int totalCost; 
        bool flag;
        string choice;
        vector<node> vertices; 
        vector<edge> edges; 
        vector<node> path;
        vector<int> output;
    public:
        Puzzle();
        bool solvedPuzzle(node);
        bool visitedNode(vector<node>, node);
        bool checkPuzzle(node); 
        int getCost() { return totalCost;   }
        void emptyTile(node&);
        void moveTiles(node&, int, int);
        void BFS(vector<int>, int); // Breadth First Search
        void DFS(vector<int>, int); // Depth First Search
        void Dijkstra(vector<int>, int); // Dijkstra's Algorithm
        void print(vector<int>, int isDijkstra = 0); 
        ~Puzzle();
};

#endif 
