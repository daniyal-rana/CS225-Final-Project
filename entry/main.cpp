#include "player_graph.h"

int main() {
    // Create graph
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);

    // Run algorithms
    std::vector<std::string> bfs = playerGraph.BFS("Brad Miller", "LeBron James");
    std::pair<std::vector<float>, std::vector<int>> shortestPaths = playerGraph.Djikstras("LeBron James");

    // Display results
    std::vector<float> distances = shortestPaths.first;
    std::vector<int> prev = shortestPaths.second;

    std::cout << '\n';
    std::cout << "BFS" << std::endl;
    for (std::string player : bfs) {
        playerGraph.getPlayer(player)->print();
    }
    
    std::cout << '\n';
    std::cout << "Shortest Paths" << std::endl;
    Node* player = playerGraph.getPlayer("Brad Miller");
    player->print();
    while (player->name_ != "LeBron James") {
        int next = prev[player->idx_];
        player = playerGraph.getPlayer(next);
        player->print();
    }

    // Run Fruchterman-Reingold algorithm
    playerGraph.fruchtermanReingold("LeBron James");

    return 0;
}