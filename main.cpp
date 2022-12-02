#include "player_graph.hpp"
#include <iostream>
int main()
{
    PlayerGraph p("NBA_STATS_WITH_PER.csv");
    std::cout << "static constructor";
}