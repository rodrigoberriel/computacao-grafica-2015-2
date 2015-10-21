#ifndef ESTRUTURASBASICAS_H
#define ESTRUTURASBASICAS_H


#include <string>
#include <cstring>
#include <math.h>
#include <GL/glut.h>

enum {
    EM_ANDAMENTO,
    GANHOU,
    PERDEU
};

class Ponto
{
    public:
        Ponto();
        Ponto(float _x, float _y) : x(_x), y(_y) {};
        GLfloat x;
        GLfloat y;
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

double calculaDistancia(Ponto p1, Ponto p2);

#endif // ESTRUTURASBASICAS_H
