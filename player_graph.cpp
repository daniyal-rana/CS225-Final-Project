#include "player_graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
std::vector<Node *> file_to_graph(const std::string filename)
{
    std::vector<Node *> node_vect;
    std::map<std::pair<std::string, std::string>, std::set<Node *>> mutual; //maps team/year pair to set of teammate nodes
    std::ifstream file(filename);
    std::string line;
    if (file.is_open())
    {
        std::getline(file, line);        //skip header line
        while (std::getline(file, line)) //construct nodes + adjacency lists
        {

            std::vector<string> line_to_string;
            stringstream ss(line);
            while (ss.good())
            {
                string col_item;
                std::getline(ss, col_item, ',');
                line_to_string.push_back(col_item);
            }

            Node *node = new Node(line_to_string[1], line_to_string[6], line_to_string[2], std::stof(line_to_string[line_to_string.size() - 1]));
            std::pair<std::string, std::string> team_year = std::make_pair(node->team_, node->year_);
            if (mutual.find(team_year) != mutual.end()) //has mutual teammates
            {
                node->adj_ = mutual[team_year];
                for (Node *old_node : mutual[team_year])
                {
                    old_node->adj_.insert(node);
                }
                mutual[team_year].insert(node);
            }
            else //no mutual yet
            {
                mutual[team_year].insert(node);
            }
            node_vect.push_back(node);
        }
    }

    /*     for (Node *node : node_vect)
    {
        std::cout << "PRINT NODE" << std::endl;
        node->print();
        node->print_adj();
    } */

    //construct edges?

    return node_vect;
}

std::vector<std::string> PlayerGraph::BFS(int startID, int endID) {
    vector<bool> visited(file_to_graph.size(), false); // mark all nodes as unvisited

    std::queue<Node*> q; //queue for bfs
    // std::vector<Node*> playerList;
    std::vector<Node*> previous{nullptr};   //to track down the order of final nodes     
    
    Node* curr = file_to_graph[startID];    //get starting node from list of nodes
    Node* endNode = file_to_graph[endID];   //get final node

    q.push_back(start);     //put starting point in queue
    previous[startNode.id] = curr;  //initialize starting point
    int currNode = startID;     // use id to track where in the list of nodes the player is in
    visited[currNode] = true;  

    while (!q.empty()) {
        curr = q.front();
        currNode = startNode.id;

        for (auto it : curr.adj_) { // look thru adj list
            if(!visited[it.id]) {       // check if next player has been visited already
                visited[it.id] = true;  //mark player as visited
                q.push_back(it);        //enqueue next player
                previous[it.id] = curr;     //keep track of list of visited player
            } 
        }
        if (curr == endNode) {
            break;
        }
        q.pop();
    }

    if (curr != endNode) {
        vector<string> T;
        return T;
    }

    std::vector<std::string> result;
    result.push_back(curr.id_);
    while (curr != file_to_graph[startID]) {
        curr = prev[currNode];
        currNode = curr.id;
        result.push_back(curr.id_);
    }
    return result;
}

Node* PlayerGraph::PlayerExists(std::string name) {
    for (Node* node : file_to_graph) {
        if (node.id_ == name) return node;
    }
    return nullptr;
}
