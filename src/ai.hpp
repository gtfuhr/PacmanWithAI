#pragma once
#include "init.hpp"

struct Ponto_Mapa
{
    int x, y;
};

enum cor_grafo
{
    BRANCO,
    CINZA,
    PRETO
};

struct Vertice
{
    int dist;
    Vertice *ant;
    Ponto_Mapa chave;
    cor_grafo cor;
    std::list<Vertice> arestas;
};
namespace ai
{
struct Ai
{
    void init_vertices(Block maze[][MAZE_SIDE_WIDTH]);
    void caminho_curto(Ponto_Mapa fonte, Ponto_Mapa destino);
    void busca_largura(Vertice *s);

  private:
    void init_arestas(Block maze[][MAZE_SIDE_WIDTH]);
    void init_aresta(Ponto_Mapa original, Ponto_Mapa nova_conexao);
    void init_vertex(int x, int j);
    void check_arestas(int x, int y);
    std::map<Ponto_Mapa, Vertice> grafo;
};
}; // namespace ai