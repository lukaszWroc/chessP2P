
#ifndef KING_H

#define KING_H

#include<SFML/Graphics.hpp>
#include<string>
#include"chessman.hpp"
#include<vector>
class King: public Chessman
{
public:
    bool checkMovement(int _id,int vis[]);
    King(int _id, SideState _state, std::string s);
    King(const King& _chessman): Chessman(_chessman) {};
    std::unique_ptr<Chessman> clone();
};


#endif // KING_H



