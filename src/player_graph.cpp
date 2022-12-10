#include "player_graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>


std::vector<Node *> PlayerGraph::file_to_graph(const std::string filename)
{
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
            idx++;
        }
    }

    for (Node *node : node_vect)
    {
        std::cout << "PRINT NODE" << std::endl;
        node->print();
        node->print_adj();
    }

    return node_vect;
}

PlayerGraph::PlayerGraph(const std::string filename) {
        nodeVector = file_to_graph(filename);
        edgeVector = std::vector<Edge>();
}

std::vector<std::string> PlayerGraph::BFS(std::string startID, std::string endID) {
    int src = 0;
    int endp = 0;
    bool foundsrc = false;
    bool foundend = false;
    for (Node* player : nodeVector) {
        std::string id = player->id_;
        std::string pyear = player->year_;
        if (id.find(startID) != std::string::npos) {
            foundsrc = true;
        }
        if (id.find(endID) != std::string::npos) {
            foundend = true;
        }
        if (!foundsrc) src++;
        if (!foundend) endp++;
    }

    if (src == (int)nodeVector.size() || endp == (int)nodeVector.size()) {
        std::cout << "Player does not exist" << std::endl;
        return std::vector<std::string>();
    }

    std::vector<std::string> result = BFS(src, endp);
    if (result.size() == 0) {
        std::cout << "Connection between " << startID << " and " << endID <<  "does not exist" << std::endl;
    } else  {
        std::cout<< "Connection Exist" << std::endl;
    }
    return result;
}
  

std::vector<std::string> PlayerGraph::BFS(int startingNode, int finishNode) {
    std::vector<int> prev(nodeVector.size(), -1);
    std::vector<bool> visited(nodeVector.size(), false);
    std::queue<int> q;

    q.push(startingNode);
    visited[startingNode] = true;

    while (!q.empty()) {
        int v = q.front();
        Node* curr = nodeVector[v];
        q.pop();

        for (auto neigh : curr->adj_) {
            if (visited[neigh.first->idx] == false) {
                prev[neigh.first->idx] = v;
                q.push(neigh.first->idx);
            }
        }
        visited[v] = true;
        if (v == finishNode) break;
    }

    std::vector<std::string> result;
    while (finishNode != -1) {
        result.push_back(nodeVector[finishNode]->id_);
        finishNode = prev[finishNode];
    }
    std::reverse(result.begin(), result.end());
    return result;    
}

Node* PlayerGraph::PlayerExists(std::string name) {
    for (Node* node : nodeVector) {
        if (name.find(node->id_) != std::string::npos) return node;
    }
    return nullptr;
}

std::pair<std::vector<int>, std::vector<int>> PlayerGraph::Djikstras(int src) {
    std::vector<int> distances(nodeVector.size(), INT_MAX);
    std::vector<int> prev(nodeVector.size(), -1);
    std::vector<bool> visited(nodeVector.size(), false);
    std::priority_queue<std::pair<int, int>, std::vector<pair<int, int>>, std::greater<std::pair<int, int>>> heap;

    distances[src] = 0;
    heap.push(std::pair<int, int>(0, src));

    while (!heap.empty()) {
        std::pair<int, int> vertex = heap.top();
        Node* curr = nodeVector[vertex.second];
        heap.pop();
        for (auto neighbor : curr->adj_) {
            if (!visited[neighbor.first->idx]) {
                if (neighbor.second + vertex.first < distances[neighbor.first->idx]) {
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

std::pair<std::vector<int>, std::vector<int>> PlayerGraph::Djikstras(std::string playerName, std::string playerYear) {
    int src = 0;

    for (Node* player : nodeVector) {
        std::string id = player->id_;
        std::string year = player->year_;
        if (id.find(playerName) != std::string::npos && year == playerYear) {
            break;
        }
        src++;
    }

    if (src == (int)nodeVector.size()) {
        std::cout << "Player does not exist" << std::endl;
        return std::pair<std::vector<int>, std::vector<int>>(std::vector<int>(), std::vector<int>());
    }

    return Djikstras(src);
}

std::vector<Coordinate> PlayerGraph::fruchtermanReingold(int height, int width, double k, double t, int iterations) {
    std::vector<Coordinate> positions;
    for (auto& n : positions) {
        n.x = rand() % width;
        n.y = rand() % height;
    }
    for (int i = 0; i < iterations; i++) {
        std::vector<Coordinate> forces(positions.size(), {0, 0});
        // Calculate repulsive forces
        for (unsigned j = 0; j < positions.size(); j++) {
            for (unsigned k = j + 1; k < positions.size(); k++) { 
                double dx = positions[j].x - positions[k].x;
                double dy = positions[j].y - positions[k].y;
                double d = std::sqrt(dx * dx + dy * dy);
                if (d > 0) {
                double f = k * k / d;
                forces[j].x += f * dx / d;
                forces[j].y += f * dy / d;
                forces[k].x -= f * dx / d;
                forces[k].y -= f * dy / d;
                }
            }
        }
        // Calculate attractive forces
        for (auto& e : edgeVector) {
            double dx = positions[e.u].x - positions[e.v].x;
            double dy = positions[e.u].y - positions[e.v].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d > 0) {
                double f = d * d / k;
                forces[e.u].x -= f * dx / d;
                forces[e.u].y -= f * dy / d;
                forces[e.v].x += f * dx / d;
                forces[e.v].y += f * dy / d;
            }
        }
        for (unsigned j = 0; j < positions.size(); j++) {
            double dx = t * forces[j].x;
            double dy = t * forces[j].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d > 0) {
                double limited_d = std::min(d, k);
                positions[j].x += limited_d * dx / d;
                positions[j].y += limited_d * dy / d;
            }
        }
        for (auto& n : positions) {
            n.x = std::max(0.0, std::min(n.x, (double)width));
            n.y = std::max(0.0, std::min(n.y, (double)height));
        }
        t -= 0.1;
    }
    return positions;
}

cs225::PNG PlayerGraph::drawGraph(int height, int width) {
    std::vector<Coordinate> positions = fruchtermanReingold(height , width, 0.1, 0.1, 100);
    cs225::PNG img;
    img.resize(width, height);
    for (Coordinate position : positions) {
        cs225::HSLAPixel& pixel = img.getPixel(position.x, position.y);
        pixel.l = 0;
    }
    return img;
}
