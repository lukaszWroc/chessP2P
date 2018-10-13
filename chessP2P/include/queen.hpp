#ifndef QUEEN_H

#define QUEEN_H

#include<SFML/Graphics.hpp>
#include<string>
#include"chessman.hpp"
#include<vector>
class Queen: public Chessman
{
public:
    bool checkMovement(int _id,int vis[]);
    Queen(int _id, SideState _state, std::string s);
    Queen(const Queen& _chessman): Chessman(_chessman) {};
    std::unique_ptr<Chessman> clone();
};


#endif // QUEEN_H




