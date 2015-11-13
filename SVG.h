#ifndef SVG_H
#define SVG_H

#include <iostream>
#include <string>
#include <time.h>
#include "tinyxml2.h"

#include "Arena.h"
#include "EstruturasBasicas.h"
#include "Rect.h"
#include "Circle.h"

class SVG
{
    public:
        SVG(const std::string path);
        bool isLoaded;
        Arena getArena(double _velTiro, double _velHelicoptero, double _tempoDeVoo, double _velInimigo, double _freqTiro);
    protected:
    private:
        tinyxml2::XMLDocument svg;
        std::vector<Rect> getRects();
        std::vector<Circle> getCircles();
};

#endif // SVG_H
