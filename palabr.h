#ifndef PALABR_H_INCLUDED
#define PALABR_H_INCLUDED

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
#include <clocale>
#include <ctype.h>
#include <wchar.h>

using namespace std;

void funpal(char *cadenafinal)
{int cont=0,num;
char cadena[20];

    ifstream fe("palabras.txt");
    srand(time(NULL));while (!fe.eof())
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
    cout<<num<<endl;
strcpy(cadenafinal,arreglo[num]);
    de.close();
    delete arreglo;
cout<<cadenafinal<<"aca";

}

#endif // PALABR_H_INCLUDED
