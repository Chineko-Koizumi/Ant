#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Ant.h"
#include "Mesh.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Ant",true);
    sf::RenderTexture Render_Texture;
    Render_Texture.create(1000,1000);

    window.setActive(true);

    Mesh mesh(400,400, &window, &Render_Texture);
    AntPath antpath(11);

    antpath.AddColor(sf::Color::Black, sf::Color(92, 0, 0),              1 ,    0);
                                                                           
    antpath.AddColor(sf::Color(92, 0, 0), sf::Color(191, 2, 2),          -1,    1);
    antpath.AddColor(sf::Color(191, 2, 2), sf::Color(255, 3, 3),         1,    2);
    antpath.AddColor(sf::Color(255, 3, 3), sf::Color(173, 55, 0),        -1,    3);
    antpath.AddColor(sf::Color(173, 55, 0), sf::Color(255, 81, 0),       -1,    4);
                                                                           
    antpath.AddColor(sf::Color(255, 81, 0), sf::Color(181, 103, 0),      1 ,    5);
    antpath.AddColor(sf::Color(181, 103, 0), sf::Color(255, 255, 0),     1 ,    6);
    antpath.AddColor(sf::Color(255, 255, 0), sf::Color(170, 255, 0),     1 ,    7);
    antpath.AddColor(sf::Color(170, 255, 0), sf::Color(0, 135, 58),      1,    8);
                                                                          
    antpath.AddColor(sf::Color(0, 135, 58), sf::Color(0, 131, 135),      1,    9);
    antpath.AddColor(sf::Color(0, 131, 135), sf::Color::Black,           1,    10);


    Ant ant(&mesh,200,200,&antpath);
    ant.SetType(1);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ant.MoveNext();
        switch (ant.stop)
        {
            case true: 
            {
                window.clear();
                mesh.RedrawMesh();
            }
            case false: 
            {
                window.clear();
                mesh.RedrawMesh(ant.back_x, ant.back_y);
               // mesh.RedrawMesh(ant2.back_x, ant2.back_y);
            }
        }
       

        window.display();
    }

    return 0;
}