#include "player_graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <algorithm>


std::vector<Node *> PlayerGraph::file_to_graph(const std::string filename)
{
    std::vector<Node*> vertices;
    std::map<std::string, Info> players;
    std::map<std::pair<std::string, std::string>, std::set<std::string>> teams;
    std::ifstream file(filename);
    std::string line;
    unsigned idx = 0;

    if (file.is_open()) {
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::vector<std::string> player;
            stringstream ss(line);
            while (ss.good()) {
                std::string item;
                std::getline(ss, item, ',');
                player.push_back(item);
            }
            std::string name = player[3]; // player name
            std::pair<std::string, std::string> team(player[6], player[2]); // team.first --> team, team.second --> year
            float per = std::stof(player[player.size() - 1]);
            if (per < 0.0) per = 0.0;
            if (players.find(name) == players.end()) {
                Info info;
                info.teammates = std::set<std::string>();
                info.per = per;
                info.count = 1;
                players[name] = info;
            } else {
                players[name].per += per;
                players[name].count++;
            }
            // Update the player's teammates set
            // Set doesn't allow duplicates! Hooray!
            if (teams.find(team) != teams.end()) {
                for (std::string teammate : teams[team]) {
                    players[name].teammates.insert(teammate);
                    players[teammate].teammates.insert(name);
                }
            }
            teams[team].insert(name);
        }
    }

    for (auto& player : players) {
        Node* vertex = new Node(idx, player.first, player.second.per / player.second.count);
        vertices.push_back(vertex);
        player.second.idx = idx;
        idx++;
    }

    for (auto& player : players) {
        int playerPos = player.second.idx;
        for (std::string teammate : player.second.teammates) {
            vertices[playerPos]->adj_[vertices[players[teammate].idx]] = (1 / (vertices[playerPos]->per_ + vertices[players[teammate].idx]->per_) / 2);
        }
    }

    return vertices;
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
        std::string name = player->name_;
        if (name == startID) {
            foundsrc = true;
        }
        if (name == endID) {
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
            if (visited[neigh.first->idx_] == false) {
                prev[neigh.first->idx_] = v;
                q.push(neigh.first->idx_);
            }
        }
        visited[v] = true;
        if (v == finishNode) break;
    }

    std::vector<std::string> result;
    while (finishNode != -1) {
        result.push_back(nodeVector[finishNode]->name_);
        finishNode = prev[finishNode];
    }
    std::reverse(result.begin(), result.end());
    return result;    
}


Node* PlayerGraph::PlayerExists(std::string name) {
    for (Node* node : nodeVector) {
        if (name.find(node->name_) != std::string::npos) return node;
    }
    return nullptr;
}

std::pair<std::vector<float>, std::vector<int>> PlayerGraph::Djikstras(int src) {
    std::vector<float> distances(nodeVector.size(), FLT_MAX);
    std::vector<int> prev(nodeVector.size(), -1);
    std::vector<bool> visited(nodeVector.size(), false);
    std::priority_queue<std::pair<float, int>, std::vector<pair<float, int>>, std::greater<std::pair<float, int>>> heap;

    distances[src] = 0;
    heap.push(std::pair<float, int>(0.0, src));

    while (!heap.empty()) {
        std::pair<float, int> vertex = heap.top();
        Node* curr = nodeVector[vertex.second];
        heap.pop();
        for (auto neighbor : curr->adj_) {
            if (!visited[neighbor.first->idx_]) {
                if (neighbor.second + vertex.first < distances[neighbor.first->idx_]) {
                    distances[neighbor.first->idx_] = neighbor.second + vertex.first;
                    prev[neighbor.first->idx_] = curr->idx_;
                    heap.push(std::pair<float, int>(neighbor.second + vertex.first, neighbor.first->idx_));
                }
            }
        }
        visited[curr->idx_] = true;
    }

    std::pair<std::vector<float>, std::vector<int>> result(distances, prev);
    return result;
}

std::pair<std::vector<float>, std::vector<int>> PlayerGraph::Djikstras(std::string playerName) {
    int src = 0;

    for (Node* player : nodeVector) {
        std::string name = player->name_;
        if (playerName == name) {
            break;
        }
        src++;
    }

    if (src == (int)nodeVector.size()) {
        std::cout << "Player does not exist" << std::endl;
        return std::pair<std::vector<float>, std::vector<int>>(std::vector<float>(), std::vector<int>());
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

 Node* PlayerGraph::getPlayer(int idx) {
    return nodeVector[idx];
 }

 Node* PlayerGraph::getPlayer(std::string name) {
    for (Node* player : nodeVector) {
        if (player->name_ == name) {
            return player;
        }
    }
    return NULL;
 }