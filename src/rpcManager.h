#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "discord-rpc.h"
#ifndef RPCMANAGER_H
#define RPCMANAGER_H
void RPC_Init();
void UpdatePresence(const char* message, const char* state, const char* largeImageKey, const char* largeImageText, const char* smallImageKey, const char* smallImageText, int partySize, int partyMax);
#endif
