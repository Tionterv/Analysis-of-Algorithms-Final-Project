#include "tiles.hpp"
#include <iostream>

int pathCost(vector<int> puzzleState);

void Puzzle::Dijkstra(vector<int> puzzleState, int num)
{
    choice = "D";
    if (num == 2)
        flag = true;

    node vertex;  
    //explored map to avoid looping  
    map<vector<int>, bool> explored;    
    vector<node> path;            
    int currCost = 0;
    int move = 0;                  
    vertex.nodeName = 0;
    vertex.puzzleVector = puzzleState;

    cout << "\nDijkstra:" << endl;

    if(solvedPuzzle(vertex)){ 
        cout << "It is already solved." << endl;
        return;
    }

    // if explored the starting configuration
    explored.emplace(make_pair(vertex.puzzleVector, true));    
    //start path add the vertex
    path.push_back(vertex);                         

    // Search in a level configuration like BFS and while the solution is not found 
    while(!solvedPuzzle(vertex)){   
        //we start building our adjency list
        emptyTile(vertex);       
        node vertexMin;            
        //create cost for comparison of dijkcost
        vertexMin.dijkCost = INT_MAX;

        list<pair<node, unsigned long> >::iterator iter_dijkstra;
		iter_dijkstra = vertex.adjList.begin();
		while(iter_dijkstra != vertex.adjList.end())
		{
			node startNode = (*iter_dijkstra).first;
            if(explored.count(startNode.puzzleVector) == 0){  
                //If configuaration has not been generator
                explored.emplace(make_pair(startNode.puzzleVector, true));  
                //if it been proccess add it to explored
                startNode.dijkCost = startNode.moveCost + currCost + pathCost(startNode.puzzleVector);

                if(startNode.dijkCost < vertexMin.dijkCost){ 
                        vertexMin = startNode;
                }
                else if(startNode.dijkCost == vertexMin.dijkCost){
                    if (startNode.moveCost < vertexMin.moveCost)
                        vertexMin = startNode;
                }
                
            }
			++iter_dijkstra;
		}

		path.push_back(vertexMin); 
        // is the addition of the cost to move plus the min path cost
        currCost += vertexMin.moveCost; 
        
        // passing the new vertex to get keep going and counting the move
        vertex = vertexMin; 
        move++;
    } 

    if (num == 1)
    {
        //total cost
        print(vertex.puzzleVector, 1);
    }

    cout << "The shortest path cost = " << currCost << endl;
    cout << "Number of moves = " << move << endl;

	totalCost = currCost;

}


int pathCost(vector<int> puzzleState){

    int count = 0;  
    //initializing the starting state in a matrix
    vector<vector<int>> matrix { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            matrix[i][j] = puzzleState[count];
            count++;
        }
    }

    int sum = 0;
    div_t result;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(matrix[i][j] != 0)
            {   
                int data = 0;
                int order = 0;
                if(matrix[i][j] == 4 || matrix[i][j] == 6 || matrix[i][j] == 8)
                { 
                    
					switch(matrix[i][j]) 
                    {
                        case 4: 
                             data = 6; 
                             break;
                        case 6: 
                             data = 8;
                             break;
                        case 8: 
                             data = 4;
                             break;
                        default: 
                             cout << "Error!" << endl;
                    } 
                    result = div(data-1, 3);
                    order = abs(result.quot - i) + abs(result.rem - j);  
 
                } 
                else if (matrix[i][j] == 5)
                {
                    order = 4-i-j;    
                } 
                else 
                {   
                    data = matrix[i][j]; 
                    result = div(data-1, 3);
                    order = abs(result.quot - i) + abs(result.rem - j);    
                }
                //the cost of the matrix and store in the sum each iterations
                sum += (order*matrix[i][j]);    
            }
        }
    }        
    return sum;
}