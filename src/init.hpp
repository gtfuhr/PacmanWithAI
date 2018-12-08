#pragma once

#define SCREEN_WIDTH 490
#define SCREEN_LENGTH 630
#define MAZE_SIDE_LENGHT 37
#define MAZE_SIDE_WIDTH 29
#define MAZE_WALL_WIDTH 15
#define MAZE_WALL_LENGHT 15
#define MOLDURE 30
#define MAX_NUM_OF_BONUS 4
#define PACMAN_RADIUS 7

#include "tela.hpp"

using namespace tela;
using namespace geom;
#include <iostream>
#include <list>
#include <map>

#define BACKGROUND_LOSS_FILE "img/background_loss.png"
#define BACKGROUND_WIN_FILE "img/background_win.png"
#define BACKGROUND_FILE "img/background.gif"
#define BLOCO_FILE "img/block.png"
#define PACMAN_FILE "img/pacman.bmp"
#define MAZE_FILE "data/maze.txt"

enum State
{
    menu,
    nothing,
    score,
    playing,
    end,
    pause_state
};

enum BlockTypes
{
    path,
    intersection,
    wall,
};

struct Block
{
    BlockTypes type;
    bool hasPoint;
    bool hasBonus;
};

struct Player
{
    Circulo cir;
    State state;
    Cor color;
    float speed;
    int move_x, move_y;
    int key; // Last key pressed by the user
    int option, score;
    time_t time;
};

struct Scores
{
    std::string *names;
    int *points;
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

struct Ponto_Mapa
{
    int x, y;
};

#include "physics.hpp"
#include "ai.hpp"
#include "geom.hpp"
#include "draw.hpp"