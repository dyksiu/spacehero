#pragma once

#include "AnimowaneObiekty.h"

class boss : public AnimowaneObiekty
{
public:
    boss(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    std::pair<int, int> losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu);

    //Sekcja metod
    void poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);
    void ustaw_granice(const sf::IntRect &bounds);

    void ruch(const sf::Time &elapsed);
    void odbicia();


    //Metody obslugujace zycia
    void zmniejsz_zycie(int odejmij_zycie);
    void dodaj_zycie(int dodaj_zycie);
    int pobierz_liczbe_zyc();

private:
    int zycia;
    sf::IntRect bounds_;
    sf::RectangleShape boss_shape_;
};


