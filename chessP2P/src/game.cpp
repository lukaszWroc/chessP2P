#include "game.h"

Game::Game()
{
    gameWindow.create(sf::VideoMode(gameWindowWidth,gameWindowHeight),"chessP2P");
    port1 = 50000;
    ipAdress = "127.0.0.1";
    state=MENU;
    if(!font.loadFromFile("data\\arial.ttf"))
       throw std::invalid_argument("can't load arial.ttf");

    chessboard = new Chessboard();

    std::string titleString="chess P2P";
    title.setString(titleString);
    title.setFont(font);
    title.setCharacterSize(80);
    title.setPosition(gameWindowWidth/2 - title.getGlobalBounds().width/2,20);

    std::string menuOptionsTableString[2] = {"PLAY", "EXIT"};

    for(int i=0;i<2;i++)
    {
        menuOptionsTableText[i].setString(menuOptionsTableString[i]);
        menuOptionsTableText[i].setCharacterSize(50);
        menuOptionsTableText[i].setFont(font);
        menuOptionsTableText[i].setPosition(gameWindowWidth/2
                                            - menuOptionsTableText[i].getGlobalBounds().width/2,200 +i*100);
    }

    std::string gameOptionsTableString[2] = {"Create Game", "Join Game"};
    for(int i=0;i<2;i++)
    {
        gameOptionsTableText[i].setString(gameOptionsTableString[i]);
        gameOptionsTableText[i].setCharacterSize(50);
        gameOptionsTableText[i].setFont(font);
        gameOptionsTableText[i].setPosition(gameWindowWidth/2
                                            - gameOptionsTableText[i].getGlobalBounds().width/2,200 +i*100);
    }


    playButtonText.setString("Play");
    playButtonText.setFont(font);
    playButtonText.setCharacterSize(80);
    playButtonText.setPosition(gameWindowWidth/2 - playButtonText.getGlobalBounds().width/2,20);

    backButtonText.setString("Back");
    backButtonText.setFont(font);
    backButtonText.setCharacterSize(50);


    std::string createGameOptionsTableString[2][2] = { {"enter ip" , "------------------"},
                                                        {"enter port", "------------------"}};
    std::string createGameOptionsTableString1[3] = { "choose color", "white", "black"};
    for(int i=0;i<2;i++)
    {
        createGameOptionsTableText[i][0].setString(createGameOptionsTableString[i][0]);
        createGameOptionsTableText[i][0].setCharacterSize(50);
        createGameOptionsTableText[i][0].setFont(font);
        createGameOptionsTableText[i][0].setPosition(gameWindowWidth/4
                                                     - createGameOptionsTableText[i][0].getGlobalBounds().width/2,200 +i*100);
    }
    for(int i=0;i<2;i++)
    {
        createGameOptionsTableText[i][1].setString(createGameOptionsTableString[i][1]);
        createGameOptionsTableText[i][1].setCharacterSize(50);
        createGameOptionsTableText[i][1].setFont(font);
        createGameOptionsTableText[i][1].setPosition(gameWindowWidth/2 + 100
                                                     - createGameOptionsTableText[i][1].getGlobalBounds().width/2,200 +i*100);
    }
    for(int i=0;i<3;i++)
    {
        createGameOptionsTableText1[i].setString(createGameOptionsTableString1[i]);
        createGameOptionsTableText1[i].setCharacterSize(50);
        createGameOptionsTableText1[i].setFont(font);
        createGameOptionsTableText1[i].setPosition(gameWindowWidth/4 + i*300
                                                   - createGameOptionsTableText1[i].getGlobalBounds().width/2,400);
    }

    std::string joinGameOptionsTableString[1][2] = {{"enter port", "------------------"}};
    for(int i=0;i<1;i++)
    {
        joinGameOptionsTableText[i][0].setString(joinGameOptionsTableString[i][0]);
        joinGameOptionsTableText[i][0].setCharacterSize(50);
        joinGameOptionsTableText[i][0].setFont(font);
        joinGameOptionsTableText[i][0].setPosition(gameWindowWidth/4
                                                   - joinGameOptionsTableText[i][0].getGlobalBounds().width/2,200 +i*100);
    }
    for(int i=0;i<1;i++)
    {
        joinGameOptionsTableText[i][1].setString(joinGameOptionsTableString[i][1]);
        joinGameOptionsTableText[i][1].setCharacterSize(50);
        joinGameOptionsTableText[i][1].setFont(font);
        joinGameOptionsTableText[i][1].setPosition(gameWindowWidth/2 + 100
                                                   - joinGameOptionsTableText[i][1].getGlobalBounds().width/2,200 +i*100);
    }


    std::string stateOfConnectionTableString[2] = {"Waiting for a connection", "Back"};
    for(int i=0;i<2;i++)
    {
        stateOfConnectionTableText[i].setString(stateOfConnectionTableString[i]);
        stateOfConnectionTableText[i].setCharacterSize(50);
        stateOfConnectionTableText[i].setFont(font);
        stateOfConnectionTableText[i].setPosition(gameWindowWidth/2
                                                  - stateOfConnectionTableText[i].getGlobalBounds().width/2,200 +i*100);
    }

    yourMoveText.setString("YOUR MOVE");
    yourMoveText.setCharacterSize(50);
    yourMoveText.setFont(font);
    yourMoveText.setPosition(gameWindowWidth/2 - yourMoveText.getGlobalBounds().width/2,
                             gameWindowHeight/2 - yourMoveText.getGlobalBounds().height/2);
    exitButtonText.setString("EXIT");
    exitButtonText.setCharacterSize(50);
    exitButtonText.setFont(font);
}

Game::~Game()
{
    listener.close();
    socket.disconnect();
    delete chessboard;
}

void Game::run()
{
    while(state!=END)
    {
        switch(state)
        {
            case MENU:
                displayMenu();
                break;
            case GAME_OPTIONS:
                displayGameOptions();
                break;
            case CREATE_GAME:
                displayCreateGameOptions();
                break;
            case JOIN_GAME:
                displayJoinGameOptions();
                break;
            case GAME:
                displayGame();
                break;
            case SEND:
                displayGame();
                break;
            case RECIVE:
                displayGame();
                break;
            case SERVER:
                server();
                break;
            case CLIENT:
                client();
                break;
            case JOIN_GAME_STATE_OF_CONNECTION:
                displayStateOfConnection();
                break;
            case CREATE_GAME_STATE_OF_CONNECTION:
                displayStateOfConnection();
                break;
            case PAUSE_LOSE:
                displayPauseMenu();
                break;
            case PAUSE_WON:
                displayPauseMenu();
                break;
            case PAUSE_RECIVE:
                displayPauseMenu();
                break;
            case PAUSE_SEND:
                displayPauseMenu();
                break;
        }
    }
}

void Game::displayMenu()
{
    while(state==MENU)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed
               || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                state = END;
            if(menuOptionsTableText[1].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                state = END;
            if(menuOptionsTableText[0].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                state = GAME_OPTIONS;
        }
        for(int i=0;i<2;i++)
        {
            if(menuOptionsTableText[i].getGlobalBounds().contains(mouse))
                menuOptionsTableText[i].setFillColor(sf::Color::Blue);
            else
                menuOptionsTableText[i].setFillColor(sf::Color::White);
        }
        gameWindow.clear();
        gameWindow.draw(title);
        for(int i=0;i<2;i++)
            gameWindow.draw(menuOptionsTableText[i]);
        gameWindow.display();
    }
}

void Game::displayGameOptions()
{
    while(state==GAME_OPTIONS)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed
               || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                state = END;
            if(gameOptionsTableText[0].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                state = CREATE_GAME;
            if(gameOptionsTableText[1].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                state = JOIN_GAME;
            }
        }
        for(int i=0;i<2;i++)
        {
            if(gameOptionsTableText[i].getGlobalBounds().contains(mouse))
                gameOptionsTableText[i].setFillColor(sf::Color::Blue);
            else
                gameOptionsTableText[i].setFillColor(sf::Color::White);
        }
        gameWindow.clear();
        for(int i=0;i<2;i++)
            gameWindow.draw(gameOptionsTableText[i]);
        gameWindow.display();
    }
}

 void Game::displayCreateGameOptions()
{
    int _id = -1;
    std::string tab[2];
    int _color = -1;
    sf::Text wrongIpOrPortText;
    wrongIpOrPortText.setString("WRONG IP OR PORT");
    wrongIpOrPortText.setCharacterSize(50);
    wrongIpOrPortText.setFont(font);
    wrongIpOrPortText.setPosition(gameWindowWidth/2 - wrongIpOrPortText.getGlobalBounds().width/2,120);
    wrongIpOrPortText.setFillColor(sf::Color::Red);

    backButtonText.setPosition(gameWindowWidth/2 - backButtonText.getGlobalBounds().width/2,510);

    while(state==CREATE_GAME || state==WRONG_IP_OR_PORT)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed
               || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                state = END;
            if(playButtonText.getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if(checkIpAndPort(static_cast<std::string>(createGameOptionsTableText[0][1].getString()),
                                  static_cast<std::string>(createGameOptionsTableText[1][1].getString())))
                {
                    state = CREATE_GAME_STATE_OF_CONNECTION;
                    port1 = std::stoi(static_cast<std::string>(createGameOptionsTableText[1][1].getString()));
                    ipAdress = static_cast<std::string>(createGameOptionsTableText[0][1].getString());
                    changeSideState(_color);
                }
                else
                {
                    state = WRONG_IP_OR_PORT;
                }
            }
            if(backButtonText.getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                state = MENU;
            }
            if(createGameOptionsTableText1[1].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                createGameOptionsTableText1[1].setFillColor(sf::Color::Blue);
                createGameOptionsTableText1[2].setFillColor(sf::Color::White);
                _color = -1;
            }
            if(createGameOptionsTableText1[2].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                createGameOptionsTableText1[2].setFillColor(sf::Color::Blue);
                createGameOptionsTableText1[1].setFillColor(sf::Color::White);
                _color = 1;
            }
            if(createGameOptionsTableText[0][1].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                _id = 0;
                break;
            }
            if(createGameOptionsTableText[1][1].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                _id = 1;
                break;
            }
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                _id = -1;

            if(_id != -1)
            {

                if (event.type == sf::Event::TextEntered)
                {
                    if (('0' <= static_cast<char>(event.text.unicode)
                         && static_cast<char>(event.text.unicode) <= '9')
                        || static_cast<char>(event.text.unicode) == '.')
                    {
                        tab[_id] += static_cast<char>(event.text.unicode);
                        createGameOptionsTableText[_id][1].setString(tab[_id]);
                        break;
                    }
                }
                if(event.type == sf::Event::KeyPressed
                   && event.key.code == sf::Keyboard::BackSpace && tab[_id].empty() == false)
                {
                    tab[_id].pop_back();
                    createGameOptionsTableText[_id][1].setString(tab[_id]);
                    break;
                }
            }
        }
        for(int i=0;i<2;i++)
        {
            if(createGameOptionsTableText[i][1].getGlobalBounds().contains(mouse))
                createGameOptionsTableText[i][1].setFillColor(sf::Color::Blue);
            else
                createGameOptionsTableText[i][1].setFillColor(sf::Color::White);
        }
        if(playButtonText.getGlobalBounds().contains(mouse))
            playButtonText.setFillColor(sf::Color::Blue);
        else
            playButtonText.setFillColor(sf::Color::White);

        if(backButtonText.getGlobalBounds().contains(mouse))
            backButtonText.setFillColor(sf::Color::Blue);
        else
            backButtonText.setFillColor(sf::Color::White);

        gameWindow.clear();
        for(int i=0;i<2;i++)
            gameWindow.draw(createGameOptionsTableText[i][0]);
        for(int i=0;i<2;i++)
            gameWindow.draw(createGameOptionsTableText[i][1]);
        for(int i=0;i<3;i++)
            gameWindow.draw(createGameOptionsTableText1[i]);
        if(state == WRONG_IP_OR_PORT)
            gameWindow.draw(wrongIpOrPortText);
        gameWindow.draw(playButtonText);
        gameWindow.draw(backButtonText);
        gameWindow.display();
    }
}

void Game::displayJoinGameOptions()
{
    int _id = -1;
    std::string tab[1];

    sf::Text wrongPortText;
    wrongPortText.setString("WRONG PORT");
    wrongPortText.setCharacterSize(50);
    wrongPortText.setFont(font);
    wrongPortText.setPosition(gameWindowWidth/2 - wrongPortText.getGlobalBounds().width/2,120);
    wrongPortText.setFillColor(sf::Color::Red);
    backButtonText.setPosition(gameWindowWidth/2 - backButtonText.getGlobalBounds().width/2,350);

    while(state==JOIN_GAME || state==WRONG_IP_OR_PORT)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed
               || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                state = END;
            if(playButtonText.getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased
               && event.mouseButton.button == sf::Mouse::Left)
            {
                if(checkIpAndPort("0",static_cast<std::string>(joinGameOptionsTableText[0][1].getString())))
                {
                    state = JOIN_GAME_STATE_OF_CONNECTION;
                    port1 = std::stoi(static_cast<std::string>(joinGameOptionsTableText[0][1].getString()));
                }
                else
                {
                    state = WRONG_IP_OR_PORT;
                }
            }
            if(backButtonText.getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased
               && event.mouseButton.button == sf::Mouse::Left)
            {
                state = MENU;
            }
            if(joinGameOptionsTableText[0][1].getGlobalBounds().contains(mouse)
               && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {

                _id = 0;
                break;
            }
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                _id = -1;

            if(_id != -1)
            {

                if(event.type == sf::Event::TextEntered)
                {
                    if (('0' <= static_cast<char>(event.text.unicode)
                         && static_cast<char>(event.text.unicode) <= '9')
                        || static_cast<char>(event.text.unicode) == '.')
                    {

                        tab[_id] += static_cast<char>(event.text.unicode);
                        joinGameOptionsTableText[_id][1].setString(tab[_id]);
                        break;
                    }
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace
                   && tab[_id].empty() == false)
                {
                    tab[_id].pop_back();
                    joinGameOptionsTableText[_id][1].setString(tab[_id]);
                    break;
                }
            }
        }
        for(int i=0;i<1;i++)
        {
            if(joinGameOptionsTableText[i][1].getGlobalBounds().contains(mouse))
                joinGameOptionsTableText[i][1].setFillColor(sf::Color::Blue);
            else
                joinGameOptionsTableText[i][1].setFillColor(sf::Color::White);
        }

        if(playButtonText.getGlobalBounds().contains(mouse))
            playButtonText.setFillColor(sf::Color::Blue);
        else
            playButtonText.setFillColor(sf::Color::White);

        if(backButtonText.getGlobalBounds().contains(mouse))
            backButtonText.setFillColor(sf::Color::Blue);
        else
            backButtonText.setFillColor(sf::Color::White);

        gameWindow.clear();
        for(int i=0;i<1;i++)
            for(int j=0;j<2;j++)
                gameWindow.draw(joinGameOptionsTableText[i][j]);
        if(state == WRONG_IP_OR_PORT)
            gameWindow.draw(wrongPortText);
        gameWindow.draw(playButtonText);
        gameWindow.draw(backButtonText);
        gameWindow.display();
    }
}


void Game::displayStateOfConnection()
{
    stateOfConnectionTableText[0].setString("Waiting for a connection");
    bool _cnt = false;
    sf::Clock clock;
    sf::Thread* thread  = 0;
    if(state == CREATE_GAME_STATE_OF_CONNECTION)
        thread = new sf::Thread(&Game::client,this);
    else
        thread = new sf::Thread(&Game::server,this);
    thread->launch();

    while(state==CREATE_GAME_STATE_OF_CONNECTION || state == JOIN_GAME_STATE_OF_CONNECTION)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed
               || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                state = END;
            if(stateOfConnectionTableText[1].getGlobalBounds().contains(mouse) &&
               event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                state = GAME_OPTIONS;
            }
        }
        if(_cnt == false && clock.getElapsedTime() > sf::seconds(60))
        {
            stateOfConnectionTableText[0].setString("Error joining multiplayer session");
            _cnt = true;
        }
        for(int i=1;i<2;i++)
        {
            if(stateOfConnectionTableText[i].getGlobalBounds().contains(mouse))
                stateOfConnectionTableText[i].setFillColor(sf::Color::Blue);
            else
                stateOfConnectionTableText[i].setFillColor(sf::Color::White);
        }
        gameWindow.clear();
        for(int i=0;i<2;i++)
            gameWindow.draw(stateOfConnectionTableText[i]);
        gameWindow.display();
    }
    thread->wait();
}

void Game::displayGame()
{
    int _id = -1;
    int _lastId = -1;
    chessboard->createChessboard();
    sf::Thread* thread  = new sf::Thread(&Game::receive,this);
    thread->launch();
    bool restart = false;
    sf::Clock clock;
    while(state != END && state != PAUSE_LOSE && state != PAUSE_WON && state != MENU)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        if(state == SEND && restart == false)
        {
            restart = true;
            clock.restart();
        }
        if(state == RECIVE)
        {
            restart = false;
        }
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed
               && event.key.code == sf::Keyboard::Escape))
            {
                state = END;
            }
            if(event.type == sf::Event::KeyPressed
               && event.key.code == sf::Keyboard::P)
            {
                if(state == SEND)
                    state = PAUSE_SEND;
                else
                    state = PAUSE_RECIVE;
                displayPauseMenu();

            }

            if(state == SEND)
            {
                if(event.type == sf::Event::MouseButtonReleased
                   && event.mouseButton.button == sf::Mouse::Left && _id >= 0)
                {
                    _id = chessboard->movement(_id,mouse);
                    if(_id == -2)
                    {
                        send(_lastId,chessboard->movement(mouse));
                    }
                    break;
                }
                if(event.type == sf::Event::MouseButtonReleased
                   && event.mouseButton.button == sf::Mouse::Left && _id < 0
                    && chessboard->ifStateGood(chessboard->contains(mouse)))
                {
                    _id = chessboard->contains(mouse);
                    if(_id > 0)
                        _lastId = _id;
                    break;
                }
            }
        }
        if(state!= RECIVE && state != SEND)
            thread->wait();
        gameWindow.clear();
        chessboard->draw(gameWindow);
        chessboard->mark(_id,gameWindow);
        if(clock.getElapsedTime() < sf::seconds(3) && state == SEND)
            gameWindow.draw(yourMoveText);
        gameWindow.display();

    }
}


void Game::displayPauseMenu()
{
    std::string title;
    if(state == PAUSE_LOSE)
        title = "YOU LOSE";
    else if(state == PAUSE_WON)
        title = "YOU WON";
    else
        title = "PAUSE";
    sf::Text titleText;
    titleText.setString(title);
    titleText.setFont(font);
    titleText.setCharacterSize(80);
    titleText.setPosition(gameWindowWidth/2 - titleText.getGlobalBounds().width/2,20);

    backButtonText.setPosition(gameWindowWidth/2 - backButtonText.getGlobalBounds().width/2,150);
    exitButtonText.setPosition(gameWindowWidth/2 - exitButtonText.getGlobalBounds().width/2,250);


    while(state == PAUSE_RECIVE || state == PAUSE_SEND || state == PAUSE_LOSE ||  state == PAUSE_WON)
    {
        sf::Event event;
        sf::Vector2f mouse(sf::Mouse::getPosition(gameWindow));
        while(gameWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed
               && event.key.code == sf::Keyboard::Escape))
            {
                state = END;
            }
            if(backButtonText.getGlobalBounds().contains(mouse) &&event.type == sf::Event::MouseButtonReleased
               && event.mouseButton.button == sf::Mouse::Left)
            {
                if(state == PAUSE_RECIVE)
                    state = RECIVE;
                else if(state == PAUSE_SEND)
                    state = SEND;
                else
                    state = MENU;
            }
            if(exitButtonText.getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased
               && event.mouseButton.button == sf::Mouse::Left)
            {
                state = MENU;
            }
        }
        if(backButtonText.getGlobalBounds().contains(mouse))
            backButtonText.setFillColor(sf::Color::Blue);
        else
            backButtonText.setFillColor(sf::Color::White);

        if(exitButtonText.getGlobalBounds().contains(mouse))
            exitButtonText.setFillColor(sf::Color::Blue);
        else
            exitButtonText.setFillColor(sf::Color::White);

        gameWindow.clear();
        gameWindow.draw(titleText);
        gameWindow.draw(exitButtonText);
        gameWindow.draw(backButtonText);
        gameWindow.display();
    }
}
void Game::client()
{
    sf::Socket::Status status;
    socket.setBlocking(true);
    while(state==CREATE_GAME_STATE_OF_CONNECTION)
    {
        status = socket.connect(ipAdress, port1);
        if (status == sf::Socket::Done)
        {
            if(sideState == white)
                state = SEND;
            else
                state = RECIVE;
            int _color;
            if(sideState == white)
                _color = -1;
            else
                _color = 1;
            sf::Packet packetSend;
            mutex.lock();
            packetSend << _color;
            socket.send(packetSend);
            mutex.unlock();

        }
   }
}

void Game::server()
{
    listener.setBlocking(true);
    while(state == JOIN_GAME_STATE_OF_CONNECTION)
    {
        if(listener.listen(port1) == sf::Socket::Done)
        {
            mutex.lock();
            listener.accept(socket);
            int _color =0;
            sf::Packet packetReceive;
            while(true)
            {
                if(socket.receive(packetReceive) == sf::Socket::Done)
                    packetReceive >> _color;
                if(_color == -1 || _color == 1)
                    break;
            }
            if(_color == -1)
                sideState = black;
            else
                sideState = white;
            if(sideState == white)
                state = SEND;
            else
                state = RECIVE;
                 mutex.unlock();
        }
   }
}
void Game::send(int _id,int _newId)
{
    sf::Packet packetSend;
    mutex.lock();
    packetSend << chessboard->mirror[_id];
    packetSend << chessboard->mirror[_newId];
    socket.send(packetSend);
    state = RECIVE;
    if(chessboard->check(sideState) && chessboard->checkmate(sideState))
    {
        state = PAUSE_LOSE;
        return;
    }
    if(chessboard->check(mirror(sideState)) && chessboard->checkmate(mirror(sideState)))
    {
        state = PAUSE_WON;
        return;
    }
    mutex.unlock();
}
void Game::send(int _id)
{
    sf::Packet packetSend;
    mutex.lock();
    packetSend << _id;
    socket.send(packetSend);
    mutex.unlock();
}
void Game::receive()
{
    int _id,_newId;
    sf::Packet packetReceive;
    socket.setBlocking(false);
    sf::Clock clockReceive,clockSend;
    while(state != END && state != PAUSE_LOSE && state != PAUSE_WON && state != MENU)
    {

        sf::sleep(sf::milliseconds(10));
        if(clockReceive.getElapsedTime() > sf::milliseconds(60))
            state = MENU;

        if(clockSend.getElapsedTime() > sf::milliseconds(10))
        {
            send(-1);
            clockSend.restart();
        }
        bool t = false;
        if(socket.receive(packetReceive)  == sf::Socket::Done)
        {
            t=true;
            clockReceive.restart();
        }
        if(state == RECIVE && t)
        {
            mutex.lock();
            packetReceive >> _id;
            mutex.unlock();
            if(_id == -1)
                continue;
            mutex.lock();
            packetReceive >>  _newId;
            chessboard->changeId(_id,_newId);
            state = SEND;
            if(chessboard->check(sideState) && chessboard->checkmate(sideState))
            {
                state = PAUSE_LOSE;
                return;
            }
            if(chessboard->check(mirror(sideState)) && chessboard->checkmate(mirror(sideState)))
            {
                state = PAUSE_WON;
                return;
            }
            mutex.unlock();
        }
    }
    listener.close();
    socket.disconnect();
}
bool Game::checkIpAndPort(std::string _ip,std::string _port)
{
    if(_ip.empty() || _port.empty())
            return false;
    for(char& c : _ip)
    {
        if(!('0' <= c && c <= '9') && c != '.')
            return false;
    }
    for(char& c : _port)
    {
        if(!('0' <= c && c <= '9'))
            return false;
    }
    return true;
}
