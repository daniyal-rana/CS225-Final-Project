# Written Report
## Project Goals
How can we connect two different current or past NBA players to each other using mutual teammates? We connected NBA players to each other using mutual teammates by implementing Breadth-first Search (BFS). How can we do so using either any mutual teammates or the best possible mutual teammates? We used each player’s Player Efficiency Rating, which sums up all of a player's positive accomplishments, subtracts the negative accomplishments, and returns a per-minute rating of a player's performance (PER =+510 [field goals made * 85.910 + steals * 53.897 + three-pointers made * 51.757 + free throws made * 46.845 + blocks * 39.190 + offensive rebounds * 39.190 + assists * 34.677 + defensive rebounds * 14.707 - fouls * 17.174 - free throws missed * 20.091 - field goals missed * 39.190 - turnovers * 53.897] * [1 / minutes played]). For our Covered Algorithm, we used Djikstra’s algorithm. For our Uncovered Algorithm, we implemented the Fruchterman-Reingold algorithm.
## Breadth-First Search
Breadth-first search is a search algorithm that finds the shortest possible path between two nodes on the graph. The shortest path indicates a path that provides the highest PER between the players. The BFS time complexity is O(|V| + |E|) where V is the number of vertices and E is the number of edges. This algorithm takes a starting and an endpoint node. In our case, we will be passing in a playerID that uniquely identifies each individual node. We will output a vector of playerID’s with the shortest path from the starting node to the ending node.
https://github.com/daniyal-rana/CS225-Final-Project/blob/19e7bbf96d6cbe02a54525995bf515a3f8b8ea59/img/bfs%20example%20output.png
We tested BFS by designing a variety of different scenarios and input data, to test what our algorithm could work with. Using a smaller dataset to test our algorithms had many benefits, the main being that we can quickly map out the proper shortest path for BFS and Djikstras. First we made a smaller dataset so we could accurately test our algorithms. After that we made a graph with connected and disconnected components to verify that our it can accurately handle certain cases. Our last testing phase was testing to see if it was getting the correct output for multiple mutual teammates. To test to see if our algorithm worked we created an answer vector, which stored the proper shortest path between two unique players. If the output of our function matched the answer vector then our algorithm would work.
## Djikstra’s Algorithm
Djikstra’s algorithm will allow us to find the shortest path from a single source to all other nodes in the graph. By having edges that correspond to the average Player Efficiency Ratings of two players, this will give us the shortest path between any player and a source player using the best possible mutual teammates. Djikstra’s algorithm has a worst case time complexity of O((|V|+|E|)log|V|). Djikstra’s takes in a starting node as input. In our case this will be a player name tag. Djikstra’s algorithm will output two vectors, both of size |V|. One vector, dist, contains the shortest path from the input node to every node in the graph. The other vector, prev, contains the node immediately preceding each node in the shortest path so that we can reconstruct the shortest path to each node. 
https://github.com/daniyal-rana/CS225-Final-Project/blob/19e7bbf96d6cbe02a54525995bf515a3f8b8ea59/img/Djikstra%E2%80%99s%20example%20output.png
Anthony Davis and Hakim Warrick were teammates in the 2012-13 season. Derrick Rose and Hakim Warrick were teammates in 2009-10. Since Hakim Warrick is in the path, he is the mutual teammate that has the best PER Anthony Davis and Derrick Rose had.
We tested Dijkstra's algorithm by designing a variety of different scenarios and input data, to test what our algorithm could work with. First we made a smaller dataset so we could accurately test our algorithms. Using a smaller dataset to test our algorithms had many benefits, the main being that we can quickly map out the proper shortest path for BFS and Djikstras. After that we made a graph with connected and disconnected components to verify that it can accurately handle certain cases. Our last testing phase was testing to see if it was getting the correct output for multiple mutual teammates. To test to see if our algorithm worked we created an answer vector, which stored the proper shortest  weighted path between two unique players by analyzing the average per between their teammate, if the output of our function matched the answer vector then our algorithm would work. 
##  Fruchterman-Reingold Algorithm
Uncovered Algorithm: Fruchterman-Reingold Algorithm (FR). A force-directed graph drawing minimizes overlaps in the graph, evenly distributes nodes and edges, and organizes nodes so that edges are of similar length. Thus, we will create an aesthetically pleasing visual representation of our graph using the FR algorithm. The FR algorithm has a worst case time complexity of O(|V|^2+|E|). The FR algorithm takes in a vector of vertices and vector of nodes along with the specified height and width of our output PNG image. It also takes in an integer input for the number of iterations that our algorithm will run. The FR algorithm will output a PNG of our graph having been processed by the FR algorithm. This is an image of the Lebron James FR algorithm before and after. In terms of implementation, the algorithm mimics a series of attractive and repulsive forces on the nodes and edges in order to make a graph that spreads the nodes equally from each other and creates edges of relatively equal length.
https://github.com/daniyal-rana/CS225-Final-Project/blob/19e7bbf96d6cbe02a54525995bf515a3f8b8ea59/img/fr%20algorithm%20example%20output.png
	The origin point is Lebron James. In the before image, the red points each indicate a player. The initial code, the algorithm randomly assigned each mutual teammate a 2-dimensional coordinate. As seen in the after picture, the algorithm evenly distanced each mutual teammate from the origin coordinate, which produced nodes and edges in a circular manner.
## Discussion
Using our BFS traversal, we found out that some of our favorite players played with mutual teammates with player that we never heard of. 
By running Djikstra’s algorithm, we were able to efficiently identify the best (quantified by PER) mutual teammates between any two inputted players: We often found that there were longer paths when the two inputted players are from different eras (eg. Devin Booker and Curly Armstrong). 
Lastly, our FR algorithm allowed us to clearly visualize the graph. We chose not to do FR on the entire graph because there were too many edges and nodes which made a graph that didn’t provide a clear enough output at a low enough PNG resolution. Thus, we chose to run the FR algorithm on a one depth graph of any player. Although, it should be noted that the algorithm works with any depth graph by simply changing the vertices and edges inputs. If we had more time, we would definitely revise our graph drawing process. At the moment, our graph drawing are very simple. Adding labels to the nodes and creating different node sizes to represent some value such as the PER is definitely something we would like to implement in the future. As a whole, we believe the project was a success; however, there are things we would do differently in the beginning. We would spend more time coming up with ideas of ways to represent the graph in terms of nodes, edges, and weights. At points, we found it difficult to work with the PER values and extrapolating some sort of meaningful conclusion.