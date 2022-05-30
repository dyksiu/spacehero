#ifndef PRZYCISK_H
#define PRZYCISK_H

#include "StatyczneObiekty.h"

class przycisk : public StatyczneObiekty
{
public:
    przycisk(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    //Sekcja metod
    bool czy_wcisniety(const sf::Vector2f &pozycja_myszki) const;

};

#endif // PRZYCISK_H
