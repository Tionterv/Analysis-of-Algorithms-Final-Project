#include "tiles.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream input("input.txt");
    int puzzleState = 1;

    while(!input.eof())
    {
        Puzzle puzzle1, puzzle2, puzzle3;
        string row1, row2, row3, line;
        vector<int> puzzle (9, 0);

        getline(input, row1);
        getline(input, row2);
        getline(input, row3);

	    puzzle.at(0) = stoi(row1.substr(0, 1)); 
        puzzle.at(1) = stoi(row1.substr(1,1)); 
        puzzle.at(2) = stoi(row1.substr(2,1));
        puzzle.at(3) = stoi(row2.substr(0,1)); 
        puzzle.at(4) = stoi(row2.substr(1,1)); 
        puzzle.at(5) = stoi(row2.substr(2,1));
        puzzle.at(6) = stoi(row3.substr(0,1)); 
        puzzle.at(7) = stoi(row3.substr(1,1)); 
        puzzle.at(8) = stoi(row3.substr(2,1));

        cout << endl << "Input " << puzzleState << endl;

        puzzle1.BFS(puzzle, 2);
        puzzle2.DFS(puzzle, 2);
        puzzle3.Dijkstra(puzzle, 2);

		int smallest = puzzle1.getCost();
        if(puzzle2.getCost() < smallest)
        {
			smallest = puzzle2.getCost();
		}
        if(puzzle3.getCost() < smallest)
        {
			smallest = puzzle3.getCost();
		}

		cout << "\n-------------------------------------------\n\n";
		cout << "The shortest path cost out of three algorithms = " << smallest << endl;
        cout << endl << "***********************************************" << endl;

        getline(input, line);
        puzzleState++;
    }

    return 0;
}