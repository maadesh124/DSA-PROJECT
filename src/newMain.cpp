#include <nana/gui.hpp>
#include "MazeGenerator.cpp"
#include "MazeSolver.cpp"
#include "MazeViewer.cpp" // Assuming your MazeViewer class is here


using namespace std;
int main() {

     int rows, cols;
     int** board;
    cout<<"Enter maze dimension"<<endl;
    cin>>rows;
    cin>>cols;
    MazeGenerator generator(rows,cols);
    board=generator.getBoard();
    MazeSolver solver(board,rows,cols);
    string shortestPath=solver.solveByBacktracking();
    cout << "Shortest Path : " << ans << "\n";

    MazeViewer viewer(board, rows, cols);
    viewer.startTracking();
    
    nana::exec(); 
    string path = viewer.getPath(); 
    std::cout << "Path taken: " << moves << "\n";
    
    return 0;
}
