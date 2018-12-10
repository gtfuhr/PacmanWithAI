#pragma once

#define SCREEN_WIDTH 490
#define SCREEN_LENGTH 630
#define MAZE_SIDE_LENGHT 37
#define MAZE_SIDE_WIDTH 29
#define MAZE_WALL_WIDTH 15
#define MAZE_WALL_LENGHT 15
#define MOLDURE 30
#define MAX_NUM_OF_BONUS 12
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
    win,
    end,
    defeat,
    pause_state
};

enum BlockTypes
{
    path,
    intersection,
    wall,
    portal,
};

enum cor_grafo
{
    BRANCO,
    CINZA,
    PRETO
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

struct Ponto_Mapa
{
    int x, y;
};

struct Ghost
{
    Circulo cir;
    Ponto_Mapa pos_coord;
    int moving, move_x, move_y;
    std::list<Ponto_Mapa> caminho;
    float speed;
    Cor color;
};

struct Vertice
{
    int dist;
    Vertice *ant;
    Ponto_Mapa chave;
    bool containsPacman;
    cor_grafo cor;
    std::list<Vertice *> arestas;
};

#include "physics.hpp"
#include "ai.hpp"
#include "geom.hpp"
#include "draw.hpp"