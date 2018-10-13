#ifndef ROOK_H

#define ROOK_H

#include<SFML/Graphics.hpp>
#include<string>
#include"chessman.hpp"
#include<vector>
class Rook: public Chessman
{
public:
    void movement(int _id);
    bool checkMovement(int _id,int vis[]);
    Rook(int _id, SideState _state, std::string s);
    Rook(const Rook& _chessman): Chessman(_chessman) {};
    std::unique_ptr<Chessman> clone();

};


#endif // ROOK_H




