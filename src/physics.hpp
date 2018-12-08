#pragma once
#include "init.hpp"
namespace physics
{
struct Physics
{
    void move_ghosts_2(std::list<Ghost> *ghosts);
    void verify_collision(Player *pacman, Block maze[MAZE_SIDE_WIDTH][MAZE_SIDE_LENGHT]);
    void move_pacman(Player *pacman);
    void initPhy(void);

  private:
    int PacmanMudouCol(int x, int y);
    int number_of_rows;
    Ponto_Mapa bloco_antigo;
};
}; // namespace physics
