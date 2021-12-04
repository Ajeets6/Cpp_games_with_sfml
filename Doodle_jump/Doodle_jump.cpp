#include <sfml/Graphics.hpp>
#include <SFML/Window.hpp>
#include<time.h>

using namespace sf; //namespace to access sfml function
struct point
{
    int x, y;

};


int main()
{
    srand(time(0));     //seeding(i.e start value till it loops back) with time(in UNIX epoch) for random num as it is increasing
    RenderWindow game(VideoMode(400,533),"Doodle game");  //creates window gmae of 400x533 pixels with window title "Doodle game" 
    game.setFramerateLimit(60);   //set framerate limit
    Texture t1, t2, t3;          //creates texture to use on sprite(texture live in graphics card)
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");

    Sprite sbackground(t1), splatform(t2), splayer(t3);  //sprite contains texture

    point platform[20];
    for (int i = 0; i < 10; i++) //creates platform
    {
        platform[i].x = rand() % 400;
        platform[i].y = rand() % 533;

    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;
    while (game.isOpen())//run the program as long as window is open(game loop)
    {
        Event event;
        while (game.pollEvent(event))
        {
            if (event.type == Event::Closed())
            {
                game.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) 
            x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) 
            x -= 3;

        dy += 0.2;
        y += dy;
        if (y > 500)
            dy = -10;
        if(y<h)
            for (int i = 0; i < 10; i++) {
                y = h;
                platform[i].y = platform[i].y - dy;
                if (platform[i].y > 533) {
                    platform[i].y = 0;
                    platform[i].x = rand() % 400;
                }
            }

        for (int i = 0; i < 10; i++) {
            if ((x + 50 > platform[i].x) && (x + 20 < platform[i].x + 68) && (y + 70 > platform[i].y) && (y + 70 < platform[i].y + 14) && (dy > 0))
                dy = -10;
        }
        splayer.setPosition(x, y);
        game.draw(sbackground);
        game.draw(splayer);
        for (int i = 0; i < 10; i++)
        {
            splatform.setPosition(platform[i].x, platform[i].y);
            game.draw(splatform);
        }


        game.display();
    }



   

    return 0;
}