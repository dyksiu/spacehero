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

    //Metody obslugujace punkty
    int pobierz_liczbe_punktow() const;
    void dodaj_punkty(int punkty_do_dodania);

private:
    int punkty;

};


