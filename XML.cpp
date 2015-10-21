#include "XML.h"

using namespace std;
using namespace tinyxml2;

XML::XML(const std::string path, const std::string filename)
{
    // carrega o XML
    XMLError error = this->doc.LoadFile ((path + filename).c_str());

    // verifica se houve erro
	this->isLoaded = (error == XML_NO_ERROR);
}

std::string XML::getArenaPath()
{
    string arenaPath;

    // pega o caminho para o arquivo da arena
    XMLElement* aplicacao = this->doc.FirstChildElement();
    XMLElement* arquivosDeEntrada = aplicacao->FirstChildElement("arquivosDeEntrada");
    XMLElement* arquivoDaArena = arquivosDeEntrada->FirstChildElement("arquivoDaArena");

    string nome = arquivoDaArena->Attribute("nome");
    string tipo = arquivoDaArena->Attribute("tipo");
    string caminho = arquivoDaArena->Attribute("caminho");

    arenaPath = caminho + nome + "." + tipo;
    return arenaPath;
}

double XML::getVelocidadeTiro()
{
    // pega a velocidade do tiro
    XMLElement* aplicacao = this->doc.FirstChildElement();
    XMLElement* helicoptero = aplicacao->FirstChildElement("helicoptero");
    return helicoptero->DoubleAttribute("velTiro");
}

double XML::getVelocidadeHelicoptero()
{
    // pega a velocidade do helicoptero
    XMLElement* aplicacao = this->doc.FirstChildElement();
    XMLElement* helicoptero = aplicacao->FirstChildElement("helicoptero");
    return helicoptero->DoubleAttribute("velHelicoptero");
}

double XML::getTempoDeVoo()
{
    // pega o tempo de voo
    XMLElement* aplicacao = this->doc.FirstChildElement();
    XMLElement* helicoptero = aplicacao->FirstChildElement("helicoptero");
    return helicoptero->DoubleAttribute("tempoDeVoo");
}

double XML::getVelocidadeHelicopteroInimigo()
{
    // pega a velocidade do helicoptero inimigo
    XMLElement* aplicacao = this->doc.FirstChildElement();
    XMLElement* helicopteroInimigo = aplicacao->FirstChildElement("helicopteroInimigo");
    return helicopteroInimigo->DoubleAttribute("velHelicoptero");
}

double XML::getFrequenciaTiroInimigo()
{
    // pega a velocidade do helicoptero inimigo
    XMLElement* aplicacao = this->doc.FirstChildElement();
    XMLElement* helicopteroInimigo = aplicacao->FirstChildElement("helicopteroInimigo");
    return helicopteroInimigo->DoubleAttribute("freqTiro");
}
