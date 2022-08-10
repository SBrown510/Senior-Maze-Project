//
// Created by SpencerB on 11/27/2020.
//

#ifndef PROJECT_2_EDGE_HPP
#define PROJECT_2_EDGE_HPP


class edge {
public:
    void setNum(int x) {edgeNum = x; }
    int getNum() {return edgeNum; }
    int getWeight() {return weight; }
    void setWeight(int x) { weight = x; }
private:
    int weight;
    int edgeNum;

};


#endif //PROJECT_2_EDGE_HPP
