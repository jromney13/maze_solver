#include <iostream>
#include <queue>
#include <vector>
#include <memory>

using namespace std;

struct Point {
	int x, y, dist;
    shared_ptr<Point> previous; // parent node to keep track of pathway
    Point(int xC, int yC, int d, shared_ptr<Point> p)
    {
        x = xC;
        y = yC;
        dist = d;
        previous = p;
    }
};

class MazeSolver
{
    public:

    int FindPath(int row, int column);
    void printMaze();
    queue<Point> path;
    vector<Point> trail;
    Point destination = {18,17,0,nullptr};
    int maze[20][20] ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 5 is the start of the maze
                       {0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}, // 8 is the end of the maze
                       {0,1,1,0,0,0,0,0,1,1,1,1,0,0,1,0,1,1,1,0}, // 1 are open pathways
                       {0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,1,0}, // 0 are walls
                       {0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0},
                       {0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,0},
                       {0,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0},
                       {0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0},
                       {0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0},
                       {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
                       {0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0},
                       {0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0},
                       {0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0},
                       {0,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0},
                       {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
                       {0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0},
                       {0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,8,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    private:

};


int MazeSolver::FindPath(int row,int column) // parameters are the starting coordinates in the maze
{

    int mazeRow = sizeof maze / sizeof maze[0];
    int mazeCol = sizeof maze[0] / sizeof(int);

    int visited[mazeRow][mazeCol]; // Generating Visited 2D array from maze array

    for(int i=0; i < sizeof maze / sizeof maze[0]; i++)
    {
        for(int e=0; e< sizeof maze[0] / sizeof(int); e++)
        {
            if(maze[i][e] == 0)
            {
                visited[i][e] = 0;
            }
            else
            {
                visited[i][e] = 1;
            }
        }
    }

    path.push(Point(row, column,0,nullptr)); //root node

    while(!path.empty())  // BFS Algorithm Finds Distance and Pathway
    {
        
        Point current = path.front();
        shared_ptr<Point> ptrcurrent = make_shared<Point>(current.x,current.y,current.dist,current.previous);
    
        if(current.x == destination.x && current.y == destination.y)
        {
            cout << "Shortest Distance Through Maze: " << current.dist << " Squares" << endl;
            cout << endl;

            while(current.previous != nullptr) // iterating through previous pointers and adding them to vector to keep track of path.
            {
                trail.push_back(current);
                current = *current.previous;
            }
            for(int i=0; i<trail.size(); i++) // adding the pathway to the maze.
            {
                if(maze[trail[i].x][trail[i].y] != 8) // if not destination mark as pathway
                {
                    maze[trail[i].x][trail[i].y] = 9;
                }
            }
            return 1;
        }

        path.pop();
        
        if(visited[current.x+1][current.y] != 0)
        {
            visited[current.x+1][current.y] = 0;
            path.push(Point(current.x+1,current.y,current.dist+1,ptrcurrent));
        }
        if(visited[current.x-1][current.y] != 0)
        {
            visited[current.x-1][current.y] = 0;
            path.push(Point(current.x-1,current.y,current.dist+1,ptrcurrent));
            
        }
        if(visited[current.x][current.y+1] != 0)
        {
            visited[current.x][current.y+1] = 0;
            path.push(Point(current.x,current.y+1,current.dist+1,ptrcurrent));
        }
        if(visited[current.x][current.y-1] != 0)
        {
            visited[current.x][current.y-1] = 0;
            path.push(Point(current.x,current.y-1,current.dist+1,ptrcurrent));
        }

    }

    cout << "Pathway Cannot Be Found" << endl;
    cout << endl;
    
    return 0;
}


void MazeSolver::printMaze() // prints maze
{

    for(int i=0; i < sizeof maze / sizeof maze[0]; i++)
    {
        for(int e=0; e< sizeof maze[0] / sizeof(int); e++)
        {
            if(maze[i][e] == 0)
            {
                cout << "- ";
            }
            else if(maze[i][e] == 1)
            {
                cout << "  ";
            }
            else if(maze[i][e] == 5)
            {
                cout << "S ";
            }
            else if(maze[i][e] == 9)
            {
                cout << "* ";
            }
            else if(maze[i][e] == 8)
            {
                cout << "F ";
            }
            else
            {
                cout << maze[i][e] << " ";
            }
            
        }
        cout << endl;
    }
    cout << endl;
}