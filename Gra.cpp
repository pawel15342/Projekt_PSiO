#include "Gra.h"
#include <iostream>
#include <vector>

const int wysokosc_cegielki = 30;
const int szerokosc_cegielki = 68;
const int wysokosc_okna = 600;
const int szerokosc_okna = 800;

Gra::Gra(void)
{
    state = MENU; // zaladowanie menu
    window = new sf::RenderWindow;
//LADOWANIE CZCIONKI
    font.loadFromFile("tekstury/font.ttf");
//TEKSTURY BLOCZKOW
    tekstura_bloczka.loadFromFile("tekstury/brick_pink_small.jpg");
//TEKSTURY TLA WYGRANA I PRZEGRANA
    tekstura.loadFromFile("tekstury/background.jpg");
    sprite_tlo1.setTexture(tekstura);
//MUZYKA
    buffer.loadFromFile("muzyka/kolizja.ogg");
    sound.setBuffer(buffer);
    buffer2.loadFromFile("muzyka/odbicie.flac");
    sound2.setBuffer(buffer2);
    buffer3.loadFromFile("muzyka/przegrana.wav");
    sound3.setBuffer(buffer3);
    buffer4.loadFromFile("muzyka/wygrana.wav");
    sound4.setBuffer(buffer4);
    buffer5.loadFromFile("muzyka/kaput.wav");
    sound5.setBuffer(buffer5);
//ZMIENNE ZYCIA I PUNKTOW
    zycie = new int;
    pkt = new int;
    *zycie = 0;
    *pkt = 0;
}
//WYWOLANIE DESTRUKTORA(ZAMKNIECIE OKNA  I USUNIECIE STATYSTYK)
Gra::~Gra(void)
{
    delete zycie;
    delete pkt;
    delete window;
}

//KOLLIZJA I ZMIANA KIERUNKU PILKI PO ODBICIU SIE OD BLOCZKA
template <class T1, class T2> bool kolizja(T1 *A, T2 *B)
{
   return A->Prawo() >= B->Lewo() && A->Lewo() <= B->Prawo() && A->Dol() >= B->Gora() && A->Gora() <= B->Dol();
}
//ZADEKLAROWANIE BOOL KOLIZJA
bool Gra::kolizjaTest(Cegielka* cegielka, Pilka *pilka, int &liczbaBlokow)
{
    if (!kolizja(cegielka, pilka))return false;

    if (!cegielka->get_rozbij())
    {
        cegielka->set_zbij();
        liczbaBlokow--; //zmienna ilosci blokow po kontakcie z pilka
        pilka->zmiana_y();
        sound.play();
    }
    return cegielka->get_rozbij();
}
void Gra::dodawnie_puntkow() {
    *pkt += 10; //ilosc dodanych punktow za zniczenie bloku
}

void Gra::Uruchom_Gre()
{
     while (state != KONIEC)
    {
        window->create(sf::VideoMode(szerokosc_okna, wysokosc_okna), "GIERKA");
        switch (state)
        {
            case EtapGry::MENU:
                menu(window);
                break;
            case EtapGry::GRA:
                Poczatek(window);
                break;
            case EtapGry::PRZEGRANA:
                Przegrana(window);
                break;
            case EtapGry::WYGRANA_1:
                Wygrana_1(window);
                break;
            case EtapGry::WYGRANA_2:
                Wygrana_2(window);
                break;
            case EtapGry::AUTOR:
                Autor(window);
                break;
            case EtapGry::GRA_2:
                Poczatek2(window);
                break;

        }
    }
}
void Gra::update() {

    napis = "    Zycia " + std::to_string(*zycie) + "    Punkty " + std::to_string(*pkt);
    text.setString(napis);
    text.setPosition((szerokosc_okna - text.getGlobalBounds().width) / 2, wysokosc_okna - 40);
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
  //  napis_koniec =
}
void Gra::menu(sf::RenderWindow *window) //interfejs menu
{
//umiejscowienie tytulu gry i rozmarow
    sf::Text nazwa_gry("Arkanoid", font, 80);
    nazwa_gry.setStyle(sf::Text::Bold);
    nazwa_gry.setPosition(szerokosc_okna / 2 - nazwa_gry.getGlobalBounds().width / 2, 20);
    nazwa_gry.setFillColor(sf::Color::Black);
//dodanie opcji do wyboru
    const int ile_wyborow = 3; //deklaracja ilosci wyborow
    sf::Text tekst[ile_wyborow]; //tablica
    std::string str[] = { "GRAJ","WYJSCIE","AUTOR" };//napisy w menu poczatkowym
    for (int i = 0; i<ile_wyborow; i++)//petla wybierania
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(80);
        tekst[i].setString(str[i]);
        tekst[i].setPosition(szerokosc_okna / 2.f - tekst[i].getGlobalBounds().width / 2.f, 200.f + i * 120.f);
    }
    while (state == MENU) // petla wybrania myszka opcji
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(*window));
        sf::Event event;
        while (window->pollEvent(event))
        {
           // Gra
            if (((tekst[0].getGlobalBounds().contains(mouse)) &&
                 (event.type == sf::Event::MouseButtonReleased) &&
                 (event.key.code == sf::Mouse::Left)) || (event.type == sf::Event::KeyPressed &&
                                                          event.key.code == sf::Keyboard::Return))
            {
                state = GRA;
            }
           //Koniec gry
            else if ((tekst[1].getGlobalBounds().contains(mouse) &&
                      event.type == sf::Event::MouseButtonReleased &&
                      event.key.code == sf::Mouse::Left)|| (event.type == sf::Event::Closed))
            {
                state = KONIEC;
            }
            else if (tekst[2].getGlobalBounds().contains(mouse) &&
                     event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
            {
                state = AUTOR;
            }
        }
        //wytluszanie tekstu po najechaniu kursorem
        for (int i = 0; i<ile_wyborow; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setFillColor(sf::Color::Blue);
           else tekst[i].setFillColor(sf::Color::Black);

        window->clear();
        window->draw(sprite_tlo1);
        window->draw(nazwa_gry);
        for (int i = 0; i<ile_wyborow; i++)
        window->draw(tekst[i]);
        window->display();
    }
}
//**************************************************************************************************************
//POCZĄTEK
void Gra::Poczatek(sf::RenderWindow *window)
{
    window->setMouseCursorVisible(false);
    window->clear();
    *pkt = 0;
    *zycie = 3;
    pilka = new Pilka(szerokosc_okna / 2-10, wysokosc_okna - 80);
    odbijak = new Odbijak((szerokosc_okna / 2)-10, wysokosc_okna - 60);
    window->setFramerateLimit(60);

    std::vector<Cegielka *> cegielki;
    int liczba_cegielek = 0;
    unsigned int l_kolumny = 11;//liczba blokow w rzedzie
    l_kolumny--;
    unsigned int  l_rzad = 5;
// PETLA USTAWIAJACA BLOCZKI W WIERSZACH I KOLUMNACH
    for (unsigned int a = 0; a < l_rzad; a++)
    {
        for (unsigned int b = 0; b < l_kolumny; b++)
        {
            switch (a) //a odpowiada ilosci rzedow
            {
                case 0: //rzad gorny
                    cegielki.push_back(new Cegielka(float((b + 1)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;         
                case 1 :
                    cegielki.push_back(new Cegielka(float((b + 1)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;             
                case 2:
                    cegielki.push_back(new Cegielka(float((b + 1)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;
                case 3:
                    cegielki.push_back(new Cegielka(float((b + 1)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;
                case 4: //rzad dolny
                    cegielki.push_back(new Cegielka(float((b + 1)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;
            }
            liczba_cegielek++;
        }
    }    
while (state == GRA)
    {
        sf::Event event;

        while (window->pollEvent(event))
        {           
            //Koniec gry
            if (event.type == sf::Event::Closed)
            {
                state = KONIEC;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                state = MENU;
            }
            //PAUZA
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                state = PAUZA;
                sf::Text title("PAUZA", font, 85);
                title.setStyle(sf::Text::Bold);
                title.setPosition(szerokosc_okna / 2 - title.getGlobalBounds().width / 2, wysokosc_okna / 2 + 50);
                title.setFillColor(sf::Color::Black);
                window->draw(title);
                window->display();

                while (state == PAUZA) {
                    sf::Event event1;
                    while (window->pollEvent(event1))
                        if (event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Space)
                            state = GRA;
                }
            }
        }       
        window->clear(sf::Color::Black);
        pilka->update();
        odbijak->update();
        update();
        window->draw(sprite_tlo1);
        window->draw(*pilka);
        window->draw(*odbijak);
        window->draw(text);

        for (std::vector<Cegielka *>::iterator wsk = cegielki.begin(); wsk!= cegielki.end(); wsk++) {

            if (!(*wsk)->get_rozbij())
            {
                if (kolizjaTest((*wsk), pilka, liczba_cegielek))
                {
                    dodawnie_puntkow();
                    break;
                }
            }
        }
        for (std::vector<Cegielka *>::iterator wsk = cegielki.begin(); wsk!= cegielki.end(); wsk++) {

            if (!(*wsk)->get_rozbij())
            {
                window->draw(*(*wsk));
            }

        }
        window->display();


        if(event.key.code == sf::Keyboard::Up)// po nacisnieciu przycisku bedzie spelniiony warunek o jeden nizej
        {
            dzwiek_odbijaka=true;
        }
        if(((pilka->Lewo() + pilka->get_promien() >= odbijak->Lewo()) &&
            (pilka->Lewo() <= odbijak->Prawo()) &&
            (pilka->Gora() + (2 * pilka->get_promien()) >= odbijak->Gora()) &&
            (pilka->Gora() <= odbijak->Gora())) && (dzwiek_odbijaka))
        {
            sound2.play();
        }
        if ((pilka->Lewo() + pilka->get_promien() >= odbijak->Lewo()) &&
                (pilka->Lewo() <= odbijak->Prawo()) &&
                (pilka->Gora() + (2 * pilka->get_promien()) >= odbijak->Gora()) &&
                (pilka->Gora() <= odbijak->Gora())) {
            pilka->zmiana_y();

        }

        else if (pilka->Gora() >= odbijak->Gora() + 5)
        {
            *zycie = *zycie - 1; //odejmowanie ilosci zycia za smierc
            *pkt -= 50; //ilosc odejmowych punktow za utrate zycia
            //koniec gry
            while (*zycie <= 0 && state == GRA) {

                state = PRZEGRANA;
            }
            pilka->set_predkosc(0);
            pilka->set_pozycja(szerokosc_okna / 2, wysokosc_okna - 80);
            odbijak->set_pozycja(szerokosc_okna / 2, wysokosc_okna - 60);
            dzwiek_odbijaka=false; // bool false, zeby nie bylo spamu dziweku jak pilka lezy na desce
            sound5.play();
        }

         if (liczba_cegielek == 0) {
            state = WYGRANA_1;
            liczba_cegielek++;
        }

    }
   for (std::vector<Cegielka* >::iterator it = cegielki.begin(); it != cegielki.end(); it++)
        delete (*it);

    delete pilka;
    delete odbijak;
    cegielki.clear();
}
//********************************************************************************************************************* poziom 2
void Gra::Poczatek2(sf::RenderWindow *window)
{
    window->setMouseCursorVisible(false);
    window->clear();
    *pkt = 0;
    *zycie = 3;
    pilka = new Pilka((szerokosc_okna / 2)-10, wysokosc_okna - 80);
    odbijak = new Odbijak((szerokosc_okna / 2)-10, wysokosc_okna - 60);
    window->setFramerateLimit(60);

    std::vector<Cegielka *> cegielki;
    int liczba_cegielek = 0;
    //liczba blokow w rzedzie
    unsigned int l_kolumny_4 = 4;
    unsigned int l_kolumny = 7;
    unsigned int l_kolumny_2 = 10;
    unsigned int l_kolumny_3 = 8;
    l_kolumny--;
    unsigned int  l_rzad = 7;
// PETLA USTAWIAJACA BLOCZKI W WIERSZACH I KOLUMNACH
    for (unsigned int a = 0; a < l_rzad; a++)
    {
        for (unsigned int b = 0; b < l_kolumny; b++)
        {
            switch (a) //a odpowiada ilosci rzedow
            {
                case 1: //rzad gorny
                    cegielki.push_back(new Cegielka(float((b + 3)*(szerokosc_cegielki + 10 )), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;
                case 5:
                    cegielki.push_back(new Cegielka(float((b + 3)*(szerokosc_cegielki + 10 )), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                    break;
            }
                liczba_cegielek++;
        }
        for (unsigned int b2 = 0; b2 < l_kolumny_2; b2++)
        {
            switch (a)
            {
              case 3:
                cegielki.push_back(new Cegielka(float((b2 + 1)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                break;
            }
            liczba_cegielek++;
        }

        for (unsigned int b3 = 0; b3 < l_kolumny_3; b3++)
        {
            switch (a)
            {
              case 2:
                cegielki.push_back(new Cegielka(float((b3 + 2)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                break;
              case 4:
                cegielki.push_back(new Cegielka(float((b3 + 2)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                break;
            }
            liczba_cegielek++;
        }
        for (unsigned int b4 = 0; b4 < l_kolumny_4; b4++)
        {
            switch (a)
            {
              case 0:
                cegielki.push_back(new Cegielka(float((b4 + 4)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                break;
              case 6:
                cegielki.push_back(new Cegielka(float((b4 + 4)*(szerokosc_cegielki + 10)), float((a + 2)*(wysokosc_cegielki + 5)), float(szerokosc_cegielki), float(wysokosc_cegielki), tekstura_bloczka));
                break;
            }
            liczba_cegielek++;
        }
    }
while (state == GRA_2)
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            //Koniec gry
            if (event.type == sf::Event::Closed)
            {
                state = KONIEC;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                state = MENU;
            }
            //PAUZA
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                state = PAUZA;
                sf::Text title("PAUZA", font, 85);
                title.setStyle(sf::Text::Bold);
                title.setPosition(szerokosc_okna / 2 - title.getGlobalBounds().width / 2, wysokosc_okna / 2 + 50);
                title.setFillColor(sf::Color::Black);
                window->draw(title);
                window->display();

                while (state == PAUZA) {
                    sf::Event event1;
                    while (window->pollEvent(event1))
                        if (event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Space)
                            state = GRA;
                }
            }
        }
        window->clear(sf::Color::Black);
        pilka->update();
        odbijak->update();
        update();
        window->draw(sprite_tlo1);
        window->draw(*pilka);
        window->draw(*odbijak);
        window->draw(text);

        for (std::vector<Cegielka *>::iterator wsk = cegielki.begin(); wsk!= cegielki.end(); wsk++) {

            if (!(*wsk)->get_rozbij())
            {
                if (kolizjaTest((*wsk), pilka, liczba_cegielek))
                {
                    dodawnie_puntkow();
                    break;
                }
            }
        }
        for (std::vector<Cegielka *>::iterator wsk = cegielki.begin(); wsk!= cegielki.end(); wsk++) {

            if (!(*wsk)->get_rozbij())
            {
                window->draw(*(*wsk));
            }

        }
        window->display();


        if(event.key.code == sf::Keyboard::Up)// po nacisnieciu przycisku bedzie spelniiony warunek o jeden nizej
        {
            dzwiek_odbijaka=true;
        }
        if(((pilka->Lewo() + pilka->get_promien() >= odbijak->Lewo()) &&
            (pilka->Lewo() <= odbijak->Prawo()) &&
            (pilka->Gora() + (2 * pilka->get_promien()) >= odbijak->Gora()) &&
            (pilka->Gora() <= odbijak->Gora())) && (dzwiek_odbijaka))
        {
            sound2.play();
        }
        if ((pilka->Lewo() + pilka->get_promien() >= odbijak->Lewo()) &&
                (pilka->Lewo() <= odbijak->Prawo()) &&
                (pilka->Gora() + (2 * pilka->get_promien()) >= odbijak->Gora()) &&
                (pilka->Gora() <= odbijak->Gora())) {
            pilka->zmiana_y();

        }

        else if (pilka->Gora() >= odbijak->Gora() + 5)
        {
            *zycie = *zycie - 1; //odejmowanie ilosci zycia za smierc
            *pkt -= 50; //ilosc odejmowych punktow za utrate zycia
            //koniec gry
            while (*zycie <= 0 && state == GRA_2) {

                state = PRZEGRANA;
            }
            pilka->set_predkosc(0);
            pilka->set_pozycja(szerokosc_okna / 2, wysokosc_okna - 80);
            odbijak->set_pozycja(szerokosc_okna / 2, wysokosc_okna - 60);
            dzwiek_odbijaka=false; // bool false, zeby nie bylo spamu dziweku jak pilka lezy na desce
            sound5.play();
        }
            \
         if (liczba_cegielek == 150) {
            state = WYGRANA_2;
            liczba_cegielek++;
        }

    }
   for (std::vector<Cegielka* >::iterator it = cegielki.begin(); it != cegielki.end(); it++)
        delete (*it);

    delete pilka;
    delete odbijak;
    cegielki.clear();
}
//************************************************************************************************************************************
//PRZEGRANA
void Gra::Przegrana(sf::RenderWindow *window) {
    window->setMouseCursorVisible(true); //pojawienie sie kurora do zaznaczenie opcji
    sound3.play();
    while (state == PRZEGRANA) {
        sf::Text title("PORAZKA", font, 80); //wyswietla napis
        title.setStyle(sf::Text::Bold); //styl
        title.setPosition(szerokosc_okna / 2 - title.getGlobalBounds().width / 2, 60);//pozycja napisu
        title.setFillColor(sf::Color::Black);
        const int ile = 2; //ile mozliwosci klikniec
        sf::Text tekst[ile];//tablica
        std::string str[] = { "OK","Jeszcze raz" };
      for (int i = 0; i<ile; i++) // petla
       {
            tekst[i].setFont(font);
            tekst[i].setCharacterSize(65);
            tekst[i].setString(str[i]);
            tekst[i].setPosition(szerokosc_okna / 2.f - tekst[i].getGlobalBounds().width / 2.f, 250.f + i * 120.f);
        }
      sf::Vector2f mouse(sf::Mouse::getPosition(*window));
      sf::Event event;


        while (window->pollEvent(event)) //STEROWANIE MENU PRZEGRANEJ KURSOREM
        {
            if (event.type == sf::Event::Closed)
            {
                state = KONIEC;
            }
            if ((tekst[0].getGlobalBounds().contains(mouse) &&
                 event.type == sf::Event::MouseButtonReleased) &&
                 (event.key.code == sf::Mouse::Left)) //KONIEC
            {
                state = MENU;
            }
            if ((tekst[1].getGlobalBounds().contains(mouse) &&
                 event.type == sf::Event::MouseButtonReleased &&
                 event.key.code == sf::Mouse::Left) || (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Return))//JESZCZE RAZ

            {
                state = GRA;
            }
        }

        for (int i = 0; i<ile; i++)
          if (tekst[i].getGlobalBounds().contains(mouse))
          tekst[i].setFillColor(sf::Color::Blue);
           else tekst[i].setFillColor(sf::Color::Black);

        update();
        window->clear();
        window->draw(sprite_tlo1);
        window->draw(title);
        window->draw(text);
        window->draw(tekst[0]);
        window->draw(tekst[1]);
        window->display();

    }

}
//*************************************************************************************************************************
//WYGRANA
void Gra::Wygrana_1(sf::RenderWindow *window) {
    window->setMouseCursorVisible(true);//pojawienie sie kursora
    sound4.play();
    sf::Text title("WYGRANA", font, 85);
    title.setStyle(sf::Text::Bold);
    title.setPosition(szerokosc_okna / 2 - title.getGlobalBounds().width / 2, 60);
    title.setFillColor(sf::Color::Black);
    const int ile = 3;
    sf::Text tekst[ile];
    std::string str[] = { "MENU","JESZCZE RAZ", "POZIOM 2" };
    for (int i = 0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);
        tekst[i].setString(str[i]);
        tekst[i].setPosition(szerokosc_okna / 2.f - tekst[i].getGlobalBounds().width / 2.f, 200.f + i * 100.f);
    }
    while (state == WYGRANA_1) { //state wygrana
        sf::Vector2f mouse(sf::Mouse::getPosition(*window));
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                state = KONIEC;
            }
           //menu
            if (tekst[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
            {
                state = MENU;
            }
            //jeszcze raz
            if ((tekst[1].getGlobalBounds().contains(mouse) &&
                 event.type == sf::Event::MouseButtonReleased &&
                 event.key.code == sf::Mouse::Left) ||
                 (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return))
            {
                state = GRA;
            }
            //poziom drugi
            if (tekst[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
            {
                state = GRA_2;
            }
}
        for (int i = 0; i<ile; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setFillColor(sf::Color::Cyan);
            else tekst[i].setFillColor(sf::Color::Black);

        update();
        window->clear();
        window->draw(sprite_tlo1);
        window->draw(title);
        window->draw(text);
        window->draw(tekst[0]);
        window->draw(tekst[1]);
        window->draw(tekst[2]);
        window->display();
    }
}
//*****************************************************************************************************************
void Gra::Wygrana_2(sf::RenderWindow *window) {
    window->setMouseCursorVisible(true);//pojawienie sie kursora
    sound4.play();
    sf::Text title("WYGRANA", font, 85);
    title.setStyle(sf::Text::Bold);
    title.setPosition(szerokosc_okna / 2 - title.getGlobalBounds().width / 2, 60);
    title.setFillColor(sf::Color::Black);
    const int ile = 2;
    sf::Text tekst[ile];
    std::string str[] = { "MENU","JESZCZE RAZ"};
    for (int i = 0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);
        tekst[i].setString(str[i]);
        tekst[i].setPosition(szerokosc_okna / 2.f - tekst[i].getGlobalBounds().width / 2.f, 200.f + i * 100.f);
    }
    while (state == WYGRANA_2) { //state wygrana
        sf::Vector2f mouse(sf::Mouse::getPosition(*window));
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                state = KONIEC;
            }
           //menu
            if (tekst[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
            {
                state = MENU;
            }
            //jeszcze raz
            if ((tekst[1].getGlobalBounds().contains(mouse) &&
                 event.type == sf::Event::MouseButtonReleased &&
                 event.key.code == sf::Mouse::Left) ||
                 (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return))
            {
                state = GRA;
            }
}
        for (int i = 0; i<ile; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setFillColor(sf::Color::Cyan);
            else tekst[i].setFillColor(sf::Color::Black);

        update();
        window->clear();
        window->draw(sprite_tlo1);
        window->draw(title);
        window->draw(text);
        window->draw(tekst[0]);
        window->draw(tekst[1]);
        window->display();
    }
}
//*****************************************************************************************************************
void Gra::Autor(sf::RenderWindow *window) {
    window->setMouseCursorVisible(true);
    sf::Text title("AUTOR:" , font, 65);
    title.setPosition(szerokosc_okna / 3 - title.getGlobalBounds().width, 10);
    title.setFillColor(sf::Color::Black);
    sf::Text autor("Pawel Bialoblocki", font, 65);
    autor.setPosition(szerokosc_okna / 3 - title.getGlobalBounds().width, 85);
    autor.setFillColor(sf::Color::Black);
    sf::Text numer_albumu("Nr albumu: 144562", font, 65);
    numer_albumu.setPosition(szerokosc_okna / 3 - title.getGlobalBounds().width, 160);
    numer_albumu.setFillColor(sf::Color::Black);
    const int ile = 2;
    sf::Text tekst[ile];//tablica
    std::string str[] = { "MENU","WYJDZ" };
    for (int i = 0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);
        tekst[i].setString(str[i]);
        tekst[i].setPosition(szerokosc_okna / 2.f - tekst[i].getGlobalBounds().width / 2.f, 350.f + i * 100.f);
    }
    while (state == AUTOR) { //state autor
        sf::Vector2f mouse(sf::Mouse::getPosition(*window));
        sf::Event event;

        while (window->pollEvent(event))
        {
            //koniec
            if (tekst[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
            {
                state = MENU;
            }
            //jeszcze raz
            if ((tekst[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) || (event.type == sf::Event::Closed))
            {
                state = KONIEC;
            }
        }

        for (int i = 0; i<ile; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setFillColor(sf::Color::Cyan);
            else tekst[i].setFillColor(sf::Color::Black);

        window->clear();
        window->draw(sprite_tlo1);
        window->draw(title);
        window->draw(text);
        window->draw(autor);
        window->draw(numer_albumu);
        window->draw(tekst[0]);
        window->draw(tekst[1]);
        window->display();
    }
}














