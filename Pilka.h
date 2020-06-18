#ifndef PILKA_H
#define PILKA_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Odbijak.h"

class Pilka : public sf::Drawable
{
public:
    Pilka(float x, float y);
   ~Pilka() {}

    enum EtapGry { START, ROZGRYWKA }; // deklaracja etapow gry
    EtapGry state;
    //ruch
    void update();
    float Lewo();
    float Prawo();
    float Gora();
    float Dol();

//zmiana kierunku po odbiciu
    void zmiana_y();
    void zmiana_x();
 //predkosc pilki
    void set_predkosc(float X);
    void set_pozycja(float x, float y);
    float get_promien();

    virtual void draw(sf::RenderTarget& cel, sf::RenderStates etap) const;

private:

    sf::CircleShape pilka; // nadanie kszatltu
    sf::Texture texture; //deklaracja tekstury
    const float ballPromien = 12.0f; //nadanie promienia pilce
    float predkosc_pilki = 0.0f; //predkosc poczatkowa
    sf::Vector2f predkosc = { predkosc_pilki, predkosc_pilki }; //predkosc w plaszczycie 2d
};

#endif

