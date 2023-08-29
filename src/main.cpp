#include <iostream>

// Gerardo Ulises Sanchez Felix - A01641788

using namespace std;

bool** generateMaze();
void fillMaze(bool**, int, int);
void printMaze(bool**, int, int);
bool backtracking(bool**, int, int, int, int);
bool isSafe(bool**, int, int, int, int);

int main() {

    generateMaze();
    

    return 0;
}

bool** generateMaze() {
    int columns, rows;
    cout << "Num of columns: ";
    cin >> columns;
    cout << "Num of rows: ";
    cin >> rows;
    bool **maze = new bool*[rows];

    for(int i = 0; i < rows; i++) {
        maze[i] = new bool[columns];
    }

    fillMaze(maze, columns, rows);
    // bool** mazeBT = generateMaze();
}

void fillMaze(bool** maze, int columns, int rows) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cin >> maze[i][j];
        }
    }

    printMaze(maze, columns, rows);

}

void printMaze(bool** maze, int columns, int rows) {
    cout << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(bool** maze, int x, int y, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1);
}

bool backtracking(bool** maze, int columns, int rows, int x, int y) {
    bool **mazeBT = maze;
    int M = columns;
    int N = rows;

    if (x == M - 1 && y == N - 1) {
        mazeBT[x][y] = 1;
        return true;
    }

    if (isSafe(mazeBT, x, y, M, N)) {
        mazeBT[x][y] = 1;

        if (backtracking(mazeBT, columns, rows, x + 1, y) || backtracking(mazeBT, columns, rows, x, y + 1)) {
            return true;
        }

        mazeBT[x][y] = 0;
        return false;
    }

    return false;
}