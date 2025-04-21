#include <nana/gui.hpp>
#include <nana/paint/graphics.hpp>
#include <string>
#include <iostream>
#include <functional> 

class MazeViewer {
public:
    nana::form* fmptr;
    unsigned int sqSize = 50;
    int rows, cols;
    int** board;
    std::string path; // Now stores path as a string
    bool started = false;
    int* src;
    int* dst;
    int currRow, currCol;
    string shortestPath;
    void (*finish)(std::string, std::string); 


    MazeViewer(int** board, int rows, int cols,string ans,void (*callback)(std::string, std::string))
        : board(board), rows(rows), cols(cols), src(src), dst(dst)
    {
        src=new int[2];
        dst=new int[2];
        src[0]=0;src[1]=0;
        dst[0]=rows-1;dst[1]=cols-1;
        this->shortestPath=ans;
        finish=callback;

        using namespace nana;
        appearance ap;
        ap.sizable = false;
        fmptr = new form(API::make_center(sqSize * cols, sqSize * rows), ap);

        fmptr->events().click([this](const arg_click& arg) {
            this->on_form_click(arg);
        });

        update();
        fmptr->show();
    }

    void startTracking() {
        path.clear();
        currRow = src[0];
        currCol = src[1];
        started = true;
        update();
    }

    void update() {
        using namespace nana;

        drawing dw(*fmptr);
        dw.draw([=](paint::graphics& graph) {
            for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {
                    int x = col * sqSize;
                    int y = row * sqSize;

                    switch (board[row][col]) {
                        case 0: graph.rectangle(rectangle{x, y, sqSize, sqSize}, true, colors::black); break; // Wall
                        case 1: graph.rectangle(rectangle{x, y, sqSize, sqSize}, true, colors::white); break; // Empty
                        case 2: graph.rectangle(rectangle{x, y, sqSize, sqSize}, true, colors::green); break; // Path
                    }

                    graph.rectangle(rectangle{x, y, sqSize, sqSize}, false, colors::black);
                }
            }

            if (started) {
                graph.rectangle(rectangle{src[1]*sqSize, src[0]*sqSize, sqSize, sqSize}, true, colors::green);
                graph.rectangle(rectangle{dst[1]*sqSize, dst[0]*sqSize, sqSize, sqSize}, true, colors::yellow);
            }
        });

        dw.update();
    }

    bool isValid(int r, int c) {
        return (r >= 0 && r < rows && c >= 0 && c < cols);
    }

    bool isAdjacent(int r, int c, int pr, int pc) {
        return (abs(r - pr) + abs(c - pc)) == 1;
    }

    char getDirection(int newR, int newC, int oldR, int oldC) {
        if (newR == oldR - 1 && newC == oldC) return 'U';
        if (newR == oldR + 1 && newC == oldC) return 'D';
        if (newR == oldR && newC == oldC - 1) return 'L';
        if (newR == oldR && newC == oldC + 1) return 'R';
        return '?'; // Invalid move
    }

    void undoLastMove() {
        if (path.empty()) return;
        char lastMove = path.back();
        path.pop_back();

        board[currRow][currCol] = 1; // Unmark path

        switch (lastMove) {
            case 'U': currRow += 1; break;
            case 'D': currRow -= 1; break;
            case 'L': currCol += 1; break;
            case 'R': currCol -= 1; break;
        }

        update();
    }

    bool on_form_click(const nana::arg_click& arg) {
        if (arg.window_handle != *fmptr) return false;

        auto pos = arg.mouse_args->pos;
        int row = pos.y / sqSize;
        int col = pos.x / sqSize;

        if (!isValid(row, col) || (row == src[0] && col == src[1])) return false;

        if (row == currRow && col == currCol) {
            undoLastMove();
            return true;
        }

        if (board[row][col] == 0 || board[row][col] == 2) return false; // Wall or already visited

        if (isAdjacent(row, col, currRow, currCol)) {
            char move = getDirection(row, col, currRow, currCol);
            path.push_back(move);
            currRow = row;
            currCol = col;
            board[row][col] = 2;
            update();
            if (row == dst[0] && col == dst[1]) {
            finish(shortestPath,path);
        }
            return true;
        }

        return false;
    }

    const std::string& getPath() const {
        return path;
    }

    ~MazeViewer() {
        delete fmptr;
    }
};
