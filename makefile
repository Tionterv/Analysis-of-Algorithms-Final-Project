puzzle: run

run: main.cpp tiles.cpp BFS.cpp DFS.cpp Dijkstra.cpp
	g++ -o run -std=c++17 main.cpp tiles.cpp BFS.cpp DFS.cpp Dijkstra.cpp