#pragma once
#include "init.hpp"
namespace physics
{
struct Physics
{
    void move_ghosts_2(std::list<Ghost> *ghosts);
    void verify_collision(Player *pacman, Block maze[MAZE_SIDE_LENGHT][MAZE_SIDE_WIDTH]);
    void move_pacman(Player *pacman);
};
}; // namespace physics
