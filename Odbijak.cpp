#include "Odbijak.h"

const int szerokosc = 800;
Odbijak::Odbijak(float X, float Y)
{
    texture.loadFromFile("tekstury/platforma.png");
    odbijak.setTexture(&texture);
    odbijak.setPosition(X, Y);
    odbijak.setSize({ this->szerokosc_odbijaka,this->wysokosc_odbijaka });
    odbijak.setOrigin(szerokosc_odbijaka / 2.f, wysokosc_odbijaka / 2.f);
}
void Odbijak::draw(sf::RenderTarget &cel, sf::RenderStates etap)const
{
    cel.draw(this->odbijak, etap);
}
//zwracanie pozycji odbijaka
float Odbijak::Lewo() {
    return this->odbijak.getPosition().x - odbijak.getSize().x / 2.f;
}

float Odbijak::Prawo() {
    return this->odbijak.getPosition().x + odbijak.getSize().x / 2.f;
}

float Odbijak::Gora() {
    return this->odbijak.getPosition().y - odbijak.getSize().y / 2.f;
}

float Odbijak::Dol() {
    return this->odbijak.getPosition().y + odbijak.getSize().y / 2.f;
}
float Odbijak::get_wysokosc() {
    return wysokosc_odbijaka;
}
float Odbijak::get_szerokosc() {
    return szerokosc_odbijaka;
}
void Odbijak::set_pozycja(float x, float y) {
    odbijak.setPosition(x, y);
}

void Odbijak::update()
{
    odbijak.move(this->predkosc);
    predkosc.x = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->Lewo() > 0) //poruszanie sie w lewo
    {
        predkosc.x = -predkosc_odbijaka;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->Prawo() < szerokosc)//poruszanie sie w prawo
    {
        predkosc.x = predkosc_odbijaka;
    }
}

