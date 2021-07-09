#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>
#define N 10

int max(int* tab, int size)
{
    int max = 0;
    for (int i = 1; i < size; i++)
    {
        if (tab[i] > tab[max])
            max = i;
    }
    return max;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 900), "Jump!", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    srand(time(0));

    sf::Texture bg;
    sf::Sprite bg_sprite;
    bg.loadFromFile("stars.jpg");
    bg_sprite.setTexture(bg);
    bg_sprite.setScale(window.getSize().x / static_cast<double>(bg.getSize().x), window.getSize().y / static_cast<double>(bg.getSize().y));
    bg_sprite.setPosition(0, 0);

    sf::Texture donut;
    sf::Sprite donut_sprite;

    donut.loadFromFile("donut.png");
    donut_sprite.setTexture(donut);
    donut_sprite.setScale(110 / static_cast<double>(donut.getSize().x), 49.5 / static_cast<double>(donut.getSize().y));

    int x[N], y[N];
    x[0] = 300;
    y[0] = 800;
    for (int i = 1; i < N; i++)
    {
        x[i] = rand() % 550 - 50; 
        y[i] = y[i - 1] - 100;
    }

    sf::Texture pony;
    sf::Sprite pony_sprite;

    pony.loadFromFile("pony.png");
    pony_sprite.setTexture(pony);
    pony_sprite.setScale(160/ static_cast<double>(pony.getSize().x), 200 / static_cast<double>(pony.getSize().y));

    double pony_x = 280;
    double pony_y = 500;
    double dy = 0;
    double h = 501;

    sf::Texture end;
    sf::Sprite end_sprite;
    end.loadFromFile("end.jpg");
    end_sprite.setTexture(end);
    end_sprite.setPosition(0, 0);
    end_sprite.setScale(window.getSize().x / static_cast<double>(end.getSize().x), window.getSize().y / static_cast<double>(end.getSize().y));

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.draw(bg_sprite);
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        for (int i = 0; i < N; i++)
        {
            donut_sprite.setPosition(x[i], y[i]);
            window.draw(donut_sprite);
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                pony_x--;
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                pony_x++;
            }
        }

        dy += 0.01;
        pony_y += dy;
        if(pony_y > 700)
            dy = -2;

        if (pony_y < h)
        {
            for (int i = 0; i < N; i++)
            {
                pony_y = h;
                y[i] -= dy;
            }
        }
        
        for (int i = 0; i < N; i++)
        {
            if (pony_y + 150 >= y[i] && pony_y + 150 <= static_cast<double>(y[i]) + 45 && pony_x + 100 >= x[i] && pony_x + 50 <= static_cast<double>(x[i]) + 100)
                dy = -2;
            if (y[i] > 900)
            {
                y[i] = 0;
                x[i] = rand() % 550 - 50;
            }
        }

        pony_sprite.setPosition(pony_x, pony_y);
        window.draw(pony_sprite);

        int i_max = max(y, N);
        if (pony_y + 200 >= y[i_max] && (pony_x + 100 < x[i_max] || pony_x + 50 > static_cast<double>(x[i_max]) + 100))
        {
            window.draw(end_sprite);
            window.display();
            bool mode = false;
            while (mode == false)
            {
                window.clear(sf::Color::Black);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    mode = true;
                }
            }
            window.close();
        }

        window.display();
    }
    return 0;
}