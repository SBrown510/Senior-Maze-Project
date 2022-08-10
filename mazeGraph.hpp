//
// Created by SpencerB on 11/22/2020.
//
#include <vector>
#include "iostream"
#include "heaptree.hpp"
#include "edge.hpp"

#ifndef PROJECT_2_MAZEGRAPH_HPP
#define PROJECT_2_MAZEGRAPH_HPP

class mazeGraph {
public:
    mazeGraph();
    ~mazeGraph();
    void createGraph(int numRows, int numCols);
    void printSol(std::vector<std::pair<int , edge>> prims, int rows, int cols);
    std::vector<std::pair<int , edge>> primSolution();
    std::vector<std::pair<int , edge>> kruskSolution();



private:
    std::vector<std::vector<std::pair<int, edge>>> adjMaze; // adjMaze[i] is the vertices and adjMaze[i][j]
                                                            // is a connected edge and a connected vert.
    std::vector<std::vector<int >> visualMaze;
    std::vector<edge > eWeights;
    std::vector<bool > usedEdge;
    std::vector<int > uParents;
    std::pair<int, int> graphstart;
    std::pair<int, int> graphend;
    std::vector<std::pair<int, int>> connEdges;
    std::vector<std::vector<bool>> used;
    std::vector<bool > usedForPath;

    //helper functions
    bool cycleCheck(int vert1, int vert2);
    bool cycleCheckKrusk(int vert1, int vert2);
    int find(int vert);
    void edgeUnion(int vertBase, int vertAdd);
    std::pair<int, int> findMinEdge(std::vector<int > mstTree); //returns position of vert and edge thats used.
    std::pair<int, int> successorPoint(int row, int point);
    void resetPath();
    void setConn();
    std::vector<std::pair<int, int>> pathFromTo(std::pair<int, int> startRP);
    bool usedE();

    void printMazeFinal(std::vector<std::pair<int, int>> finPath);
    void sizePath();
    bool contains(int x, std::vector<int >);
};


#endif //PROJECT_2_MAZEGRAPH_HPP
