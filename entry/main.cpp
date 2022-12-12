#include "player_graph.h"

int main() {
    // Create graph
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);

    // User input variables
    std::string playerOne;
    std::string playerTwo;
    std::string algorithm;

    // Algorithm selection
    std::cout << std::endl;
    std::cout << "Welcome to the NBA Player Graph!" << std::endl;
    std::cout << std::endl;
    std::cout << "There are three different algorithms to choose from: BFS, Djikstra's, Fruchterman-Reingold Layout." << std::endl;
    std::cout << "Please select one by entering 'bfs', 'djikstras', or 'fr': ";
    std::cin >> algorithm;

    while (algorithm != "bfs" && algorithm != "djikstras" && algorithm != "fr") {
        std::cout << "Please enter a valid algorithm with correct spelling and capitalization: 'bfs', 'djikstras', 'fr': ";
        std::cin >> algorithm;
    }

    // Run selected algorithm with custom prompts
    if (algorithm == "bfs") {
        std::cout << std::endl;
        std::cout << "You have selected BFS. This will give you the shortest path between any two players using only mutual teammates." << std::endl;
        std::cout << "Enter the full name of the first player: ";
        std::cin.ignore();
        getline(std::cin, playerOne);
        while (!playerGraph.PlayerExists(playerOne)) {
            std::cout << "Please enter a valid player name: ";
            getline(std::cin, playerOne);
        }
        std::cout << "Enter the full name of the second player: ";
        getline(std::cin, playerTwo);
        while (!playerGraph.PlayerExists(playerOne)) {
            std::cout << "Please enter a valid player name: ";
            getline(std::cin, playerOne);
        }
        std::vector<std::string> bfs = playerGraph.BFS(playerOne, playerTwo);
        if (bfs.empty()) {
            std::cout << std::endl;
            std::cout << "There is no path between the two players." << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "Here is the path between the two: ";
            for (std::string player : bfs) {
                if (player != playerOne) std::cout << " --> " << playerGraph.getPlayer(player)->print_name();
                else std::cout << playerGraph.getPlayer(player)->print_name();
            }
            std::cout << std::endl;
        }
    } else if (algorithm == "djikstras") {
        std::cout << std::endl;
        std::cout << "You have selected Djikstra's. This will give you the shortest path between any two players using only mutual teammates with the highest PER." << std::endl;
        std::cout << "Enter the full name of the first player: ";
        std::cin.ignore();
        getline(std::cin, playerOne);
        while (!playerGraph.PlayerExists(playerOne)) {
            std::cout << "Please enter a valid player name: ";
            getline(std::cin, playerOne);
        }
        std::cout << "Enter the full name of the second player: ";
        getline(std::cin, playerTwo);
        while (!playerGraph.PlayerExists(playerTwo)) {
            std::cout << "Please enter a valid player name: ";
            getline(std::cin, playerTwo);
        }
        std::pair<std::vector<float>, std::vector<int>> shortestPaths = playerGraph.Djikstras(playerTwo);
        std::vector<float> distances = shortestPaths.first;
        std::vector<int> prev = shortestPaths.second;
        Node* player = playerGraph.getPlayer(playerOne);
        std::cout << std::endl;
        std::cout << "Here is the path between the two with average: ";
        std::cout << player->print_name();
        while (player->name_ != playerTwo) {
            int next = prev[player->idx_];
            player = playerGraph.getPlayer(next);
            std::cout << " --> " << player->print_name();
        }
        std::cout << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "You have selected Fruchterman-Reingold layout. This will give you a before and after graph drawing of a player and his teammates." << std::endl;
        std::cout << "Enter the full name of the first player: ";
        std::cin.ignore();
        getline(std::cin, playerOne);
        while (!playerGraph.PlayerExists(playerOne)) {
            std::cout << "Please enter a valid player name: ";
            getline(std::cin, playerOne);
        }
        playerGraph.fruchtermanReingold(playerOne);
        std::cout << std::endl;
        std::cout << "Success! Please see the graph drawings under 'before.png' and 'after.png'." << std::endl;
    }

    return 0;
}