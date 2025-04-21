#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class MazeGenerator {
private:
    int rows, cols;
    int** board;
    bool** visited;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void shuffleDirections(int* dir) {
        for (int i = 3; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(dir[i], dir[j]);
        }
    }

    bool isValid(int nx, int ny) {
        return nx >= 0 && ny >= 0 && nx < rows && ny < cols;
    }

    // Carve a path using DFS
    bool carvePath(int x, int y) {
        if(x==rows-1 && y==cols-1)
        return true;
        visited[x][y] = true;
        board[x][y] = 1;

        int dir[4] = {0, 1, 2, 3};
        shuffleDirections(dir);

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[dir[i]];
            int ny = y + dy[dir[i]];

            if (isValid(nx, ny) && !visited[nx][ny]) {
                if(carvePath(nx, ny))
                return true;
            }
        }
        return false;
    }

    public:
    MazeGenerator(int r, int c) {
        srand(time(0));
        rows = r;
        cols = c;

        board = new int*[rows];
        visited = new bool*[rows];

        for (int i = 0; i < rows; ++i) {
            board[i] = new int[cols];
            visited[i] = new bool[cols];
            for (int j = 0; j < cols; ++j) {
                board[i][j] = 0;
                visited[i][j] = false;
            }
        }

        
        carvePath(0, 0);
        int numRandomOpens = rand() % ((rows * cols) / 2);  

        for (int i = 0; i < numRandomOpens; ++i) {
            int rIdx = rand() % rows;
            int cIdx = rand() % cols;     
            board[rIdx][cIdx] = 1;  
        }

        // Ensure start and end points are open
        board[0][0] = 1;
        board[rows - 1][cols - 1] = 1;
    }

    void printBoard() const {
        cout << "Generated Maze:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (board[i][j] == 1 ? " " : "#") << " ";
            }
            cout << "\n";
        }
    }

    int** getBoard() const {
        return board;
    }

    ~MazeGenerator() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
            delete[] visited[i];
        }
        delete[] board;
        delete[] visited;
    }


};