#ifndef GameSettings_H
#define GameSettings_H

const int gameWindowWidth=1200;
const int gameWindowHeight=600;
const int squareSize=75;
enum SideState {white,black};
enum ChessmanState {KING,QUEEN,KNIGHT,ROOK,PAWN,BISHOP};
extern SideState sideState;
void changeSideState(int _color);

struct Position
{
    int x, y;
    Position(int _x,int _y) : x(_x), y(_y) {};
};

Position getPosition(int id);

SideState mirror(SideState _state);
#endif // GameSettings_H
