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
  void win_condition(Player *player, Block maze[][MAZE_SIDE_LENGHT]);
  void defeat_condition(Player *player, std::list<Ghost> *ghosts);
  double distancia2d(Ponto p1, Ponto p2);
  int ghostMudouDeNo(Ghost *ghost);
  void initPhy(int x, int y);
  Ponto_Mapa get_local_pac(void);

private:
  int block_contain_pacman(int x, int y, Player pacman);
  int block_contain_ghost(int x, int y, Ghost *ghost);
  int pacmanMudouDeNo(Player *pacman);
  int number_of_rows;
  Ponto_Mapa localPac, bloco_antigo;
  bool moving;
};
}; // namespace physics
