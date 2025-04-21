#include <nana/gui.hpp>
#include "MazeGenerator.cpp"
#include "MazeViewer.cpp" // Assuming your MazeViewer class is here

int main() {
    // // Sample maze setup
     int rows = 5, cols = 5;
    // int** board = new int*[rows];
    // for (int i = 0; i < rows; ++i) {
    //     board[i] = new int[cols];
    //     for (int j = 0; j < cols; ++j) {
    //         board[i][j] = 1; // 1 = empty, 0 = wall
    //     }
    // }

    // // Add walls as needed
    // board[1][1] = 0;
    // board[2][2] = 0;

    // int src[] = {0, 0};  // Start
    // int dst[] = {4, 4};  // End

    MazeGenerator generator(rows,cols);
    MazeViewer viewer(generator.getBoard(), rows, cols);
    viewer.startTracking();

    nana::exec(); // This blocks until the GUI window is closed

    std::string moves = viewer.getPath(); // <-- Reached after window closes
    std::cout << "Path taken: " << moves << "\n";

    // Cleanup
    // for (int i = 0; i < rows; ++i) delete[] board[i];
    // delete[] board;

    return 0;
}
