#ifndef PAWN_H

#define PAWN_H

#include<SFML/Graphics.hpp>
#include<string>
#include"chessman.hpp"
#include<vector>
class Pawn: public Chessman
{
public:
    bool checkMovement(int _id,int vis[]);
    Pawn(int _id, SideState _state, std::string s);
    Pawn(const Pawn& _chessman): Chessman(_chessman) {};
    std::unique_ptr<Chessman> clone();

};


#endif // PAWN_H




