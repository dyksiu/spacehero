#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class StatyczneObiekty : public sf::Sprite
{
public:
    StatyczneObiekty() : Sprite() {};
    virtual ~StatyczneObiekty()=default;
};
