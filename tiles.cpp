#include "tiles.hpp"
#include <iostream>
using namespace std;

Puzzle::Puzzle()
{
    totalCost = 0; 
    nodeName = 0; 
    output.push_back(1); 
    output.push_back(2); 
    output.push_back(3);
    output.push_back(8); 
    output.push_back(0); 
    output.push_back(4);
    output.push_back(7); 
    output.push_back(6); 
    output.push_back(5);
}
//creates a vertex to move the empty tile
void Puzzle::moveTiles(node& vertex, int empty, int tile) 
{
    //node to move the tile
    node moveTiles; 
    edge newEdge;
    moveTiles.nodeName = ++nodeName; 
    moveTiles.puzzleVector = vertex.puzzleVector; 
    moveTiles.moveCost = moveTiles.puzzleVector.at(tile); 
    //move the empty tile
    moveTiles.puzzleVector.at(empty) = moveTiles.puzzleVector.at(tile); 
    moveTiles.puzzleVector.at(tile) = 0; 
    newEdge.edgeNodes = make_pair(vertex.nodeName, moveTiles.nodeName);

    newEdge.edgeWeight = 1; 

    vertices.push_back(moveTiles);
    edges.push_back(newEdge);

    //update vertex
    vertex.adjList.push_back(make_pair(moveTiles, newEdge.edgeWeight)); 
    moveTiles.adjList.push_back(make_pair(vertex, newEdge.edgeWeight));
}

//check if a vertex was already visited
bool Puzzle::visitedNode(vector <node> visit, node vertex) 
{
	int i = 0;
	while (i < visit.size())
	{
        if (visit.at(i).nodeName == vertex.nodeName)
        {
            return true;
        }
		i++;
	}
	return false;
}

//already solved?
bool Puzzle::solvedPuzzle(node vertex) 
{
    if (vertex.puzzleVector == output)  return true;
    else    
        return false;
}


void Puzzle::emptyTile(node& vertex) 
{
    //The 0 tile is the top left corner: (right and down)
    if (vertex.puzzleVector.at(0) == 0) {   moveTiles(vertex, 0, 1); moveTiles(vertex, 0, 3);   }

    //The 0 tile is in the middle of the first row: (left , right, and down)
    else if (vertex.puzzleVector.at(1) == 0) {   moveTiles(vertex, 1, 0);   moveTiles(vertex, 1, 2);  moveTiles(vertex, 1, 4); }
    
    //the 0 tile in top left corner: (left, down)
    else if (vertex.puzzleVector.at(2) == 0)  {     moveTiles(vertex, 2, 1);  moveTiles(vertex, 2, 5);  }

    //the 0 tile in thethe left of the second row: (up, right, down )
    else if (vertex.puzzleVector.at(3) == 0)  {    moveTiles(vertex, 3, 0);  moveTiles(vertex, 3, 4);  moveTiles(vertex, 3, 6); }
    
    //the 0 tile in the middle of the second row: (left, up, right, down)
    else if (vertex.puzzleVector.at(4) == 0) {    moveTiles(vertex, 4, 3);  moveTiles(vertex, 4, 1);  moveTiles(vertex, 4, 5); moveTiles(vertex, 4, 7); }

    //the 0 tile right of the second row: (left, up, down)
    else if (vertex.puzzleVector.at(5) == 0) {    moveTiles(vertex, 5, 4); moveTiles(vertex, 5, 2); moveTiles(vertex, 5, 8); }

    //the 0 tile left of the third row: (up, right)
    else if (vertex.puzzleVector.at(6) == 0) {    moveTiles(vertex, 6, 3); moveTiles(vertex, 6, 7); }

    //the 0 tile in the of the third row: (left, up, right)
    else if (vertex.puzzleVector.at(7) == 0) {   moveTiles(vertex, 7, 6); moveTiles(vertex, 7, 4); moveTiles(vertex, 7, 8); }

    //the 0 tile right of the third row: (left, up)
    else if (vertex.puzzleVector.at(8) == 0) {   moveTiles(vertex, 8, 7); moveTiles(vertex, 8, 5);  }
} 


bool Puzzle::checkPuzzle(node vertex) 
{
    if (choice == "DFS") 
    {
        for (int i = 0; i < path.size(); i++)
        {
            if (path.at(i).puzzleVector == vertex.puzzleVector && path.at(i).nodeName != vertex.nodeName)
                return true;
        }
    }
    else if(choice == "BFS")
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).puzzleVector == vertex.puzzleVector && vertices.at(i).nodeName != vertex.nodeName)
                return true;
        }
    }
    return false;
}


void Puzzle::print(vector<int> puzzleState, int isDijkstra)
{
    cout << endl;
    cout << puzzleState.at(0) << " " << puzzleState.at(1) << " " << puzzleState.at(2) << endl;
    cout << puzzleState.at(3) << " " << puzzleState.at(4) << " " << puzzleState.at(5) << endl;
    cout << puzzleState.at(6) << " " << puzzleState.at(7) << " " << puzzleState.at(8) << endl << endl;
    if(isDijkstra || flag) 
    {
        return;
    }
}

Puzzle::~Puzzle()
{
    vertices.clear();
    edges.clear();
    path.clear();
    output.clear();
}