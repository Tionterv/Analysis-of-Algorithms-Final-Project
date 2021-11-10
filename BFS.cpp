#include "tiles.hpp"
#include <iostream>

// Breadth first search
void Puzzle::BFS(vector<int> puzzleState, int num) 
{
    choice = "BFS";
    int status = 0;
    if (num == 2)
        flag = true;

    // create a queue
    queue <node> Queue; 
    // new node to start the search from
    node startState;
    //counter with the weight for transversing 
    int weightCounter = 1;
    //iterator to tranverse the neighbors of an edge
    list<pair<node, unsigned long> >::iterator iter_neighbor; 
    // vector to mark all the visited 
    vector <node> processed;
    
    startState.nodeName = nodeName;
    startState.puzzleVector = puzzleState;
    cout << endl << "Start State: " << endl; 
    print(startState.puzzleVector);
    cout << "BFS:" << endl;

    //checks if problem has been solved
    if(solvedPuzzle(startState)) 
    {
        cout << "Already solved" << endl;
        return;
    }

    //Add the root to the list of vertices in our graph
    vertices.push_back(startState); 
    //add the vertex to the queue
    Queue.push(startState); 
    //mark as processed 
    processed.push_back(startState); 

    //iterate until the queue is not empty
    while(!Queue.empty()) 
    {   
        node vertex = Queue.front(); 
        Queue.pop();

        while (checkPuzzle(vertex)) 
        {
            vertex = Queue.front(); 
            Queue.pop();
        }
        if (vertex.nodeName != 0) 
        {
            totalCost += edges.at(weightCounter).edgeWeight; 
            weightCounter++;
        }

        //check the vertex
        if(solvedPuzzle(vertex)) 
        {
            status = 1; 
            cout << "The shortest path cost = " << totalCost << endl;
            cout << "Number of moves = " << weightCounter - 1 << endl; 
            
            if (num == 1)
            {
                print(vertex.puzzleVector); 
            }
        }

        emptyTile(vertex); 

		iter_neighbor = vertex.adjList.begin();
        while(iter_neighbor != vertex.adjList.end())
        {
            if (!visitedNode(processed, (*iter_neighbor).first)) 
			{
				Queue.push((*iter_neighbor).first);			  
				processed.push_back((*iter_neighbor).first); 
			}
			iter_neighbor++;
		}
        
        // breaks from while loop if solved puzzle
        if (status) 
            break;
    }
}
