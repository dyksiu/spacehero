#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class AnimowaneObiekty : public sf::Sprite
{
public:
    AnimowaneObiekty() : Sprite() {};
    virtual ~AnimowaneObiekty()=default;

    //Sekcja metod
    virtual void poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)=0;


    //Metoda do ustawiania predkosci
    void ustaw_predkosc(int predkosc_x, int predkosc_y)
    {
        predkosc_x_ = predkosc_x;
        predkosc_y_ = predkosc_y;
    }
protected:
    float predkosc_x_;
    float predkosc_y_;
};
