#include "juego.h"
#include "palabra.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string.h>
#include "palabr.h"
#include "jugador.h"
#include <stdlib.h>
#include <time.h>
#include <thread>


using namespace std;
using namespace sf;

juego::juego()
{
    //ctor
    int x=800;
    int y=600;
    ventana = new RenderWindow(VideoMode(x,y),"Rain Words");
    ventana->setVerticalSyncEnabled(true);
    SoundBuffer buffer;
    buffer.loadFromFile("happy.wav");
    sound=new Sound;

    sound->setBuffer(buffer);
    sound->setVolume(30);
    SoundBuffer fin;
    fin.loadFromFile("fin.wav");

    fin1=new Sound;
    fin1->setBuffer(fin);

    SoundBuffer error;
    error.loadFromFile("error.wav");
    error1=new Sound;
    error1->setBuffer(error);

///   sound->play();

    SoundBuffer moneda;
    moneda.loadFromFile("moneda.wav");
    moneda1=new Sound;
    moneda1->setBuffer(moneda);
    textura1=new Texture;
    sprite1=new Sprite;
    texturabotonatras= new Texture;
    spritebotonatras=new Sprite;
    texturabotonatras->loadFromFile("botonatras.png");
    spritebotonatras->setTexture(*texturabotonatras);
    fuente=new Font;
    fuente->loadFromFile("calibri.ttf");
    vector_jugador= new jugador[6];
    creararchivo();
    puntajesmax();
    while(ventana->isOpen())
    {
        Event evento;
        textura1->loadFromFile("pantalla.png");
        sprite1->setTexture(*textura1);
        renderizar(3);
        int opcion;
        opcion=juego:: mainmenu();

        switch (opcion)
        {
        case 1:///arranca el juego
        {
            reiniciarvidas();
            int nume[50];
            srand(time(NULL));
            for(int x=0; x<20; x++)
            {
                nume[x] = 150 +( rand() % (600 -200));
            }
            iniciar();

            vpalabras= new Text[50];
            for(int x=0; x<50; x++)
            {
                vpalabras[x].setFont( *fuente );
                vpalabras[x].setStyle( sf::Text::Bold );
                vpalabras[x].setFillColor( sf::Color::Red );
                vpalabras[x].setOutlineColor(Color::White);
                vpalabras[x].setOutlineThickness(5);
                vpalabras[x].setCharacterSize( 30 );
                vpalabras[x].setPosition(nume[x],10 );
            }
            renderizar(2);
            gameloop();
           gameover();
            guardardatos();
        }
        break;
        case 2:
        {
puntajes();

        }
        break;
        case 3:
        {
            configuracion();

        }
        break;
        default:
            break;
        }

    }
}
void juego:: creararchivo()
{

    FILE *parch;

    parch=fopen("jugadores.dat","ab");

    if(parch==NULL)
    {
        cout<<"No se pudo abrir"<<endl;

    }
    fclose(parch);
}

void juego:: puntajesmax()
{
    FILE *parch;

    parch=fopen("jugadores.dat","rb+");

    if(parch==NULL)
    {
        cout<<"No se pudo abrir"<<endl;

    }
    jugador reg;

    for(int j=0; j<5; j++)
    {
        fread(&reg,sizeof reg, 1, parch);
        vector_jugador[j].setNombre(reg.getNombre());
        vector_jugador[j].setPuntaje(reg.getPuntaje());
    }
    fclose(parch);

}


void juego:: reiniciarvidas()
{
    vidas=3;
}
void juego:: palabraalaealtoria(char *cadenafinal)
{
    int cont=0;
    char cadena[20];
    int num;
    ifstream fe("palabras.txt");
    while (!fe.eof())
    {
        cont++;
        fe >> cadena;
    }
    fe.close();
    int m, n;
    m=cont;
    n=100;
    char **arreglo = new char*[m];
    for (int i = 0; i < m; i++)
    {
        arreglo[i] = new char[n];
    }
    ifstream de("palabras.txt");
    for (int i = 0; i < m; i++)
    {
        de >> arreglo[i];
    }
    num=rand()%cont;
    strcpy(cadenafinal,arreglo[num]);
    de.close();
    delete arreglo;
}


void juego::setvidas( )
{
    vidas--;
}


int juego::getvidas ()
{
    return vidas;
}

int juego::mainmenu()
{
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                ventana->close();
            }
            if(evento.type == sf::Event::MouseButtonPressed)
            {
                textura1->loadFromFile("segundapantalla.png");
                sprite1->setTexture(*textura1);
                menu= new Text[3];
                for(int i=0; i<3; i++)
                {
                    menu[i].setFont( *fuente );
                    menu[i].setStyle( sf::Text::Bold );
                    menu[i].setFillColor( sf::Color::Black );
                    menu[i].setCharacterSize( 48 );
                    menu[i].setPosition( 140, 20+100*i );
                }
                menu[0].setString( "Nuevo Juego" );
                menu[1].setString( "Puntajes" );
                menu[2].setString( "Configuracion" );
                renderizar(4);

                while (ventana->isOpen())
                {
                    while (ventana->pollEvent(evento))
                    {
                        switch ( evento.type )
                        {
                        case sf::Event::Closed:
                        {
                            ventana->close();
                        }
                        break;
                        case sf::Event::MouseMoved:

                        {

                            Vector2i mousePos = Mouse::getPosition( *ventana );
                            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                            for (int x=0; x<3; x++)
                            {
                                if ( menu[x].getGlobalBounds().contains( mousePosF ) )
                                {
                                    menu[x].setFillColor( sf::Color::Red);
                                    renderizar(4);
                                }
                            }
                            for(int i=0; i<3; i++)
                            {
                                menu[i].setFillColor( sf::Color::Black);
                            }
                            renderizar(4);

                        }
                        break;
                        case Event::MouseButtonPressed:
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition( *ventana );
                            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                            for (int x=0; x<3; x++)
                            {
                                if ( menu[x].getGlobalBounds().contains( mousePosF ) )
                                {
                                    return x+1;
                                }
                            }
                            break;

                        }
                        }

                    }
                }
            }
        }
    }
}
void juego::iniciar()
{
    int cont=0;
    textura1->loadFromFile("juegonuevo1.png");
    sprite1->setTexture(*textura1);
    renderizar(3);
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                ventana->close();

            }
            if(evento.type == sf::Event::MouseButtonPressed)
            {
                textura1->loadFromFile("juegonuevo2.png");
                sprite1->setTexture(*textura1);
                renderizar(3);
                char cadenafinal[20];
                int a=1;

                procesar_eventos2(cadenafinal, a, cont);
                j1=new jugador();
                j1->setNombre(cadenafinal);
                return;

            }

        }
    }
}
void juego:: gameloop()
{
    int devo=0;
    int cont=0;
    char cadenafinal[20];
    char ingresoteclado[20];
    Clock tiempo;
    while (ventana->isOpen())
    {
        if(getvidas()==0)
        {
            return;
        }

        Time   cronometro = tiempo.getElapsedTime();
        float sec  = cronometro.asSeconds();
        cout << sec<<endl;
        if(sec>3)
        {
            cont++;
            palabraalaealtoria( cadenafinal);
            vpalabras[cont].setString(cadenafinal);
            for(int i=0; i<cont; i++)
            {
                sf::Vector2f vec = vpalabras[i-1].getPosition();
                vpalabras[i-1].setPosition(vec.x,vec.y+50);
            }
            devo=colision(cont);
            cont=cont+devo;
            tiempo.restart();

        }
        renderizar(2,cont);
        procesar_eventos(ingresoteclado,2, cont);
        devo=procesar_logica(ingresoteclado, cont);
        cont=cont+devo;
        devo=colision(cont);
        cont=cont+devo;

    }
}
int juego:: colision(int cont)
{
    int guardari=0;


    sf::Vector2f vec = vpalabras[0].getPosition();
    if(vec.y>=430)
    {
        error1->play();
        setvidas();
        guardari++;
    }
    if(guardari!=0)
    {
        for(int j=0; j<cont; j++)
        {
            vpalabras[j]=vpalabras[j+1];
        }
        return -1;
    }
    return 0;
}


void juego::procesar_eventos( char *cadena, int a, int cont)

{
    std:: string aux;
    ingreso.setFont( *fuente );
    ingreso.setStyle( sf::Text::Bold );
    ingreso.setFillColor( sf::Color::Red);
    ingreso.setCharacterSize( 32 );
    ingreso.setPosition( 300, 480 );
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {

            if (evento.type == sf::Event::Closed|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                ventana->close();
                juego();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                aux=userInput;
                strcpy(cadena,aux.c_str());

                userInput="";

                return;
            }
            if(evento.type == sf::Event::TextEntered)
            {
                if (evento.text.unicode == 8)
                {
                    if (userInput.getSize())
                    {
                        userInput.erase(userInput.getSize() - 1, userInput.getSize());

                        ingreso.setString(userInput);
                        renderizar(a, cont);


                    }
                }
                else
                {
                    if(userInput.getSize() < 16)
                    {
                        userInput += (char)evento.text.unicode;
                        ingreso.setString(userInput);
                        renderizar(a, cont);

                    }
                }
            }
        }
        return;
    }
}
void juego::procesar_eventos2( char *cadena, int a, int cont)

{
    std:: string aux;
    ingreso.setFont( *fuente );
    ingreso.setStyle( sf::Text::Bold );
    ingreso.setFillColor( sf::Color::Red);
    ingreso.setCharacterSize( 32 );
    ingreso.setPosition( 300, 480 );
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {

            if (evento.type == sf::Event::Closed|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
               ventana->close();

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                aux=userInput;
                strcpy(cadena,aux.c_str());

                userInput="";

                return;
            }
            if(evento.type == sf::Event::TextEntered)
            {
                if (evento.text.unicode == 8)
                {
                    if (userInput.getSize())
                    {
                        userInput.erase(userInput.getSize() - 1, userInput.getSize());

                        ingreso.setString(userInput);
                        renderizar(a, cont);


                    }
                }
                else
                {
                    if(userInput.getSize() < 16)
                    {
                        userInput += (char)evento.text.unicode;
                        ingreso.setString(userInput);
                        renderizar(a, cont);

                    }
                }
            }
        }
    }
}


int  juego::procesar_logica(char *cadena, int cont)
{
    int guardari=-1;
    char aux[20];
    for(int i=0; i<cont; i++)
    {
        const string palabra=vpalabras[i].getString();
        strcpy(aux,palabra.c_str());
        int b=strlen(aux);
        if(strcmp(cadena,aux)== 0)
        {
            guardari=i;
            int suma;
            suma=2*b;
            j1->setPuntaje(suma);
            moneda1->play();

        }
        if(guardari!=-1)
        {
            for(int j=guardari; j<cont; j++)
            {
                vpalabras[j]=vpalabras[j+1];
            }
            return -1;
        }

    }
    return 0;
}
void juego:: gameover()
{
    renderizar(5);
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {
            if (evento.type ==  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {

                return;
            }



            while (ventana->isOpen())
            {
                while (ventana->pollEvent(evento))
                {

                } if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {

                    return;
                }
                switch ( evento.type )
                {

                case sf::Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( *ventana );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );


                    if ( spritebotonatras->getGlobalBounds().contains( mousePosF ) )
                    {
                        spritebotonatras->setColor(Color::Red);
                        renderizar(5);
                    }
                    else
                    {
                        spritebotonatras->setColor(Color::White);
                        renderizar(5);
                    }


                }
                break;
                case Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( *ventana );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    if(spritebotonatras->getGlobalBounds().contains(mousePosF))
                    {
                        return;
                    }

                }
                break;
                default:
                    break;
                }
            }

        }
    }

}
void juego:: puntajes()
{
renderizar(7);
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {
            if (evento.type ==  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {

                return;
            }



            while (ventana->isOpen())
            {
                while (ventana->pollEvent(evento))
                {

                } if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {

                    return;
                }
                switch ( evento.type )
                {

                case sf::Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( *ventana );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );


                    if ( spritebotonatras->getGlobalBounds().contains( mousePosF ) )
                    {
                        spritebotonatras->setColor(Color::Red);
                        renderizar(7);
                    }
                    else
                    {
                        spritebotonatras->setColor(Color::White);
                        renderizar(7);
                    }


                }
                break;
                case Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( *ventana );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    if(spritebotonatras->getGlobalBounds().contains(mousePosF))
                    {
                        return;
                    }

                }
                break;
                default:
                    break;
                }
            }

        }
    }

}

void juego:: configuracion()
{
    while (ventana->isOpen())
    {
        while (ventana->pollEvent(evento))
        {
            if (evento.type ==  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {

                return;
            }

            textura1->loadFromFile("configuracion.png");
            sprite1->setTexture(*textura1);
            textuimagenconfiguracion= new Texture[8];
            spriteimagenconfiguracion= new Sprite[8];
            textuimagenconfiguracion[0].loadFromFile("volumen.png");
            textuimagenconfiguracion[1].loadFromFile("volumen1.png");
            textuimagenconfiguracion[2].loadFromFile("volumen2.png");
            textuimagenconfiguracion[3].loadFromFile("volumen3.png");
            textuimagenconfiguracion[4].loadFromFile("volumen.png");
            textuimagenconfiguracion[5].loadFromFile("volumen1.png");
            textuimagenconfiguracion[6].loadFromFile("volumen2.png");
            textuimagenconfiguracion[7].loadFromFile("volumen3.png");

            int cima=0;

            for(int i=0; i<8; i++)
            {
                spriteimagenconfiguracion[i].setTexture(textuimagenconfiguracion[i]);
                if(i<4)
                {
                    spriteimagenconfiguracion[i].setPosition(170+120*i,117);
                }
                else
                {

                    spriteimagenconfiguracion[i].setPosition(170+120*cima,268);
                    cima++;
                }

            }

            renderizar(6);

            while (ventana->isOpen())
            {
                while (ventana->pollEvent(evento))
                {

                } if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {

                    return;
                }
                switch ( evento.type )
                {

                case sf::Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( *ventana );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    for (int x=0; x<8; x++)
                    {
                        if ( spriteimagenconfiguracion[x].getGlobalBounds().contains( mousePosF ) )
                        {
                            spriteimagenconfiguracion[x].setScale(1.2,1.2);

                            renderizar(6);
                        }
                    }
                    if ( spritebotonatras->getGlobalBounds().contains( mousePosF ) )
                    {
                        spritebotonatras->setColor(Color::Red);
                        renderizar(6);
                    }
                    for(int i=0; i<8; i++)
                    {
                        spriteimagenconfiguracion[i].setScale(1,1);
                        spritebotonatras->setColor(Color::White);
                    }
                    renderizar(6);

                }
                break;
                case Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( *ventana );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    for (int x=0; x<4; x++)
                    {
                        if ( spriteimagenconfiguracion[x].getGlobalBounds().contains( mousePosF ) )
                        {
                            sound->setVolume(1*x);
                            sound->play();
                        }
                    }
                    for (int x=4; x<8; x++)
                    {
                        if ( spriteimagenconfiguracion[x].getGlobalBounds().contains( mousePosF ) )
                        {
                            moneda1->setVolume(30*(x-4));
                            moneda1->play();

                        }
                    }
                    if(spritebotonatras->getGlobalBounds().contains(mousePosF))
                    {
                        return;
                    }

                }
                break;
                default:
                    break;
                }
            }

        }
    }
}




void juego::renderizar(int a, int cont)
{
    switch(a)
    {
    case 1:
    {
        ventana->clear();

        ventana->draw( *sprite1 );

        ventana->draw( ingreso );

        ventana->display();
    }
    break;
    case 2:
    {

        ventana->clear();
        textura1->loadFromFile("MODELO.png");
        sprite1->setTexture(*textura1);
        ventana->draw( *sprite1 );
        ventana->draw( ingreso );
        int vidasactual=getvidas();
        texturacorazon= new Texture[vidasactual];
        spritecorazon= new Sprite [vidasactual];
        for(int j=0; j<vidasactual; j++)
        {
            texturacorazon[j].loadFromFile("corazon1.png");
            spritecorazon[j].setPosition( 50, 120+50*j );
            spritecorazon[j].setTexture(texturacorazon[j]);

            ventana->draw(spritecorazon[j]);
        }
        for(int i=0; i<cont; i++)
        {
            ventana->draw(  vpalabras[i] );

        }

        /// Nombre
        Text nombre;
        nombre.setFont( *fuente );
        nombre.setStyle( sf::Text::Bold );
        nombre.setFillColor( sf::Color::Green );
        nombre.setCharacterSize( 30 );
        nombre.setPosition(350,530 );
        nombre.setString(j1->getNombre());

        ventana->draw (nombre);

        ///Puintaje
        Text puntajeactual;
        puntajeactual.setFont( *fuente );
        puntajeactual.setStyle( sf::Text::Bold );
        puntajeactual.setFillColor( sf::Color::Blue );
        puntajeactual.setCharacterSize( 30 );
        puntajeactual.setPosition(675,140 );
        puntajeactual.setString(to_string(j1->getPuntaje()));
        ventana->draw (puntajeactual);
        /// puntaje max
        Text puntajemax;
        puntajemax.setFont( *fuente );
        puntajemax.setStyle( sf::Text::Bold );
        puntajemax.setFillColor( sf::Color::Blue );
        puntajemax.setCharacterSize( 30 );
        puntajemax.setPosition(675,460 );

        puntajemax.setString(to_string(vector_jugador[0].getPuntaje()));

        ventana->draw (puntajemax);


        ventana->display();
    }
    break;
    case 3:
    {
        ventana->clear();
        ventana->draw(*sprite1);
        ventana->display();
    }
    break;
    case 4:
    {

        ventana->clear();
        ventana->draw(*sprite1);
        for(int x=0; x<3; x++)
        {
            ventana->draw( Text(menu[x]) );
        }
        ventana->display();
    }
    break;
    case 5:
    {
        ventana->clear();
        textura1->loadFromFile("GAMEOVER.png");
        sprite1->setTexture(*textura1);
        ventana->draw( *sprite1 );
        Text puntajeactual;
        puntajeactual.setFont( *fuente );
        puntajeactual.setStyle( sf::Text::Bold );
        puntajeactual.setFillColor( sf::Color::Blue );
        puntajeactual.setCharacterSize( 50 );
        puntajeactual.setPosition(300,250 );
        puntajeactual.setString(to_string(j1->getPuntaje()));
        ventana->draw(puntajeactual);
        Text nombre;
        nombre.setFont( *fuente );
        nombre.setStyle( sf::Text::Bold );
        nombre.setFillColor( sf::Color::Blue );
        nombre.setCharacterSize( 50 );
        nombre.setPosition(320,200 );
        nombre.setString(j1->getNombre());
        ventana->draw(nombre);
        fin1->play();
        ventana->draw(*spritebotonatras);
        ventana->display();
    }
    break;
    case 6:
    {
        ventana->clear();
        ventana->draw(*sprite1);
        for(int x=0; x<8; x++)
        {
            ventana->draw( Sprite(spriteimagenconfiguracion[x]) );
        }
        ventana->draw(*spritebotonatras);
        ventana->display();
    }
    break;
    case 7:
    {
        ventana->clear();
        textura1->loadFromFile("PUNTAJES.png");
        ventana->draw(*sprite1);
        puntaje= new Text[5];
        for(int x=0; x<5; x++)
        {
            puntaje[x].setFont( *fuente );
            puntaje[x].setStyle( sf::Text::Bold );
            puntaje[x].setFillColor( sf::Color::Cyan );
            puntaje[x].setCharacterSize( 30 );
            puntaje[x].setPosition(500,140+40*x);
            puntaje[x].setString(to_string(vector_jugador[x].getPuntaje()));
            ventana->draw(Text  (puntaje[x]) );
        }

        nombrepuntaje= new Text[5];
        for(int x=0; x<5; x++)
        {
            nombrepuntaje[x].setFont( *fuente );
            nombrepuntaje[x].setStyle( sf::Text::Bold );
            nombrepuntaje[x].setFillColor( sf::Color::Cyan);
            nombrepuntaje[x].setCharacterSize( 30 );
            nombrepuntaje[x].setPosition(200,140+40*x  );
            nombrepuntaje[x].setString(vector_jugador[x].getNombre());
            ventana->draw(Text (nombrepuntaje[x]));
        }
ventana->draw(*spritebotonatras);
 ventana->display();

    }
    break;
    }

}

void juego::guardardatos()
{
    vector_jugador[5].setNombre(j1->getNombre());
    vector_jugador[5].setPuntaje(j1->getPuntaje());

    class jugador aux;
    int i, j, posmin;
    for( i=0; i<6-1; i++)
    {
        posmin=i;
        for( j=i+1; j<6; j++)
        {
            if(vector_jugador[j].getPuntaje()>vector_jugador[posmin].getPuntaje())
                posmin=j;
        }

        aux=vector_jugador[i];
        vector_jugador[i]=vector_jugador[posmin];
        vector_jugador[posmin]=aux;
    }

    FILE *parch;
    parch=fopen("jugadores.dat","rb+");
    if(parch==NULL)
    {
        cout<<"No se pudo abrir"<<endl;

    }
    for(int x=0; x<5; x++)
    {
        fwrite(&vector_jugador[x], sizeof (jugador), 1,parch);
    }
    fclose(parch);
}
juego::~juego()
{
    //dtor
}

