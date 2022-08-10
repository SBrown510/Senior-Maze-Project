//
// Created by SpencerB on 11/21/2020.
//
//
#include <iostream>
#include "vector"
#include <tuple>
#include "edge.hpp"

#ifndef PROJECT_2_HEAPTREE_HPP
#define PROJECT_2_HEAPTREE_HPP


class heaptree {
public:
    heaptree();
    ~heaptree();
    void insert(edge);
    edge hTreeMin() { return hTree[0]; }
    void set();
    void removemin();
    void heapify(int index);


private:
    std::vector<edge> hTree; //edge number comes first, then edge weight
    std::vector<bool > usedVal;
    void swapElements(edge *sOne, edge *sTwo);
    int parentIndex(int num) { return ((num-1)/2); }
    int lChildIndex(int num) { return ((num*2)+1); }
    int rChildIndex(int num) { return ((num*2)+2); }

};


#endif //PROJECT_2_HEAPTREE_HPP
