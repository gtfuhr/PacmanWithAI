#pragma once
#include "init.hpp"
namespace physics
{
struct Physics
{
  void move_ghosts_2(std::list<Ghost> *ghosts);
  void verify_collision(Player *pacman, std::map<Ponto_Mapa, Vertice> grafo, Block maze[][MAZE_SIDE_LENGHT]);
  int pacman_score(Player *pacman, Block maze[][MAZE_SIDE_LENGHT], int score);
  void move_pacman(Player *pacman);
  void initPhy(int x, int y);

private:
  int pacmanMudouDeNo(Player *pacman);
  int number_of_rows;
  Ponto_Mapa localPac, bloco_antigo;
  bool moving;
};
}; // namespace physics
