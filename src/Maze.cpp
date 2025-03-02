#include <nana/gui.hpp>
#include <nana/paint/graphics.hpp>
#include <iostream>
#include <cstdlib>  
#include <ctime> 


using namespace std;
class Maze{
public:
int sqSize;
int rows,cols;
int* src;
int* dst;
int** board;
nana::form* fmptr;
int** path;
int nSelected;
const int ds[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
bool started=false;

Maze(int rows,int cols,int src[2],int dst[2]){

    this->src=src;
    this->dst=dst;


    this->sqSize=50;
    this->rows=rows;
    this->cols=cols;
    this->board = new int*[rows];  
    for (int i = 0; i < rows; ++i) {
        board[i] = new int[cols];  
    }
    this->path=new int*[rows*cols];
        for (int i = 0; i < rows*cols; ++i) {
        path[i] = new int[2];  
    }
    this->nSelected=0;


        
    srand(time(0));
    int n1=(rows*cols/4);
    initialize(n1);
    
}

bool isValidSq(int row,int col){
    if(row<0 || row>=rows || col<0 || col>=cols)
    return false;

    return true;
}

void update() {
    using namespace nana;

        //form fm=*fmptr;
        drawing dw(*fmptr);  
        dw.draw([=](paint::graphics& graph) {
            for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {
                    int x = col * sqSize;
                    int y = row * sqSize;

                    if (board[row][col] == 1) {
                        graph.rectangle(nana::rectangle{x, y, sqSize, sqSize}, true, colors::white);  // Wall (red)
                    }

                    else if(board[row][col] == 0){
                        graph.rectangle(nana::rectangle{x, y, sqSize, sqSize}, true, colors::black);  // Empty (blue)
                    }
                    else if(board[row][col] == 2)
                    {
                       graph.rectangle(nana::rectangle{x, y, sqSize, sqSize}, true, colors::green);
                    }

                    graph.rectangle(nana::rectangle{x, y, sqSize, sqSize}, false, colors::black);  // Border (black)
                }
            }

            if(started){
            graph.rectangle(nana::rectangle{src[1] * sqSize, src[0] * sqSize, sqSize, sqSize}, true, colors::green); // Source (green)
            graph.rectangle(nana::rectangle{dst[1] * sqSize, dst[0] * sqSize, sqSize, sqSize}, true, colors::yellow); // Destination (yellow)
            }
        });

        dw.update();
    }

void startGame(int src[2],int dst[2]){
    this->src=src;
    this->dst=dst;

    if(!isValidSq(src[0],src[1]) || !isValidSq(dst[0],dst[1]))
    {
    cerr<<"Invalid src or dst"<<endl;
    exit(0);
    }
    started=true;

    board[src[0]][src[1]]=2;
    path[nSelected][0]=src[0];
    path[nSelected][1]=src[1];
    nSelected++;

    fmptr->events().click([this](const nana::arg_click& arg) {
    this->on_form_click(arg);
});
    
}

bool on_form_click(const nana::arg_click& arg) {
    if (arg.window_handle != *fmptr) 
    return false;

    nana::point click_pos = arg.mouse_args->pos;
    int cell_row=click_pos.y/sqSize;
    int cell_col=click_pos.x/sqSize;

    if(!isValidSq(cell_row,cell_col))
    return false;

    if(cell_row==src[0] && cell_col==src[1])
    return false;

    if(cell_row==path[nSelected-1][0] && cell_col==path[nSelected-1][1] )
    {
        board[cell_row][cell_col]=1;
        nSelected--;
        update();
        return false;
    }

    if(board[cell_row][cell_col]==2)
    return false;

    if(board[cell_row][cell_col]==0)
    return false;




    for(int i=0;i<4;i++){

         int adj[]={path[nSelected-1][0]+ds[i][0],path[nSelected-1][1]+ds[i][1]};

        if(isValidSq(adj[0],adj[1]) && adj[0]==cell_row && adj[1]==cell_col )
        {
            path[nSelected][0]=cell_row;
            path[nSelected][1]=cell_col;
            nSelected++;
            board[cell_row][cell_col]=2;
            
            if(cell_row==dst[0] && cell_col==dst[1])
            {
                cout<<"Success"<<endl;
                exit(0);
            }
            break;
        }
    }
    update();

    return false;
}

void initialize(int blocks){

    for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
    board[i][j]=1;

    srand(time(0));
    for(int x=0;x<blocks;x++){
        int i=rand()%rows;
        int j=rand()%cols;
        board[i][j]=0;
    }
   
    

    using namespace nana;
    appearance ap;
    ap.sizable=false;
    fmptr = new form(API::make_center(sqSize * cols, sqSize * rows),ap);
    update(); 
    fmptr->show();
    
    startGame(src,dst);
    ::nana::exec();
}
    
};

