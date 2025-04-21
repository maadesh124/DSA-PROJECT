#include <nana/gui.hpp>
#include "MazeGenerator.cpp"
#include "MazeSolver.cpp"
#include "MazeViewer.cpp" // Assuming your MazeViewer class is here


using namespace std;
int main() {

     int rows = 5, cols = 5;
     int** board;

    MazeGenerator generator(rows,cols);
    board=generator.getBoard();
    MazeSolver solver(board,rows,cols);
    string ans=solver.solveByDijkstra();
    cout << "Shortest Path : " << ans << "\n";

    MazeViewer viewer(board, rows, cols);
    viewer.startTracking();
    
    nana::exec(); 
    string moves = viewer.getPath(); 
    std::cout << "Path taken: " << moves << "\n";
    
    return 0;
}
