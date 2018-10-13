#ifndef CHESSBOARD_H

#define CHESSBOARD_H


#include<SFML/Graphics.hpp>
#include <stdexcept>
#include<vector>
#include"game_settings.h"
#include"square.hpp"
#include"knight.hpp"
#include"king.hpp"
#include"queen.hpp"
#include"bishop.hpp"
#include"rook.hpp"
#include"pawn.hpp"
#include<memory>
#include<cassert>
#include<functional>


class Chessboard
{
private:
    sf::Texture onTexture;
    sf::Sprite onSprite;
    void setChessman1(SideState _state);
    void setChessman2(SideState _state);
    void setChessman(const std::vector<std::unique_ptr<Chessman>>& chessman,int _vis[]);
    int getKingId(SideState _state);
    int vis[64];
    int visSize = 64;
public:
    std::vector<std::unique_ptr<Square>> chessboard;
    std::vector<std::unique_ptr<Chessman>> chessman;
    int mirror[64];
    Chessboard(const std::vector<std::unique_ptr<Chessman>>& chessman,int _vis[]);
    Chessboard();
    ~Chessboard();
    bool check(SideState _state);
    bool check(int _id, int _newId);
    bool checkmate(SideState _state);
    bool collisionWithKing(int _id);
    SideState chessmanState(int _id);
    void createChessboard();
    void draw(sf::RenderWindow &window);
    int contains(sf::Vector2f _mouse);
    int movement(int _id, sf::Vector2f _mouse);
    int movement(sf::Vector2f _mouse);
    void changeId(int _id,int _newId);
    bool checkMovement(int _id,int _newId);
    void mark(int _id,sf::RenderWindow &window);
    bool ifStateGood(int _id);
    void clearVis();
    void changeVis(int cnt,SideState _state);

};

#endif // CHESSBOARD_H

