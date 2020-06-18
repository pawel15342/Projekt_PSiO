#include "Cegielka.h"

Cegielka::Cegielka(float X, float Y, float szerokosc, float wysokosc, sf::Texture &texture)//konstruktor
{
    cegielka.setPosition(X - 30, Y);
    cegielka.setSize({ szerokosc,wysokosc });
    cegielka.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    cegielka.setTexture(&texture);
 }

void Cegielka::draw(sf::RenderTarget& target, sf::RenderStates state)const
{
    target.draw(this->cegielka, state);
}
float Cegielka::Lewo() {

    return this->cegielka.getPosition().x - cegielka.getSize().x / 2.f;
}

float Cegielka::Prawo() {

    return this->cegielka.getPosition().x + cegielka.getSize().x / 2.f;
}

float Cegielka::Gora() {

    return this->cegielka.getPosition().y - cegielka.getSize().y / 2.f;
}

float Cegielka::Dol() {

    return this->cegielka.getPosition().y + cegielka.getSize().y / 2.f;
}

bool Cegielka::get_rozbij()
{
    return this->visible;
}

void Cegielka::set_zbij()
{
    this->visible = true;

}


