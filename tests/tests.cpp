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
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Andre Drummond", "Charles Thomas McMillen");
    answer = {};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Deandre Ayton", "Marvin Bagley III");
    answer = {};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Trae Young", "Luca Doncic");
    answer = {};
    REQUIRE(output == answer);
}

TEST_CASE("BFS Test Case 1", "Direct Player Connection") {
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Bradley Beal", "John Wall");
    answer = {"Bradley Beal", "John Wall"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Kevin Garnett", "Paul Pierce");
    answer = {"Kevin Garnett", "Paul Pierce"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Isaiah Rider", "Chuck Person");
    answer = {"Isaiah Rider", "Chuck Person"};
    REQUIRE(output == answer);
}

TEST_CASE("BFS Test Case 2", "One Mutual Teammate Connection") {
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    output = playerGraph.BFS("Dwyane Wade", "Kobe Bryant");
    answer = {"Dwyane Wade", "Jason Kapono","Kobe Bryant"};
    REQUIRE(output == answer);

    // output = playerGraph.BFS("Marlon Maxey", "Michael Jordan");
    // answer = {"Marlon Maxey", "Christian Laettner","Michael Jordan"};
    // REQUIRE(output == answer);

    output = playerGraph.BFS("Pau Gasol", "Tim Duncan");
    answer = {"Pau Gasol", "Tony Parker", "Tim Duncan"};
    REQUIRE(output == answer);
}

TEST_CASE("BFS Test Case 3", "Two Mutual Teammate Connection") {
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    // output = playerGraph.BFS("Michael Beasley", "George Gervin");
    // answer = {"Michael Beasley", "Brad Miller", "Charles Oakley","George Gervin"};
    // REQUIRE(output == answer);

    output = playerGraph.BFS("Carmelo Anthony", "Bison Dele");
    answer = {"Carmelo Anthony", "Von Wafer", "Theo Ratliff", "Bison Dele"};
    REQUIRE(output == answer);

    output = playerGraph.BFS("Manute Bol", "Chris Paul");
    answer = {"Manute Bol", "Tom Gugliotta", "Speedy Claxton", "Chris Paul"};
    REQUIRE(output == answer);
}

TEST_CASE("BFS Test Case 4", "Multiple Mutual Teammate Connection") {
    const std::string filename = "../data/NBA_STATS_WITH_PER.csv";
    PlayerGraph playerGraph(filename);
    std::vector<std::string> output;
    std::vector<std::string> answer;

    // output = playerGraph.BFS("Rick Barry", "Lamarcus Aldridge");
    // answer = {"Rick Barry", "George Johnson", "Herb Williams", "Marcus Camby", "Lamarcus Aldridge", "Lamarcus Aldridge"};
    // REQUIRE(output == answer);

    // output = playerGraph.BFS("Bob Cousy", "Ricky Rubio");
    // answer = {"Bob Cousy", "John Havlicek", "Cedric Maxwell", "Benoit Benjamin", "Andre Miller", "Ricky Rubio"};
    // REQUIRE(output == answer);

    // output = playerGraph.BFS("Calvin Murphy", "Ricky Rubio");
    // answer = {"Calvin Murphy", "Elvin Hayes", "Rick Mahorn", "Nazr Mohammed", "Russell Westbrook"};
    // REQUIRE(output == answer);
}

