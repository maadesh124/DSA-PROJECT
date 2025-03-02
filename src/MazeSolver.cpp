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
    int pos;

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


    int* solve(int** board, int rows, int cols) {
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

// int evaluate(int l){
//     pos=nSols-lowerBound(pathLengths,nSols,l);
//     return pos*100/nSols;
// }

};