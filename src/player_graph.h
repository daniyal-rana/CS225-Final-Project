#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <cfloat>
#include "cs225/PNG.h"
using namespace std;

struct Info {
    std::set<std::string> teammates;
    float per;
    int count;
    unsigned idx;
};

struct Node
{
    unsigned idx_;
    string name_;   
    float per_;

    Node(unsigned IDX, string NAME, float PER)
    {
        idx_ = IDX;
        name_ = NAME;
        per_ = PER;
    }

    std::unordered_map<Node*, float> adj_;

    void print() {
        std::cout << name_ << " " << per_ << std::endl;
    }

    void print_adj() {
        std::cout << "ADJ" << std::endl;

        for (std::pair<Node*, float> pair : adj_)
        {
            pair.first->print();
            std::cout << "\tEDGE: " << pair.second << std::endl;
        }
    }
};

struct Coordinate {
    double x;
    double y;
};

struct Edge {
    int u;
    int v;
    int weight;
};


class PlayerGraph {
    public:
    PlayerGraph(const std::string filename);
    std::vector<std::string> BFS(std::string origin, std::string end);
    Node* PlayerExists(std::string name);
    std::pair<std::vector<float>, std::vector<int> > Djikstras(std::string playerName);
    std::vector<Coordinate> fruchtermanReingold(int height, int width, double k, double t, int iterations);
    cs225::PNG drawGraph(int height, int width);
    std::vector<Node*> file_to_graph(const std::string filename);
    Node* getPlayer(int idx);
    Node* getPlayer(std::string name);

    private:
    std::vector<Node*> nodeVector;
    std::vector<Edge> edgeVector;
    std::pair<std::vector<float>, std::vector<int> > Djikstras(int src);
    std::vector<std::string> BFS(int startingNode, int finishNode);
};
