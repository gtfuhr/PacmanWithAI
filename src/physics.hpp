#pragma once
#include "init.hpp"
namespace physics
{
struct Physics
{
    void move_ghosts_2(std::list<Ghost> *ghosts);
    void verify_colision(void);
    void move_pacman(Player *pacman);
};
}; // namespace physics
