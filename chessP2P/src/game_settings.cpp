#include"game_settings.h"

SideState sideState = white;

void changeSideState(int _color)
{
    if(_color == -1)
        sideState = white;
    else
        sideState = black;
}

Position getPosition(int id)
{
    int y = id/8;
    int x = id%8;
    return Position(x*squareSize+(gameWindowWidth-squareSize*8)/2,y*squareSize);
}

SideState mirror(SideState _state)
{
    return (_state == white ? black : white) ;
}
