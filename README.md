
# <ins align = "center"> CS225-Final-Project </ins>

# README
## Download and Install Clang++ https://clang.llvm.org/get_started.html
### How to execute code
1. Make new build folder with a new version (mkdir build)
2. In your terminal, move into the build folder (cd build) and type cmake ..
3. Still in this directory, type make to compile the main and test executables
5. Type ./main to run the main executable
6. Type ./test to run the test executable 
7. When running the executable, there is the opportunity to run 3 different algorithms in our NBA Player Graph
*You can find the list of players to input in our graph in NBA_STATS_WITH_PER.csv located in the data folder

BFS:
Input 2 players that exists in the graph
You will receive a response that starts from first input to last input.

Dijkstra's:
Input 2 players that exists in the graph that were teammates for a period of time
You will receive a response that starts from first input to last input.

Fruchterman-Reingold Layout:
Input a player that exists in the graph
You will receive a response that directs you to 2 images of the adjacently list before and after algorithm runs 
(before.png	https://github.com/daniyal-rana/CS225-Final-Project/blob/f795fadf9651656b4b24c705d9277c1fdd45f5b7/before.png)

(after.png	https://github.com/daniyal-rana/CS225-Final-Project/blob/d5c4727499f80ab01e238893b90cde6e63b78e3b/after.png).

PlayerGraph class is found in the src folder 
(https://github.com/daniyal-rana/CS225-Final-Project/tree/main/src)
What is algorithms found in our PlayerGraph class:
Fruchterman-Reingold
Dijkstra's
BFS
*Test cases for these algorithms are reproduced through ./test executable

Data and Data parsing of our NBA dataset is found in the data folder.
Data parsing test cases are found here:
https://github.com/daniyal-rana/CS225-Final-Project/blob/f795fadf9651656b4b24c705d9277c1fdd45f5b7/data/dataset_test.ipynb
