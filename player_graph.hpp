#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

struct Node
{

    string id_;
    string team_;
    string year_;
    float per_;
    Node(string ID, string TEAM, string YEAR, float PER)
    {
        id_ = ID;
        team_ = TEAM;
        year_ = YEAR;
        per_ = PER;
    }

    std::set<Node *> adj_; //adjac
    std::vector<std::pair<Node *, float>> edges_;

    void print()
    {
        std::cout << id_ << " " << team_ << " " << year_ << std::endl;
    }
    void print_adj()
    {
        std::cout << "ADJ" << std::endl;
        ;
        for (Node *node : adj_)
        {
            node->print();
        }
    }
};

std::vector<Node *> file_to_graph(const std::string filename);