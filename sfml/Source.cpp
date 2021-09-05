#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Menu.h"

using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG ZS");
    Menu menu(window.getSize().x, window.getSize().y);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    //variables that keep the game loop running
    bool play = true;
    
    //event object holding all events
    Event event;

    //font
    Font font;
    font.loadFromFile("Data/font.otf");
    Text Score1;
    Score1.setFont(font);
    Score1.setCharacterSize(30);
    Score1.setFillColor(Color::Black);
    Score1.setPosition(360, 10);
    Score1.setString("Score");
    
    Text Score;
    Score.setFont(font);
    Score.setCharacterSize(30);
    Score.setFillColor(Color::Black);
    Score.setPosition(370, 40);
    Score.setString("Score");
    Score.setString("0 : 0");

    Text Name;
    Name.setFont(font);
    Name.setCharacterSize(20);
    Name.setFillColor(Color::Black);
    Name.setPosition(650, 550);
    Name.setString("Zeyad Sultan");

    //images
    Texture texPad;
    Texture texBall;
    Texture texBackground;
    if (texPad.loadFromFile("Data/rec.png") == 0)
    {
        return -1;
    }
    if (texBall.loadFromFile("Data/ball.png") == 0)
    {
        return -1;
    }
    if (texBackground.loadFromFile("Data/background.jpg") == 0)
    {
        return -1;
    }


    //sounds
    SoundBuffer buff_hit;

    Sound hit;
    hit.setBuffer(buff_hit);
    if (buff_hit.loadFromFile("Data/hit.wav") == 0)
    {
        return-1;
    }

    //states
    bool up = false, down = false;
    bool up2 = false, down2 = false;

    //variables
    int yVelocityP1 = 0;
    int yVelocityP2 = 0;
    int xVelocityBall = 0;
    int yVelocityBall = 0;
    int P1Score = 0;
    int P2Score = 0;
    int index = -6;

    //shapes
    RectangleShape Background;
    Background.setSize(Vector2f(800, 600));
    Background.setPosition(0, 0);
    Background.setTexture(&texBackground);

    RectangleShape P1;
    P1.setSize(Vector2f(20, 200));
    P1.setOrigin(Vector2f(5, 100));
    P1.setPosition(Vector2f(20, 300));
    P1.setFillColor(Color::White);
    P1.setTexture(&texPad);

    RectangleShape P2;
    P2.setSize(Vector2f(20, 200));
    P2.setOrigin(Vector2f(10, 100));
    P2.setPosition(Vector2f(780, 300));
    P2.setFillColor(Color::Blue);
    P2.setTexture(&texPad);

    CircleShape ball;
    ball.setRadius(15);
    ball.setPosition(385,285);
    ball.setTexture(&texBall);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
                if (event.key.code == Keyboard::W)
                {
                    up = true;
                }
                if (event.key.code == Keyboard::S)
                {
                    down = true;
                }
                if (event.key.code == Keyboard::Up)
                {
                    up2 = true;
                }
                if (event.key.code == Keyboard::Down)
                {
                    down2 = true;
                }
                if (event.key.code == Keyboard::Space)
                {
                     xVelocityBall = index;
                     yVelocityBall = index;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::W)
                {
                    up = false;
                }
                if (event.key.code == Keyboard::S)
                {
                    down = false;
                }
                if (event.key.code == Keyboard::Up)
                {
                    up2 = false;
                }
                if (event.key.code == Keyboard::Down)
                {
                    down2 = false;
                }
            }
        }
        //logic
        if (up == true) 
        {
            yVelocityP1 = -5;
        }
        if (down == true)
        {
            yVelocityP1 = 5;
        }
        if (up == true && down == true)
        {
            yVelocityP1 = 0;
        }
        if (up == false && down == false)
        {
            yVelocityP1 = 0;
        }
        P1.move(0, yVelocityP1);

        //out of bound check
        if (P1.getPosition().y < 100)
        {
            P1.setPosition(20, 100);
        }
        if (P1.getPosition().y > 500)
        {
            P1.setPosition(20, 500);
        }

        if (up2 == true)
        {
            yVelocityP2 = -5;
        }
        if (down2 == true)
        {
            yVelocityP2 = 5;
        }
        if (up2 == true && down2 == true)
        {
            yVelocityP2 = 0;
        }
        if (up2 == false && down2 == false)
        {
            yVelocityP2 = 0;
        }
        P2.move(0, yVelocityP2);

        //out of bound check
        if (P2.getPosition().y < 100)
        {
            P2.setPosition(780, 100);
        }
        if (P2.getPosition().y > 500)
        {
            P2.setPosition(780, 500);
        }


        ball.move(xVelocityBall, yVelocityBall);
        if (ball.getPosition().y < 0)
        {
            yVelocityBall = -yVelocityBall;
        }
        if (ball.getPosition().y > 550)
        {
            yVelocityBall = -yVelocityBall;
        }
        if (ball.getPosition().x < -50)
        {
            P2Score ++ ;
            ball.setPosition(375, 275);
             xVelocityBall = 0;
             yVelocityBall = 0;
        }
        if (ball.getPosition().x > 800)
        {
            P1Score ++;
            ball.setPosition(375, 275);
            xVelocityBall = 0;
            yVelocityBall = 0;
        }

        if (ball.getGlobalBounds().intersects(P1.getGlobalBounds()) == true)
        {
            xVelocityBall = -xVelocityBall;
            hit.play();
        }
        if (ball.getGlobalBounds().intersects(P2.getGlobalBounds()) == true)
        {
            xVelocityBall = -xVelocityBall;
            hit.play();
        }

        if (P1Score + P2Score == 1)
        {
            index=-7;
        }
        if (P1Score + P2Score == 3)
        {
            index = -8;
        }
        if (P1Score + P2Score == 6)
        {
            index = -9;
        }
        if (P1Score + P2Score == 8)
        {
            index = -10;
        }

        //rendering
        window.clear();
        
        window.draw(Background);
        window.draw(Name);
        window.draw(P1);
        window.draw(P2);
        window.draw(ball);

        stringstream text;
        text << P1Score << " : " << P2Score;
        Score.setString(text.str());
        window.draw(Score);
        window.draw(Score1);
        

        window.display();
    }
    return 0;
}
/*#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include "Menu.h"


int main()
{


    const int screenX = 800;
    const int screenY = 600;
    sf::Vector2f paddleSize(10, 60);
    const int ballRad = 5;
    float ballSpeed = 400.f;
    float ballAngle = 75.f;
    sf::Vector2f velocity;


    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Pong", sf::Style::Titlebar | sf::Style::Close);
    Menu menu(window.getSize().x, window.getSize().y);

    window.setVerticalSyncEnabled(true);

    sf::RectangleShape paddle1;
    paddle1.setSize(paddleSize);
    paddle1.setFillColor(sf::Color::White);
    paddle1.setPosition(paddleSize.x, (screenY / 2) - paddleSize.y);
    paddle1.setOrigin(sf::Vector2f(paddle1.getSize().x / 2, paddle1.getSize().y / 2));

    sf::RectangleShape paddle2;
    paddle2.setSize(paddleSize);
    paddle2.setFillColor(sf::Color::White);
    paddle2.setPosition(screenX - (paddleSize.x * 2), (screenY / 2) - paddleSize.y);

    sf::RectangleShape topBorder;
    topBorder.setSize(sf::Vector2f(screenX, paddleSize.x));
    topBorder.setPosition(0, 0);

    sf::RectangleShape botBorder;
    botBorder.setSize(sf::Vector2f(screenX, paddleSize.x));
    botBorder.setPosition(0, screenY - paddleSize.x);

    sf::Font font;

    if (!font.loadFromFile("Data/font.otf"))
        return EXIT_FAILURE;

    bool Sound;
    sf::SoundBuffer bufferPaddle;
    if (!bufferPaddle.loadFromFile("Data/hit.wav")) {}
    sf::Sound soundPaddle;
    soundPaddle.setBuffer(bufferPaddle);

    sf::SoundBuffer bufferScore;
    if (!bufferScore.loadFromFile("Data/hit.wav")) {}
    sf::Sound soundScore;
    soundScore.setBuffer(bufferScore);

    sf::SoundBuffer bufferWall;
    if (!bufferWall.loadFromFile("Data/hit.wav")) {}
    sf::Sound soundWall;
    soundWall.setBuffer(bufferWall);

    int intScore1 = 0;
    sf::Text textScore1;
    std::string strScore1 = std::to_string(intScore1);
    textScore1.setString(strScore1);
    textScore1.setFont(font);
    textScore1.setCharacterSize(paddleSize.y * 1.5f);
    textScore1.setPosition(sf::Vector2f(screenX / 5.f, 0.f));

    int intScore2 = 0;
    sf::Text textScore2;
    std::string strScore2 = std::to_string(intScore2);
    textScore2.setString(strScore2);
    textScore2.setFont(font);
    textScore2.setCharacterSize(paddleSize.y * 1.5f);
    textScore2.setPosition(sf::Vector2f(365.f, 0.f));

    //add sf::VertexArray, dashed line splitting map into 2

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(screenX / 2 + 1,0)),
        sf::Vertex(sf::Vector2f(screenX / 2 + 1,screenY))
    };

    sf::CircleShape ball(ballRad);
    ball.setPointCount(10);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(sf::Vector2f(screenX / 2.f, screenY / 2.f));

    //run prog as long as the window is open
    sf::Clock clock;
    bool Playing = false;
    while (window.isOpen())
    {
        if (Playing)
        {
            float deltaTime = clock.restart().asSeconds();
            float factor = deltaTime * ballSpeed;
            velocity.x = std::cos(ballAngle) * factor;
            velocity.y = std::sin(ballAngle) * factor;

            ball.move(velocity.x, velocity.y);

            if ((ball.getGlobalBounds().intersects(paddle2.getGlobalBounds())) || ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()))
            {
                // ball.move(sf::Vector2f(;
                velocity.x = -(velocity.x);
                ballSpeed = -ballSpeed;
                ballAngle = -ballAngle;
                soundPaddle.play();
            }


            if (ball.getGlobalBounds().intersects(topBorder.getGlobalBounds()) || ball.getGlobalBounds().intersects(botBorder.getGlobalBounds()))
            {
                velocity.x = -velocity.x;
                ballAngle = -ballAngle;
                soundWall.play();
            }

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !(paddle1.getGlobalBounds().intersects(topBorder.getGlobalBounds()))) //only move up if not touching top border
                paddle1.move(sf::Vector2f(0, -(paddleSize.x / 2)));
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && !(paddle1.getGlobalBounds().intersects(botBorder.getGlobalBounds())))
                paddle1.move(sf::Vector2f(0, paddleSize.x / 2));

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !(paddle2.getGlobalBounds().intersects(topBorder.getGlobalBounds())))
                paddle2.move(sf::Vector2f(0, -(paddleSize.x / 2)));
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !(paddle2.getGlobalBounds().intersects(botBorder.getGlobalBounds())))
                paddle2.move(sf::Vector2f(0, paddleSize.x / 2));

            if (ball.getPosition().x > paddle2.getPosition().x + 2 * ballRad)
            {
                intScore1++;
                strScore1 = std::to_string(intScore1);
                textScore1.setString(strScore1);
                ball.setPosition(sf::Vector2f(screenX / 2, screenY / 2));
                soundScore.play();
            }

            if (ball.getPosition().x < paddle1.getPosition().x - 2 * ballRad)
            {
                intScore2++;
                strScore2 = std::to_string(intScore2);
                textScore2.setString(strScore2);
                ball.setPosition(sf::Vector2f(screenX / 2, screenY / 2));
                soundScore.play();
            }


            window.clear(sf::Color::Black);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.draw(topBorder);
            window.draw(botBorder);
            window.draw(line, 2, sf::Lines);
            window.draw(textScore1);
            window.draw(textScore2);
            window.display();
        }

        if (!Playing)
        {
            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
        }



        //check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            //"close requested" event: we close the window

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();

            case sf::Event::KeyPressed:
                switch (event.key.code)
            case sf::Keyboard::Escape:
                Playing = false;
                break;

            case sf::Event::KeyReleased:  //menu controls
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        Playing = true;
                        break;
                    case 1:
                        //open sound menu
                        //Sound = !Sound; add to sound menu
                        break;
                    case 2:
                        window.close();
                        break;
                    }
                    break;
                }
                break;
            }

        }

    }
    return EXIT_SUCCESS;
}*/