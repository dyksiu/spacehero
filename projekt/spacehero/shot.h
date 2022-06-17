#pragma once

#include "AnimowaneObiekty.h"
#include "spaceship.h"
#include "boss.h"

class shot : public AnimowaneObiekty
{
public:
    shot(const sf::Texture &texture, Spaceship &statek);
    shot(const sf::Texture &texture, boss &boss);

    //Sekcja metod
    void poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);
    void strzal(const sf::Event &event, Spaceship &statek, sf::Music &strzal);
    void strzal_2(const sf::Event &event, Spaceship &statek, sf::Music &strzal2);

    void usun_pocisk(std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski);

    void zmniejsz_zycie(int odejmij_zycie);
    int pobierz_liczbe_zyc();


private:
    int skala;

};


