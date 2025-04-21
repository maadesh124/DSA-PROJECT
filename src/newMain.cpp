#include <nana/gui.hpp>
#include "MazeGenerator.cpp"
#include "MazeSolver.cpp"
#include "MazeViewer.cpp" // Assuming your MazeViewer class is here



using namespace std;

void finish(string shortestPath,string path)
{
    cout << "Shortest Path : " << shortestPath << "\n";
    cout << "Path taken: " << path << "\n";
    int score=100*shortestPath.length()/path.length();
    cout<<"Your score is "<<score<<endl;

}
int main() {

     int rows, cols;
     int** board;
    cout<<"Enter maze dimension"<<endl;
    cin>>rows;
    cin>>cols;
    MazeGenerator generator(rows,cols);
    board=generator.getBoard();
    MazeSolver solver(board,rows,cols);
    
    
    string shortestPath=solver.solveByBFS();
    

    MazeViewer viewer(board, rows, cols,shortestPath,&finish);
    viewer.startTracking();
    
    nana::exec();
   
    
    
    
    return 0;
}
