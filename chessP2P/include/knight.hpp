#ifndef KNIGHT_H

#define KNIGHT_H

#include<SFML/Graphics.hpp>
#include<string>
#include"chessman.hpp"
#include<vector>
class Knight: public Chessman
{
public:
    bool checkMovement(int _id,int vis[]);
    Knight(int _id, SideState _state, std::string s);
    Knight(const Knight& _chessman): Chessman(_chessman) {};
    std::unique_ptr<Chessman> clone();
};


#endif // KNIGHT_H




