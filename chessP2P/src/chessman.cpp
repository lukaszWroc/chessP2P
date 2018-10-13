#include"chessman.hpp"




bool Chessman::checkMovementHelper(int _id,int _newId,int dx,int dy,int cnt,int maxCnt,int _color,int vis[])
{

    int y = _id/8 + dy;
    int x = _id%8 + dx;
    int _y = _newId/8;
    int _x = _newId%8;

    if(x < 0 || 8 < x)
        return false;
    if(y < 0 || 8 < y)
        return false;
    if(x == _x && y == _y  && (vis[y*8+x] * _color == 0 || vis[y*8+x] * _color == -1))
        return true;
    if(vis[y*8+x] * _color !=  0)
        return false;
    if(maxCnt == cnt)
        return false;
    return checkMovementHelper(y*8+x,_newId,dx,dy,cnt+1,maxCnt,_color,vis);
}
