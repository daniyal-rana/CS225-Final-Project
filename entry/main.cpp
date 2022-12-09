#include "player_graph.h"

int main()
{
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    playerGraph.drawGraph(1000, 1000).writeToFile("./myImage.png");
    std::cout << "Hello" << std::endl;
    return 0;
}