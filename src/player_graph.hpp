#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <climits>
#include "../lib/cs225/PNG.h"
using namespace std;
using namespace cs225;

struct Node
{
    unsigned idx; // index of Node in node vector
    int id;
    string id_; // unique node ID (ex. Lebron James_1)
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

    std::string getName()
    {
        return id_.substr(0, id_.find("_"));
    }

    std::unordered_map<Node *, float> adj_;

    void print()
    {
        std::cout << id_ << " " << team_ << " " << year_ << " " << per_ << std::endl;
    }

    void print_adj()
    {
        std::cout << "ADJ" << std::endl;

        for (std::pair<Node *, float> pair : adj_)
        {
            pair.first->print();
            std::cout << "\tEDGE: " << pair.second << std::endl;
        }
    }
};

struct Coordinate
{
    double x;
    double y;
};

struct Edge
{
    int u;
    int v;
    int weight;
};

class PlayerGraph
{
public:
    PlayerGraph(const std::string filename);
    std::vector<std::string> BFS(int orgin, int end);
    Node *PlayerExists(std::string name);
    std::pair<std::vector<int>, std::vector<int>> Djikstras(std::string playerName, std::string year);
    // std::vector<Coordinate> fruchtermanReingold(int height, int width, double k, double t, int iterations);
    // cs225::PNG drawGraph(int height, int width);
    std::vector<Node *> file_to_graph(const std::string filename);

    struct Player // single player->multiple nodes that each represent season
    {
        string name;
        std::vector<Node *> node_seasons;
        std::unordered_map<Player *, float> player_total_per;
        std::unordered_map<Player *, unsigned int> num_seasons_together;
        std::unordered_map<Player *, float> player_adj_;

        Player(const std::string &NAME, const std::vector<Node *> nodes, std::unordered_map<std::string, std::vector<Node *>> &name_to_nodes, std::unordered_map<std::string, Player *> &name_to_player)
        {
            name = NAME;
            name_to_player[name] = this;
            for (auto season_node : nodes)
            {
                for (auto teammate_pair : season_node->adj_)
                {
                    if (name_to_player.find(teammate_pair.first->getName()) != name_to_player.end())
                    {
                        Player *&other_player = name_to_player[teammate_pair.first->getName()];
                        player_total_per[other_player] += teammate_pair.second;
                        num_seasons_together[other_player]++;

                        other_player->player_total_per[this] = this->player_total_per[other_player];
                        other_player->num_seasons_together[this] = this->num_seasons_together[other_player];

                        player_adj_[other_player] = (player_total_per[other_player]) / (num_seasons_together[other_player]);
                        other_player->player_adj_[this] = player_adj_[other_player];
                    }
                    else
                    {
                        // not found-> do nothing (corresponding teammate will be dynamically allocated later)
                    }
                }
            }
        }

        void print()
        {
            std::cout << name << std::endl;
        }

        void print_adj()
        {
            std::cout << "ADJ" << std::endl;

            for (std::pair<Player *, float> pair : player_adj_)
            {
                pair.first->print();
                std::cout << "\tEDGE: " << pair.second << std::endl;
            }
        }
    };

private:
    std::vector<Node *> nodeVector;
    std::vector<Edge> edgeVector;
    std::pair<std::vector<int>, std::vector<int>> Djikstras(int src);
};
