#pragma once
//Sekcja bibliotek ogolnych
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <memory>
#include <utility>
#include <fstream>

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
#include "shot.h"
#include "boss.h"
#include "boost.h"

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
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;
      std::string z_pliku2;
      std::ifstream Czytaj_Plik("./../spacehero/parameters/dodaj_przeciwnikow_1.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku >> z_pliku2;
      Czytaj_Plik.close();

    for(int i=0; i<stoi(z_pliku); i++)
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

    for(int i=0; i<stoi(z_pliku2); i++)
    {
        auto asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, asteroid.get()))
        {
            asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(asteroid));
    }
}

//Funkcja dodająca pociski
void dodaj_pociski(std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski, const sf::Texture &textureShot, Spaceship &statek)
{
   for(int i=0; i<1; i++)
   {
       pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
   }
}

//Funkcja dodajaca pierwsze boosty
void dodaj_boosty_1(std::vector<std::unique_ptr<boost>> &boosty, const sf::Texture &textureBoost, int rozmiar_x, int rozmiar_y)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/dodaj_boosty_1.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku;
      Czytaj_Plik.close();

    for(int i = 0; i<stoi(z_pliku); i++)
    {
        boosty.emplace_back(std::make_unique<boost>(textureBoost, rozmiar_x, rozmiar_y));
    }
}

//Funkcja dodajaca drugie boosty
void dodaj_boosty_2(std::vector<std::unique_ptr<boost>> &boosty, const sf::Texture &textureBoost2, int rozmiar_x, int rozmiar_y)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/dodaj_boosty_2.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku;
      Czytaj_Plik.close();

    for(int i = 0; i < stoi(z_pliku); i++)
    {
        boosty.emplace_back(std::make_unique<boost>(textureBoost2, rozmiar_x, rozmiar_y));
    }
}

//Funkcja dodajaca przeciwnikow na drugim poziomie
void dodaj_przeciwnikow_2(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, const sf::Texture &textureUfo, const sf::Texture &textureAsteroid, int rozmiar_x, int rozmiar_y)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;
      std::string z_pliku2;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/dodaj_boosty_1.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku >> z_pliku2;
      Czytaj_Plik.close();

    for (int i=0; i<stoi(z_pliku); i++)
    {
        auto ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, ufo.get()))
        {
            ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(ufo));
    }

    for(int i=0; i<stoi(z_pliku2); i++)
    {
        auto asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, asteroid.get()))
        {
            asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(asteroid));
    }

}

//Funkcja odpowiedzialna za zderzenia z pociskiem
void zderzenia(Spaceship &statek, std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski, std::vector<std::unique_ptr<AnimowaneObiekty>> &obiekty, sf::Texture &textureShot, sf::Music &dzwiek)
{

    for(auto itr1 = pociski.begin(); itr1 != pociski.end(); itr1++)
    {
        //shot *pociski = dynamic_cast<shot *>(itr1->get());
        for(auto itr2 = obiekty.begin(); itr2 != obiekty.end(); itr2++)
        {
            Ufo *ufo = dynamic_cast<Ufo *>(itr2->get());
          if(ufo != nullptr)
          {
              if((*itr1)->getGlobalBounds().intersects((*itr2)->getGlobalBounds()))
              {
              //statek.dodaj_punkty(10);
              (*itr2)->zmniejsz_zycie(1);
              itr1 = pociski.erase(itr1);
              pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
              if((*itr2)->pobierz_liczbe_zyc() <= 0)
              {
              statek.dodaj_punkty(10);

              itr2 = obiekty.erase(itr2);
              itr1 = pociski.erase(itr1);
              dzwiek.play();
              pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
              std::cout << "Zniszczono ufo, +10 PKT!" <<std::endl;
              }
              else
              {
                  dzwiek.stop();
              }
              break;
              }

        }
          Asteroid *asteroid = dynamic_cast<Asteroid *>(itr2->get());
            if(asteroid != nullptr)
          {
              if((*itr1)->getGlobalBounds().intersects((*itr2)->getGlobalBounds()))
              {
                  //statek.dodaj_punkty(20);
                  (*itr2)->zmniejsz_zycie(1);
                  itr1 = pociski.erase(itr1);
                  pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
                  if((*itr2)->pobierz_liczbe_zyc() <= 0)
                  {
                      statek.dodaj_punkty(20);
                      itr2 = obiekty.erase(itr2);
                      itr1 = pociski.erase(itr1);
                      dzwiek.play();

                      pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
                      std::cout << "Zniszczono asteroide, +20 PKT!" <<std::endl;
                  }
                  else
                  {
                      dzwiek.stop();
                  }

                  break;
              }

        }
        }
    }
}

//Funkcja odpowiedzialna za strzelanie do bossa
void strzelanie_do_bosa(Spaceship &statek, boss &boss, std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski, sf::Texture &textureShot)
{
    for(auto itr1 = pociski.begin(); itr1 != pociski.end(); itr1++)
    {
        if((*itr1)->getGlobalBounds().intersects(boss.getGlobalBounds()))
        {
            boss.zmniejsz_zycie(1);
            itr1 = pociski.erase(itr1);
            pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
        }
    }
}

//Funkcja odpowiedzialna za zderzenie obiektow ze statkiem
void zderzenia_z_obiektami(Spaceship &statek, std::vector<std::unique_ptr<AnimowaneObiekty>> &obiekty, int rozmiar_x, int rozmiar_y, const sf::RectangleShape &hide_collision)
{
    for(auto itr = obiekty.begin(); itr != obiekty.end();)
    {
        if((hide_collision.getGlobalBounds().intersects((*itr)->getGlobalBounds())) || (statek.getGlobalBounds().intersects((*itr)->getGlobalBounds())))
        {
            Ufo *ufo = dynamic_cast<Ufo *>(itr->get());
            if(ufo != nullptr){
             statek.zmniejsz_zycie(1);
             itr = obiekty.erase(itr);
             statek.pozycja_startowa(rozmiar_x, rozmiar_y);
             std::cout << "STRATA 1 ZYCIA!" << std::endl;
            }
            else
            {
                statek.zmniejsz_zycie(2);
                itr = obiekty.erase(itr);
                statek.pozycja_startowa(rozmiar_x, rozmiar_y);
                std::cout << "STRATA 2 ZYC!" << std::endl;
            }
        }

        else
        {
            itr++;
        }
    }
}

//Funkcja odpowiedzialna za kolizje statku z bossem
void zderzenia_z_bossem(boss &boss, Spaceship &statek,int rozmiar_x, int rozmiar_y)
{
    if(boss.getGlobalBounds().intersects(statek.getGlobalBounds()))
    {
        statek.zmniejsz_zycie(1);
        statek.pozycja_startowa(rozmiar_x, rozmiar_y);
        boss.dodaj_zycie(1);
        boss.setPosition(rozmiar_x/2, rozmiar_y/2);
        std::cout << "STRATA 1 ZYCIA! BOSS ZYSKAL DODATKOWE ZYCIE!" << std::endl;
    }

}

//Funkcja odpowiedzialna za wywolanie fali przeciwnikow gdy boss straci 5 zyc
void fala_1(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, const sf::Texture &textureUfo, int rozmiar_x, int rozmiar_y)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/fala_1.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku;
      Czytaj_Plik.close();

    for(int i=0; i<stoi(z_pliku); i++)
    {
        auto ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, ufo.get()))
        {
            ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(ufo));
    }
}

//Funkcja odpowiedzialna za wywolanie fali przeciwnikow gdy boss straci 10 zyc
void fala_2(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, const sf::Texture &textureAsteroida, int rozmiar_x, int rozmiar_y)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/fala_2.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku;
      Czytaj_Plik.close();

    for(int i=0; i<stoi(z_pliku); i++)
    {
        auto asteroid = std::make_unique<Asteroid>(textureAsteroida, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, asteroid.get()))
        {
            asteroid = std::make_unique<Asteroid>(textureAsteroida, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(asteroid));
    }
}
