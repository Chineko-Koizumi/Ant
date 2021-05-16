#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Mesh.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!",true);
    sf::RenderTexture Render_Texture;
    Render_Texture.create(1000,1000);
    //window.setFramerateLimit(75);
    window.setActive(true);

    Mesh mesh(800,800, &window, &Render_Texture);
    AntPath antpath;

    antpath.AddColor(sf::Color::Black, sf::Color(92, 0, 0), std::vector<int>({ 1 }));

    sf::Color(209, 146, 10);
    
    antpath.AddColor(sf::Color(92, 0, 0), sf::Color(191, 2, 2), std::vector<int>({ -1 }));
    antpath.AddColor(sf::Color(191, 2, 2), sf::Color(255, 3, 3), std::vector<int>({ -1 }));
    antpath.AddColor(sf::Color(255, 3, 3), sf::Color(173, 55, 0), std::vector<int>({ -1 }));
    antpath.AddColor(sf::Color(173, 55, 0), sf::Color(255, 81, 0), std::vector<int>({ -1 }));
                     
    antpath.AddColor(sf::Color(255, 81, 0), sf::Color(181, 103, 0), std::vector<int>({ 1 }));
    antpath.AddColor(sf::Color(181, 103, 0), sf::Color(255, 255, 0), std::vector<int>({ 1 }));
    antpath.AddColor(sf::Color(255, 255, 0), sf::Color(170, 255, 0), std::vector<int>({ 1 }));
    antpath.AddColor(sf::Color(170, 255, 0), sf::Color(0, 135, 58), std::vector<int>({ -1 }));
                     
    antpath.AddColor(sf::Color(0, 135, 58), sf::Color(0, 131, 135), std::vector<int>({ -1 }));
    antpath.AddColor(sf::Color(0, 131, 135), sf::Color::Black, std::vector<int>({ -1 }));
    /*
    antpath.AddColor(sf::Color(209, 146, 10), sf::Color(209, 158, 10), std::vector<int>({ -1 }));
    antpath.AddColor(sf::Color(209, 158, 10), sf::Color(209, 170, 10), std::vector<int>({ -1 }));

    antpath.AddColor(sf::Color(209, 170, 10), sf::Color(209, 182, 10), std::vector<int>({ 1 }));
    antpath.AddColor(sf::Color(209, 182, 10), sf::Color(209, 194, 10), std::vector<int>({ -1 }));
    antpath.AddColor(sf::Color(209, 194, 10), sf::Color(209, 109, 10), std::vector<int>({ 1 }));
    antpath.AddColor(sf::Color(209, 109, 10), sf::Color(209, 10, 10), std::vector<int>({ -1 }));
    */



    Ant ant(&mesh,400,400,&antpath);
    //Ant ant2(&mesh, 550, 550, &antpath);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ant.MoveNext();
       // ant2.MoveNext();
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