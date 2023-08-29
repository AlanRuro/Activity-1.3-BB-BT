//Gerardo Ulises Sanchez Felix - A01641788

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

#include <iostream>

using namespace std;

bool** generateMaze(int, int);
void fillMaze(bool**, int, int);
void printMaze(bool**, int, int);
bool backtracking(bool**, int, int, int, int, bool**);
bool isSafe(bool**, int, int, int, int);

int main() {
    int columns, rows;
    cout << "Num of columns: ";
    cin >> columns;
    cout << "Num of rows: ";
    cin >> rows;

    bool** maze = generateMaze(columns, rows);
    // bool **mazeBT = maze;
    bool** mazeBT = new bool*[rows];
    for (int i = 0; i < rows; i++) {
        mazeBT[i] = new bool[columns];
        for (int j = 0; j < columns; j++) {
            mazeBT[i][j] = 0;
        }
    }

    // printMaze(mazeBT, columns, rows);
    if (backtracking(maze, columns, rows, 0, 0, mazeBT)) {
        cout << "Path found!" << endl;
        printMaze(mazeBT, columns, rows); // Imprime la matriz mazeBT
    } else {
        cout << "No path found!" << endl;
    }

    // Liberacion de memoria 
    for (int i = 0; i < rows; i++) {
        delete[] maze[i];
        delete[] mazeBT[i];
    }
    delete[] maze;
    delete[] mazeBT;

    return 0;
}

bool** generateMaze(int columns, int rows) {
    bool** maze = new bool*[rows];

    for (int i = 0; i < rows; i++) {
        maze[i] = new bool[columns];
    }

    fillMaze(maze, columns, rows);
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

bool backtracking(bool** maze, int columns, int rows, int x, int y, bool** mazeBT) {
    int M = columns;
    int N = rows;

    if (x == M - 1 && y == N - 1) {
        mazeBT[x][y] = 1;
        return true;
    }

    if (isSafe(maze, x, y, M, N)) {
        mazeBT[x][y] = 1;

        if (backtracking(maze, columns, rows, x + 1, y, mazeBT) || backtracking(maze, columns, rows, x, y + 1, mazeBT)) {
            return true;
        }

        mazeBT[x][y] = 0;
        return false;
    }

    return false;
}


