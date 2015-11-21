#ifndef RECT_H
#define RECT_H


#include <vector>
#include <GL/glut.h>
#include <cmath>

#include "EstruturasBasicas.h"

class Rect
{
    public:
        Rect();
        Rect(int _x, int _y, int _largura, int _altura, Cor _cor = Cor("white"));
        Ponto posicao;
        Cor cor;
        std::string id;
        int altura;
        int largura;
        int strokeLargura;
        Cor strokeCor;
        Textura textura;
        int fatorRepeticaoTextura = 10;

        bool estaDentro(Ponto p);
        void Draw(int flag = DRAW_2D, Textura *_textura = NULL, bool drawStroke = NO_STROKE);
        void DrawArestas();
        static void DrawCubo(Rect *r, float profundidade, float textureS = 1);
    protected:
    private:
        std::vector<Ponto> getVertices();


};

#endif // RECT_H
