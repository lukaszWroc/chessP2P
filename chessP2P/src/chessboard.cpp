#include"chessboard.hpp"

Chessboard::Chessboard()
{

    if(!onTexture.loadFromFile("data\\on.png") )
        throw std::invalid_argument("can't load on.png");
    onSprite.setTexture(onTexture);
}
void Chessboard::createChessboard()
{
    chessboard.clear();
    chessman.clear();
    clearVis();
    int state;
    int shift;
    if(sideState == white)
        shift = 0;
    else
        shift = 1;
    for(int i=0;i<8;i++)
    {
        state = (i+shift)%2;
        for(int j=0;j<8;j++)
        {
            chessboard.push_back(std::make_unique<Square>((state + j) % 2,getPosition(i*8+j).x,getPosition(i*8+j).y,i*8 + j));
        }
    }
    setChessman1(sideState);
    for(int i=48;i<64;i++)
            changeVis(i,sideState);
    if(sideState == white)
    {
        setChessman2(black);
        for(int i=0;i<16;i++)
            changeVis(i,black);
    }
    else
    {
        setChessman2(white);
        for(int i=0;i<16;i++)
            changeVis(i,white);
    }

    for(int i=0;i<64;i++)
    {
        mirror[i] = 63- i;
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<4;j++)
            std::swap(mirror[i*8+j],mirror[i*8+7-j]);
    }
}
Chessboard::~Chessboard()
{
    chessboard.clear();
    chessman.clear();
}
void Chessboard::setChessman1(SideState _state)
{
    std::string _color;
    if(_state == white)
        _color = "White";
    else
        _color = "Black";
    for(int i=0;i<8;i++)
    {
        chessman.push_back(std::make_unique<Pawn>(48 + i,_state,"pawn" + _color));
    }
    chessman.push_back(std::make_unique<Rook>(56,_state,"rook" + _color));
    chessman.push_back(std::make_unique<Rook>(63,_state,"rook" + _color));
    chessman.push_back(std::make_unique<Knight>(57,_state,"knight" + _color));
    chessman.push_back(std::make_unique<Knight>(62,_state,"knight" + _color));
    chessman.push_back(std::make_unique<Bishop>(58,_state,"bishop" + _color));
    chessman.push_back(std::make_unique<Bishop>(61,_state,"bishop" + _color));
    chessman.push_back(std::make_unique<Queen>(59,_state,"queen" +  _color));
    chessman.push_back(std::make_unique<King>(60,_state,"king" + _color));
}
void Chessboard::setChessman2(SideState _state)
{

    std::string _color;
    if(_state == white)
        _color = "White";
    else
        _color = "Black";
    for(int i=0;i<8;i++)
    {
        chessman.push_back(std::make_unique<Pawn>(8 + i,_state,"pawn" + _color));
    }
    chessman.push_back(std::make_unique<Rook>(0,_state,"rook" + _color));
    chessman.push_back(std::make_unique<Rook>(7,_state,"rook" + _color));
    chessman.push_back(std::make_unique<Knight>(1,_state,"knight" + _color));
    chessman.push_back(std::make_unique<Knight>(6,_state,"knight" + _color));
    chessman.push_back(std::make_unique<Bishop>(2,_state,"bishop" + _color));
    chessman.push_back(std::make_unique<Bishop>(5,_state,"bishop" + _color));
    chessman.push_back(std::make_unique<Queen>(3,_state,"queen" +  _color));
    chessman.push_back(std::make_unique<King>(4,_state,"king" + _color));
}
void Chessboard::draw(sf::RenderWindow &window)
{
    for(auto& i: chessboard)
    {
        i->draw(window);
    }
    for(auto& i: chessman)
    {
        i->draw(window);
    }
}

int Chessboard::contains(sf::Vector2f _mouse)
{
    for(auto& i: chessman)
    {
        if(i->sprite.getGlobalBounds().contains(_mouse))
        {
            return i->id;
        }
    }
    return -1;
}
int Chessboard::movement(sf::Vector2f _mouse)
{
    for(auto& i: chessboard)
    {
        if(i->squareSprite.getGlobalBounds().contains(_mouse))
        {
            return i->id;
        }
    }
    return 0;
}
int Chessboard::movement(int _id, sf::Vector2f _mouse)
{
    int newId = -1;
    for(auto& i: chessboard)
    {
        if(i->squareSprite.getGlobalBounds().contains(_mouse))
        {
            newId = i->id;
            break;
        }
    }
    if(_id == newId)
        return -1;
    if(newId == -1)
        return _id;
    if(collisionWithKing(newId) == false && check(_id,newId) == false &&  checkMovement(_id,newId) == true)
    {
        changeId(_id,newId);
        return -2;
    }
    return _id;
}

void Chessboard::changeId(int _id,int _newId)
{
    auto it = find_if(chessman.begin(), chessman.end(), [&](std::unique_ptr<Chessman>& obj){ return obj->id == _newId; });

    if (it != chessman.end())
    {
        chessman.erase(it);
    }
    for(auto& i: chessman)
    {
        if(i->id == _id)
        {
            i->movement(_newId);
            break;
        }
    }
    vis[_newId] = vis[_id];
    vis[_id] = 0;
}

bool Chessboard::checkMovement(int _id,int _newId)
{
    for(auto& i: chessman)
    {
        if(i->id == _id)
        {
            if(i->checkMovement(_newId,vis))
                return true;
            break;
        }
    }
    return false;
}
void Chessboard::mark(int _id,sf::RenderWindow &window)
{
    if(_id < 0 || 63 < _id)
        return;
    onSprite.setPosition(getPosition(_id).x,getPosition(_id).y);
    window.draw(onSprite);
}

bool Chessboard::ifStateGood(int _id)
{
    for(auto& i: chessman)
    {
        if(i->id == _id)
        {
            if(i->state == sideState)
            {
                return true;
            }
            break;
        }
    }
    return false;
}
int Chessboard::getKingId(SideState _state)
{
    int KingId=0;
    for(auto& i: chessman)
    {
        if(i->chessmanState == KING && i->state == _state)
        {
           KingId = i->id;
           break;
        }
    }
    return KingId;
}
bool Chessboard::check(SideState _state)
{

    int KingId = getKingId(_state);
    int x =0;
    for(int i=0;i<chessman.size();i++)
    {
        if(chessman[i]->state != _state)
        {
           if(checkMovement(chessman[i]->id,KingId))
                return true;
            x++;
        }
    }
    return false;
}

bool Chessboard::check(int _id, int _newId)
{
    SideState _state = chessmanState(_id);
    Chessboard _chessboard(chessman,vis);
    _chessboard.changeId(_id,_newId);
    return _chessboard.check(_state);
}

SideState Chessboard::chessmanState(int _id)
{
    for(auto &i: chessman)
    {
        if(i->id == _id)
            return i->state;
    }
    return white;
}


bool Chessboard::checkmate(SideState _state)
{
    Chessboard _chessboard;
    _chessboard.setChessman(chessman,vis);
    for(int j=0;j<64;j++)
    {
        for(int i=0;i<_chessboard.chessman.size();i++)
        {
            _chessboard.setChessman(chessman,vis);
            if(_chessboard.chessman[i]->state == _state)
            {
                if(_chessboard.checkMovement(_chessboard.chessman[i]->id,j))
                {
                    _chessboard.changeId(_chessboard.chessman[i]->id,j);
                    if(_chessboard.check(_state) == false)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

Chessboard::Chessboard(const std::vector<std::unique_ptr<Chessman>>& _chessman,int _vis[])
{
    chessman.clear();
    for(auto &i: _chessman)
    {
        chessman.push_back(i->clone());
    }
    for(int i=0;i<64;i++)
        vis[i] = _vis[i];

}
void Chessboard::setChessman(const std::vector<std::unique_ptr<Chessman>>& _chessman,int _vis[])
{
    chessman.clear();
    for(auto &i: _chessman)
    {
        chessman.push_back(i->clone());
    }
    for(int i=0;i<64;i++)
        vis[i] = _vis[i];
}

bool Chessboard::collisionWithKing(int _id)
{
    if(getKingId((sideState == white ? black : white)) == _id)
       return true;
    return false;
}
void Chessboard::clearVis()
{
    for(int i=0;i<visSize;i++)
        vis[i]=0;
}
void Chessboard::changeVis(int cnt,SideState _state)
{
    int val = 0;
    if(_state == white)
        val = -1;
    else
        val =  1;
    vis[cnt] = val;
}
