#include <iostream>
#include <string>
#include "Queue.cpp"


using namespace std;

class MazeSolver {
public:
    string* paths;  
    int nSols; 
    int** board;
    int rows,cols;  
    bool** visited; 
    int pos;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    MazeSolver(int** board,int rows ,int cols)
    {
        nSols = 0;
        visited = new bool*[rows];
        for (int i = 0; i < rows; ++i) {
            visited[i] = new bool[cols]();
        }
        paths = new string[1000];  

        this->board=board;
        this->rows=rows;
        this->cols=cols;
    }

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


    int* solve() {
        

        if (board[0][0] == 1) {
            findPaths(0, 0,"");
        }

        int* pathLengths;  
        pathLengths=new int[nSols];
        for(int i=0;i<nSols;i++)
        pathLengths[i]=paths[i].length();

        mergeSort(pathLengths,0,nSols-1);

        return pathLengths;

    }

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];


    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


static int lowerBound(int arr[], int size, int num) {
   
    int left = 0, right = size - 1;
    int result = -1; 

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] >= num) {
            result = mid; 
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int** solveByBFS() {
    
    int** predecessor = new int*[rows];

    for (int i = 0; i < rows; ++i) {
        predecessor[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            predecessor[i][j] = -1;
        }
    }

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

    return predecessor;
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
};