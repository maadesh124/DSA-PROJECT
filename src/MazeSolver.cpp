#include <iostream>
#include <string>

using namespace std;

class MazeSolver {
public:
    string* paths;  
    int nSols; 
    int** board;
    int rows,cols;  
    bool** visited;   

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    bool isSafe(int x, int y) {

        return (x >= 0 && y >= 0 && x < rows && y < cols && board[x][y] == 1 && !visited[x][y]);
    }

    void findPaths(int x, int y, string path) {
        
        if (x == rows - 1 && y == cols - 1) {
            paths[nSols++] = path;  
            return;
        }
        visited[x][y] = true;

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isSafe(newX, newY)) {
                
                char direction = (i == 0) ? 'R' : (i == 1) ? 'D' : (i == 2) ? 'L' : 'U';
                findPaths(newX, newY,  path + direction);
            }
        }

        visited[x][y] = false;
    }


    void solve(int** board, int rows, int cols) {
        nSols = 0;
        visited = new bool*[rows];
        for (int i = 0; i < rows; ++i) {
            visited[i] = new bool[cols]();
        }
        paths = new string[1000];  

        this->board=board;
        this->rows=rows;
        this->cols=cols;

        if (board[0][0] == 1) {
            findPaths(0, 0,"");

        }

    }
};