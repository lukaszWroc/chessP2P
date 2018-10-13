#include"king.hpp"

bool King::checkMovement(int _id,int vis[])
{
    int _color;
    if(state == white)
        _color = -1;
    else
        _color = 1;

    if(checkMovementHelper(id,_id,1,1,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,-1,1,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,1,-1,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,-1,-1,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,1,0,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,-1,0,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,0,1,0,1,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,0,-1,0,1,_color,vis))
        return true;
    return false;
}
King::King(int _id, SideState _state, std::string s)
    : Chessman(_id,_state,s,KING)
{
}

std::unique_ptr<Chessman> King::clone()
{
    return std::make_unique<King>(*this);
}
