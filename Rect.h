#ifndef RECT_H
#define RECT_H


#include <vector>
#include <GL/glut.h>

#include "EstruturasBasicas.h"

enum {
    WITH_STROKE = true,
    NO_STROKE = false
};

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

        bool estaDentro(Ponto p);
        void Draw(bool drawStroke = NO_STROKE);
    protected:
    private:
        std::vector<Ponto> getVertices();

};

#endif // RECT_H
