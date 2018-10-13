#include"square.hpp"


Square::Square(int state,int _height,int _width,int _id)
{
    id = _id;
    height = _height;
    width = _width;
    if(state == 0)
    {
        if(!squareTexture.loadFromFile("data\\whiteSquare.png") )
            throw std::invalid_argument("can't load whiteSquare.png");
    }
    else
    {
        if(!squareTexture.loadFromFile("data\\blackSquare.png") )
            throw std::invalid_argument("can't load blackSquare.png");
    }
    squareSprite.setTexture(squareTexture);
    squareSprite.setPosition(height,width);
}


void Square::draw(sf::RenderWindow &window)
{
      window.draw(squareSprite);
}
