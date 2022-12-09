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

    std::unordered_map<Node *, float> adj_; // key = connected node (teammate in given season)
    // value = avg per

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

/* class PlayerGraph {
    public:
    PlayerGraph(const std::string filename);
    std::vector<std::string> BFS(std::string orgin, std::string end);
    Node* PlayerExists(std::string name);
    std::vector<Node *> file_to_graph(const std::string filename);

    private:
    std::vector<Node *> nodeVector;

} */
