#ifndef RECT_H
#define RECT_H


#include <vector>
#include <GL/glut.h>

#include "EstruturasBasicas.h"

class Rect
{
    public:
        Rect();
        Rect(int _x, int _y, int _largura, int _altura, Cor _cor);
        Ponto posicao;
        Cor cor;
        std::string id;
        int altura;
        int largura;
        int strokeLargura;
        Cor strokeCor;
        Textura textura;

        bool estaDentro(Ponto p);
        void Draw(int flag = DRAW_2D, bool drawStroke = NO_STROKE);
    protected:
    private:
        std::vector<Ponto> getVertices();


};

#endif // RECT_H
