#pragma once

//Sekcja bibliotek ogolnych
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <memory>
#include <utility>

//Sekcja bibliotek SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//Sekcja klas i funkcji
#include "AnimowaneObiekty.h"
#include "StatyczneObiekty.h"
#include "spaceship.h"
#include "ufo.h"
#include "przycisk.h"
#include "asteroid.h"


////////////////////////////////////////////
//Funkcja odpowiedzialna za wczytywanie tekstur
sf::Texture loadTexture(const std::string &nazwa_pliku)
{
    sf::Texture texture;
    if(!texture.loadFromFile(nazwa_pliku)){
        std::cerr << "Nie udalo sie wczytac pliku!" << std::endl;
    }
    return texture;
}

//Funkcja odpowiedzialna za kolizje przeciwnikow
bool kolizja_przeciwnikow(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, AnimowaneObiekty *przeciwnik)
{
    for(auto &p : przeciwnicy)
    {
      if(przeciwnik->getGlobalBounds().intersects(p->getGlobalBounds()))
      {
          return true;
      }
    }
    return false;
}

//Funkcja odpowiedzialna za dodawanie przeciwnikow
void dodaj_przeciwnikow_1(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, const sf::Texture &textureUfo, const sf::Texture &textureAsteroid, int rozmiar_x, int rozmiar_y)
{
    //Dodanie Ufo
    //Na 1 poziomie 15 ufo
    for(int i=0; i<15; i++)
    {
        auto ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, ufo.get()))
        {
            ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(ufo));
    }
    //Dodanie Asteroid
    //Na 1 poziomie 5 asteroid

    for(int i=0; i<5; i++)
    {
        auto asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, asteroid.get()))
        {
            asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(asteroid));
    }
}

//Funkcja od strzalu
void strzelanie(std::vector<std::unique_ptr<AnimowaneObiekty>> &statek_pocisk, const sf::Texture &textureStatek, const sf::Texture &textureShot,int rozmiar_x, int rozmiar_y)
{

}


