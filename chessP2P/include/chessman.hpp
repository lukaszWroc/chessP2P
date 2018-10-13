#ifndef CHESSMAN_H

#define CHESSMAN_H

#include<SFML/Graphics.hpp>
#include<string>
#include<vector>
#include<string>
#include <stdexcept>
#include<memory>
#include"game_settings.h"
#include<iostream>
class Chessman
{
private:
    sf::Texture texture;

public:
    int id;
    int movementCnt;
    SideState state;
    ChessmanState chessmanState;
    sf::Sprite sprite;
    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }
    void movement(int _id)
    {
        movementCnt++;
        id = _id;
        sprite.setPosition(getPosition(id).x,getPosition(id).y);
    };

    Chessman(int _id,SideState _state,std::string s,ChessmanState _chessmanState) :id(_id), state(_state) ,chessmanState(_chessmanState)
    {
        if( !texture.loadFromFile("data\\" + s + ".png"))
            throw std::invalid_argument("can't load " + s);
        sprite.setTexture(texture);
        movementCnt = -1;
        movement(id);
    }
    Chessman(const Chessman& _chessman)
    {
        id = _chessman.id;
        movementCnt = _chessman.movementCnt;
        state = _chessman.state;
        chessmanState = _chessman.chessmanState;
    };
    virtual ~Chessman(){};
    virtual bool checkMovement(int _id,int vis[]) = 0;
    virtual std::unique_ptr<Chessman> clone() = 0;
    bool checkMovementHelper(int _id,int _newId,int dx,int dy,int cnt,int maxCnt,int _color,int vis[]);
};

#endif // CHESSMAN_H


