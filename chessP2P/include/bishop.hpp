#ifndef BISHOP_H

#define BISHOP_H

#include<SFML/Graphics.hpp>
#include<string>
#include"chessman.hpp"
#include<vector>
class Bishop: public Chessman
{
public:
    bool checkMovement(int _id,int vis[]);
    Bishop(int _id, SideState _state, std::string s);
    Bishop(const Bishop& _chessman): Chessman(_chessman) {};
    std::unique_ptr<Chessman> clone();
};


#endif // BISHOP_H



