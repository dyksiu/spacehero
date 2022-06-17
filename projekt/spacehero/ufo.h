#ifndef UFO_H
#define UFO_H

#include "AnimowaneObiekty.h"

class Ufo : public AnimowaneObiekty
{
public:
    Ufo(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    std::pair<int, int> losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu);

    //Sekcja metod
    void poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);

    //Metody obslugujace zycia
    void zmniejsz_zycie(int odejmij_zycie);
    int pobierz_liczbe_zyc();

private:
    int zycia;
};

#endif // UFO_H
