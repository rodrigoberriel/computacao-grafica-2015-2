#ifndef CIRCLE_H
#define CIRCLE_H


#include <math.h>
#include <GL/glut.h>

#include "EstruturasBasicas.h"

class Circle
{
    public:
        Circle();
        Circle(Ponto posicao, int _raio, Cor _cor);
        Ponto posicao;
        Cor cor;
        std::string id;
        int raio;
        Textura textura;

        bool estaDentro(Ponto p);
        void Draw(int flag = DRAW_2D);
    protected:
    private:
        int numeroDePontos;
        OBJ* criaEsfera();
        void DrawEsfera();
};

#endif // CIRCLE_H
