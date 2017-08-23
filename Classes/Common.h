#pragma once
#include "cocos2d.h"
#include "GameStage.h"
USING_NS_CC;

//게임 화면
#define GAME_WIDTH 640
#define GAME_HEIGHT 360

//플레이어 공통
#define PLAYERSIZE_RADIUS 75		//넉넉하게 잡음.
#define HEATBOX_RADIUS 5

//레이무
#define REIMU_WIDTH 94
#define REIMU_HEIGHT 102
#define REIMU_FRAMES 11

//마리사
#define MARISA_WIDTH 55
#define MARISA_HEIGHT 100
#define MARISA_FRAMES 10

#define MARISA_SHOT_WIDTH 30
#define MARISA_SHOT_HEIGHT 28

//적군
#define ENEMY_TYPE1_WIDTH 30
#define ENEMY_TYPE1_HEIGHT 29
#define ENEMY_TYPE1_FRAMES 4

//총알
#define BULLET_TYPE0_WIDTH 16
#define BULLET_TYPE0_HEIGHT 16
#define BULLET_TYPE0_STYLES 16
#define BULLET_TYPE0_COLLISION_RADIUS 3.f

#define BULLET_TYPE1_WIDTH 16
#define BULLET_TYPE1_HEIGHT 16
#define BULLET_TYPE1_STYLES 16
#define BULLET_TYPE1_COLLISION_RADIUS 3.f

//게임스테이지 신
extern GameStage * g_pGameStage;