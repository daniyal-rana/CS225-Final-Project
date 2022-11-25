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