
# <ins align = "center"> CS225-Final-Project </ins>

# How to use the Code
## Download and Install Clang++ https://clang.llvm.org/get_started.html
1. Delete build folder
2. Replace previous folder with a new version
3. In your terminal, move into the build folder and type cmake ..
4. Still in this directory, type make main to compile the main executable
5. Type ./main to run the executable
6. When running the executable, there is the opportunity to run 3 different algorithms in our NBA Player Graph

BFS:
Input 2 players that exists in the graph
You will receive a response that starts from your first input to you last input.

Dijkstra's:
Input 2 players that exists in the graph that were teammates for a period of time
You will receive a response that starts from your first input to you last input.

Fruchterman-Reingold Layout:
Input a player that exists in the graph
You will receive a response that directs you to 2 images of the adjacently list before and after algorithm runs.


# Project Proposal
## Leading Question 
How can we connect two different current or past NBA players to each other using mutual teammates? How can we do so using either any mutual teammates or the best possible mutual teammates? 
The motivation for figuring out how to connect players in two different ways is as follows:
By using any mutual teammate, we can get the shortest possible way to connect two teammates.
By using the best possible teammates, we can get the shortest possible way to connect two teammates using hopefully more well-known players.

## Dataset Acquisition
This is a CSV file that we found for our project. We will extract the data using python https://www.kaggle.com/datasets/abhinavp23/nba-stats-player-and-team
## Data Format
Our graph will be a simple, undirected, weighted graph. We will be using data found in the dataset https://www.kaggle.com/datasets/abhinavp23/nba-stats-player-and-team and extract it using python. This dataset is formatted in CSV. This means that our dataset is a file of new-line separated rows of comma-separated entries in the form: year, player, position, age, team, games played, games started, minutes played, field goals, three-pointers made, three-pointers attempted, three-point percentage, pt made, 2 pt attempted, 2pt percentage, eFG percentage, free throws attempted, free throws attempted, offensive rebounds, defensive rebounds, total rebounds, assists, steals, blocks, turnovers, personal fouls, points. 
We will be calculating every NBA player's Player Efficiency Rating (PER), which involves many player stats. These are as follows: field goals made, steals, three-pointers made, free throws made, blocks, offensive rebounds, assists, defensive rebounds, fouls, free throws missed, field goals missed, turnovers, and minutes played. We will be getting all of these from the dataset which contains all besides free throws missed and field goals missed. To calculate the two we will be using the difference between free throws and three-pointers made/attempted. We will also be using the player names which we intend on storing within the nodes. Our edges will be weighted and undirected. An edge between two players indicates that the two players played for the same team at the same time (they were teammates) and the weight of the edge will be the average of the two Player Efficiency Ratings. 
In order to calculate the Player Efficiency Ratings, we will be using the following formula: PER = [field goals made * 85.910 + steals * 53.897 + three-pointers made * 51.757 + free throws made  * 46.845 + blocks * 39.190 + offensive rebounds * 39.190 + assists * 34.677  + defensive rebounds * 14.707 - fouls * 17.174 - free throws missed * 20.091 -  field goals missed * 39.190  - turnovers * 53.897] * [1 / minutes played].

## Data Correction
Errors that we might find are finding two different players with the same name or players that played on multiple teams in the same season. After doing research we found that there are only a few players in NBA history with the same name. To correct this and make sure there is not an issue in the data, we can create player ids. This would give each player a unique id. 
Another error that we found within the dataset is that in the years 1950 and 1951 the minutes played and games started are not listed. Not having these inputs will cause inconsistencies in our PER algorithm so we will not include these seasons in our project.

## Data Storage
During this project, we will create a vector of strings that will store all player name tags (i.e. Lebron_James_1. To represent the graph, we will be using an adjacency list, because many players played at completely different times and were never teammates. Therefore, we would be wasting space using a structure like a matrix to hold the edges. The edge list would store the two names of the connected vertices (player name tags), the name of the edge, and the weight of the edge (average Player Efficiency Rating between the two players). The space cost of this implementation should be O(n+m) since this is a sparse graph. There are over 4,000 different players, and most of these players have played with less than 100 teammates. Thus, our graph will not nearly contain the maximal number of possible edges.
## Algorithm 
Traversal: Breadth First Search (BFS). breadth-first search is a search algorithm that finds the shortest possible path between two nodes on the graph. Thus, we will be finding the shortest path between any two players using only mutual players. The BFS time complexity is O(|V| + |E|) where V is the number of vertices and E is the number of edges. This algorithm takes a starting and an endpoint node. In our case, we will be passing in a playerID that uniquely identifies each individual node. We will output a vector of playerID’s with the shortest path from the starting node to the ending node. 
	Covered Algorithm: Djikstra’s Algorithm. Djikstra’s algorithm will allow us to find the shortest path from a single source to all other nodes in the graph. Thus, we will be finding the shortest path between any player and a source player. By having edges the correspond to the average Player Efficiency Ratings of two players, this will give us the path shortest path between any player and a source player using the best possible mutual teammates. Djikstra’s algorithm has a worst case time complexity of O((|V|+|E|)log|V|). Djikstra’s takes in a starting node as input. In our case this will be a player name tag. Djikstra’s algorithm will output two vectors, both of size |V|. One vector, dist, contains the shortest path from the input node to every node in the graph. The other vector, prev, contains the node immediately preceding each node in the shortest path so that we can reconstruct the shortest path to each node.
	Uncovered Algorithm: Fruchterman-Reingold Algorithm. A force-directed graph drawing minimizes overlaps in the graph, evenly distributes nodes and edges, and organizes nodes so that edges are of similar length. Thus, we will create an aesthetically pleasing visual representation of our graph using the FR algorithm. The FR algorithm has a worst case time complexity of O(|V|^2+|E|). The FR algorithm takes in a graph as an input. In this case, we will be passing in our adjacency list of players. The FR algorithm will output a PNG of our graph having been processed by the FR algorithm. 
## Timeline
Data acquisition: November 18
Data processing: November 22
Completion of algorithm: November 29
Visualization of result: December 2
Finish project and touch-ups: December 9



# Team Contract

## Communication

1. **Team Meetings** 
We will have weekly in-person hour-long meetings. Mondays at 8 pm CST. Everyone will take turns taking notes throughout the meetings
2. **Assistance** 
We have set up a group chat where anyone is free to send messages. Group members should expect a response within 24 hours of sending the message.

3. **Respect**
Every team member will be given an opportunity to share their ideas to make sure that it is an inclusive environment. Taking notes will also ensure that people are paying attention to what is happening.


## Collaboration


4. **Work Distribution**
Each group member will be given a set of responsibilities on a week to week basis. The responsibilities for the next week will be determined during the weekly meetings. In the event of an unexpected complication, we will determine resolving steps during the weekly meetings. This could include redistributing the work loads and reevaluating weekly goals. We will determine responsibilities based off of group member strengths so that we can get the best out of everyone.

5. **Time Commitment** 
Each week each group member will put in at least 2 hours of work to contribute to the project to make sure everyone is doing their part. If there is an issue with a member not completing their work, other group members can assist to finish any incomplete work.

6. **Conflict Resolution** 
If there are any conflicts of interest within the group, we will have a group meeting that will consist of polls that will help resolve the issue. This would allow for the group to come up with a fair solution after hearing out both of the opposing arguments.

Signatures:
Sebastian Gluszak, Daniyal Rana, Joshua Belser, Emmanuel Buabeng
