#include "gameUtil.h"

void *gauntletsOnLoadAddr;

void *gauntletsOnArrowExitAddr;

void *optionRendererAddr;

bool isOnGauntlets;

int getBasePointer(int baseOffset)
{
	int *basePointer = NULL;
	basePointer = (int*)((int)GetModuleHandle("GeometryDash.exe") + baseOffset);
	return *basePointer;
}

bool isPlaying() 
{
	int *basePointer = NULL;
	basePointer = (int*)((int)GetModuleHandle("GeometryDash.exe") + 0x003222D0);
	basePointer = (int*)(*basePointer + 0x164);
	if (*basePointer == 0)
	{
		return false;
	}
	basePointer = (int*)(*basePointer + 0x224);
	if (*basePointer == 0) 
	{
		return false;
	}
	basePointer = (int*)(*basePointer + 0x67C);
	if (*basePointer == 0)
	{
		return false;
	}
	return true;
}

int getBestPercentage()
{
	int *basePointer = NULL;
	basePointer = (int*)((int)GetModuleHandle("GeometryDash.exe") + 0x003222D0);
	basePointer = (int*)(*basePointer + 0x164);
	if (*basePointer == 0)
	{
		return 0;
	}
	basePointer = (int*)(*basePointer + 0x488);
	if (*basePointer == 0)
	{
		return 0;
	}
	basePointer = (int*)(*basePointer + 0x248);
	if (*basePointer == 0)
	{
		return 0;
	}
	return *basePointer;
}

Gauntlets getLevelGauntlets(int gauntletID)
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 1), &wsaData);
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("162.216.16.96");
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	connect(Connection, (SOCKADDR*)&addr, sizeofaddr);
	char p[] = "POST /database/getGJLevels21.php HTTP/1.1\r\n"
		"Host: www.boomlings.com\r\n"
		"Accept: */*\r\n"
		"Content-Length: %d\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n\r\n"
		"gameVersion=21&binaryVersion=35&gdw=0&gauntlet=%d&secret=Wmfd2893gb7";
	char buffer[1024];
	sprintf(buffer, p, (int)(std::to_string(gauntletID).length() + 66), gauntletID);
	std::string packet = buffer;
	send(Connection, buffer, strlen(buffer), 0);
	shutdown(Connection, SD_SEND);
	char recvBuffer[1024];
	int iResult = 0;
	do
	{
		iResult = recv(Connection, recvBuffer, 1024, 0);
	} while (iResult > 0);
	shutdown(Connection, SD_BOTH);
	closesocket(Connection);
	WSACleanup();
	if (strstr(recvBuffer, "\r\n\r\n-1"))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		Gauntlets LI;
		return LI;
	}
	std::stringstream test(recvBuffer);
	std::string segment;
	std::vector<std::string> seglist;
	Gauntlets LI;
	while (std::getline(test, segment, '\n'))
	{
		seglist.push_back(segment);
	}
	std::stringstream test2(seglist[seglist.size() - 1]);
	std::vector<std::string> seglist2;
	while (std::getline(test2, segment, '|'))
	{
		seglist2.push_back(segment);
	}
	for (int i = 0; i < seglist2.size(); i++)
	{
		std::stringstream test3(seglist2[i]);
		std::vector<std::string> seglist3;
		while (std::getline(test3, segment, ':'))
		{
			seglist3.push_back(segment);
		}
		for (int i = 0; i < seglist3.size(); i++)
		{
			if (seglist3[i] == "1")
			{
				LI.LevelID.push_back(atoi(seglist3[i + 1].c_str()));
			}
			else if (seglist3[i] == "2")
			{
				LI.levelName.push_back(seglist3[i + 1]);
			}
			else if (seglist3[i] == "9")
			{
				LI.difficulty.push_back(atoi(seglist3[i + 1].c_str()));
			}
			else if (seglist3[i] == "17")
			{
				LI.isDemon.push_back(atoi(seglist3[i + 1].c_str()));
			}
			else if (seglist3[i] == "18")
			{
				LI.stars.push_back(atoi(seglist3[i + 1].c_str()));
			}
			else if (seglist3[i] == "25")
			{
				LI.isAuto.push_back(atoi(seglist3[i + 1].c_str()));
			}
			else if (seglist3[i] == "43")
			{
				LI.demonDiff.push_back(atoi(seglist3[i + 1].c_str()));
			}
			i++;
		}
		LI.levelAuthor.push_back(seglist3[seglist3.size() - 4]);
	}
	return LI;
}

LevelInfo getLevelInfo(int levelID) 
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 1), &wsaData);
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("162.216.16.96");
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	connect(Connection, (SOCKADDR*)&addr, sizeofaddr);
	char p[] = "POST /database/getGJLevels21.php HTTP/1.1\r\n"
		"Host: www.boomlings.com\r\n"
		"Accept: */*\r\n"
		"Content-Length: %d\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n\r\n"
		"gameVersion=21&binaryVersion=35&gdw=0&type=0&str=%d&diff=-&len=-&page=0&total=0&uncompleted=0&onlyCompleted=0&featured=0&original=0&twoPlayer=0&coins=0&epic=0&secret=Wmfd2893gb7";
	char buffer[1024];
	sprintf(buffer, p, (int)(std::to_string(levelID).length() + 175), levelID);
	std::string packet = buffer;
	send(Connection, buffer, strlen(buffer), 0);
	shutdown(Connection, SD_SEND);
	char recvBuffer[1024];
	int iResult = 0;
	do 
	{
		iResult = recv(Connection, recvBuffer, 1024, 0);
	} 
	while (iResult > 0);
	shutdown(Connection, SD_BOTH);
	closesocket(Connection);
	WSACleanup();
	if (strstr(recvBuffer, "\r\n\r\n-1")) 
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		LevelInfo LI;
		return LI;
	}
	std::stringstream test(recvBuffer);
	std::string segment;
	std::vector<std::string> seglist;
	LevelInfo LI;
	while (std::getline(test, segment, '\n'))
	{
		seglist.push_back(segment);
	}
	std::stringstream test2(seglist[seglist.size() - 1]);
	std::vector<std::string> seglist2;
	while (std::getline(test2, segment, ':'))
	{
		seglist2.push_back(segment);
	}
	for (int i = 0; i < seglist2.size(); i++) 
	{
		if (seglist2[i] == "1")
		{
			LI.LevelID = atoi(seglist2[i + 1].c_str());
		}
		else if (seglist2[i] == "2")
		{
			LI.levelName = seglist2[i + 1];
		}
		else if (seglist2[i] == "9")
		{
			LI.difficulty = atoi(seglist2[i + 1].c_str());
		}
		else if (seglist2[i] == "17")
		{
			LI.isDemon = atoi(seglist2[i + 1].c_str());
		}
		else if (seglist2[i] == "18")
		{
			LI.stars = atoi(seglist2[i + 1].c_str());
		}
		else if (seglist2[i] == "25")
		{
			LI.isAuto = atoi(seglist2[i + 1].c_str());
		}
		else if (seglist2[i] == "43")
		{
			LI.demonDiff = atoi(seglist2[i + 1].c_str());
		}
		i++;
	}
	LI.levelAuthor = seglist2[seglist2.size() - 4];
	return LI;
}

char * getDiff(int val, int isAuto, int isDemon, int demonDiff) 
{
	if (isAuto == 1)
	{
		return "auto";
	}
	else if (isDemon == 1)
	{
		switch (demonDiff) {
		case 3:
			return "easy_demon";
		case 4:
			return "medium_demon";
		case 5:
			return "insane_demon";
		case 6:
			return "extreme_demon";
		default:
			return "hard_demon";
		}
	}
	else
	{
		switch (val) {
		case 10:
			return "easy";
		case 20:
			return "normal";
		case 30:
			return "hard";
		case 40:
			return "harder";
		case 50:
			return "insane";
		case 0:
			return "na";
		}
	}
}

std::string getLeaderboardRank(int accountID)
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 1), &wsaData);
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("162.216.16.96");
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	connect(Connection, (SOCKADDR*)&addr, sizeofaddr);
	char p[] = "POST /database/getGJUserInfo20.php HTTP/1.1\r\n"
		"Host: www.boomlings.com\r\n"
		"Accept: */*\r\n"
		"Content-Length: %d\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n\r\n"
		"gameVersion=21&binaryVersion=35&gdw=0&accountID=0&targetAccountID=%d&secret=Wmfd2893gb7";
	char buffer[1024];
	sprintf(buffer, p, (int)(std::to_string(accountID).length() + 85), accountID);
	std::string packet = buffer;
	send(Connection, buffer, strlen(buffer), 0);
	shutdown(Connection, SD_SEND);
	char recvBuffer[1024];
	int iResult = 0;
	do
	{
		iResult = recv(Connection, recvBuffer, 1024, 0);
	} while (iResult > 0);
	shutdown(Connection, SD_BOTH);
	closesocket(Connection);
	WSACleanup();
	if (strstr(recvBuffer, "\r\n\r\n-1"))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return "[UNLINKED]";
	}
	std::stringstream test(recvBuffer);
	std::string segment;
	std::vector<std::string> seglist;
	LevelInfo LI;
	while (std::getline(test, segment, '\n'))
	{
		seglist.push_back(segment);
	}
	std::stringstream test2(seglist[seglist.size() - 1]);
	std::vector<std::string> seglist2;
	while (std::getline(test2, segment, ':'))
	{
		seglist2.push_back(segment);
	}
	std::stringstream ss;
	for (int i = 0; i < seglist2.size(); i++)
	{
		if (seglist2[i] == "1")
		{
			ss << seglist2[i + 1];
		}
		else if (seglist2[i] == "30")
		{
			if (seglist2[i + 1] == "0")
			{
				ss << " [BANNED]";
			}
			else
			{
				ss << " (rank #" << seglist2[i + 1] << ")";
			}
		}
		i++;
	}
	std::string result = ss.str();
	return result;
}

std::string getSmallImageText(int stars, std::string levelName, std::string levelAuthor, int levelID)
{
	std::stringstream buffer;
	buffer << "[" << stars << "*]" << levelName << " - " << levelAuthor << " (" << levelID << ")";
	std::string result = buffer.str();
	return result;
}

std::string getPercentageText(int percentage)
{
	std::stringstream buffer;
	buffer << "Best: " << percentage << "%";
	std::string result = buffer.str();
	return result;
}

__declspec(naked) void __fastcall gauntletsOnArrowExit() 
{
	__asm 
	{
		mov[isOnGauntlets], 0
		jmp[gauntletsOnArrowExitAddr]
	}
}

__declspec(naked) bool __fastcall gauntletsOnLoad() 
{
	__asm 
	{
		mov[isOnGauntlets], 1
		jmp[gauntletsOnLoadAddr]
	}
}

__declspec(naked) int __stdcall optionRenderer(int BoxName, char *BoxID, int BoxDesc) 
{
	int title, desc;
	title = (int)"Rich Presence";
	char *code;
	code = "0420";
	desc = (int)"Enables the Rich Presence Technology for Discord. For more info: https://discord.gg/tPjnzxu";
	__asm 
	{
		push desc
		push code
		push title
		call optionRendererAddr
		push ebp
		mov ebp, esp
		push BoxDesc
		push BoxID
		push BoxName
		mov eax, optionRendererAddr
		add eax, 3
		mov ecx, esi
		jmp eax
	}
}

bool hook(void *toBeHooked, void *hooker) {
	DWORD oldProtect, newProtect;
	DWORD offset = (DWORD)hooker - (DWORD)toBeHooked - 5;
	if (!(VirtualProtect((LPVOID)toBeHooked, 5, PAGE_EXECUTE_READWRITE, &oldProtect) &&
		WriteProcessMemory((HANDLE)-1, (LPVOID)toBeHooked, new byte{ 0xe8 }, 1, NULL) &&
		WriteProcessMemory((HANDLE)-1, (LPVOID)((DWORD)toBeHooked + 1), &offset, 4, NULL) &&
		VirtualProtect((LPVOID)toBeHooked, 5, oldProtect, &newProtect))) {
		return false;
	}
	return true;
}
bool hookPush(void *toBeHooked, void *hooker) {
	DWORD oldProtect, newProtect;
	DWORD offset = (DWORD)hooker - (DWORD)toBeHooked - 5;
	if (!(VirtualProtect((LPVOID)toBeHooked, 5, PAGE_EXECUTE_READWRITE, &oldProtect) &&
		WriteProcessMemory((HANDLE)-1, (LPVOID)toBeHooked, new byte{ 0x68 }, 1, NULL) &&
		WriteProcessMemory((HANDLE)-1, (LPVOID)((DWORD)toBeHooked + 1), &hooker, 4, NULL) &&
		VirtualProtect((LPVOID)toBeHooked, 5, oldProtect, &newProtect))) {
		return false;
	}
	return true;
}

void Hooks_Init()
{
	gauntletsOnLoadAddr = (void*)(0x1045C0 + 0xC00 + (int)GetModuleHandle("GeometryDash.exe"));
	gauntletsOnArrowExitAddr = (void*)(0x105920 + 0xC00 + (int)GetModuleHandle("GeometryDash.exe"));
	optionRendererAddr = (void*)(0x001DEAB0 + 0xC00 + (int)GetModuleHandle("GeometryDash.exe"));
	hook((void*)(0x10457B + 0xC00 + (int)GetModuleHandle("GeometryDash.exe")), gauntletsOnLoad);
	hookPush((void*)(0x104BE5 + 0xC00 + (int)GetModuleHandle("GeometryDash.exe")), gauntletsOnArrowExit);
	hook((void*)(0x001DDF3F + 0xC00 + (int)GetModuleHandle("GeometryDash.exe")), optionRenderer);
}

std::string getBigImage(bool isOnGauntlets, int gauntletsType)
{
	switch (isOnGauntlets)
	{
	case 0:
		return "gd";
	case 1:
		switch (gauntletsType)
		{
		case 1:
			return "fire_gauntlet";
		case 2:
			return "ice_gauntlet";
		case 3:
			return "poison_gauntlet";
		}
	}
}
