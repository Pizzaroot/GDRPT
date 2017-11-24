#include "gameUtil.h"

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
	sprintf(buffer, p, (int)(std::to_string(accountID).length() + 175), accountID);
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
