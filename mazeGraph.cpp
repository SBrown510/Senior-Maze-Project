//
// Created by SpencerB on 11/22/2020.
//

#include <tuple>
#include <cstdlib>
#include <fstream>
#include <stack>
#include "mazeGraph.hpp"

mazeGraph::mazeGraph() {
}

mazeGraph::~mazeGraph() {
}

void mazeGraph::createGraph(int numRows, int numCols) {
    srand (time(nullptr));

    int numEdges = 0;
    if (numCols == 1) {
        numEdges = numRows-1;
    } else if (numCols == 2) {
        numEdges = ((numRows - 1)*2)+numRows;
    } else {
        numEdges = (((numRows-1)*2)+numRows) + ((numRows + numRows-1)* (numCols-2));
    }
    for (int i = 0; i < numEdges; ++i) {
        int randomNum;
        if (numRows == 10 && numCols == 10) {
            randomNum = 1;
	} else {
            randomNum = rand() % 100 + 1;
        }
        edge e;
        e.setNum(i);
        e.setWeight(randomNum);
        eWeights.push_back(e);
    }

    int i = 0;
    int RC = 0; //ROW COUNTER
    std::vector<std::pair<int, edge>> edgeList;
    while (i < (numRows * numCols)) { //POPULATES ADJACENCY LIST

        int up = (i-1) + (numRows-1) * (RC - 1); //UP
        if (up < 1) {
            up = 0;
        } else {
            edgeList.push_back(std::make_pair(i-numRows, eWeights[up]));
        }

        int down = i + (numRows-1) * (RC + 1); //DOWN
        if (down > eWeights.size()) {
            down = 0;
        } else {
            edgeList.push_back(std::make_pair(i+numRows, eWeights[down]));
        }

        int left = (i-1) + (numRows-1) * RC; //LEFT
        if (left < 1 || ((i % numRows) == 0)) {
            left = 0;
        } else {
            edgeList.push_back(std::make_pair(i-1, eWeights[left]));;
        }

        int right = i + (numRows-1) * RC; //RIGHT
        if (right > eWeights.size() || ((i % numRows) == (numRows-1))) {
            right = 0;
        } else {
            edgeList.push_back(std::make_pair(i+1,eWeights[right]));
        }

        if (i % numRows == (numRows-1)) {
            RC++;
        }
        adjMaze.push_back(edgeList);
        i++;
        edgeList.clear();
    }
}

bool mazeGraph::cycleCheck(int vert1, int vert2) {
    if (find(vert1) == find(vert2)) {
        return true;
    } else {
        return false;
    }
}

bool mazeGraph::cycleCheckKrusk(int vert1, int vert2) {
    if (find(vert1) == find(vert2)) {
        return true;
    } else {
        edgeUnion(vert1, vert2);
        return false;
    }
}

int mazeGraph::find(int vert) {
    if (uParents[vert] == -1) {
        return vert;
    } else {
        return find(uParents[vert]);
    }
}

void mazeGraph::edgeUnion(int vertBase, int vertAdd) {
    if (find(vertAdd) == -1) {
        uParents[vertAdd] = vertBase;
    } else if (find(vertBase) == -1) {
        uParents[vertBase] = vertAdd;
    } else {
        uParents[find(vertAdd)] = vertBase;
    }
}

std::vector<std::pair<int, edge>> mazeGraph::primSolution() {
    for (int i = 0; i < adjMaze.size(); ++i) { //initializing arrays
        uParents.push_back(-1);
    }
    std::vector<int > mstTree;
    std::vector<std::pair<int, edge>> retTree;
    mstTree.push_back(0);
    while (mstTree.size() < adjMaze.size()) {
        std::pair<int, int> nextEdge = findMinEdge(mstTree);
        int nextVert = std::get<0>(adjMaze[std::get<0>(nextEdge)][std::get<1>(nextEdge)]);
        mstTree.push_back(nextVert);
        retTree.push_back(adjMaze[std::get<0>(nextEdge)][std::get<1>(nextEdge)]);
        edgeUnion(std::get<0>(nextEdge), nextVert);
    }
    return retTree;
}

std::pair<int, int> mazeGraph::findMinEdge(std::vector<int > mstTree) {
    int retVert;
    int retJ;
    int lowest = 101;
    for (int i = 0; i < mstTree.size(); ++i) {
        for (int j = 0; j < adjMaze[mstTree[i]].size(); ++j) {
            if (!cycleCheck(0, std::get<0>(adjMaze[mstTree[i]][j]))) {
                if (std::get<1>(adjMaze[mstTree[i]][j]).getWeight() < lowest) {
                    lowest = std::get<1>(adjMaze[mstTree[i]][j]).getWeight();
                    retVert = mstTree[i];
                    retJ = j;
                }
            }
        }
    }
    return std::make_pair(retVert, retJ);
}

void mazeGraph::printSol(std::vector<std::pair<int , edge>> alg, int rows, int cols) {
    visualMaze.clear();
    for (int i = 0; i < eWeights.size(); ++i) {
        usedEdge.push_back(false);
    }

    for (int i = 0; i < alg.size(); ++i) {
        usedEdge[std::get<1>(alg[i]).getNum()] = true;
    }

    std::vector<int > row;
    int edgeCount = 0;
    for (int i = 0; i < cols*2+1; ++i) {
        for (int j = 0; j < rows*2+1; ++j) {
            if (i == 1 && j == 0) { // ENTERANCE
                row.push_back(0);
            } else if (i == (cols*2)-1 && j == (rows*2)) { // EXIT
                row.push_back(0);
            } else if (i == 0 || i == (cols * 2)) { //WALLS
                row.push_back(1);
            } else if (j == 0 || j == (rows * 2)) { //WALLS
                row.push_back(1);
            } else if ((j % 2) == 1 && ((i % 2) == 1)) { // POINTS
                row.push_back(0);
            } else if ((j % 2) == 1 && ((i % 2) == 0)) { //VERTICAL EDGES
                if (usedEdge[edgeCount]) {
                    row.push_back(0);
                } else {
                    row.push_back(1);
                }
                edgeCount++;
            } else if ((j % 2) == 0 && ((i % 2) == 1)) { //HORIZANTAL EDGES
                if (usedEdge[edgeCount]) {
                    row.push_back(0);
                } else {
                    row.push_back(1);
                }
                edgeCount++;
            } else {
                row.push_back(1);
            }
        }
        visualMaze.push_back(row);
        row.clear();
    }

    for (int i = 0; i < visualMaze.size(); ++i) {
        for (int j = 0; j < visualMaze[i].size(); ++j) {
            std::cout << visualMaze[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    graphstart = std::make_pair(1, 0);
    graphend = std::make_pair(visualMaze.size()-2, visualMaze[0].size()-1);
    printMazeFinal(pathFromTo(graphstart));

}

std::pair<int, int> mazeGraph::successorPoint(int row, int point) {
    if (visualMaze[row + 1][point] == 0 && !used[row + 1][point]) {
        std::pair<int, int> retVal(row + 1, point);
        return retVal;
    } else if (visualMaze[row - 1][point] == 0 && !used[row - 1][point]) {
        std::pair<int, int> retVal(row - 1, point);
        return retVal;
    } else if (visualMaze[row][point + 1] == 0 && !used[row][point + 1]) {
        std::pair<int, int> retVal(row, point + 1);
        return retVal;
    } else if (visualMaze[row][point - 1] == 0 && !used[row][point - 1]) {
        std::pair<int, int> retVal(row, point - 1);
        return retVal;
    } else {
        std::pair<int, int> retVal(visualMaze.size() + 1, visualMaze.size() + 1);
        return retVal;
    }
}

std::vector<std::pair<int, int>> mazeGraph::pathFromTo(std::pair<int, int> startPos) {
    sizePath();
    std::pair<int, int> endPos(std::get<0>(graphend), std::get<1>(graphend));
    std::vector<std::pair<int, int>> returnPath;
    int befX = std::get<0>(startPos);
    int befY = std::get<1>(startPos);
    used[befX][befY] = true;
    std::stack<std::pair<int, int>> path;
    path.push(startPos);
    std::pair<int, int> curXY = startPos;
    while (curXY != endPos) {

        curXY = successorPoint(std::get<0>(curXY), std::get<1>(curXY));
        if (std::get<0>(curXY) ==visualMaze.size() + 1) {
            path.pop();
            if (path.empty())
                break;
            curXY = path.top();
        } else {  // did find a successor
            path.push(curXY);
            used[std::get<0>(curXY)][std::get<1>(curXY)] = true;
        }
    }
    while (!path.empty()) {
        returnPath.push_back(path.top());
        path.pop();
    }
    return returnPath;
}

void mazeGraph::resetPath() {
    for (int i = 0; i < used.size(); i++) {
        for (int x = 0; x < used[i].size(); x++) {
            used[i][x] = false;
        }
    }
}

void mazeGraph::printMazeFinal(std::vector<std::pair<int, int>> finPath) {
    resetPath();
    if (finPath.empty()) {
        std::cout << "there is no path" << std::endl;
    } else {
        for (int i = 0; i < finPath.size(); i++) {
            used[std::get<0>(finPath[i])][std::get<1>(finPath[i])] = true;
        }
        //reset used to create actual path
        //print path with empty characters
        for (int i = 0; i < visualMaze.size(); i++) {
            for (int x = 0; x < visualMaze[i].size(); x++) {
                if (used[i][x]) {
                    std::cout << " ";
                } else {
                    std::cout << visualMaze[i][x];
                }
            }
            std::cout << std::endl;
        }
    }
}

void mazeGraph::sizePath() {
	std::vector<bool > usedTmp;
	for (int i = 0; i < visualMaze.size(); i++) {
		for (int j = 0; j < visualMaze[i].size(); j++) {
			usedTmp.push_back(false);
		}
		used.push_back(usedTmp);
		usedTmp.clear();
	}
}

std::vector<std::pair<int, edge>> mazeGraph::kruskSolution() {
    for (int i = 0; i < adjMaze.size(); ++i) { //initializing arrays
        uParents.push_back(-1);
    }
    setConn();
    std::vector<int > mstTree;
    std::vector<edge > retTree;
    heaptree hep;
    for (int i = 0; i < eWeights.size(); ++i) {
        hep.insert(eWeights[i]);
    }
    hep.set();

    for (int i = 0; i < eWeights.size(); ++i) {
        usedForPath.push_back(false);
    }

    while (!usedE()) {
        if (!cycleCheckKrusk(std::get<0>(connEdges[hep.hTreeMin().getNum()]),
                std::get<1>(connEdges[hep.hTreeMin().getNum()]))) {
            retTree.push_back(hep.hTreeMin());
            if (!contains(std::get<0>(connEdges[hep.hTreeMin().getNum()]), mstTree)) {
                mstTree.push_back(std::get<0>(connEdges[hep.hTreeMin().getNum()]));
            }
            if (!contains(std::get<1>(connEdges[hep.hTreeMin().getNum()]), mstTree)) {
                mstTree.push_back(std::get<1>(connEdges[hep.hTreeMin().getNum()]));
            }
        }
        usedForPath[hep.hTreeMin().getNum()] = true;
        hep.removemin();
    }
    std::vector<std::pair<int, edge>> rets;
    for (int i = 0; i < retTree.size(); ++i) {
        rets.push_back(std::make_pair(i, retTree[i]));
    }
    return rets;
}

void mazeGraph::setConn() {
    int edgeCounter = 0;
    for (int x = 0; x < eWeights.size(); ++x) {
        for (int i = 0; i < adjMaze.size(); ++i) {
            for (int j = 0; j < adjMaze[i].size(); ++j) {
                if (std::get<1>(adjMaze[i][j]).getNum() == edgeCounter) {
                    connEdges.push_back(std::make_pair(i, (std::get<0>(adjMaze[i][j]))));
                    edgeCounter++;
                    break;
                }
            }
        }
    }
}

bool mazeGraph::contains(int x, std::vector<int > vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == x) {
            return true;
        }
    }
    return false;
}

bool mazeGraph::usedE() {
    for (int i = 0; i < usedForPath.size(); ++i) {
        if (!usedForPath[i]) {
            return false;
        }
    }
    return true;
}
