#include <nana/gui.hpp>
#include "Maze.cpp"

int main()
{
    int src[2]={0,0};
    int dst[2]={4,4};
    Maze* m=new Maze(5,5,src,dst);

}
