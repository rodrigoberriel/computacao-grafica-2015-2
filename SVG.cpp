#include "SVG.h"

using namespace std;
using namespace tinyxml2;

SVG::SVG(const string path)
{
    // carrega o SVG
    XMLError error = this->svg.LoadFile(path.c_str());

    // verifica se houve erro
	this->isLoaded = (error == XML_NO_ERROR);
}


Arena SVG::getArena(double _velTiro, double _velHelicoptero, double _tempoDeVoo, double _velInimigo, double _freqTiro)
{
    Arena arena;

    // declara os elementos da arena
    Rect mapa;
    Rect postoAbastecimento;
    Circle areaJogador;
    vector<Circle> areaInimigos;
    vector<Circle> objetosResgate;

    // pega os 'rect'
    vector<Rect> rects = this->getRects();
    for (Rect r : rects) {
        arena.mapaCorID[r.id] = r.cor;
        if (r.id == "Arena") mapa = r;
        else if (r.id == "PostoAbastecimento") postoAbastecimento = r;
    }

    // pega os 'circle'
    vector<Circle> circles = this->getCircles();
    for (Circle c : circles) {
        arena.mapaCorID[c.id] = c.cor;
        if (c.id == "Jogador") areaJogador = c;
        else if (c.id == "Inimigo") areaInimigos.push_back(c);
        else if (c.id == "ObjetoResgate") objetosResgate.push_back(c);
    }

    // monta a arena
    arena.mapa = mapa;
    arena.postoAbastecimento = postoAbastecimento;
    arena.objetosResgate = objetosResgate;

    areaJogador.posicao.z = ALTURA_HELICOPTERO / 2.0;
    arena.jogador.area = areaJogador;
    arena.jogador.id = areaJogador.id;
    arena.jogador.velocidadeHelicoptero = _velHelicoptero;
    arena.jogador.velocidadeTiro = _velTiro;
    arena.jogador.tempoMaximoDeVoo = _tempoDeVoo;
    arena.jogador.corCorpo = Cor("lightgreen");

    srand(time(NULL));

    for (Circle areaInimigo : areaInimigos) {
        Helicoptero inimigo;
        areaInimigo.posicao.z = ALTURA_HELICOPTERO + (rand() % ((areaJogador.raio * 5) - ALTURA_HELICOPTERO * 2));
        inimigo.area = areaInimigo;
        inimigo.id = areaInimigo.id;
        inimigo.velocidadeHelicoptero = _velInimigo;
        inimigo.velocidadeTiro = _velTiro;
        inimigo.decolar(); // inimigos começam voando
        arena.inimigos.push_back(inimigo);
    }

    arena.nObjetos = arena.objetosResgate.size();
    arena.nInimigos = arena.inimigos.size();
    arena.frequenciaTiro = _freqTiro;

    return arena;

}


vector<Rect> SVG::getRects()
{
    vector<Rect> rects;
    XMLElement* arenaSVG = this->svg.FirstChildElement();

    // pega os 'rect'
    for (XMLElement* rect = arenaSVG->FirstChildElement("rect"); rect != NULL; rect = rect->NextSiblingElement("rect"))
    {
        Rect r;
        int _x, _y;
        rect->QueryIntAttribute("x", &_x);
        rect->QueryIntAttribute("y", &_y);
        rect->QueryIntAttribute("width", &r.largura);
        rect->QueryIntAttribute("height", &r.altura);
        r.cor = Cor(rect->Attribute("fill"));
        if (rect->Attribute("stroke-width")) rect->QueryIntAttribute("stroke-width", &r.strokeLargura);
        if (rect->Attribute("stroke")) r.strokeCor = Cor(rect->Attribute("stroke"));
        r.id = rect->Attribute("id");
        r.posicao.x = _x;
        r.posicao.y = _y;
        rects.push_back(r);
    }

    return rects;
}


vector<Circle> SVG::getCircles()
{
    vector<Circle> circles;
    XMLElement* arenaSVG = this->svg.FirstChildElement();

    // pega os 'rect'
    for (XMLElement* circle = arenaSVG->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle"))
    {
        Circle c;
        int _x, _y;
        circle->QueryIntAttribute("cx", &_x);
        circle->QueryIntAttribute("cy", &_y);
        circle->QueryIntAttribute("r", &c.raio);
        c.cor = Cor(circle->Attribute("fill"));
        c.id = circle->Attribute("id");
        c.posicao.x = _x;
        c.posicao.y = _y;
        circles.push_back(c);
    }

    return circles;
}
