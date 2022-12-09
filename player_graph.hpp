#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

struct Node
{
    unsigned idx; // index of Node in node vector
<<<<<<< HEAD
    int id; 
=======
>>>>>>> 0363f2257cd786f72cb08a2076415670be85b11b
    string id_;   // unique node ID (ex. Lebron James_1)
    string team_;
    string year_;
    float per_;
<<<<<<< HEAD
    
=======
>>>>>>> 0363f2257cd786f72cb08a2076415670be85b11b
    Node(unsigned IDX, string ID, string TEAM, string YEAR, float PER)
    {
        idx = IDX;
        id_ = ID;
        team_ = TEAM;
        year_ = YEAR;
        per_ = PER;
    }

<<<<<<< HEAD
    std::unordered_map<Node*, float> adj_;
=======
    std::unordered_map<Node *, float> adj_; // key = connected node (teammate in given season)
    // value = avg per
>>>>>>> 0363f2257cd786f72cb08a2076415670be85b11b

    void
    print()
    {
        std::cout << id_ << " " << team_ << " " << year_ << " " << per_ << std::endl;
    }
    void print_adj()
    {
        std::cout << "ADJ" << std::endl;

        for (auto pair : adj_)
        {
            pair.first->print();
            std::cout << "\tEDGE: " << pair.second << std::endl;
        }
    }
};
std::vector<Node *> file_to_graph(const std::string filename); // converts input CSV into graph

<<<<<<< HEAD
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
=======
/* class PlayerGraph {
>>>>>>> 0363f2257cd786f72cb08a2076415670be85b11b
    public:
    PlayerGraph(const std::string filename);
    std::vector<std::string> BFS(int orgin, int end);
    Node* PlayerExists(std::string name);
    std::pair<std::vector<int>, std::vector<int>> Djikstras(std::string playerName, std::string year);
    std::vector<Coordinate> fruchtermanReingold(int height, int width, double k = 0.1, double t = 0.1, int iterations = 100);
    std::vector<Node*> file_to_graph(const std::string filename);

    private:
    std::vector<Node*> nodeVector;
    std::vector<Edge> edgeVector;
    std::pair<std::vector<int>, std::vector<int>> Djikstras(int src);
};


<<<<<<< HEAD
=======
} */
>>>>>>> 0363f2257cd786f72cb08a2076415670be85b11b
