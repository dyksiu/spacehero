#ifndef ASTEROID_H
#define ASTEROID_H

#include "AnimowaneObiekty.h"

class Asteroid : public AnimowaneObiekty
{
public:
    Asteroid(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    std::pair<int, int> losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu);

    //Sekcja metod
    void poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);
};

#endif // ASTEROID_H
