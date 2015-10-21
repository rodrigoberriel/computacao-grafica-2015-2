#include "EstruturasBasicas.h"

using namespace std;

Ponto::Ponto()
{
}

Cor::Cor()
{
}

Cor::Cor(std::string color_name)
{
    // padrão é a cor preta
    this->r = 0;
    this->g = 0;
    this->b = 0;

    // preenche caso seja outra cor
    if (color_name == "white") {
        this->r = this->g = this->b = 255.0;
    } else if (color_name == "gray") {
        this->r = this->g = this->b = 127.0;
    } else if (color_name == "lightgray") {
        this->r = this->g = this->b = 210.0;
    } else if (color_name == "green") {
        this->g = 255.0;
    } else if (color_name == "red") {
        this->r = 255.0;
    } else if (color_name == "blue") {
        this->b = 255.0;
    } else if (color_name == "lightgreen") {
        this->r = 155.0;
        this->g = 187.0;
        this->b = 89.0;
    } else if (color_name == "darkgreen") {
        this->r = 99.0;
        this->g = 169.0;
        this->b = 117.0;
    } else if (color_name == "lightblue") {
        this->r = 79.0;
        this->g = 129.0;
        this->b = 189.0;
    } else if (color_name == "darkred") {
        this->r = 170;
        this->g = 0.0;
        this->b = 0.0;
    }

    // normaliza para o intervalo [0,1]
    this->r /= 255.0;
    this->g /= 255.0;
    this->b /= 255.0;
}

Cor::Cor(int _r, int _g, int _b)
{
    this->r = (float)_r/255.0;
    this->g = (float)_g/255.0;
    this->b = (float)_b/255.0;
}

double calculaDistancia(Ponto p1, Ponto p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
