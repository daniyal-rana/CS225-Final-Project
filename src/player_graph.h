#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <climits>
#include "cs225/PNG.h"
using namespace std;

struct Node
{
    unsigned idx; // index of Node in node vector
    int id; 
    string id_;   // unique node ID (ex. Lebron James_1)
    string team_;
    string year_;
    float per_;

    Node(unsigned IDX, string ID, string TEAM, string YEAR, float PER)
    {
        idx = IDX;
        id_ = ID;
        team_ = TEAM;
        year_ = YEAR;
        per_ = PER;
    }

    std::unordered_map<Node*, float> adj_;

    void print() {
        std::cout << id_ << " " << team_ << " " << year_ << " " << per_ << std::endl;
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
    std::vector<std::string> BFS(std::string startID, std::string endID);
    std::vector<std::string> BFS(int startingNode, int finishNode);
    Node* PlayerExists(std::string name);
    std::pair<std::vector<int>, std::vector<int> > Djikstras(std::string playerName, std::string year);
    std::vector<Coordinate> fruchtermanReingold(int height, int width, double k, double t, int iterations);
    cs225::PNG drawGraph(int height, int width);
    std::vector<Node*> file_to_graph(const std::string filename);

    private:
    std::vector<Node*> nodeVector;
    std::vector<Edge> edgeVector;
    std::pair<std::vector<int>, std::vector<int> > Djikstras(int src);
};
