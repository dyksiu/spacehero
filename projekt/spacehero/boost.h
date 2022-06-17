#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class boost : public sf::Sprite
{
public:
    boost(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    //Sekcja metod
    void poruszaj(const sf::Time &elapsed);

private:
    int predkosc_x;
    int predkosc_y;
};


