#pragma once

#ifndef MYCONST_H
#define MYCONST_H

#include <iostream>


const unsigned int WHEEL_PIECES = 24;
const unsigned int WHEELS_COUNT = 4;
const float WHEEL_WIDTH = 0.1;

const unsigned int BALKS_COUNT = 2;
const float BALK_WIDTH = 0.05;
const float BALK_HEIGHT = 0.05;

const std::string BODY_TEX_NAME = "deska.png";
const std::string WHEEL_TEX_NAME1 = "kolo.jpg";
const std::string WHEEL_TEX_NAME2 = "black.jpg";
const std::string BALK_TEX_NAME = "silver.jpg";


const float BODY_TEX_COORD[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 5.0, 1.0, 5.0 };
const float BALK_TEX_COORD[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

//tree parameters
const unsigned int TREES_COUNTER_1 = 10;
const unsigned int TREE_TRUNK_PIECES = 10;
const unsigned int TREE_CROWN_PIECES = 12;
const unsigned int TREE_CROWN_LEVELS_C = 5;
const std::string TREE_TRUNK_TEX = "treeTrunk.jpg";
const std::string TREE_CROWN_TEX = "treeCrown.jpg";


#endif // !CONST_H
