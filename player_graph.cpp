#include "player_graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
std::vector<Node *> PlayerGraph::file_to_graph(const std::string filename)
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


PlayerGraph::PlayerGraph(const std::string filename) {
        nodeVector = file_to_graph(filename);
}

std::vector<std::string> PlayerGraph::BFS(int startID, int endID) {
    vector<bool> visited(nodeVector.size(), false); // mark all nodes as unvisited

    std::queue<Node*> q; //queue for bfs
    // std::vector<Node*> playerList;
    std::vector<Node*> previous{nullptr};   //to track down the order of final nodes     
    
    Node* curr = nodeVector[startID];    //get starting node from list of nodes
    Node* endNode = nodeVector[endID];   //get final node

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
        if (curr == endNode) { // stop once the player is reached
            break;
        }
        q.pop();
    }

    if (curr != endNode) { //if theres no path return an empty vector
        vector<string> T;
        return T;
    }

    std::vector<std::string> result;
    result.push_back(curr.id_);
    while (curr != nodeVector[startID]) {
        curr = prev[currNode];
        currNode = curr.id;
        result.insert(result.begin(), curr.id_); //Add to result vector in proper reverse order
    }
    return result;
}

Node* PlayerGraph::PlayerExists(std::string name) {
    for (Node* node : nodeVector) {
        if (node.id_ == name) return node;
    }
    return nullptr;
}
