#pragma once
//Sekcja bibliotek ogolnych
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <memory>
#include <utility>
#include <sstream>

//Sekcja bibliotek SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//Sekcja klas i funkcji
#include "AnimowaneObiekty.h"
#include "spaceship.h"
#include "ufo.h"
#include "asteroid.h"
#include "przycisk.h"
#include "shot.h"
#include "boss.h"
#include "boost.h"
#include "funkcje.h"

using namespace std;

//CO JESZCZE DODAĆ:
//boss ciagle lata


void wygrana()
{
  sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlotytul.png");
  sf::Texture texturePoli = loadTexture("./../spacehero/graphics/krolestwo.png");

  //Rozmiar okna
  int rozmiar_x = 1080;
  int rozmiar_y = 720;

  //Utworzenie okna gry
  sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

  //Granice okna gry
  sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

  sf::Sprite spritetlo;
  spritetlo.setTexture(textureTlo);
  spritetlo.setScale(1.0,1.0);
  spritetlo.setTextureRect(windowBounds);

  //Ustawienie tekstury tla na cale okno
  textureTlo.setRepeated(true);
  sf::Clock clock;

  //Muzyka
  sf::Music wygrana;
  if(!wygrana.openFromFile("./../spacehero/music/wygrana.wav"))
  {
      std::cerr <<"Nie udalo sie wczytac muzyki!" << std::endl;
  }
  wygrana.play();
  wygrana.setLoop(true);
  wygrana.setVolume(100.f);


  //Obiekt politechnika
  sf::CircleShape politechnika;
  sf::Sprite poli;
  poli.setTexture(texturePoli);
  poli.setScale(0.4, 0.4);
  poli.setPosition(rozmiar_x/2, rozmiar_y/2);
  float predkosc_x = 250;
  float predkosc_y = 250;
  float obrot = 50;


  //Fonty
  sf::Font font;
  if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
  {
      std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
  }

  sf::Text text;

  //Stworzenie fontu
  text.setFont(font);
  text.setString("Zwyciestwo!");
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);

  text.setPosition(rozmiar_x/2 - 150, rozmiar_y/2/2);

  while (window.isOpen()) {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      sf::Time elapsed = clock.restart();

      sf::FloatRect poli_bounds = poli.getGlobalBounds();
      poli.move(predkosc_x * elapsed.asSeconds(), predkosc_y * elapsed.asSeconds());
      poli.rotate(obrot*elapsed.asSeconds());

      if(poli_bounds.left + poli_bounds.width - 50>= window.getSize().x)
      {
          predkosc_x = -std::abs(predkosc_x);
      }
      if(poli_bounds.top + 50 < 0)
      {
          predkosc_y = std::abs(predkosc_y);
      }
      else if(poli_bounds.top + poli_bounds.height - 50 >= window.getSize().y)
      {
          predkosc_y = -std::abs(predkosc_y);
      }
      else if(poli_bounds.left + 50 <= 0)
      {
          predkosc_x = std::abs(predkosc_x);
      }


      while (window.pollEvent(event)) {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed)
              window.close();


        }



      // clear the window with black color
      window.clear(sf::Color::Black);

      // draw everything here...
      window.draw(spritetlo);
      window.draw(text);
      window.draw(poli);

      // end the current frame
      window.display();
  }

}

void poziom_2()
{
    srand(time(NULL));
    //Tekstury
    sf::Texture textureStatek = loadTexture("./../spacehero/graphics/spaceship.png");
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureUfo = loadTexture("./../spacehero/graphics/denufo.png");
    sf::Texture textureAsteroida = loadTexture("./../spacehero/graphics/asteroid.png");
    sf::Texture textureShot = loadTexture("./../spacehero/graphics/shot.png");
    sf::Texture textureBoss = loadTexture("./../spacehero/graphics/krolestwo.png");
    sf::Texture textureBoost = loadTexture("./../spacehero/graphics/boost.png");
    sf::Texture textureBoost2 = loadTexture("./../spacehero/graphics/boost2.png");

    sf::Music dzwiek;
    if(!dzwiek.openFromFile("./../spacehero/music/shot.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;


    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);



    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);


    //Utworzenie obiektu klasy spaceship
    Spaceship statek(textureStatek, rozmiar_x, rozmiar_y);
    boss boss(textureBoss, rozmiar_x, rozmiar_y);


    //Pole ktorego nie moga przekroczyc przeciwnicy
    sf::RectangleShape hide_collision(sf::Vector2f(10000, 100));
    hide_collision.setPosition(window.getSize().x/30, statek.getPosition().y + 125);
    hide_collision.setFillColor(sf::Color(100,50, 250));

    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Kontener pociskow
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_2(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

    dodaj_pociski(pociski, textureShot, statek);

    //Kontenery z boostami
    std::vector<std::unique_ptr<boost>> boosty1;
    std::vector<std::unique_ptr<boost>> boosty2;

    //Muzyka
    sf::Music muzyka;
    if(!muzyka.openFromFile("./../spacehero/music/intro.wav"))
    {
        std::cerr <<"Nie udalo sie wczytac muzyki!" << std::endl;
    }

    muzyka.setVolume(10.f);
    muzyka.play();

    sf::Music zderzenie;
    if(!zderzenie.openFromFile("./../spacehero/music/zderzenie.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music dzwiek_boost;
    if(!dzwiek_boost.openFromFile("./../spacehero/music/boost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music dzwiek_boost2;
    if(!dzwiek_boost2.openFromFile("./../spacehero/music/boost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music unboost;
    if(!unboost.openFromFile("./../spacehero/music/unboost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music unboost2;
    if(!unboost2.openFromFile("./../spacehero/music/unboost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }


    //Fonty od punktow
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text wyniki;
    wyniki.setFont(font);
    wyniki.setCharacterSize(24);
    wyniki.setFillColor(sf::Color::Red);
    wyniki.setStyle(sf::Text::Bold);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setString("Twoje punkty: ");
    punkty.setCharacterSize(24);
    punkty.setFillColor(sf::Color::Red);
    punkty.setStyle(sf::Text::Bold);

    wyniki.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2);
    punkty.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2);


    //Fonty od zycia
    sf::Text zycie_wskaznik;
    zycie_wskaznik.setFont(font);
    zycie_wskaznik.setCharacterSize(24);
    zycie_wskaznik.setFillColor(sf::Color::Red);
    zycie_wskaznik.setStyle(sf::Text::Bold);

    sf::Text zycie;
    zycie.setFont(font);
    zycie.setCharacterSize(24);
    zycie.setFillColor(sf::Color::Red);
    zycie.setStyle(sf::Text::Bold);
    zycie.setString("Twoje zycia: ");

    zycie_wskaznik.setPosition(rozmiar_x/2 + 500 , rozmiar_y/2 - rozmiar_y/2);
    zycie.setPosition(rozmiar_x/2 + 320, rozmiar_y/2 - rozmiar_y/2);


    //Tekst dla pauzy
    sf::Text pauza_;
    pauza_.setFont(font);
    pauza_.setCharacterSize(30);
    pauza_.setFillColor(sf::Color::White);
    pauza_.setStyle(sf::Text::Bold);
    pauza_.setString("PAUZA! Nacisnij P");

    pauza_.setPosition((rozmiar_x/2 - rozmiar_x/2) + 400, rozmiar_y/2);

//////////////////////////////////////////////////////////////////////////////////////
      // run the program as long as the window is open
    sf::Clock clock;
    sf::Clock shot_clock;

    bool pauza = false;
    bool fala1 = false;
    bool fala2 = false;
    bool boosty_1 = false;
    bool boost_rozmiar = false;
    bool boost_potwory = false;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;
          sf::Time elapsed = clock.restart();


          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();
              //Sterowanie statkiem za pomoca klawiszy

              if(event.type == sf::Event::KeyPressed)
              {

                  for(auto itr=pociski.begin(); itr != pociski.end(); itr++)
                  {
                      shot *pocisk = dynamic_cast<shot *>(itr->get());
                              if(pocisk != nullptr){
                                  pocisk->strzal(event, statek, dzwiek);

                              }
                  }

              }

              //PAUZA PO WCISNIECIU KLAWISZA P
              if(event.type == sf::Event::KeyReleased)
              {
                  if(event.key.code == sf::Keyboard::P)
                  {
                      pauza =! pauza;
                  }
              }

          }
          if(!pauza)
          {
              //SEKCJA OD PORUSZANIA
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
               statek.ruch_po_x(elapsed, window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
              statek.ruch_po_x(elapsed, window, 1);
              }



              for(auto &poc : pociski)
              {
              poc->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }


              for(auto &el : przeciwnicy)
              {
                 el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

              zderzenia(statek, pociski, przeciwnicy, textureShot, zderzenie);

              zderzenia_z_obiektami(statek, przeciwnicy, rozmiar_x, rozmiar_y, hide_collision);

             //Poruszanie boostow
              for(auto &b : boosty1)
              {
                  b ->poruszaj(elapsed);
              }


              for(auto &b : boosty2)
              {
                  b ->poruszaj(elapsed);
              }


            //Wyswietlenie punktow
            wyniki.setString(std::to_string(statek.pobierz_liczbe_punktow()));

            //Wyswietlenie zycia
            zycie_wskaznik.setString(std::to_string(statek.pobierz_liczbe_zyc()));
            if(!statek.czy_zyje())
            {
                window.close();
                std::cout << "PRZEGRANA!" << std::endl;
            }
          }
          else
          {
              clock.restart();
          }

          // clear the window with black color
          window.clear(sf::Color::Black);

          //RYSOWANIE

          window.draw(spritetlo);
          window.draw(statek);
          window.draw(wyniki);
          window.draw(punkty);
          window.draw(zycie_wskaznik);
          window.draw(zycie);

          for(auto itr = przeciwnicy.begin(); itr != przeciwnicy.end(); itr++)
          {
              Ufo *ufo = dynamic_cast<Ufo *>(itr->get());
              if(ufo != nullptr)
              {
              sf::RectangleShape hp(sf::Vector2f(ufo->pobierz_liczbe_zyc()*10,10));
              hp.setPosition(ufo->getPosition().x + 10, ufo->getPosition().y - 10);
              hp.setFillColor(sf::Color(255,0,0));
              window.draw(hp);
              }
              Asteroid *asteroid = dynamic_cast<Asteroid *>(itr->get());
              if(asteroid != nullptr)
              {
                  sf::RectangleShape hp(sf::Vector2f(asteroid->pobierz_liczbe_zyc()*10,10));
                  hp.setPosition(asteroid->getPosition().x + 30, asteroid->getPosition().y);
                  hp.setFillColor(sf::Color(255,153,25));
                  window.draw(hp);
              }

          }

          //Sekcja od bossa
          if(przeciwnicy.empty())
          {
            boss.ruch(elapsed);
            strzelanie_do_bosa(statek,boss,pociski,textureShot);
            zderzenia_z_bossem(boss, statek,rozmiar_x, rozmiar_y);

            //Sekcja od HP bossa
            sf::RectangleShape hp(sf::Vector2f(boss.pobierz_liczbe_zyc()*25,10));            
            hp.setPosition(rozmiar_x/2 - 250, rozmiar_y/2 - rozmiar_y/2 + 10);
            hp.setFillColor(sf::Color(255,0,0));
            window.draw(hp);

            //Fale
            if((boss.pobierz_liczbe_zyc() <= 15) && (fala1 == false))
            {
                fala_1(przeciwnicy, textureUfo, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);                
                fala1 = true;
            }
            if((boss.pobierz_liczbe_zyc() <= 10) && (fala2 == false))
            {
                fala_2(przeciwnicy, textureAsteroida, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala2 = true;
            }

            //Warunek na wygraną
            if(boss.pobierz_liczbe_zyc() == 0)
            {
              muzyka.stop();
              wygrana();
              window.close();
            }
           }

          //Sekcja boostow
          if((statek.pobierz_liczbe_punktow() == 50) && (boosty_1 == false))
          {
              dodaj_boosty_1(boosty1, textureBoost, rozmiar_x, rozmiar_y);
              boosty_1 = true;
          }
          //Boosty pierwsze
          for(auto itr = boosty1.begin(); itr != boosty1.end();)
          {
              if((*itr)->getGlobalBounds().intersects(statek.getGlobalBounds()) && boost_rozmiar == false && boost_potwory == false)
              {
                  int losowanie = rand()%2;
                  itr = boosty1.erase(itr);
                  dzwiek_boost.play();
                  if(losowanie == 0)
                  {
                  statek.setScale(0.2,0.2);
                  boost_rozmiar = true;
                  std::cout << "TWOJ STATEK SIE ZMNIEJSZYL!" << std::endl;
                  }
                  if(losowanie == 1)
                  {
                      for(auto it = przeciwnicy.begin(); it != przeciwnicy.end(); it++)
                      {
                          (*it)->ustaw_predkosc(0,0);
                      }
                      boost_potwory = true;
                      std::cout << "PRZECIWNICY ZAMARLI BEZ RUCHU!" << std::endl;
                  }

              }
              else
              {
                 itr++;
             }
          }
          //Warunek kiedy sie konczy pierwszy boost
         if(statek.pobierz_liczbe_punktow() == 150 && (boost_rozmiar == true))
          {
                statek.setScale(0.3,0.3);
                unboost.play();
          }
         if(statek.pobierz_liczbe_punktow() == 100 && (boost_potwory == true))
          {
             for(auto it = przeciwnicy.begin(); it != przeciwnicy.end(); it++)
             {
                 (*it)->ustaw_predkosc(0,10);
                 unboost.play();
             }
          }


          //Usuwanie boostow po wyjsciu za okno
          for(auto itr = boosty1.begin(); itr!= boosty1.end();)
          {
              if((*itr)->getGlobalBounds().intersects(hide_collision.getGlobalBounds()))
              {
              itr = boosty1.erase(itr);
              }
              else
              {
                  itr++;
              }
          }

          if(przeciwnicy.empty())
          {
           window.draw(boss);
          }

          for(auto &p : przeciwnicy)
          {
              window.draw(*p);
          }

          for(auto &p : pociski)
          {
              window.draw(*p);
          }

          for(auto &b : boosty1)
          {
              window.draw(*b);
          }

          for(auto &b2 : boosty2)
          {
              window.draw(*b2);
          }


          if(pauza)
          {
              window.draw(pauza_);
          }

          // end the current frame
          window.display();
      }
}

void poziom_2_2()
{
    srand(time(NULL));
    //Tekstury
    sf::Texture textureStatek = loadTexture("./../spacehero/graphics/spaceship.png");
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureUfo = loadTexture("./../spacehero/graphics/denufo.png");
    sf::Texture textureAsteroida = loadTexture("./../spacehero/graphics/asteroid.png");
    sf::Texture textureShot = loadTexture("./../spacehero/graphics/shot.png");
    sf::Texture textureBoss = loadTexture("./../spacehero/graphics/krolestwo.png");
    sf::Texture textureShot2 = loadTexture("./../spacehero/graphics/shot2.png");
    sf::Texture textureStatek2 = loadTexture("./../spacehero/graphics/spaceship2.png");

    sf::Music dzwiek;
    if(!dzwiek.openFromFile("./../spacehero/music/shot.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;


    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);



    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);


    //Utworzenie obiektu klasy spaceship
    Spaceship statek(textureStatek, rozmiar_x, rozmiar_y);
    Spaceship statek2(textureStatek2, rozmiar_x, rozmiar_y);
    boss boss(textureBoss, rozmiar_x, rozmiar_y);


    //Pole ktorego nie moga przekroczyc przeciwnicy
    sf::RectangleShape hide_collision(sf::Vector2f(10000, 100));
    hide_collision.setPosition(window.getSize().x/30, statek.getPosition().y + 125);
    hide_collision.setFillColor(sf::Color(100,50, 250));

    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Kontener pociskow
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski;

    //Kontener pociskow gracza 2
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski_2;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_2(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

    dodaj_pociski(pociski, textureShot, statek);
    dodaj_pociski(pociski_2, textureShot2, statek2);

    //Muzyka
    sf::Music muzyka;
    if(!muzyka.openFromFile("./../spacehero/music/intro.wav"))
    {
        std::cerr <<"Nie udalo sie wczytac muzyki!" << std::endl;
    }

    muzyka.setVolume(10.f);
    muzyka.play();

    sf::Music zderzenie;
    if(!zderzenie.openFromFile("./../spacehero/music/zderzenie.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music dzwiek2;
    if(!dzwiek2.openFromFile("./../spacehero/music/shot2.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    //Fonty od punktow
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text wyniki;
    wyniki.setFont(font);
    wyniki.setCharacterSize(24);
    wyniki.setFillColor(sf::Color::Red);
    wyniki.setStyle(sf::Text::Bold);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setString("Twoje punkty: ");
    punkty.setCharacterSize(24);
    punkty.setFillColor(sf::Color::Red);
    punkty.setStyle(sf::Text::Bold);

    wyniki.setPosition(rozmiar_x/2  + 491, rozmiar_y/2 - rozmiar_y/2);
    punkty.setPosition(rozmiar_x/2 + 290 , rozmiar_y/2 - rozmiar_y/2);


    //Fonty od zycia
    sf::Text zycie_wskaznik;
    zycie_wskaznik.setFont(font);
    zycie_wskaznik.setCharacterSize(24);
    zycie_wskaznik.setFillColor(sf::Color::Red);
    zycie_wskaznik.setStyle(sf::Text::Bold);

    sf::Text zycie;
    zycie.setFont(font);
    zycie.setCharacterSize(24);
    zycie.setFillColor(sf::Color::Red);
    zycie.setStyle(sf::Text::Bold);
    zycie.setString("Twoje zycia: ");

    zycie_wskaznik.setPosition(rozmiar_x/2 + 480 , rozmiar_y/2 - rozmiar_y/2 + 30);
    zycie.setPosition(rozmiar_x/2 + 290, rozmiar_y/2 - rozmiar_y/2 + 30);

    //Gracz po lewej
        sf::Text wyniki2;
        wyniki2.setFont(font);
        wyniki2.setCharacterSize(24);
        wyniki2.setFillColor(sf::Color::Red);
        wyniki2.setStyle(sf::Text::Bold);

        sf::Text punkty2;
        punkty2.setFont(font);
        punkty2.setString("Twoje punkty: ");
        punkty2.setCharacterSize(24);
        punkty2.setFillColor(sf::Color::Red);
        punkty2.setStyle(sf::Text::Bold);

        wyniki2.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2);
        punkty2.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2);

        //Fonty od zycia
        sf::Text zycie_wskaznik2;
        zycie_wskaznik2.setFont(font);
        zycie_wskaznik2.setCharacterSize(24);
        zycie_wskaznik2.setFillColor(sf::Color::Red);
        zycie_wskaznik2.setStyle(sf::Text::Bold);

        sf::Text zycie2;
        zycie2.setFont(font);
        zycie2.setCharacterSize(24);
        zycie2.setFillColor(sf::Color::Red);
        zycie2.setStyle(sf::Text::Bold);
        zycie2.setString("Twoje zycia: ");

        zycie_wskaznik2.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2 + 30);
        zycie2.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2 + 30);



    //Tekst dla pauzy
    sf::Text pauza_;
    pauza_.setFont(font);
    pauza_.setCharacterSize(30);
    pauza_.setFillColor(sf::Color::White);
    pauza_.setStyle(sf::Text::Bold);
    pauza_.setString("PAUZA! Nacisnij P");

    pauza_.setPosition((rozmiar_x/2 - rozmiar_x/2) + 400, rozmiar_y/2);

//////////////////////////////////////////////////////////////////////////////////////
      // run the program as long as the window is open
    sf::Clock clock;
    sf::Clock shot_clock;

    bool pauza = false;
    bool fala1 = false;
    bool fala2 = false;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;
          sf::Time elapsed = clock.restart();


          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();
              //Sterowanie statkiem za pomoca klawiszy

              if(event.type == sf::Event::KeyPressed)
              {

                  for(auto itr=pociski.begin(); itr != pociski.end(); itr++)
                  {
                      shot *pocisk = dynamic_cast<shot *>(itr->get());
                              if(pocisk != nullptr){
                                  pocisk->strzal(event, statek, dzwiek);

                              }
                  }
                  for(auto itr=pociski_2.begin(); itr != pociski_2.end(); itr++)
                  {
                      shot *pocisk_2 = dynamic_cast<shot *>(itr->get());
                      if(pocisk_2 != nullptr){
                          pocisk_2->strzal_2(event, statek2, dzwiek2);
                      }
                  }

              }

              //PAUZA PO WCISNIECIU KLAWISZA P
              if(event.type == sf::Event::KeyReleased)
              {
                  if(event.key.code == sf::Keyboard::P)
                  {
                      pauza =! pauza;
                  }
              }

          }
          if(!pauza)
          {
              //SEKCJA OD PORUSZANIA
              //STATEK 1
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
               statek.ruch_po_x(elapsed, window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
              statek.ruch_po_x(elapsed, window, 1);
              }
              //STATEK 2
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
              {
                  statek2.ruch_po_x(elapsed,window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
              {
                  statek2.ruch_po_x(elapsed,window,1);
              }


              for(auto &poc : pociski)
              {
              poc->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }

              for(auto &poc2 : pociski_2)
              {
                  poc2->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }


              for(auto &el : przeciwnicy)
              {
                 el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

             zderzenia(statek, pociski, przeciwnicy, textureShot, zderzenie);
             zderzenia(statek2, pociski_2, przeciwnicy, textureShot2, zderzenie);

              zderzenia_z_obiektami(statek, przeciwnicy, rozmiar_x, rozmiar_y, hide_collision);
              zderzenia_z_obiektami(statek2, przeciwnicy, rozmiar_x, rozmiar_y, hide_collision);

            //Wyswietlenie punktow
            wyniki.setString(std::to_string(statek.pobierz_liczbe_punktow()));
            wyniki2.setString(std::to_string(statek2.pobierz_liczbe_punktow()));

            //Wyswietlenie zycia
            zycie_wskaznik.setString(std::to_string(statek.pobierz_liczbe_zyc()));
            zycie_wskaznik2.setString(std::to_string(statek2.pobierz_liczbe_zyc()));
            if(!statek.czy_zyje() || !statek2.czy_zyje())
            {
                window.close();
                std::cout << "PRZEGRANA!" << std::endl;
            }
          }
          else
          {
              clock.restart();
          }

          // clear the window with black color
          window.clear(sf::Color::Black);

          //RYSOWANIE

          window.draw(spritetlo);
          window.draw(statek);
          window.draw(statek2);
          window.draw(wyniki);
          window.draw(punkty);
          window.draw(wyniki2);
          window.draw(punkty2);
          window.draw(zycie_wskaznik);
          window.draw(zycie);
          window.draw(zycie_wskaznik2);
          window.draw(zycie2);

          for(auto itr = przeciwnicy.begin(); itr != przeciwnicy.end(); itr++)
          {
              Ufo *ufo = dynamic_cast<Ufo *>(itr->get());
              if(ufo != nullptr)
              {
              sf::RectangleShape hp(sf::Vector2f(ufo->pobierz_liczbe_zyc()*10,10));
              hp.setPosition(ufo->getPosition().x + 10, ufo->getPosition().y - 10);
              hp.setFillColor(sf::Color(255,0,0));
              window.draw(hp);
              }
              Asteroid *asteroid = dynamic_cast<Asteroid *>(itr->get());
              if(asteroid != nullptr)
              {
                  sf::RectangleShape hp(sf::Vector2f(asteroid->pobierz_liczbe_zyc()*10,10));
                  hp.setPosition(asteroid->getPosition().x + 30, asteroid->getPosition().y);
                  hp.setFillColor(sf::Color(255,153,25));
                  window.draw(hp);
              }

          }

          //Sekcja od bossa
          if(przeciwnicy.empty())
          {
            boss.ruch(elapsed);
            strzelanie_do_bosa(statek,boss,pociski,textureShot);
            strzelanie_do_bosa(statek2, boss, pociski_2, textureShot2);

            window.draw(boss);

            zderzenia_z_bossem(boss, statek,rozmiar_x, rozmiar_y);
            zderzenia_z_bossem(boss, statek2, rozmiar_x, rozmiar_y);

            //Sekcja od HP bossa
            sf::RectangleShape hp(sf::Vector2f(boss.pobierz_liczbe_zyc()*25,10));
            hp.setPosition(rozmiar_x/2 - 250, rozmiar_y/2 - rozmiar_y/2 + 10);
            hp.setFillColor(sf::Color(255,0,0));
            window.draw(hp);

            //Fale
            if((boss.pobierz_liczbe_zyc() <= 15) && (fala1 == false))
            {
                fala_1(przeciwnicy, textureUfo, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala1 = true;
            }
            if((boss.pobierz_liczbe_zyc() <= 10) && (fala2 == false))
            {
                fala_2(przeciwnicy, textureAsteroida, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala2 = true;
            }

            //Warunek na wygraną
            if(boss.pobierz_liczbe_zyc() == 0)
            {
              muzyka.stop();
              wygrana();
              window.close();
            }
           }

          for(auto &p : przeciwnicy)
          {
              window.draw(*p);
          }

          for(auto &p : pociski)
          {
              window.draw(*p);
          }

          for(auto &p2 : pociski_2)
          {
              window.draw(*p2);
          }


          if(pauza)
          {
              window.draw(pauza_);
          }


          // end the current frame
          window.display();
      }
}

void ekran_wygranej_1()
{
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureDalej = loadTexture("./../spacehero/graphics/kolejny.png");

    //Rozmiar okna
    int rozmiar_x =  500;
    int rozmiar_y =  500;

    //Okno
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0, 1.0);
    spritetlo.setTextureRect(windowBounds);

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text text;

    //Stworzenie fontu
    text.setFont(font);
    text.setString("WYGRANA!");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);


    text.setPosition(rozmiar_x/2 - 150, rozmiar_y/2 - rozmiar_y/2);

    //Przyciski
    przycisk przyciskKolejny(textureDalej, rozmiar_x, rozmiar_y);
    przyciskKolejny.setPosition(rozmiar_x/2 - 75, rozmiar_y/2 - 100);


    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

             //Wcisniecie przyciskow
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f pozycja_myszki = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(przyciskKolejny.czy_wcisniety(pozycja_myszki))
                    {
                        std::cout << "Wcisnieto KOLEJNY POZIOM" << std::endl;
                        window.close();
                        poziom_2();
                    }
                }
            }

            }




        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);
        window.draw(text);
        window.draw(przyciskKolejny);



        // end the current frame
        window.display();
    }
}

void ekran_wygranej_2()
{
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureDalej = loadTexture("./../spacehero/graphics/kolejny.png");

    //Rozmiar okna
    int rozmiar_x =  500;
    int rozmiar_y =  500;

    //Okno
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0, 1.0);
    spritetlo.setTextureRect(windowBounds);

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text text;

    //Stworzenie fontu
    text.setFont(font);
    text.setString("WYGRANA!");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);


    text.setPosition(rozmiar_x/2 - 150, rozmiar_y/2 - rozmiar_y/2);

    //Przyciski
    przycisk przyciskKolejny(textureDalej, rozmiar_x, rozmiar_y);
    przyciskKolejny.setPosition(rozmiar_x/2 - 75, rozmiar_y/2 - 100);


    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

             //Wcisniecie przyciskow
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f pozycja_myszki = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(przyciskKolejny.czy_wcisniety(pozycja_myszki))
                    {
                        std::cout << "Wcisnieto KOLEJNY POZIOM" << std::endl;
                        window.close();
                        poziom_2_2();
                    }
                }
            }

            }




        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);
        window.draw(text);
        window.draw(przyciskKolejny);



        // end the current frame
        window.display();
    }
}

void gra_1()
{
    srand(time(NULL));
    //Tekstury
    sf::Texture textureStatek = loadTexture("./../spacehero/graphics/spaceship.png");
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureUfo = loadTexture("./../spacehero/graphics/ufo.png");
    sf::Texture textureAsteroida = loadTexture("./../spacehero/graphics/asteroid.png");
    sf::Texture textureShot = loadTexture("./../spacehero/graphics/shot.png");
    sf::Texture textureBoost = loadTexture("./../spacehero/graphics/boost.png");
    sf::Texture textureBoost2 = loadTexture("./../spacehero/graphics/boost2.png");


    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;


    sf::Music dzwiek;
    if(!dzwiek.openFromFile("./../spacehero/music/shot.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }


    sf::Music muzyka;
    if(!muzyka.openFromFile("./../spacehero/music/poziom1.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }
    muzyka.setVolume(10.f);
    muzyka.play();

    sf::Music zderzenie;
    if(!zderzenie.openFromFile("./../spacehero/music/zderzenie.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music dzwiek_boost;
    if(!dzwiek_boost.openFromFile("./../spacehero/music/boost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music dzwiek_boost2;
    if(!dzwiek_boost2.openFromFile("./../spacehero/music/boost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music unboost;
    if(!unboost.openFromFile("./../spacehero/music/unboost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music unboost2;
    if(!unboost2.openFromFile("./../spacehero/music/unboost.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);



    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    //Utworzenie obiektu klasy spaceship
    Spaceship statek(textureStatek, rozmiar_x, rozmiar_y);

    //Pole ktorego nie moga przekroczyc przeciwnicy
    sf::RectangleShape hide_collision(sf::Vector2f(10000, 100));
    hide_collision.setPosition(window.getSize().x/30, statek.getPosition().y + 125);
    hide_collision.setFillColor(sf::Color(100,50, 250));


    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Kontener pociskow
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

    dodaj_pociski(pociski, textureShot, statek);

    //Kontenery z boostami
    std::vector<std::unique_ptr<boost>> boosty1;
    std::vector<std::unique_ptr<boost>> boosty2;



    //Fonty od punktow
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text wyniki;
    wyniki.setFont(font);
    wyniki.setCharacterSize(24);
    wyniki.setFillColor(sf::Color::Red);
    wyniki.setStyle(sf::Text::Bold);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setString("Twoje punkty: ");
    punkty.setCharacterSize(24);
    punkty.setFillColor(sf::Color::Red);
    punkty.setStyle(sf::Text::Bold);

    wyniki.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2);
    punkty.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2);


    //Fonty od zycia
    sf::Text zycie_wskaznik;
    zycie_wskaznik.setFont(font);
    zycie_wskaznik.setCharacterSize(24);
    zycie_wskaznik.setFillColor(sf::Color::Red);
    zycie_wskaznik.setStyle(sf::Text::Bold);

    sf::Text zycie;
    zycie.setFont(font);
    zycie.setCharacterSize(24);
    zycie.setFillColor(sf::Color::Red);
    zycie.setStyle(sf::Text::Bold);
    zycie.setString("Twoje zycia: ");

    zycie_wskaznik.setPosition(rozmiar_x/2 + 500 , rozmiar_y/2 - rozmiar_y/2);
    zycie.setPosition(rozmiar_x/2 + 320, rozmiar_y/2 - rozmiar_y/2);

    //Tekst dla pauzy
    sf::Text pauza_;
    pauza_.setFont(font);
    pauza_.setCharacterSize(30);
    pauza_.setFillColor(sf::Color::White);
    pauza_.setStyle(sf::Text::Bold);
    pauza_.setString("PAUZA! Nacisnij P");

    pauza_.setPosition((rozmiar_x/2 - rozmiar_x/2) + 400, rozmiar_y/2);


    sf::RectangleShape hp;
//////////////////////////////////////////////////////////////////////////////////////
      // run the program as long as the window is open
    sf::Clock clock;

    bool pauza = false;
    bool fala_1 = false;
    bool fala_2 = false;
    bool boosty_1 = false;
    bool boost_rozmiar = false;
    bool boost_potwory = false;
    bool boosty_2 = false;
    bool boost_rozmiar_2 = false;
    bool boost_przeciwnicy_2 = false;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;
          sf::Time elapsed = clock.restart();


          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();
              //Sterowanie statkiem za pomoca klawiszy


              {
              if(event.type == sf::Event::KeyPressed)
              {

                  for(auto itr=pociski.begin(); itr != pociski.end(); itr++)
                  {
                      shot *pocisk = dynamic_cast<shot *>(itr->get());
                              if(pocisk != nullptr){
                                  pocisk->strzal(event, statek, dzwiek);
                              }
                  }

              }

}
              //PAUZA PO WCISNIECIU KLAWISZA P
              if(event.type == sf::Event::KeyReleased)
              {
                  if(event.key.code == sf::Keyboard::P)
                  {
                      pauza =! pauza;
                      std::cout << "PAUZA" << std::endl;
                  }
              }

          }
          if(!pauza)
          {
              //SEKCJA OD PORUSZANIA
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
               statek.ruch_po_x(elapsed, window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
              statek.ruch_po_x(elapsed, window, 1);
              }


              for(auto &poc : pociski)
              {
              poc->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }


              for(auto &el : przeciwnicy)
              {
                  el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

              for(auto &b : boosty1)
              {
                  b ->poruszaj(elapsed);
              }


              for(auto &b : boosty2)
              {
                  b ->poruszaj(elapsed);
              }

              zderzenia(statek, pociski, przeciwnicy, textureShot, zderzenie);

              zderzenia_z_obiektami(statek, przeciwnicy, rozmiar_x, rozmiar_y, hide_collision);



            //Wyswietlenie punktow
            wyniki.setString(std::to_string(statek.pobierz_liczbe_punktow()));

            //Warunek na wygrana
            if((przeciwnicy.empty()) && (fala_1 == false))
            {
                dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala_1 = true;
            }
            if((przeciwnicy.empty()) && (fala_2 == false))
            {
                dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala_2 = true;
            }
            if(przeciwnicy.empty())
            {
                muzyka.stop();
                window.close();
                ekran_wygranej_1();

                std::cout << "NASTEPNY POZIOM!" << std::endl;
            }


            //Wyswietlenie zycia
            zycie_wskaznik.setString(std::to_string(statek.pobierz_liczbe_zyc()));
            if(!statek.czy_zyje())
            {
                window.close();
                std::cout << "PRZEGRANA!" << std::endl;
            }
          }
          else
          {
              clock.restart();
          }


          //Boosty pierwsze
          if((statek.pobierz_liczbe_punktow() == 50) && (boosty_1 == false))
          {

              dodaj_boosty_1(boosty1, textureBoost, rozmiar_x, rozmiar_y);
              boosty_1 = true;

          }

          //Boosty zmieniajace wielkosc statku i zamrazajace przeciwnikow w miejscu

          for(auto itr = boosty1.begin(); itr != boosty1.end();)
          {
              if((*itr)->getGlobalBounds().intersects(statek.getGlobalBounds()) && boost_rozmiar == false && boost_potwory == false)
              {
                  int losowanie = rand()%2;
                  itr = boosty1.erase(itr);
                  dzwiek_boost.play();
                  if(losowanie == 0)
                  {
                  statek.setScale(0.2,0.2);
                  boost_rozmiar = true;
                  std::cout << "TWOJ STATEK SIE ZMNIEJSZYL!" << std::endl;
                  }
                  if(losowanie == 1)
                  {
                      for(auto it = przeciwnicy.begin(); it != przeciwnicy.end(); it++)
                      {
                          (*it)->ustaw_predkosc(0,0);
                      }
                      boost_potwory = true;
                      std::cout << "PRZECIWNICY ZAMARLI BEZ RUCHU!" << std::endl;
                  }

              }
              else
              {
                 itr++;
             }
          }
          //Warunek kiedy sie konczy pierwszy boost
         if(statek.pobierz_liczbe_punktow() == 250 && (boost_rozmiar == true))
          {
                statek.setScale(0.3,0.3);
                unboost.play();
          }
         if(statek.pobierz_liczbe_punktow() == 100 && (boost_potwory == true))
          {
             for(auto it = przeciwnicy.begin(); it != przeciwnicy.end(); it++)
             {
                 (*it)->ustaw_predkosc(0,10);
                 unboost.play();
             }
          }

         //Pojawienie sie drugich boostow
         if((statek.pobierz_liczbe_punktow() == 350) && (boosty_2 == false))
         {
             dodaj_boosty_2(boosty2, textureBoost2, rozmiar_x, rozmiar_y);
             boosty_2 = true;
         }


         for(auto itr = boosty2.begin(); itr != boosty2.end();)
         {
             if((*itr)->getGlobalBounds().intersects(statek.getGlobalBounds()) && boost_rozmiar_2 == false)
             {
                 int losowanie = rand()%2;
                 itr = boosty2.erase(itr);
                 dzwiek_boost2.play();
                 if(losowanie == 0)
                 {
                   statek.setScale(0.2,0.2);
                   std::cout << "TWOJ STATEK SIE ZMNIEJSZYL!" << std::endl;
                   boost_rozmiar_2 = true;

                 }
                 if(losowanie == 1)
                 {
                     for(auto it = przeciwnicy.begin(); it != przeciwnicy.end(); it++)
                     {
                         (*it)->ustaw_predkosc(0,0);
                         Ufo *ufo = dynamic_cast<Ufo *>(it->get());
                         if(ufo != nullptr)
                         {
                             ufo->setScale(0.3,0.3);
                         }

                     }
                       boost_przeciwnicy_2 = true;
                       std::cout << "PRZECIWNICY ZAMARLI! LATWIEJSZY CEL!" << std::endl;
                 }

             }
             else
             {
                itr++;
            }
         }
         //Kiedy konczy sie drugi boost
         if((statek.pobierz_liczbe_punktow() == 500) && (boost_rozmiar_2 == true))
         {
             statek.setScale(0.3,0.3);
             unboost2.play();
         }
         if((statek.pobierz_liczbe_punktow() == 450) && (boost_przeciwnicy_2 == true))
         {
             for(auto it = przeciwnicy.begin(); it != przeciwnicy.end(); it++)
             {
                 (*it)->ustaw_predkosc(0,10);
                 Ufo *ufo = dynamic_cast<Ufo *>(it->get());
                 if(ufo != nullptr)
                 {
                     ufo->setScale(0.2,0.2);
                 }

             }
             unboost2.play();
         }


         //Pętla odpowiedzialna za boosty
          for(auto itr = boosty1.begin(); itr!= boosty1.end();)
          {
              if((*itr)->getGlobalBounds().intersects(hide_collision.getGlobalBounds()))
              {
              itr = boosty1.erase(itr);
              }
              else
              {
                  itr++;
              }
          }

          for(auto itr = boosty2.begin(); itr!= boosty2.end();)
          {
              if((*itr)->getGlobalBounds().intersects(hide_collision.getGlobalBounds()))
              {
              itr = boosty2.erase(itr);
              }
              else
              {
                  itr++;
              }
          }


          // clear the window with black color
          window.clear(sf::Color::Black);

          //RYSOWANIE
          window.draw(spritetlo);
          window.draw(statek);
          window.draw(wyniki);
          window.draw(punkty);
          window.draw(zycie_wskaznik);
          window.draw(zycie);


          for(auto itr = przeciwnicy.begin(); itr != przeciwnicy.end(); itr++)
          {
              Ufo *ufo = dynamic_cast<Ufo *>(itr->get());
              if(ufo != nullptr)
              {
              sf::RectangleShape hp(sf::Vector2f(ufo->pobierz_liczbe_zyc()*10,10));
              hp.setPosition(ufo->getPosition().x + 10, ufo->getPosition().y - 10);
              hp.setFillColor(sf::Color(255,0,0));
              window.draw(hp);
              }
              Asteroid *asteroid = dynamic_cast<Asteroid *>(itr->get());
              if(asteroid != nullptr)
              {
                  sf::RectangleShape hp(sf::Vector2f(asteroid->pobierz_liczbe_zyc()*10,10));
                  hp.setPosition(asteroid->getPosition().x + 30, asteroid->getPosition().y);
                  hp.setFillColor(sf::Color(255,153,25));
                  window.draw(hp);
              }

          }


          for(auto &p : przeciwnicy)
          {

              window.draw(*p);
          }

          for(auto &p : pociski)
          {
              window.draw(*p);
          }

          for(auto &b : boosty1)
          {
              window.draw(*b);
          }

          for(auto &b2 : boosty2)
          {
              window.draw(*b2);
          }
          //Wyswietlenie napisu pauzy
          if(pauza)
          {
              window.draw(pauza_);
          }

          // end the current frame
          window.display();
      }
}

void gra_2()
{
    srand(time(NULL));
    //Tekstury
    sf::Texture textureStatek = loadTexture("./../spacehero/graphics/spaceship.png");
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureUfo = loadTexture("./../spacehero/graphics/ufo.png");
    sf::Texture textureAsteroida = loadTexture("./../spacehero/graphics/asteroid.png");
    sf::Texture textureShot = loadTexture("./../spacehero/graphics/shot.png");
    sf::Texture textureStatek2 = loadTexture("./../spacehero/graphics/spaceship2.png");
    sf::Texture textureShot2 = loadTexture("./../spacehero/graphics/shot2.png");

    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;


    sf::Music dzwiek;
    if(!dzwiek.openFromFile("./../spacehero/music/shot.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music dzwiek2;
    if(!dzwiek2.openFromFile("./../spacehero/music/shot2.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }

    sf::Music muzyka;
    if(!muzyka.openFromFile("./../spacehero/music/poziom1.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }
    muzyka.setVolume(10.f);
    muzyka.play();

    sf::Music zderzenie;
    if(!zderzenie.openFromFile("./../spacehero/music/zderzenie.wav"))
    {
        std::cerr << "Nie udalo sie wczytac dzwieku!" << std::endl;
    }


    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);



    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    //Utworzenie obiektu klasy spaceship
    Spaceship statek(textureStatek, rozmiar_x, rozmiar_y);
    Spaceship statek2(textureStatek2, rozmiar_x/4, rozmiar_y);


    //Pole ktorego nie moga przekroczyc przeciwnicy
    sf::RectangleShape hide_collision(sf::Vector2f(10000, 100));
    hide_collision.setPosition(window.getSize().x/30, statek.getPosition().y + 125);
    hide_collision.setFillColor(sf::Color(100,50, 250));

    sf::RectangleShape hide_collision_2(sf::Vector2f(10000, 100));
    hide_collision.setPosition(window.getSize().x/30, statek.getPosition().y + 125);
    hide_collision.setFillColor(sf::Color(100,50, 250));

    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Kontener pociskow
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski;

    //Kontener pociskow gracza 2
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski_2;

    //Pociski bossa
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski_boss;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

    dodaj_pociski(pociski, textureShot, statek);
    dodaj_pociski(pociski_2, textureShot2, statek2);

    //Fonty od punktow
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

//Gracz po prawej
    sf::Text wyniki;
    wyniki.setFont(font);
    wyniki.setCharacterSize(24);
    wyniki.setFillColor(sf::Color::Red);
    wyniki.setStyle(sf::Text::Bold);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setString("Twoje punkty: ");
    punkty.setCharacterSize(24);
    punkty.setFillColor(sf::Color::Red);
    punkty.setStyle(sf::Text::Bold);

    wyniki.setPosition(rozmiar_x/2  + 491, rozmiar_y/2 - rozmiar_y/2);
    punkty.setPosition(rozmiar_x/2 + 290 , rozmiar_y/2 - rozmiar_y/2);


    //Fonty od zycia
    sf::Text zycie_wskaznik;
    zycie_wskaznik.setFont(font);
    zycie_wskaznik.setCharacterSize(24);
    zycie_wskaznik.setFillColor(sf::Color::Red);
    zycie_wskaznik.setStyle(sf::Text::Bold);

    sf::Text zycie;
    zycie.setFont(font);
    zycie.setCharacterSize(24);
    zycie.setFillColor(sf::Color::Red);
    zycie.setStyle(sf::Text::Bold);
    zycie.setString("Twoje zycia: ");

    zycie_wskaznik.setPosition(rozmiar_x/2 + 480 , rozmiar_y/2 - rozmiar_y/2 + 30);
    zycie.setPosition(rozmiar_x/2 + 290, rozmiar_y/2 - rozmiar_y/2 + 30);


//Gracz po lewej
    sf::Text wyniki2;
    wyniki2.setFont(font);
    wyniki2.setCharacterSize(24);
    wyniki2.setFillColor(sf::Color::Red);
    wyniki2.setStyle(sf::Text::Bold);

    sf::Text punkty2;
    punkty2.setFont(font);
    punkty2.setString("Twoje punkty: ");
    punkty2.setCharacterSize(24);
    punkty2.setFillColor(sf::Color::Red);
    punkty2.setStyle(sf::Text::Bold);

    wyniki2.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2);
    punkty2.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2);

    //Fonty od zycia
    sf::Text zycie_wskaznik2;
    zycie_wskaznik2.setFont(font);
    zycie_wskaznik2.setCharacterSize(24);
    zycie_wskaznik2.setFillColor(sf::Color::Red);
    zycie_wskaznik2.setStyle(sf::Text::Bold);

    sf::Text zycie2;
    zycie2.setFont(font);
    zycie2.setCharacterSize(24);
    zycie2.setFillColor(sf::Color::Red);
    zycie2.setStyle(sf::Text::Bold);
    zycie2.setString("Twoje zycia: ");

    zycie_wskaznik2.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2 + 30);
    zycie2.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2 + 30);


    //Tekst dla pauzy
    sf::Text pauza_;
    pauza_.setFont(font);
    pauza_.setCharacterSize(30);
    pauza_.setFillColor(sf::Color::White);
    pauza_.setStyle(sf::Text::Bold);
    pauza_.setString("PAUZA! Nacisnij P");

    pauza_.setPosition((rozmiar_x/2 - rozmiar_x/2) + 400, rozmiar_y/2);

    sf::RectangleShape hp;
//////////////////////////////////////////////////////////////////////////////////////
      // run the program as long as the window is open
    sf::Clock clock;

    bool pauza = false;
    bool fala_1 = false;
    bool fala_2 = false;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;
          sf::Time elapsed = clock.restart();


          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();
              //Sterowanie statkiem za pomoca klawiszy


              {
              if(event.type == sf::Event::KeyPressed)
              {

                  for(auto itr=pociski.begin(); itr != pociski.end(); itr++)
                  {
                      shot *pocisk = dynamic_cast<shot *>(itr->get());
                              if(pocisk != nullptr){
                                  pocisk->strzal(event, statek, dzwiek);
                              }
                  }
                  for(auto itr=pociski_2.begin(); itr != pociski_2.end(); itr++)
                  {
                      shot *pocisk_2 = dynamic_cast<shot *>(itr->get());
                      if(pocisk_2 != nullptr){
                          pocisk_2->strzal_2(event, statek2, dzwiek2);
                      }
                  }



              }
}
              //PAUZA PO WCISNIECIU KLAWISZA P
              if(event.type == sf::Event::KeyReleased)
              {
                  if(event.key.code == sf::Keyboard::P)
                  {
                      pauza =! pauza;
                      std::cout << "PAUZA" << std::endl;
                  }
              }

          }
          if(!pauza)
          {
              //SEKCJA OD PORUSZANIA
              //STATEK 1
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
               statek.ruch_po_x(elapsed, window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
              statek.ruch_po_x(elapsed, window, 1);
              }
              //STATEK 2
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
              {
                  statek2.ruch_po_x(elapsed,window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
              {
                  statek2.ruch_po_x(elapsed,window,1);
              }


              for(auto &poc : pociski)
              {
              poc->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }

              for(auto &poc2 : pociski_2)
              {
                  poc2->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }


              for(auto &el : przeciwnicy)
              {
                  el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

              zderzenia(statek, pociski, przeciwnicy,  textureShot, zderzenie);
              zderzenia(statek2, pociski_2, przeciwnicy, textureShot2, zderzenie);

              zderzenia_z_obiektami(statek, przeciwnicy, rozmiar_x, rozmiar_y, hide_collision);
              zderzenia_z_obiektami(statek2, przeciwnicy, rozmiar_x, rozmiar_y, hide_collision);


            //Wyswietlenie punktow
            wyniki.setString(std::to_string(statek.pobierz_liczbe_punktow()));
            wyniki2.setString(std::to_string(statek2.pobierz_liczbe_punktow()));

            //Warunek na wygrana
            if((przeciwnicy.empty()) && (fala_1 == false))
            {
                dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala_1 = true;
            }
            if((przeciwnicy.empty()) && (fala_2 == false))
            {
                dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);
                statek.dodaj_zycie(1);
                fala_2 = true;
            }
            if(przeciwnicy.empty())
            {
                muzyka.stop();
                window.close();
                ekran_wygranej_2();

                std::cout << "NASTEPNY POZIOM!" << std::endl;
            }


            //Wyswietlenie zycia
            zycie_wskaznik.setString(std::to_string(statek.pobierz_liczbe_zyc()));
            zycie_wskaznik2.setString(std::to_string(statek2.pobierz_liczbe_zyc()));
            if(!statek.czy_zyje() || !statek2.czy_zyje())
            {
                window.close();
                std::cout << "PRZEGRANA!" << std::endl;
            }

          }
          else
          {
              clock.restart();
          }

          // clear the window with black color
          window.clear(sf::Color::Black);

//////////////////////////////////////////////////////////////////////////////////////////////////////
          //RYSOWANIE
          window.draw(spritetlo);
          window.draw(statek);
          window.draw(statek2);
          window.draw(wyniki);
          window.draw(punkty);
          window.draw(wyniki2);
          window.draw(punkty2);
          window.draw(zycie_wskaznik);
          window.draw(zycie);
          window.draw(zycie_wskaznik2);
          window.draw(zycie2);



          //Rysowanie HP przeciwnikow
          for(auto itr = przeciwnicy.begin(); itr != przeciwnicy.end(); itr++)
          {
              Ufo *ufo = dynamic_cast<Ufo *>(itr->get());
              if(ufo != nullptr)
              {
              sf::RectangleShape hp(sf::Vector2f(ufo->pobierz_liczbe_zyc()*10,10));
              hp.setPosition(ufo->getPosition().x + 10, ufo->getPosition().y - 10);
              hp.setFillColor(sf::Color(255,0,0));
              window.draw(hp);
              }
              Asteroid *asteroid = dynamic_cast<Asteroid *>(itr->get());
              if(asteroid != nullptr)
              {
                  sf::RectangleShape hp(sf::Vector2f(asteroid->pobierz_liczbe_zyc()*10,10));
                  hp.setPosition(asteroid->getPosition().x + 30, asteroid->getPosition().y);
                  hp.setFillColor(sf::Color(255,153,25));
                  window.draw(hp);
              }

          }


          for(auto &p : przeciwnicy)
          {

              window.draw(*p);
          }

          for(auto &p : pociski)
          {
              window.draw(*p);
          }

          for(auto &p2 : pociski_2)
          {
              window.draw(*p2);
          }

          //Wyswietlenie napisu pauzy
          if(pauza)
          {
              window.draw(pauza_);
          }
          // end the current frame
          window.display();
      }
}

void opis()
{
    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");
    sf::Texture textureA = loadTexture("./../spacehero/graphics/a.png");
    sf::Texture textureD = loadTexture("./../spacehero/graphics/d.png");
    sf::Texture textureP = loadTexture("./../spacehero/graphics/p.png");
    sf::Texture textureSpacja = loadTexture("./../spacehero/graphics/spacja.png");
    sf::Texture textureLewy = loadTexture("./../spacehero/graphics/lewy.png");

    //Rozmiar okna
    int rozmiar_x = 600;
    int rozmiar_y = 600;

    //Utworzenie okna
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);


    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text sterowanie;
    sf::Text ruch;
    sf::Text ruch1;
    sf::Text pauza;
    sf::Text strzal;
    sf::Text mysz;

    //Napis sterowanie
    //Stworzenie fontu i ustawienie
    sterowanie.setFont(font);
    sterowanie.setString("Sterowanie:");
    sterowanie.setCharacterSize(24);
    sterowanie.setFillColor(sf::Color::White);
    sterowanie.setStyle(sf::Text::Bold);
    sterowanie.setPosition(rozmiar_x/2 - 75, rozmiar_y/2 - rozmiar_y/2);

    //Opis sterowania(ruch)
    ruch.setFont(font);
    ruch.setString("A - ruch w lewo");
    ruch.setCharacterSize(20);
    ruch.setFillColor(sf::Color::White);
    ruch.setStyle(sf::Text::Bold);
    ruch.setPosition(rozmiar_x/2 - 100, rozmiar_y/2 - rozmiar_y/2 + 50);

    ruch1.setFont(font);
    ruch1.setString("D - ruch w prawo");
    ruch1.setCharacterSize(20);
    ruch1.setFillColor(sf::Color::White);
    ruch1.setStyle(sf::Text::Bold);
    ruch1.setPosition(rozmiar_x/2 - 100, rozmiar_y/2 - rozmiar_y/2 + 70);

    pauza.setFont(font);
    pauza.setString("P - pauza");
    pauza.setCharacterSize(20);
    pauza.setFillColor(sf::Color::White);
    pauza.setStyle(sf::Text::Bold);
    pauza.setPosition(rozmiar_x/2 - 100, rozmiar_y/2 - rozmiar_y/2 + 140);

    strzal.setFont(font);
    strzal.setString("Spacja - strzal");
    strzal.setCharacterSize(20);
    strzal.setFillColor(sf::Color::White);
    strzal.setStyle(sf::Text::Bold);
    strzal.setPosition(rozmiar_x/2 + 50, rozmiar_y/2 - rozmiar_y/2 + 210);

    mysz.setFont(font);
    mysz.setString("LPM - interakcja w MENU");
    mysz.setCharacterSize(20);
    mysz.setFillColor(sf::Color::White);
    mysz.setStyle(sf::Text::Bold);
    mysz.setPosition(rozmiar_x/2 - 50, rozmiar_y/2 - rozmiar_y/2 + 350);

    //Grafiki
    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    sf::Sprite a;
    a.setTexture(textureA);
    a.setScale(0.7,0.7);
    a.setPosition(rozmiar_x/2 - 250, rozmiar_y/2 - rozmiar_y/2 + 50);

    sf::Sprite d;
    d.setTexture(textureD);
    d.setScale(0.7, 0.7);
    d.setPosition(rozmiar_x/2 - 180, rozmiar_y/2 - rozmiar_y/2 + 50);

    sf::Sprite p;
    p.setTexture(textureP);
    p.setScale(0.7, 0.7);
    p.setPosition(rozmiar_x/2 - 228, rozmiar_y/2 - rozmiar_y/2 + 125);

    sf::Sprite spacja;
    spacja.setTexture(textureSpacja);
    spacja.setScale(0.7, 0.7);
    spacja.setPosition(rozmiar_x/2 - 290, rozmiar_y/2 - rozmiar_y/2 + 200);

    sf::Sprite lewy;
    lewy.setTexture(textureLewy);
    lewy.setScale(0.2,0.2);
    lewy.setPosition(rozmiar_x/2 - 180, rozmiar_y/2 - rozmiar_y/2 + 300);


    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            }


        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);
        window.draw(a);
        window.draw(d);
        window.draw(p);
        window.draw(spacja);
        window.draw(lewy);
        window.draw(sterowanie);
        window.draw(ruch);
        window.draw(ruch1);
        window.draw(pauza);
        window.draw(strzal);
        window.draw(mysz);


        // end the current frame
        window.display();
    }
}

void autor()
{
    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlo.png");

    //Rozmiar okna
    int rozmiar_x = 600;
    int rozmiar_y = 600;

    //Utworzenie okna
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Gif
    sf::Texture giff = loadTexture("./../spacehero/graphics/sweet.gif");

    sf::Sprite giff_s;
    giff_s.setTexture(giff);
    giff_s.setPosition(rozmiar_x/2 - 100, rozmiar_y/2);
    giff_s.setScale(1.5,1.5);

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/graphics/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text text;
    sf::Text text_2;
    sf::Text text_3;

    //Stworzenie fontu i ustawienie
    text.setFont(font);
    text.setString("AUTOR");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    //Opis autora
    text_2.setFont(font);
    text_2.setString("Maciej Dyks");
    text_2.setCharacterSize(24);
    text_2.setFillColor(sf::Color::Red);
    text_2.setStyle(sf::Text::Bold);
    //Rok powstania
    text_3.setFont(font);
    text_3.setString("Gra powstala w 2022 roku, II semestr PSiO");
    text_3.setCharacterSize(24);
    text_3.setFillColor(sf::Color::Red);
    text_3.setStyle(sf::Text::Bold);


    //Granice okna
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);


    text.setPosition(rozmiar_x/2 - 50, rozmiar_y/2 - rozmiar_y/2);
    text_2.setPosition(rozmiar_x/2 - 75, rozmiar_y/2 - rozmiar_y/2 + 25);
    text_3.setPosition(rozmiar_x/2 - 300, rozmiar_y/2 - rozmiar_y/2 + 65);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);
        window.draw(text);
        window.draw(text_2);
        window.draw(text_3);
        window.draw(giff_s);



        // end the current frame
        window.display();
    }

}

void tryb_gry()
{
    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlotytul.png");
    sf::Texture textureJeden = loadTexture("./../spacehero/graphics/jednoosobowy.png");
    sf::Texture textureDwa = loadTexture("./../spacehero/graphics/dwuosobowy.png");

    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;

    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    //Przyciski
    przycisk przyciskJedno(textureJeden, rozmiar_x, rozmiar_y);
    przycisk przyciskDwa(textureDwa, rozmiar_x, rozmiar_y + rozmiar_y/6 + 20);

    sf::Clock clock;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;

          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();

              //Wcisniecie przyciskow
              if (event.type == sf::Event::MouseButtonPressed){
                  sf::Vector2f pozycja_myszki = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                  if(event.mouseButton.button == sf::Mouse::Left){
                      if(przyciskJedno.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout <<"WYBRANO TRYB JEDNOOSOBOWY" << std::endl;
                          window.close();
                          gra_1();
                      }
                      if(przyciskDwa.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout <<"WYBRANO TRYB DWUOSOBOWY!" << std::endl;
                          window.close();
                          gra_2();
                      }
                  }

}


          // clear the window with black color
          window.clear(sf::Color::Black);

          // draw everything here...
          window.draw(spritetlo);
          window.draw(przyciskJedno);
          window.draw(przyciskDwa);

          // end the current frame
          window.display();
      }
}
}

void okno_startowe()
{

    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/graphics/tlotytul.png");
    sf::Texture textureGraj = loadTexture("./../spacehero/graphics/graj.png");
    sf::Texture textureOpis = loadTexture("./../spacehero/graphics/opis.png");
    sf::Texture textureAutor = loadTexture("./../spacehero/graphics/autor.png");
    sf::Texture textureDzwiek = loadTexture("./../spacehero/graphics/dzwiek.png");
    sf::Texture textureWylacz = loadTexture("./../spacehero/graphics/wylacz.png");

    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;

    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    //Przyciski
    przycisk przyciskGraj(textureGraj, rozmiar_x, rozmiar_y);
    przycisk przyciskOpis(textureOpis, rozmiar_x, rozmiar_y + rozmiar_y/6);
    przycisk przyciskAutor(textureAutor, rozmiar_x, rozmiar_y + rozmiar_y/3);
    przycisk przyciskSoundOn(textureDzwiek, rozmiar_x - 150, rozmiar_y + rozmiar_y/2);
    przycisk przyciskSoundOff(textureWylacz, rozmiar_x + 150, rozmiar_y + rozmiar_y/2);


    //Muzyka
    sf::Music muzyka_intro;
    if(!muzyka_intro.openFromFile("./../spacehero/music/intro.wav"))
    {
        std::cerr <<"Nie udalo sie wczytac muzyki!" << std::endl;
    }

    muzyka_intro.setVolume(10.f);
    muzyka_intro.play();

    sf::Clock clock;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;

          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();

              //Wcisniecie przyciskow
              if (event.type == sf::Event::MouseButtonPressed){
                  sf::Vector2f pozycja_myszki = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                  if(event.mouseButton.button == sf::Mouse::Left){
                      if(przyciskGraj.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto GRAJ" << std::endl;
                         window.close();
                         muzyka_intro.stop();
                          tryb_gry();
                      }
                      if(przyciskOpis.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto Opis" << std::endl;
                          opis();
                      }
                      if(przyciskAutor.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto Autor" << std::endl;
                          autor();
                      }
                      if(przyciskSoundOn.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto wlacz dzwiek" << std::endl;
                          muzyka_intro.play();
                      }
                      if(przyciskSoundOff.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto wylacz dzwiek" << std::endl;
                          muzyka_intro.stop();
                      }
              }

}


          // clear the window with black color
          window.clear(sf::Color::Black);

          // draw everything here...
          window.draw(spritetlo);
          window.draw(przyciskGraj);
          window.draw(przyciskOpis);
          window.draw(przyciskAutor);
          window.draw(przyciskSoundOn);
          window.draw(przyciskSoundOff);

          // end the current frame
          window.display();
      }
}
}


