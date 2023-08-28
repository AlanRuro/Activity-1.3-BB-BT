#include <iostream>

using namespace std;

bool** generateMaze();
void fillMaze(bool**, int, int);
void printMaze(bool**, int, int);

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

    return maze;
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