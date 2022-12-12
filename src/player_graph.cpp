#include "player_graph.h"

std::vector<Node*> PlayerGraph::file_to_graph(const std::string filename)
{
    std::vector<Node*> vertices;
    std::vector<Edge> edges;
    std::map<std::string, Info> players;
    std::map<std::pair<std::string, std::string>, std::set<std::string>> teams;
    std::ifstream file(filename);
    std::string line;
    unsigned idx = 0;

    if (file.is_open()) {
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::vector<std::string> player;
            std::stringstream ss(line);
            while (ss.good()) {
                std::string item;
                std::getline(ss, item, ',');
                player.push_back(item);
            }
            std::string name = player[3];
            if (name[name.length() - 1] == '*') {
                name = name.substr(0, name.length() - 1);
            }
            std::pair<std::string, std::string> team(player[6], player[2]);
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

    std::vector<bool> visited(players.size(), false);

    for (auto& player : players) {
        int playerPos = player.second.idx;
        visited[playerPos] = true;
        for (std::string teammate : player.second.teammates) {
            vertices[playerPos]->adj_[vertices[players[teammate].idx]] = (1 / (vertices[playerPos]->per_ + vertices[players[teammate].idx]->per_) / 2);
            Edge edge(player.second.idx, players[teammate].idx, (1 / (vertices[playerPos]->per_ + vertices[players[teammate].idx]->per_) / 2));
            if (!visited[players[teammate].idx]) {
                edges.push_back(edge);
            }
        }
    }

    edgeVector = edges;

    return vertices;
}

PlayerGraph::PlayerGraph(const std::string filename) {
        nodeVector = file_to_graph(filename);
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
        return std::vector<std::string>();
    }

    std::vector<std::string> result = BFS(src, endp);
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
                visited[neigh.first->idx_] = true;
            }
        }
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

std::pair<std::vector<float>, std::vector<int>> PlayerGraph::Djikstras(int src) {
    std::vector<float> distances(nodeVector.size(), FLT_MAX);
    std::vector<int> prev(nodeVector.size(), -1);
    std::vector<bool> visited(nodeVector.size(), false);
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> heap;

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

std::vector<Point>  PlayerGraph::fruchtermanReingold(std::vector<Node*> vertices, std::vector<Edge> edges, int height, int width, int iterations) {
    std::vector<Point> positions(vertices.size(), Point(0, 0));
    double k = std::sqrt(height * width / positions.size());
    double temperature = width / 10;

    for (Point& position : positions) {
        position.x = rand() % width;
        position.y = rand() % height;
    }

    drawGraph(height, width, positions, edges).writeToFile("../before.png");

    for (int i = 0; i < iterations; i++) {
        std::vector<Point> displacements(positions.size(), Point(0, 0));
        // Repulsive forces
        for (unsigned j = 0; j < positions.size(); j++) {
            for (unsigned k = 0; k < positions.size(); k++) {
                if (j == k) continue;
                double dx = positions[j].x - positions[k].x;
                double dy = positions[j].y - positions[k].y;
                double distance = std::sqrt(dx * dx + dy * dy);
                if (distance > 0) {
                    double repulsion = (k * k) / distance;
                    displacements[j].x += dx / distance * repulsion;
                    displacements[j].y += dy / distance * repulsion;
                }
            }
        }
        // Attractive forces 
        for (Edge e : edges) {
            double dx = positions[e.v].x - positions[e.u].x;
            double dy = positions[e.v].y - positions[e.u].y;
            double distance = sqrt(dx * dx + dy * dy);
            if (distance > 0) {
                double attraction = (distance * distance) / k;
                displacements[e.v].x -= dx / distance * attraction;
                displacements[e.v].y -= dy / distance * attraction;
                displacements[e.u].x += dx / distance * attraction;
                displacements[e.u].y += dy / distance * attraction;
            }
        }
        // Adjust positions
        for (unsigned j = 0; j < positions.size(); j++) {
            double dx = displacements[j].x;
            double dy = displacements[j].y;
            double displacement_norm = std::sqrt(dx * dx + dy * dy);
            double capped_displacement_norm = std::min(displacement_norm, temperature);
            if (displacement_norm > 0) {
                positions[j].x += dx / displacement_norm * capped_displacement_norm;
                positions[j].y += dy / displacement_norm * capped_displacement_norm;
            }
        }
        // Fix positions outside of frame
        for (auto& n : positions) {
            n.x = std::max(0.0, std::min(n.x, (double)width - 1));
            n.y = std::max(0.0, std::min(n.y, (double)height - 1));
        }
        // Lower temperature
        temperature -= (width / 10) / iterations;
    }

    drawGraph(height, width, positions, edges).writeToFile("../after.png");

    return positions;
}

std::vector<Point> PlayerGraph::fruchtermanReingold(std::string playerName) {
    Node* player = getPlayer(playerName);

    if (player == NULL) {
        return std::vector<Point>();
    }

    std::vector<Node*> vertices;
    std::vector<Edge> edges;
    int idx = 1;
 
    vertices.push_back(player);
    for (auto teammate : player->adj_) {
        Edge e(0, idx, teammate.second);
        vertices.push_back(teammate.first);
        edges.push_back(e);
        idx++;
    }

    return fruchtermanReingold(vertices, edges, 1000, 1000, 50);
}

cs225::PNG PlayerGraph::drawGraph(int height, int width, std::vector<Point> nodes, std::vector<Edge> edges) {
    // Create empty image
    cs225::PNG img;
    img.resize(width, height);

    // Add nodes
    for (Point node : nodes) {
        for (int i = -2; i < 3; i++) {
            for (int j = -2 ; j < 3; j++) {
                cs225::HSLAPixel& pixel = img.getPixel(node.x + i, node.y + j);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
            }
        }
    }

    // Add edges
    for (auto e : edges) {
        Point p1(nodes[e.u].x, nodes[e.u].y);
        Point p2(nodes[e.v].x, nodes[e.v].y);
        std::vector<Point> points = line(p1, p2);

        for (Point point : points) {
            cs225::HSLAPixel& pixel = img.getPixel(point.x, point.y);
            pixel.l = 0.0;
        }
    } 

    return img;
}

std::vector<Point> PlayerGraph::line(Point p1, Point p2) {
    std::vector<Point> points;
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double length = sqrt(dx * dx + dy * dy);
    int n = length;

    for (int i = 0; i < n; i++) {
        double x = round(p1.x + (i + 1) * dx / n);
        double y = round(p1.y + (i + 1) * dy / n);
        Point point(x, y);
        points.push_back(point);
    }

    return points;
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

bool PlayerGraph::PlayerExists(std::string name) {
    for (Node* node : nodeVector) {
        if (node->name_ == name) return true;
    }
    return false;
}