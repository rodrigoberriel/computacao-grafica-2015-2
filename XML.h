#ifndef XML_H
#define XML_H

#include <iostream>
#include <string>
#include "tinyxml2.h"

class XML
{
    public:
        XML(const std::string path, const std::string filename="config.xml");
        bool isLoaded;
        std::string getArenaPath();
        double getVelocidadeTiro();
        double getVelocidadeHelicoptero();
        double getVelocidadeHelicopteroInimigo();
        double getFrequenciaTiroInimigo();
        double getTempoDeVoo();
    protected:
    private:
        tinyxml2::XMLDocument doc;
};

#endif // XML_H
