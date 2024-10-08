//game.h
#pragma once
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "bullet.h"
constexpr uint16_t gameWidth = 850;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;

extern sf::Texture spritesheet;
extern std::vector<Ship*> ships;
static std::vector<Bullet*> bullets;
