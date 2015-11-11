#include "Arena.h"

using namespace std;

#define NUMERO_DE_MARCADORES_COMBUSTIVEL 5

Arena::Arena()
{
    this->statusPartida = EM_ANDAMENTO;
}

void Arena::Draw()
{
    mapa.cor = Cor("lightgray");
    mapa.Draw();
    postoAbastecimento.Draw();
    for (Circle c : objetosResgate) c.Draw();
    for (Tiro t : tiros) t.Draw();
    for (Helicoptero h : inimigos) h.Draw(DRAW_3D);
    jogador.Draw(DRAW_3D);
    jogador.desenharCombustivel(10, mapa.altura - 10, NUMERO_DE_MARCADORES_COMBUSTIVEL);
    jogador.desenharResgates(mapa.largura - 10, mapa.altura - 10, nObjetos);

    if (statusPartida != EM_ANDAMENTO) mostrarMensagem();
}

void Arena::mostrarMensagem()
{
    const char * mensagem = (statusPartida == GANHOU) ? "GANHOU!" : "PERDEU!";
    Cor _cor = (statusPartida == GANHOU) ? Cor("blue") : Cor("darkred");

    glPushMatrix();
        glColor3f(_cor.r, _cor.g, _cor.b);
        glRasterPos2f((mapa.largura/2.0) - (75.0/2.0), (mapa.altura/2.0) - (14.0 / 2.0));
        for (unsigned int i = 0; i < strlen(mensagem); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mensagem[i]);
        }
    glPopMatrix();
}

void Arena::MostraDados()
{
    cout << "A arena foi criada com:" << endl;
    cout << " - " << ((mapa.id == "Arena") ? 1 : 0) << " mapa" << endl;
    cout << " - " << ((postoAbastecimento.id == "PostoAbastecimento") ? 1 : 0) << " posto de abastecimento" << endl;
    cout << " - " << ((jogador.area.id == "Jogador") ? 1 : 0) << " jogador" << endl;
    cout << " - " << (inimigos.size()) << " inimigo(s)" << endl;
    cout << " - " << (objetosResgate.size()) << " objeto(s) de resgate" << endl << endl;
}

void Arena::ImprimeElemento(Cor corElemento)
{
    for (auto i : this->mapaCorID) {
        if (i.second == corElemento) cout << "Voce clicou em '" << i.first << "'!" << endl;
    }
}
