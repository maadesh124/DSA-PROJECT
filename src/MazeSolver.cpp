#include <iostream>
#include <string>
#include "Queue.cpp"


using namespace std;

class MazeSolver {
public:
    int** board;
    int rows,cols;  
    int** predecessor;
    bool** visited;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    MazeSolver(int** board,int rows ,int cols)
    {

        this->board=board;
        this->rows=rows;
        this->cols=cols;
        predecessor = new int*[rows];
        visited = new bool*[rows];

        for (int i = 0; i < rows; ++i) {
            predecessor[i] = new int[cols];
            visited[i] = new bool[cols];
            for (int j = 0; j < cols; ++j) {
                predecessor[i][j] = -1;
                visited[i][j]=false;
            }
        }

        
    }


string solveByBFS() {
    
    Queue q;  
    if (board[0][0] == 1) {
        q.enqueue(0);
    }

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    while (!q.isEmpty()) {
        
        int size=q.size();

        for(int x=0;x<size;x++)
        {
            int parent=q.peek();
            q.deque();
            int px,py;
            to2DIndex(parent,px,py);
            
            for(int i=0;i<4;i++)
            {
                int x=px+dx[i],y=py+dy[i];
                if(isValid(x,y) && predecessor[x][y]==-1 && board[x][y]==1)
                {
                    predecessor[x][y]=parent;
                    q.enqueue(toLinearIndex(x,y));
                }
                
            }
        }
    }

    return getPath(rows*cols -1);
}

int toLinearIndex(int row, int col) {
    return row * cols + col;
}

void to2DIndex(int index, int &row, int &col) {
    row = index / cols;
    col = index % cols;
}


bool isValid(int r,int c)
{
    return (r<rows && c<cols && r>=0 && c>=0);
}

char getDirection(int index1, int index2) {
    int r1 = index1 / cols, c1 = index1 % cols;
    int r2 = index2 / cols, c2 = index2 % cols;

    if (r1 == r2 && c1 + 1 == c2) return 'R';
    if (r1 == r2 && c1 - 1 == c2) return 'L';
    if (c1 == c2 && r1 + 1 == r2) return 'D';
    if (c1 == c2 && r1 - 1 == r2) return 'U';

    return '?';  // Not adjacent or invalid relation
}

string getPath(int index)
{
    if(index==0)
    return "";
    int parent = predecessor[index / cols][index % cols];
    return getPath(parent) + getDirection(parent, index);
}



};