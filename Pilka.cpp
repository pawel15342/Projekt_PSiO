#include "Pilka.h"

const int wysokosc = 600;
const int szerokosc = 800;

Pilka::Pilka(float x, float y)
{
    texture.loadFromFile("tekstury/pilka.png");
    pilka.setTexture(&texture);
    pilka.setPosition(x, y);
    pilka.setRadius(this->ballPromien);
    pilka.setOrigin(this->ballPromien, this->ballPromien);
    state = START;
}
void Pilka::draw(sf::RenderTarget& target, sf::RenderStates state)const
{
    target.draw(this->pilka, state);
}
void Pilka::update() {

    if (state == START) {
        predkosc.x = 0; //predkosc poczatkowa na odbijaku jest rowna 0
        float x{ 8.f };//predkosc pilki na odbijaku musi byc rowna predkosci odbijaka

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->Lewo() > 0 + 60)//poruszanie sie pilki na odbijaku w lewo
        {
            predkosc.x = -x;
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->Prawo() < szerokosc - 60)//poruszanie sie pilki na odbijaku w prawo
        {
            predkosc.x = x;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && state == START)
    {

        set_predkosc(6);//predkosc pilki po uwolnieniu
        state = ROZGRYWKA;
    }

    pilka.move(this->predkosc);

    if (this->Lewo() < 0)
    {
        zmiana_x();
    }

    if (this->Prawo() > szerokosc)
    {
        zmiana_x();
    }


    if (this->Gora() < 0)
    {

        zmiana_y();
    }

    if (this->Dol() > wysokosc)
    {

        zmiana_y();
    }

}
//zwracanie pozycji pilki
float Pilka::Lewo() {

    return this->pilka.getPosition().x - pilka.getRadius();
}

float Pilka::Prawo() {
    return this->pilka.getPosition().x + pilka.getRadius();
}

float Pilka::Gora() {
    return this->pilka.getPosition().y - pilka.getRadius();
}

float Pilka::Dol() {
    return this->pilka.getPosition().y + pilka.getRadius();
}

void Pilka::zmiana_y() {
    predkosc.y = -predkosc.y;
}
void Pilka::zmiana_x() {
    predkosc.x = -predkosc.x;
}
float Pilka::get_promien() {
    return ballPromien;
}
void Pilka::set_predkosc(float x) {
    predkosc_pilki = x;
    predkosc = { predkosc_pilki ,-predkosc_pilki };
    if (state == START) state = ROZGRYWKA;
    if (state == ROZGRYWKA) state = START;

}
void Pilka::set_pozycja(float x, float y) {
    pilka.setPosition(x, y);
}

