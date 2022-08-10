//
// Created by SpencerB on 11/21/2020.
//

#include <bits/stdc++.h>
#include "heaptree.hpp"
#ifndef PROJECT_2_HEAPTREE_CPP
#define PROJECT_2_HEAPTREE_CPP

void heaptree::insert(edge pair) {
    hTree.push_back(pair);
    if (hTree.size() == 0) {
        return;
    } else {
        int heapCounter = hTree.size() - 1;
        while (hTree[parentIndex(heapCounter)].getWeight() >
                hTree[heapCounter].getWeight()) {
            swapElements(&hTree[heapCounter], &hTree[parentIndex(heapCounter)]);
            heapCounter = parentIndex(heapCounter);
        }
    }
}

void heaptree::swapElements(edge *sOne, edge *sTwo) {
    edge tmpOne = *sOne;
    *sOne = *sTwo;
    *sTwo = tmpOne;
}

void heaptree::set() {
    for (int i = 0; i < hTree.size(); ++i) {
        usedVal.push_back(false);
    }
}

void heaptree::heapify(int index) {
    int leftC, rightC, minInd;
    edge tmp;
    leftC = lChildIndex(index);
    rightC = rChildIndex(index);
    if (rightC >= hTree.size()) {
        if (leftC >= hTree.size()) {
            return;
        } else {
            minInd = leftC;
        }
    } else {
        if (hTree[leftC].getWeight() <= hTree[rightC].getWeight()) {
            minInd = leftC;
        } else {
            minInd = rightC;
        }
    }
    if (hTree[index].getWeight() > hTree[minInd].getWeight()) {
        tmp = hTree[minInd];
        hTree[minInd] = hTree[index];
        hTree[index] = tmp;
        heapify(minInd);
    }
}

void heaptree::removemin() {
    if (hTree.empty()) {
        return;
    } else {
        hTree[0] = hTree[hTree.size()-1];
        hTree.pop_back();
        if (!hTree.empty()) {
            heapify(0);
        }
    }
}

heaptree::~heaptree() {

}

heaptree::heaptree() {

}

#endif //PROJECT_2_HEAPTREE_CPP