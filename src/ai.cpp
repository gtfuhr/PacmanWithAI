#include "ai.hpp"
#include <list>
#include <map>
#include <queue>
//Ja que o Ponto_mapa é usado como uma chave do Map, ele precisa ter uma forma de comparacao
inline bool operator<(const Ponto_Mapa &a, const Ponto_Mapa &b)
{
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}
namespace ai
{

void Ai::initContainsPacman(int x, int y)
{
    Ponto_Mapa localPacman = {x, y};
    grafo[localPacman].containsPacman = true;
}

void Ai::init_vertex(int x, int y)
{
    Ponto_Mapa vertice = {x, y};
    grafo[vertice] = Vertice();
    grafo[vertice].dist = 0;
    grafo[vertice].chave = vertice;
}
void Ai::init_vertices(Block maze[][MAZE_SIDE_LENGHT])
{
    for (int y = 0; y < MAZE_SIDE_LENGHT; y++)
        for (int x = 0; x < MAZE_SIDE_WIDTH; x++)
        {
            if (maze[x][y].type == BlockTypes::path)
                init_vertex(x, y);
            else if (maze[x][y].type == BlockTypes::intersection)
                init_vertex(x, y);
        }
    init_arestas(maze);
}

void Ai::init_aresta(Ponto_Mapa original, Ponto_Mapa nova_conexao)
{
    grafo[original].arestas.push_back(grafo[nova_conexao]);
}

void Ai::check_arestas(int x, int y)
{
    Ponto_Mapa centro = {x, y},
               cima = {x, y + 1},
               baixo = {x, y - 1},
               esquerda = {x - 1, y},
               direita = {x + 1, y};

    auto it_cima = grafo.find(cima),
         it_baixo = grafo.find(baixo),
         it_esquerda = grafo.find(esquerda),
         it_direita = grafo.find(direita),
         it_end = grafo.end();

    if (it_cima != it_end)
        init_aresta(centro, cima);

    if (it_baixo != it_end)
        init_aresta(centro, baixo);

    if (it_direita != it_end)
        init_aresta(centro, direita);

    if (it_esquerda != it_end)
        init_aresta(centro, esquerda);
}
void Ai::init_arestas(Block maze[][MAZE_SIDE_LENGHT])
{
    Ponto_Mapa atual;
    for (int y = 0; y < MAZE_SIDE_LENGHT; y++)
        for (int x = 0; x < MAZE_SIDE_WIDTH; x++)
        {
            atual = {x, y};
            auto it = grafo.find(atual);
            if (it != grafo.end())
                check_arestas(x, y);
        }
}

// recebe o grafo, o vertice de fonte 's'
void Ai::busca_largura(Vertice *s)
{
    std::queue<Vertice> f;
    for (auto it = grafo.begin(); it != grafo.end(); ++it)
        it->second.cor = cor_grafo::BRANCO;
    f.emplace(*s);
    while (!f.empty())
    {
        Vertice u = f.front();
        f.pop();
        for (auto &v : u.arestas)
        {
            if (v.cor == cor_grafo::BRANCO)
            {
                v.cor = cor_grafo::CINZA;
                v.dist = u.dist + 1;
                v.ant = &u;
                f.emplace(v);
            }
        }
        u.cor = cor_grafo::PRETO;
    }
}
void Ai::caminho_curto(Ponto_Mapa fonte, Ponto_Mapa destino)
{
    Vertice *s = &(grafo[fonte]);
    Vertice *v = &(grafo[destino]);
    if (s == v)
    {
        printf("(%d,%d) ", s->chave.x, s->chave.y);
        return;
    }
    if (v->ant == NULL)
    {
        printf("Nao existe caminho de (%d,%d) a (%d,%d)\n", s->chave.x, s->chave.y, v->chave.x, v->chave.y);
    }
    else
    {
        caminho_curto(fonte, v->ant->chave);
        printf("(%d,%d) ", v->chave.x, v->chave.y);
    }
}

}; // namespace ai