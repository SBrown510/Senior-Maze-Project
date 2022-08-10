#include <iostream>
#include "heaptree.hpp"
#include "mazeGraph.hpp"

int main(int argc, char* argv[]) {
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    if (row < 10 || col < 10) {
        std::cout << "This graph is too small, needs to be at least 10 x 10" << std::endl;
    } else {
        std::cout << std::endl;
	std::cout << "Printing Prim's Graph & Solutions:" << std::endl;
        mazeGraph *maze = new mazeGraph;
        maze->createGraph(row, col);
        std::vector<int> preHeap;
        maze->printSol(maze->primSolution(), row, col);

        mazeGraph *kmaze = new mazeGraph;
        kmaze->createGraph(row, col);
        std::cout << std::endl;
	std::cout << "Printing Kruskal's Graph & Solution:" << std::endl;
        kmaze->printSol(kmaze->kruskSolution(), row, col);
        std::cout << std::endl;
   }
    return 0;
}
