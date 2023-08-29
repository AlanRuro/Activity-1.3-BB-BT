//Gerardo Ulises Sanchez Felix - A01641788
// Alan Antonio Ruelas Robles - A01641426

/*
Backtracking implementation complexity
Time Complexity: O(2^(n^2)). 
The recursion can run upper-bound 2^(n^2) times. 
Output matrix is required so an extra space of size n*n is needed.
The recursive backtracking algorithm explores all possible paths in the maze.
For each cell, it has two choices (move right or move down) if it's a valid move.
As there are potentially 2^(n^2) paths to explore in the worst case, the time complexity 
is indeed exponential.

Auxiliary Space: O(n^2).
The auxiliary space complexity typically refers to the additional space required 
by the algorithm to store data other than the input. In this case, it should not be considered O(n^2) 
because the extra space required to store the recursive call stack hasn't been accounted for.

Therefore, the space complexity should be considered O(n^2) for the output matrix plus O(n^2) 
for the call stack, resulting in a total space complexity of O(n^2 + n^2) = O(2n^2) = O(n^2).
*/

/*
Branch and Bound implementation
Time Complexity: O(M * N)
The function uses a breadth-first search (BFS) approach to explore the maze. 
In the worst case, the BFS will visit every cell in the maze before reaching the exit. 
Since it is using a queue to store the points to be explored, each cell is enqueued once. 
So, the time complexity of your function is O(M * N), where M is the number of rows and N is 
the number of columns in the maze.

Space Complexity: O(M * N)
The function uses additional space for the visited array and the points queue. 
Both of these data structures grow with the size of the maze. The visited array is a 2D boolean array 
of size M x N, and the points queue may contain at most M * N points (although in reality, it's likely 
to contain fewer due to pruning). Therefore, the space complexity of the function is also O(M * N).
*/

// compile: g++ main.cpp -o main
// run: ./main < in.txt

#include <iostream>
#include <queue>

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

bool** generateMaze(int, int);
void fillMaze(bool**, int, int);
void printMaze(bool**, int, int);
bool backtracking(bool**, int, int, int, int, bool**);
bool isSafe(bool**, int, int, int, int);
bool branchAndBound(bool**, int, int, bool**);

int main() {
    int columns, rows;
    cout << "Num of columns: ";
    cin >> columns;
    cout << "Num of rows: ";
    cin >> rows;

    bool** maze = generateMaze(columns, rows);
    fillMaze(maze, columns, rows);


    bool** solutionBT = generateMaze(columns, rows);
    cout << "Backtracking" << endl;
    if (backtracking(maze, columns, rows, 0, 0, solutionBT)) {
        cout << "Path found!" << endl;
        printMaze(solutionBT, columns, rows);
    } else {
        cout << "No path found!" << endl;
    }

    cout << endl;

    bool** solutionBB = generateMaze(columns, rows);
    cout << "Branch and bound" << endl;
    if (branchAndBound(maze, columns, rows, solutionBB)) {
        cout << "Path found!" << endl;
        printMaze(solutionBB, columns, rows);
    } else {
        cout << "No path found!" << endl;
    }
    
    // Liberacion de memoria 
    for (int i = 0; i < rows; i++) {
        delete[] maze[i];
        delete[] solutionBT[i];
        delete[] solutionBB[i];
    }
    delete[] maze;
    delete[] solutionBT;
    delete[] solutionBB;

    return 0;
}

bool** generateMaze(int columns, int rows) {
    bool** maze = new bool*[rows];
    for (int i = 0; i < rows; i++) {
        maze[i] = new bool[columns];
        for (int j = 0; j < columns; j++) {
            maze[i][j] = 0;
        }
    }
    return maze;
}

void fillMaze(bool** maze, int columns, int rows) {
    cout << "Enter maze values (0 for blocked, 1 for open):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> maze[i][j];
        }
    }
}

void printMaze(bool** maze, int columns, int rows) {
    cout << "Maze:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(bool** maze, int x, int y, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1);
}

bool backtracking(bool** maze, int columns, int rows, int x, int y, bool** solution) {
    int M = columns;
    int N = rows;

    if (x == M - 1 && y == N - 1) {
        solution[x][y] = 1;
        return true;
    }

    if (isSafe(maze, x, y, M, N)) {
        solution[x][y] = 1;

        if (backtracking(maze, columns, rows, x + 1, y, solution) || backtracking(maze, columns, rows, x, y + 1, solution)) {
            return true;
        }

        solution[x][y] = 0;
        return false;
    }

    return false;
}

bool branchAndBound(bool** maze, int columns, int rows, bool** solution) {
    bool** visited = generateMaze(columns, rows);

    queue<Point> points;
    points.push(Point(0, 0));
    visited[0][0] = true;

    while (!points.empty()) {
        Point current = points.front();
        points.pop();
        int x = current.x;
        int y = current.y;

        solution[x][y] = 1;

        if (x == columns - 1 && y == rows - 1) {
            return true;
        }

        if (y + 1 < rows && maze[x][y + 1] && !visited[x][y + 1]) {
            points.push(Point(x, y + 1));
            visited[x][y + 1] = true;
        }

        if (x + 1 < columns && maze[x + 1][y] && !visited[x + 1][y]) {
            points.push(Point(x + 1, y));
            visited[x + 1][y] = true;
        }
    }

    return false;
}



