#include "shot.h"

shot::shot(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(1.0,1.0);
  //setPosition((rozmiar_x/2 - getGlobalBounds().width/2)+30,(rozmiar_y - getGlobalBounds().height)+15);


  predkosc_x_ = 0;
  predkosc_y_ = 0;
}

void shot::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
    move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
}

void shot::strzal(const sf::Event &event)
{
    float predkosc_pocisku = 200;

    if(event.key.code == sf::Keyboard::Space)
    {
        predkosc_y_ = -predkosc_pocisku;
    }
}
