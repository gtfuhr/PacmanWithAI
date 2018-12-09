#pragma once
#include "init.hpp"

namespace ai
{
struct Ai
{
    void init_vertices(Block maze[][MAZE_SIDE_LENGHT]);
    void caminho_curto(Ponto_Mapa fonte, Ponto_Mapa destino);
    void busca_largura(Vertice *s);
    std::map<Ponto_Mapa, Vertice> grafo;
    void initContainsPacman(int x, int y);

  private:
    void init_arestas(Block maze[][MAZE_SIDE_LENGHT]);
    void init_aresta(Ponto_Mapa original, Ponto_Mapa nova_conexao);
    void init_vertex(int x, int j);
    void check_arestas(int x, int y);
};
}; // namespace ai