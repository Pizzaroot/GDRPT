#include "dllmain.h"

__declspec(naked) int __stdcall GDRPC()
{
	__asm
	{
		ret
	}
}

void showDebugConsole() 
{
	AllocConsole();
	FILE *fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
}

void mainThread() 
{
	//showDebugConsole();
	RPC_Init();
	int *levelID = NULL;
	levelID = (int*)(getBasePointer(0x003222D0) + 0x2A0);
	int *accountID = NULL;
	accountID = (int*)(getBasePointer(0x003222D8) + 0x120);
	bool presenceUpdated = false;
	int lastPercentage = 0;
	while (1)
	{
		while (*levelID == 0 || *levelID == 0xFFFFFFFF)
		{
			if (presenceUpdated == false)
			{
				UpdatePresence("Surfing the menu", "Idle", "gd", getLeaderboardRank(*accountID).c_str(), "play", "0", 0, 0);
				~presenceUpdated;
			}
		}
		~presenceUpdated;
		while (*levelID != 0)
		{
			LevelInfo LI = getLevelInfo(*levelID);
			while (isPlaying())
			{
				if (lastPercentage != getBestPercentage()) 
				{
					lastPercentage = getBestPercentage();
					presenceUpdated = false;
				}
				if (presenceUpdated == false)
				{
					UpdatePresence(getPercentageText(getBestPercentage()).c_str(), "Playing", "gd", getLeaderboardRank(*accountID).c_str(), getDiff(LI.difficulty, LI.isAuto, LI.isDemon, LI.demonDiff), getSmallImageText(LI.stars, LI.levelName, LI.levelAuthor, LI.LevelID).c_str(), 0, 0);
					~presenceUpdated;
				}
			}
			lastPercentage = 0;
			UpdatePresence("Surfing the menu", "Idle", "gd", getLeaderboardRank(*accountID).c_str(), "play", "0", 0, 0);
		}
		~presenceUpdated;
	}
}

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) 
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&mainThread, 0, 0, 0);
	}
	return true;
}
