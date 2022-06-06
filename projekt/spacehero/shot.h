#pragma once

#include "AnimowaneObiekty.h"
#include "spaceship.h"

class shot : public AnimowaneObiekty
{
public:
    shot(const sf::Texture &texture, Spaceship &statek);


    //Sekcja metod
    void poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);
    void strzal(const sf::Event &event, Spaceship &statek);

    void usun_pocisk(std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski);


};


