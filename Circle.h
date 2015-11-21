#ifndef CIRCLE_H
#define CIRCLE_H


#include <math.h>
#include <GL/glut.h>
#include <memory>

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
        bool estaTocando(Circle c);
        void Draw(int flag = DRAW_2D, Textura *_textura = NULL);
    protected:
    private:
        int numeroDePontos;
        std::unique_ptr<OBJ> criaEsfera();
        void DrawEsfera();
};

#endif // CIRCLE_H
