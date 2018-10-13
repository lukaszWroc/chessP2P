#include"bishop.hpp"

bool Bishop::checkMovement(int _id,int vis[])
{
    int _color;
    if(state == white)
        _color = -1;
    else
        _color = 1;

    if(checkMovementHelper(id,_id,1,1,0,8,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,-1,1,0,8,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,1,-1,0,8,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,-1,-1,0,8,_color,vis))
        return true;
    return false;
}

Bishop::Bishop(int _id, SideState _state, std::string s)
    : Chessman(_id,_state,s,BISHOP)
{
}

std::unique_ptr<Chessman> Bishop::clone()
{
    return std::make_unique<Bishop>(*this);
}
