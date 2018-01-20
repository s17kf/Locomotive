#pragma once

#ifndef MYCONST_H
#define MYCONST_H

#include <iostream>
#include <vector>

const float SPEED_MULTTIPLIER = 3.5;
const unsigned int WHEEL_PIECES = 24;
const unsigned int WHEELS_COUNT = 4;
const float WHEEL_WIDTH = 0.12;
const float WHEEL_RADIUS = 0.3;

const float LOC_WIDTH = 1.2;
const float LOC_HEIGHT = 0.3;
const float LOC_LENGTH = 2.5;

const float START_X = 0;
const float START_Y = (LOC_HEIGHT - WHEEL_RADIUS) / 2 + WHEEL_RADIUS;
const float START_Z = 0;

const unsigned int BALKS_COUNT = 2;
const float BALK_WIDTH = 0.05;
const float BALK_HEIGHT = 0.05;

const std::string BODY_TEX_NAME = "deska.png";
const std::string WHEEL_TEX_NAME1 = "kolo.jpg";
const std::string WHEEL_TEX_NAME2 = "black.jpg";
const std::string BALK_TEX_NAME = "silver.jpg";
const std::vector<std::string> WALLS_TEX_NAMES{ "right.jpg","left.jpg","top.jpg","bottom.jpg","back.jpg","front.jpg" };



/*
* textCoord: {front side, back side, left, right, bottom, top side}
* for each side has 4 values: x-start, x-end, y-s. and y-e. ==> size of array is: 6*4=24
*/							//	front		back	left	right	bottom		top
const float BODY_TEX_COORD[] = { 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,5, 0,1,0,5 };
const float BALK_TEX_COORD[] = { 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1 };

const std::string PLATFORM_TEX_NAME = "road.jpg";
//									front			back		left		right	bottom		top
const float PLATFORM_TEX_COORD[] = { 0,1,1,0.8125, 0,1,0,0.1875, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,15,0,1 };

const float PLATFORM_WIDTH = 3;
const float PLATFORM_HEIGHT = 0.3;
const float PLATFORM_LENGTH = 50;

//tree parameters
const unsigned int TREES_COUNTER_1 = 25;
const unsigned int TREE_TRUNK_PIECES = 10;
const unsigned int TREE_CROWN_PIECES = 12;
const unsigned int TREE_CROWN_LEVELS_C = 5;
const std::string TREE_TRUNK_TEX = "treeTrunk.jpg";
const std::string TREE_CROWN_TEX = "treeCrown.jpg";

//walls parameters
const unsigned int WALLS_COUNTER = 6;
const float WALL_TEX_COORD[] = { 0,1,0,1 };


#endif // !CONST_H
