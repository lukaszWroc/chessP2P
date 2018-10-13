#ifndef GAME_H

#define GAME_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<string>
#include"chessboard.hpp"
#include"game_settings.h"

extern const int gameWindowHeight;
class Game
{
public:
    Game();
    ~Game();
    void run();
    void displayMenu();
    void displayGame();
    void displayGameOptions();
    void displayCreateGameOptions();
    void displayJoinGameOptions();
    void displayPauseMenu();
    void connect();
    void server();
    void client();
    void send(int _id,int _newId);
    void send(int _id);
    void receive();
    void initializeChessboard();
    void displayStateOfConnection();
    bool checkIpAndPort(std::string _ip,std::string _port);
private:
    enum GameState {MENU,GAME_OPTIONS,CREATE_GAME,JOIN_GAME,GAME,END,SERVER,SEND,RECIVE,CLIENT,
                    CREATE_GAME_STATE_OF_CONNECTION,JOIN_GAME_STATE_OF_CONNECTION,WRONG_IP_OR_PORT,
                    PAUSE_RECIVE,PAUSE_SEND,PAUSE_LOSE,PAUSE_WON};
    GameState state;
    sf::RenderWindow gameWindow;
    Chessboard *chessboard;
    sf::Text title;
    sf::Text menuOptionsTableText[2];
    sf::Text gameOptionsTableText[2];
    sf::Text createGameOptionsTableText[2][2];
    sf::Text createGameOptionsTableText1[3];
    sf::Text joinGameOptionsTableText[1][2];
    sf::Text stateOfConnectionTableText[2];
    sf::Text playButtonText;
    sf::Text yourMoveText;
    sf::Text backButtonText;
    sf::Text exitButtonText;
    sf::Font font;
    int port1;
    std::string ipAdress;
    sf::TcpSocket socket;
    sf::TcpListener listener;
    sf::Mutex mutex;

};


#endif // GAME_H
