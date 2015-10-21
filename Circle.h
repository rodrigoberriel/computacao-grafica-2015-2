#ifndef CIRCLE_H
#define CIRCLE_H


#include <math.h>
#include <GL/glut.h>

#include "EstruturasBasicas.h"

class Circle
{
    public:
        Circle();
        Circle(int _x, int _y, int _raio, Cor _cor);
        Ponto posicao;
        Cor cor;
        std::string id;
        int raio;

        bool estaDentro(Ponto p);
        void Draw();
    protected:
    private:
        int numeroDePontos;
};

#endif // CIRCLE_H
