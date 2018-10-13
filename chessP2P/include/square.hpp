#ifndef SQUARE_H

#define SQUARE_H


#include<SFML/Graphics.hpp>
#include <stdexcept>

class Square
{
private:
    sf::Texture squareTexture;
public:
    int id;
    int height,width;
    sf::Sprite squareSprite;
    Square(int state,int _height,int _width,int _id);
    void draw(sf::RenderWindow &window);
};

#endif // SQUARE_H
