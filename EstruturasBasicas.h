#ifndef ESTRUTURASBASICAS_H
#define ESTRUTURASBASICAS_H


#include <string>
#include <cstring>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "imageloader.h"

enum {
    EM_ANDAMENTO,
    GANHOU,
    PERDEU,
    PAUSADO
};

enum {
    DRAW_2D,
    DRAW_3D
 };

class Ponto
{
    public:
        Ponto();
        Ponto(float _x, float _y, float _z = 0) : x(_x), y(_y), z(_z) {};
        void print();
        GLfloat x;
        GLfloat y;
        GLfloat z;
    protected:
    private:
};

class Cor
{
	public:
        Cor();
        Cor(std::string color_name);
        Cor(int _r, int _g, int _b);
        GLfloat r;
        GLfloat g;
        GLfloat b;
        inline bool operator==(const Cor& c){ return (this->r == c.r && this->g == c.g && this->b == c.b); }
    protected:
    private:
};

class Textura
{
    public:
        Textura();
        Textura(std::string texture_name);
        GLuint get() { return this->t; };
    private:
        GLuint LoadTextureRAW(const char * filename);
        GLuint t;
};

double calculaDistancia(Ponto p1, Ponto p2);


#endif // ESTRUTURASBASICAS_H
