#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>
#include <tuple>
#include <algorithm>
#include "cs225/PNG.h"

struct Info {
    std::set<std::string> teammates;
    float per;
    int count;
    unsigned idx;
};

struct Node
{
    unsigned idx_;
    std::string name_;   
    float per_;
    std::unordered_map<Node*, float> adj_;

    Node(unsigned IDX, std::string NAME, float PER)
    {
        idx_ = IDX;
        name_ = NAME;
        per_ = PER;
    }

    std::string print_name() {
        return name_;
    }

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

struct Edge {
    int u;
    int v;
    float weight;

    Edge(int U, int V, int WEIGHT) {
        u = U;
        v = V;
        weight = WEIGHT;
    }
};

struct Point {
    double x;
    double y;

    Point(double X, double Y) {
        x = X;
        y = Y;
    }
};


class PlayerGraph {
    public:
        PlayerGraph(const std::string filename);
        std::vector<Node*> file_to_graph(const std::string filename);
        std::vector<std::string> BFS(std::string startID, std::string endID);
        std::pair<std::vector<float>, std::vector<int> > Djikstras(std::string playerName);
        std::vector<Point> fruchtermanReingold(std::string playerName);
        cs225::PNG drawGraph(int height, int width, std::vector<Point> nodes, std::vector<Edge> edges);
        std::vector<Point> line(Point p1, Point p2);
        Node* getPlayer(int idx);
        Node* getPlayer(std::string name);
        bool PlayerExists(std::string name);

    private:
        std::vector<Node*> nodeVector;
        std::vector<Edge> edgeVector;
        std::vector<std::string> BFS(int startingNode, int finishNode);
        std::pair<std::vector<float>, std::vector<int> > Djikstras(int src);
        std::vector<Point> fruchtermanReingold(std::vector<Node*> vertices, std::vector<Edge> edges, int height, int width, int iterations);
};
