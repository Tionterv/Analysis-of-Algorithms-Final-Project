#include "tiles.hpp"
#include <iostream>

void Puzzle::DFS(vector<int> puzzleState, int num)
{
    choice = "DFS";
    int status = 0;
    if (num == 2)
        flag = true;

    
    //stack to hold and store visited edges
    stack <node> Stack; 
    //Starting stage 
    node startState; 
    int weightCounter = 1;
    startState.nodeName = 0;
    startState.puzzleVector = puzzleState;
    //Discoved nodes
    vector <node> processed;
    //iterator to go trough all vertex neighbors
    list<pair<node, unsigned long> >::reverse_iterator iter_neighbor; 

    cout << "\nDFS:" << endl;

    // check is for repeating configurations that has been solved
    if(solvedPuzzle(startState)) 
    {
        cout << "This puzzle is already solved." << endl;
        return;
    }

    // add the move to the vertices 
    vertices.push_back(startState); 
    //add to the stack
    Stack.push(startState); 
    //mark as processed
    processed.push_back(startState); 
    path.push_back(startState);

    //traverse until stack is empty and remove the top if has been visited
    while(!Stack.empty()) 
    {   
        node vertex = Stack.top(); 
        Stack.pop();

        // check if previous configurations and remove the top fromn the stack
        while (checkPuzzle(vertex))
        {
            vertex = Stack.top(); 
            Stack.pop();
        }
        //increment the path counter if some move has been done (cost++)
        if (vertex.nodeName != 0) 
        {
            path.push_back(vertex);
            totalCost += edges.at(weightCounter).edgeWeight; 
            weightCounter++;
        }
        
        if(solvedPuzzle(vertex)) 
        {
           
            status = 1;
            cout << "The shortest path cost = " << totalCost << endl;
            cout << "Number of Moves = " << weightCounter - 1 << endl; 
            if (num == 1)
                print(vertex.puzzleVector); 
        }

        emptyTile(vertex);  
        iter_neighbor = vertex.adjList.rbegin(); 
        while(iter_neighbor != vertex.adjList.rend()) 
        {   
            if (!visitedNode(processed, (*iter_neighbor).first)) 
            {
                Stack.push((*iter_neighbor).first); 
                processed.push_back((*iter_neighbor).first); 
            }
            iter_neighbor++;
        }
        
        if (status) 
            break;
    }
}