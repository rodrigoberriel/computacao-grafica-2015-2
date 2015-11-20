#include "EstruturasBasicas.h"

using namespace std;

Ponto::Ponto()
{
}

void Ponto::print()
{
    cout << "Ponto: " << x << ", " << y << ", " << z << endl;
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
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
}

Textura::Textura()
{
}

Textura::Textura(std::string texture_name)
{
    string arquivo = "images/" + texture_name;
    this->t = this->LoadTextureRAW(arquivo.c_str());
}

GLuint Textura::LoadTextureRAW(const char * filename)
{

    GLuint texture;

    Image* image = loadBMP(filename);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                             0,                            //0 for now
                             GL_RGB,                       //Format OpenGL uses for image
                             image->width, image->height,  //Width and height
                             0,                            //The border of the image
                             GL_RGB, //GL_RGB, because pixels are stored in RGB format
                             GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
                             image->pixels);               //The actual pixel data
    delete image;

    return texture;
}

void drawBox(GLfloat tamanho, GLfloat textureS)
{
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -tamanho / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = tamanho / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -tamanho / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = tamanho / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -tamanho / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = tamanho / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f (textureS, 0);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f (textureS, textureS);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f (0, textureS);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f (0, 0);
            glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}
