#include "shot.h"

shot::shot(const sf::Texture &texture, Spaceship &statek)
{
  setTexture(texture);
  setScale(0.2,0.2);
  //setPosition((rozmiar_x/2 - getGlobalBounds().width/2)+30,(rozmiar_y - getGlobalBounds().height)+15);
  //setPosition(statek.getPosition().x, statek.getPosition().y);
  //setPosition(statek.getPosition().x-30, statek.getPosition().y-30);


  predkosc_x_ = 0;
  predkosc_y_ = 0;
}

void shot::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
    move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
}

void shot::strzal(const sf::Event &event, Spaceship &statek)
{
    float predkosc_pocisku = 500;

    if(event.key.code == sf::Keyboard::Space)
    {
        predkosc_y_ = -predkosc_pocisku;
        setPosition(statek.getPosition().x, statek.getPosition().y);
        //this->setOrigin(statek.getGlobalBounds().width/2, statek.getGlobalBounds().height/2);
    }
}

//Obsluga punktow
int shot::pobierz_liczbe_punktow() const
{
    return punkty;
}

void shot::dodaj_punkty(int punkty_do_dodania)
{
    punkty += punkty_do_dodania;
}
