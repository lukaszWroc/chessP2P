#include"queen.hpp"

bool Queen::checkMovement(int _id,int vis[])
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
    if(checkMovementHelper(id,_id,1,0,0,8,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,-1,0,0,8,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,0,1,0,8,_color,vis))
        return true;
    if(checkMovementHelper(id,_id,0,-1,0,8,_color,vis))
        return true;

    return false;
}

Queen::Queen(int _id, SideState _state, std::string s)
    : Chessman(_id,_state,s,QUEEN)
{
}

std::unique_ptr<Chessman> Queen::clone()
{
    return std::make_unique<Queen>(*this);
}
