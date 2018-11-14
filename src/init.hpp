#pragma once
#include "physics.hpp"
#include "ai.hpp"
#include "geom.hpp"
#include "tela.hpp"
#include "draw.hpp"
using namespace tela;
using namespace geom;

#include <iostream>

#define BACKGROUND_LOSS_FILE "img/background_loss.png"
#define BACKGROUND_WIN_FILE "img/background_win.png"
#define BACKGROUND_FILE "img/background.gif"
#define BLOCO_FILE "img/block.png"
#define PACMAN_FILE "img/pacman.bmp"
#define MAZE_FILE "data/maze.txt"

#define SCREEN_WIDTH 490
#define SCREEN_LENGTH 630
#define MAZE_SIDE_LENGHT 37
#define MAZE_SIDE_WIDTH 29
#define MAZE_WALL_WIDTH 15
#define MAZE_WALL_LENGHT 15
#define MOLDURE 30

enum State
{
    nothing,
    end,
    pause_s
};

enum BlockTypes
{
    vertical,
    horizontal,
    crossing,
    wall,
    spawn,
};

struct Block
{
    BlockTypes type;
};

struct Player
{
    Ponto pos;
    State state;
    Cor color;
    int key; // Last key pressed by the user
};

struct Pacman
{
    Cor color;
    Circulo circle;
};

struct Ghost
{
    Ponto pos;
    Cor color;
};
