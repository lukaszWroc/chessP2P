#include"knight.hpp"

bool Knight::checkMovement(int _id,int vis[])
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
    if(vis[_id] * _color != 1)
    {
        if(x + 2 == _x && y + 1 == _y)
            return true;
        if(x + 2 == _x && y - 1 == _y)
            return true;
        if(x - 2 == _x && y + 1 == _y)
            return true;
        if(x - 2 == _x && y - 1 == _y)
            return true;
        if(x + 1 == _x && y + 2 == _y)
            return true;
        if(x - 1 == _x && y + 2  == _y)
            return true;
        if(x + 1 == _x && y - 2 == _y)
            return true;
        if(x - 1 == _x && y - 2 == _y)
            return true;
    }
    return false;
}
Knight::Knight(int _id, SideState _state, std::string s)
    : Chessman(_id,_state,s,KNIGHT)
{
}

std::unique_ptr<Chessman> Knight::clone()
{
    return std::make_unique<Knight>(*this);
}
