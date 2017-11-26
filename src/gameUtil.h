#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WinSock2.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#ifndef GAMEUTIL_H
#define GAMEUTIL_H
typedef struct LevelInfo {
	int LevelID;
	std::string levelName;
	std::string levelAuthor;
	int difficulty;
	int isDemon;
	int isAuto;
	int demonDiff;
	int stars;
};
typedef struct Gauntlets {
	std::vector<int> LevelID;
	std::vector<std::string> levelName;
	std::vector<std::string> levelAuthor;
	std::vector<int> difficulty;
	std::vector<int> isDemon;
	std::vector<int> isAuto;
	std::vector<int> demonDiff;
	std::vector<int> stars;
};
extern bool isOnGauntlets;
bool isPlaying();
int getBasePointer(int baseOffset);
char * getDiff(int val, int isAuto, int isDemon, int demonDiff);
std::string getSmallImageText(int stars, std::string levelName, std::string levelAuthor, int levelID);
std::string getLeaderboardRank(int accountID);
std::string getBigImage(bool isOnGauntlets, int gauntletsType);
LevelInfo getLevelInfo(int levelID);
std::string getPercentageText(int percentage);
int getBestPercentage();
void Hooks_Init();
#endif
