#include"pawn.hpp"

bool Pawn::checkMovement(int _id,int vis[])
{
    int y = id/8;
    int x = id%8;

    int _y = _id/8;
    int _x = _id%8;

    int _color;
    if(state == white)
        _color = -1;
    else
        _color = 1;
    if((8<= id && id <=15) || (48<= id && id <=55))
    {
        if(state == sideState)
        {
            if(x == _x && y - 2 == _y && vis[(y-2)*8 + x] == 0 && movementCnt == 0)
                return true;
        }

        else
        {
            if(x == _x && y + 2 == _y && vis[(y+2)*8 + x] == 0  && movementCnt == 0)
                return true;
        }
    }
    if(state == sideState)
    {
        if(x == _x && y - 1 == _y && vis[(y-1)*8 + x] == 0)
            return true;
        if( x  - 1== _x && y - 1 == _y&& vis[(y-1)*8 + x - 1] * _color == -1)
            return true;
        if( x + 1== _x && y - 1 == _y&& vis[(y-1)*8 + x + 1] * _color == -1)
            return true;
    }
    else
    {
        if(x == _x && y + 1 == _y  && vis[(y+1)*8 + x] == 0)
            return true;
        if( x  - 1== _x && y + 1 == _y && vis[(y+1)*8 + x - 1] * _color == -1)
            return true;
        if( x + 1== _x && y + 1 == _y && vis[(y+1)*8 + x + 1] * _color == -1)
            return true;

    }
    return false;
}

Pawn::Pawn(int _id, SideState _state, std::string s)
    : Chessman(_id,_state,s,PAWN)
{
}

std::unique_ptr<Chessman> Pawn::clone()
{
    return std::make_unique<Pawn>(*this);
}
