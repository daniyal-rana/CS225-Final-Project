#include "player_graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>

PlayerGraph::PlayerGraph(const std::string filename)
{
    nodeVector = file_to_graph(filename);
}

std::vector<Node *> PlayerGraph::file_to_graph(const std::string filename)
{
    static std::unordered_map<std::string, std::vector<Node *>> name_to_nodes;
    static std::unordered_map<std::string, Player *> name_to_player;
    std::vector<Node *> node_vect;

    std::map<std::pair<std::string, std::string>, std::set<Node *>> mutual; // maps team/year pair to set of teammate nodes
                                                                            // std::map<std::pair<std::string, std::string>, std::unordered_map<Node *, float>> mutual;
    std::ifstream file(filename);
    std::string line;
    unsigned idx = 0;
    if (file.is_open())
    {
        std::getline(file, line);        // skip header line
        while (std::getline(file, line)) // construct nodes + adjacency lists
        {

            std::vector<string> line_to_string;
            stringstream ss(line);
            while (ss.good())
            {
                string col_item;
                std::getline(ss, col_item, ',');
                line_to_string.push_back(col_item);
            }

            Node *node = new Node(idx, line_to_string[1], line_to_string[6], line_to_string[2], std::stof(line_to_string[line_to_string.size() - 1]));
            string name = line_to_string[3];
            std::pair<std::string, std::string> team_year = std::make_pair(node->team_, node->year_);

            if (mutual.find(team_year) != mutual.end()) // has mutual teammates
            {

                for (Node *old_node : mutual[team_year])
                {
                    float diff = (old_node->per_ + node->per_) / 2; // edge weight between 2 nodes
                    old_node->adj_[node] = diff;                    // add edge in prev node adj map
                    node->adj_[old_node] = diff;                    // add edge in cur node adj map
                }
                mutual[team_year].insert(node);
            }
            else // no mutual yet
            {
                mutual[team_year].insert(node); // no edges to add (teammates not found yet)
            }
            node_vect.push_back(node); // add every new node to vect
            name_to_nodes[name].push_back(node);

            idx++;
        }
    }
    else
    {
        std::cout << "file cannot be opened" << std::endl;
    }

    /*     for (Node *node : node_vect)
        {
            std::cout << "PRINT NODE" << std::endl;
            node->print();
            node->print_adj();
        } */

    std::vector<Player *> player_vect;

    for (auto pair : name_to_nodes)
    {
        std::string name = pair.first;
        if (pair.first[pair.first.length() - 1] == ' ' || pair.first[pair.first.length() - 1] == '*')
        {
            name = pair.first.substr(0, pair.first.length() - 1);
        }

        Player *player = new Player(name, pair.second, name_to_nodes, name_to_player);

        player_vect.push_back(player);
    }

    /*     for (auto player : player_vect)
        {
            std::cout << "PRINT Player" << std::endl;
            player->print();
            player->print_adj();
        } */

    /*     name_to_player["LeBron James"]->print();
        name_to_player["LeBron James"]->print_adj();

        name_to_player["Kevin Love"]->print();
        name_to_player["Kevin Love"]->print_adj();
        // it works :) */
    return node_vect;
}

std::vector<std::string> PlayerGraph::BFS(int startID, int endID)
{
    // vector<bool> visited(nodeVector.size(), false); // mark all nodes as unvisited
    // std::queue<Node*> q; //queue for bfs
    // // std::vector<Node*> playerList;
    // std::vector<Node*> previous{nullptr};   //to track down the order of final nodes

    // Node* curr = nodeVector[startID];    //get starting node from list of nodes
    // Node* endNode = nodeVector[endID];   //get final node
    // q.push_back(start);     //put starting point in queue
    // previous[startNode.id] = curr;  //initialize starting point
    // int currNode = startID;     // use id to track where in the list of nodes the player is in
    // visited[currNode] = true;

    // while (!q.empty()) {
    //     curr = q.front();
    //     currNode = startNode.id;
    //     for (auto it : curr.adj_) { // look thru adj list
    //         if(!visited[it.id]) {       // check if next player has been visited already
    //             visited[it.id] = true;  //mark player as visited
    //             q.push_back(it);        //enqueue next player
    //             previous[it.id] = curr;     //keep track of list of visited player
    //         }
    //     }
    //     if (curr == endNode) { // stop once the player is reached
    //         break;
    //     }
    //     q.pop();
    // }
    // if (curr != endNode) { //if theres no path return an empty vector
    //     vector<string> T;
    //     return T;
    // }
    // std::vector<std::string> result;
    // result.push_back(curr.id_);
    // while (curr != nodeVector[startID]) {
    //     curr = prev[currNode];
    //     currNode = curr.id;
    //     result.insert(result.begin(), curr.id_); //Add to result vector in proper reverse order
    // }
    // return result;
    return std::vector<std::string>();
}

Node *PlayerGraph::PlayerExists(std::string name)
{
    for (Node *node : nodeVector)
    {
        if (name.find(node->id_) != std::string::npos)
            return node;
    }
    return nullptr;
}

std::pair<std::vector<int>, std::vector<int>> PlayerGraph::Djikstras(int src)
{
    std::vector<int> distances(nodeVector.size(), INT_MAX);
    std::vector<int> prev(nodeVector.size(), -1);
    std::vector<bool> visited(nodeVector.size(), false);
    std::priority_queue<std::pair<int, int>, std::vector<pair<int, int>>, std::greater<std::pair<int, int>>> heap;

    distances[src] = 0;
    heap.push(std::pair<int, int>(0, src));

    while (!heap.empty())
    {
        std::pair<int, int> vertex = heap.top();
        Node *curr = nodeVector[vertex.second];
        heap.pop();
        for (auto neighbor : curr->adj_)
        {
            if (!visited[neighbor.first->idx])
            {
                if (neighbor.second + vertex.first < distances[neighbor.first->idx])
                {
                    distances[neighbor.first->idx] = neighbor.second + vertex.first;
                    prev[neighbor.first->idx] = curr->idx;
                    heap.push(std::pair<int, int>(neighbor.second + vertex.second, neighbor.first->idx));
                }
            }
        }
        visited[curr->idx] = true;
    }

    std::pair<std::vector<int>, std::vector<int>> result(distances, prev);
    return result;
}

std::pair<std::vector<int>, std::vector<int>> PlayerGraph::Djikstras(std::string playerName, std::string playerYear)
{
    int src = 0;

    for (Node *player : nodeVector)
    {
        std::string id = player->id_;
        std::string year = player->year_;
        if (id.find(playerName) != std::string::npos && year == playerYear)
        {
            break;
        }
        src++;
    }

    if (src == (int)nodeVector.size())
    {
        std::cout << "Player does not exist" << std::endl;
        return std::pair<std::vector<int>, std::vector<int>>(std::vector<int>(), std::vector<int>());
    }

    return Djikstras(src);
}

/* std::vector<Coordinate> PlayerGraph::fruchtermanReingold(int height, int width, double k, double t, int iterations)
{
    std::vector<Coordinate> positions;
    for (auto &n : positions)
    {
        n.x = rand() % width;
        n.y = rand() % height;
    }
    for (int i = 0; i < iterations; i++)
    {
        std::vector<Coordinate> forces(positions.size(), {0, 0});
        // Calculate repulsive forces
        for (unsigned j = 0; j < positions.size(); j++)
        {
            for (unsigned k = j + 1; k < positions.size(); k++)
            {
                double dx = positions[j].x - positions[k].x;
                double dy = positions[j].y - positions[k].y;
                double d = std::sqrt(dx * dx + dy * dy);
                if (d > 0)
                {
                    double f = k * k / d;
                    forces[j].x += f * dx / d;
                    forces[j].y += f * dy / d;
                    forces[k].x -= f * dx / d;
                    forces[k].y -= f * dy / d;
                }
            }
        }
        // Calculate attractive forces
        for (auto &e : edgeVector)
        {
            double dx = positions[e.u].x - positions[e.v].x;
            double dy = positions[e.u].y - positions[e.v].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d > 0)
            {
                double f = d * d / k;
                forces[e.u].x -= f * dx / d;
                forces[e.u].y -= f * dy / d;
                forces[e.v].x += f * dx / d;
                forces[e.v].y += f * dy / d;
            }
        }
        for (unsigned j = 0; j < positions.size(); j++)
        {
            double dx = t * forces[j].x;
            double dy = t * forces[j].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d > 0)
            {
                double limited_d = std::min(d, k);
                positions[j].x += limited_d * dx / d;
                positions[j].y += limited_d * dy / d;
            }
        }
        for (auto &n : positions)
        {
            n.x = std::max(0.0, std::min(n.x, (double)width));
            n.y = std::max(0.0, std::min(n.y, (double)height));
        }
        t -= 0.1;
    }
    return positions;
}

cs225::PNG PlayerGraph::drawGraph(int height, int width)
{
    std::vector<Coordinate> positions = fruchtermanReingold(height, width, 0.1, 0.1, 100);
    cs225::PNG img;
    img.resize(width, height);
    for (Coordinate position : positions)
    {
        cs225::HSLAPixel &pixel = img.getPixel(position.x, position.y);
        pixel.l = 0;
    }
    return img;
}
 */