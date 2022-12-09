#include "player_graph.hpp"

int main()
{
    std::vector<Node *> vect_graph = file_to_graph("NBA_STATS_WITH_PER.csv");
    return 0;
}