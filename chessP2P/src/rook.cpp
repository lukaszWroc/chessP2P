#include"rook.hpp"


bool Rook::checkMovement(int _id,int vis[])
{
    int _color;
    if(state == white)
        _color = -1;
    else
        _color = 1;
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

Rook::Rook(int _id, SideState _state, std::string s)
    : Chessman(_id,_state,s,ROOK)
{
}

std::unique_ptr<Chessman> Rook::clone()
{
    return std::make_unique<Rook>(*this);
}
