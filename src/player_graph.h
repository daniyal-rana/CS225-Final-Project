#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include "cs225/PNG.h"

// This struct is used to help construct our graph.
// It includes a set of a player's all time teammates, the total PER over all seasons, seasons count, and the index of the location in nodeVector
struct Info {
    std::set<std::string> teammates;
    float per;
    int count;
    unsigned idx;
};

// This struct is used to represent our nodes/players in our graph.
// It store the index of the location in nodeVector, the name of the player, the average PER of the player, and the node's adjacency list.
struct Node
{
    unsigned idx_;
    std::string name_;   
    float per_;
    std::unordered_map<Node*, float> adj_;

    Node(unsigned IDX, std::string NAME, float PER)
    {
        idx_ = IDX;
        name_ = NAME;
        per_ = PER;
    }

    std::string print_name() {
        return name_;
    }

    void print() {
        std::cout << name_ << " " << per_ << std::endl;
    }

    void print_adj() {
        std::cout << "ADJ" << std::endl;

        for (std::pair<Node*, float> pair : adj_)
        {
            pair.first->print();
            std::cout << "\tEDGE: " << pair.second << std::endl;
        }
    }
};

// This struct is used to represent our edges in the graph.
// It store two integers: u and v.
// These represent the index positions of the two connected nodes in nodeVector.
// It also stores the weight of the edge which is the average PER betweeen the two players.
struct Edge {
    int u;
    int v;
    float weight;

    Edge(int U, int V, int WEIGHT) {
        u = U;
        v = V;
        weight = WEIGHT;
    }
};

// This struct is used to help draw a graphical output of our graph.
// It includes both an x and y coordinate to represent the position of a point on a PNG.
struct Point {
    double x;
    double y;

    Point(double X, double Y) {
        x = X;
        y = Y;
    }
};

// This class represents our graph of all NBA players in our dataset. 
// It includes various algorithms including BFS, Djikstra's, Fruchterman-Reingold Layout.
class PlayerGraph {
    public:
        // PlayerGraph Constructor
        // This constructor takes in a filename and constructs our PlayerGraph object.
        PlayerGraph(const std::string filename);
        // PlayerGraph Constructor Helper Method
        // This function takes in a filename and parses the file to create our PlayerGraph.
        // The function returns a vector of all the nodes in the graph.
        std::vector<Node*> file_to_graph(const std::string filename);
        // BFS Public Function
        // This function takes in two strings which represent the two names of the two players we wish to find a path between. 
        // If neither of the two players exist in our graph, then the function will return an empty vector.
        // Else, the function will call our private BFS function and return its output.
        std::vector<std::string> BFS(std::string startID, std::string endID);
        // Djikstra's Algorithm Public Function
        // This function takes in a string which represents the name of the player whom we wish to be the source node for Djikstra's algorithm.
        // If the player does not exist in our graph, then the function will return a pair of empty vectors.
        // Else, the function will call our private Djikstra's function and return its output.
        std::pair<std::vector<float>, std::vector<int> > Djikstras(std::string playerName);
        // Fruchterman-Reingold Layout Algorithm Public Function
        // This function takes in a string which represents the name of the player whom we wish to run the Fruchterman-Reingold algorithm on.
        // If the player does not exist in our graph, then the function will return an empty vector of points.
        // Else, the function will call our private Fruchterman-Reingold function and return its output
        // When calling the private function, it will call it with the following parameters:
        // height := 1000, width := 1000, iterations := 100
        // vertices := vector of nodes of a 1 depth graph from the input player, edges := vector of edges of a 1 depth graph from the input player
        std::vector<Point> fruchtermanReingold(std::string playerName);
        // This function takes in a height, width, a vector of positions for our nodes, and a vector of the edges.
        // The output is a PNG object that represents the graph of the input vertices and edges with a height and width equal to the input.
        cs225::PNG drawGraph(int height, int width, std::vector<Point> nodes, std::vector<Edge> edges);
        // This function takes in two points with x and y coordinates.
        // The output is a vector of points that, in order, is the straight line of points from p1 to p2.
        std::vector<Point> line(Point p1, Point p2);
        // This function takes in an integer representing the index of a player in our vector of nodes.
        // It will return Node* at the index location in nodeVector.
        Node* getPlayer(int idx);
        // This function takes in a string representing the player name of a player in our graph.
        // It will return Node* at the index location in nodeVector if the player is in our graph.
        // Else, it will return NULL
        Node* getPlayer(std::string name);
        // This function tkaes in a string representing the name of a player.
        // It will return true if the player is in our graph and false otherwise.
        bool PlayerExists(std::string name);

    private:
        // Our nodeVector stores all of our nodes in our PlayerGraph.
        std::vector<Node*> nodeVector;
        // Our edgeVector stores all of edges in our Player Graph.
        std::vector<Edge> edgeVector;
        // BFS Private Function
        // This function takes in two integers that represent the starting point and end point of the two players we wish to connect.
        // The integers represent the index of each player in the vector of nodes in our graph.
        // The output is a vector of strings which, in order, gives us a path of mutual teammates from startingNode to finishNode.
        std::vector<std::string> BFS(int startingNode, int finishNode);
        // Djikstra's Algorithm Private Function
        // This functions takes in one integer that represent the source node of Djikstra's algorithm. 
        // This function will compute the shortest path from every node in the graph to the source node.
        // The output is a pair of two vectors.
        // The first vector is the distance vector. For any index in the vector of nodes, it will return the shortest distance from that node to the source node.
        // The second vector is the previous vector. For any index in the vector of nodes, it will return the previous node's index in its shortest path to the source node.
        std::pair<std::vector<float>, std::vector<int> > Djikstras(int src);
        // Fruchterman-Reingold Layout Algorithm Private Function
        // This function takes in a vector of nodes, a vector of edges, a height, a width, and a number of iterations.
        // The vector of nodes and vector of edges will be what we use to draw a graph layout.
        // The height and width represent the height and width of the PNG image.
        // The iterations represents the number of iterations that the algorithm will run for.
        // The output is a vector of points for every one of the nodes in the vector of nodes. These points include both an x and y coordinate on the PNG image.
        // This function will also write a PNG to two files. These files are 'before.png' and 'after.png'.
        // 'before.png' is how our graph looks before the algorithm runs.
        // 'after.png' is how our graph looks after the algorithm runs.
        std::vector<Point> fruchtermanReingold(std::vector<Node*> vertices, std::vector<Edge> edges, int height, int width, int iterations);
};
