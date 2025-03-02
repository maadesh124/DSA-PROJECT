#include <nana/gui.hpp>
#include "Maze.cpp"

int main()
{
    int m,n;

    cout<<"Enter Maze dimensions"<<endl;
    cin>>m;
    cin>>n;
    int src[2]={0,0};
    int dst[2]={m-1,n-1};
    // cout<<"Ente src";
    // cin>>src[0];
    // cin>>src[1];
    // cout<<"Enter dst";
    // cin>>dst[0];
    // cin>>dst[1];
    Maze* maze=new Maze(m,n,src,dst);
    //maze->startGame(src,dst);
}
