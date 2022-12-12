#include <catch2/catch_test_macros.hpp>

#include "player_graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <queue>
#include <cmath>
#include <algorithm>


TEST_CASE("BFS Test Case 0", "No Player Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Darrell Arthur", "Kyle Wiltjer");

    REQUIRE(output.size() == 1);

    output = playerGraph.BFS("Hilton Armstrong", "Jeff Withey");
    REQUIRE(output.size() == 1);

    output = playerGraph.BFS("Stephen Zimmerman", "Nick Young");
    REQUIRE(output.size() == 1);
}

TEST_CASE("BFS Test Case 1", "Direct Player Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Troy Williams", "Nick Young");
    answer = {"Troy Williams", "Nick Young"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Brandan Wright", "Joel Anthony");
    answer = {"Brandan Wright", "Joel Anthony"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Kyle Wiltjer", "Jeff Withey");
    answer = {"Kyle Wiltjer", "Jeff Withey"};
    REQUIRE(output == answer);
}

TEST_CASE("BFS Test Case 2", "One Mutual Teammate Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Nick Young", "Brandan Wright");
    answer = {"Nick Young", "Troy Williams", "Brandan Wright"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Gilbert Arenas", "Jeff Withey");
    answer = {"Gilbert Arenas", "Kyle Wiltjer", "Jeff Withey"};
    REQUIRE(output == answer);
}

TEST_CASE("BFS Test Case 3", "Two Mutual Teammate Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Jeff Withey", "Nick Young");
    answer = {"Jeff Withey", "Kyle Wiltjer", "Troy Williams", "Nick Young"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Carmelo Anthony", "Antonio Anderson");
    answer = {"Carmelo Anthony", "Troy Williams", "Kyle Wiltjer", "Antonio Anderson"};
    REQUIRE(output == answer);
}





TEST_CASE("DJIKSTRAS Test Case 0", "No Player Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::string playerOne = "Troy Williams";
    std::string playerTwo = "Stephen Zimmerman";

    std::pair<std::vector<float>, std::vector<int>> shortestPaths = playerGraph.Djikstras(playerTwo);
    std::vector<float> distances = shortestPaths.first;
    std::vector<int> prev = shortestPaths.second;
    Node* player = playerGraph.getPlayer(playerOne);
    std::vector<std::string> output;
    
    std::vector<std::string> ans;
    REQUIRE(ans.size() == output.size());
}

TEST_CASE("DJIKSTRAS Test Case 1", "Direct Player Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::string playerOne = "Troy Williams";
    std::string playerTwo = "Nick Young";

    std::pair<std::vector<float>, std::vector<int>> shortestPaths = playerGraph.Djikstras(playerTwo);
    std::vector<float> distances = shortestPaths.first;
    std::vector<int> prev = shortestPaths.second;
    Node* player = playerGraph.getPlayer(playerOne);
    std::vector<std::string> output;
    output.push_back(player->name_);
    while (player->name_ != playerTwo) {
        int next = prev[player->idx_];
        player = playerGraph.getPlayer(next);
        output.push_back(player->name_);
    }

    std::vector<std::string> ans;
    ans = {"Troy Williams", "Nick Young"};
    REQUIRE(ans == output);
}

TEST_CASE("DJIKSTRAS Test Case 2", "One Mutual Teammate Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::string playerOne = "Kyle Wiltjer";
    std::string playerTwo = "Nick Young";

    std::pair<std::vector<float>, std::vector<int>> shortestPaths = playerGraph.Djikstras(playerTwo);
    std::vector<float> distances = shortestPaths.first;
    std::vector<int> prev = shortestPaths.second;
    Node* player = playerGraph.getPlayer(playerOne);
    std::vector<std::string> output;
    output.push_back(player->name_);
    while (player->name_ != playerTwo) {
        int next = prev[player->idx_];
        player = playerGraph.getPlayer(next);
        output.push_back(player->name_);
    }

    std::vector<std::string> ans;
    ans = {"Kyle Wiltjer", "Troy Williams", "Nick Young"};
    REQUIRE(ans == output);
}

TEST_CASE("DJIKSTRAS Test Case 3", "Two Mutual Teammate Connection") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::string playerOne = "Jeff Withey";
    std::string playerTwo = "Nick Young";

    std::pair<std::vector<float>, std::vector<int>> shortestPaths = playerGraph.Djikstras(playerTwo);
    std::vector<float> distances = shortestPaths.first;
    std::vector<int> prev = shortestPaths.second;
    Node* player = playerGraph.getPlayer(playerOne);
    std::vector<std::string> output;
    output.push_back(player->name_);
    while (player->name_ != playerTwo) {
        int next = prev[player->idx_];
        player = playerGraph.getPlayer(next);
        output.push_back(player->name_);
    }

    std::vector<std::string> ans;
    ans = {"Jeff Withey", "Kyle Wiltjer", "Troy Williams", "Nick Young"};
    REQUIRE(ans == output);
}


TEST_CASE("FR Algorithm Test Case 1", "Same Number of Points") {
    const std::string filename = "../data/TEST_NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);

    std::string playerOne = "Troy Williams";


    Node* player = playerGraph.getPlayer(playerOne);

    std::vector<Node*> vertices;

 
    vertices.push_back(player);
    for (auto teammate : player->adj_) {
        vertices.push_back(teammate.first);
    }

    std::vector<Point> ans = playerGraph.fruchtermanReingold(playerOne);
    std::cout << ans.size() << std::endl;
    std::cout << vertices.size() << std::endl;

    REQUIRE(ans.size() == vertices.size());
}
