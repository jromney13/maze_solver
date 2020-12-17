#include <iostream>
#include "mazeBFS.h"

using namespace std;

int main()
{
    MazeSolver myMaze;

    cout << endl;
    cout << "Maze 1: " << endl;
    cout << endl;
    myMaze.printMaze();
    myMaze.FindPath(1,1); // parameters are the starting coordinates of the maze
    cout << "Completed Maze: " << endl;
    cout << endl;
    myMaze.printMaze();

    return 0;
}