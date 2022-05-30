#pragma once

#include "AnimowaneObiekty.h"

class shot : public AnimowaneObiekty
{
public:
    shot(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    //Sekcja metod
    void poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);
    void strzal(const sf::Event &event);
};


