#include "physics.hpp"
#include "ai.hpp"
#include "geom.hpp"
#include "tela.hpp"

#pragma once

#define BACKGROUND_LOSS_FILE "img/background_loss.png"
#define BACKGROUND_WIN_FILE "img/background_win.png"
#define BACKGROUND_FILE "img/background.gif"
#define BLOCO_FILE "img/block.png"
#define PACMAN_FILE "img/pacman.bmp"

using namespace tela;
using namespace geom;

#define MAZE_SIDE_LENGHT 36
#define MAZE_SIDE_WIDTH 56

enum State
{
    nothing,
    end,
    pause_s
};

enum BlockTypes
{
    path,
    point,
    bonus,
    wall,
    portal
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
};

struct Ghost
{
    Ponto pos;
    Cor color;
};