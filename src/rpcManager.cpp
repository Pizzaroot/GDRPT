#include "rpcManager.h"

void handleDiscordReady() {}

void handleDiscordDisconnected(int errcode, const char* message) {}

void handleDiscordError(int errcode, const char* message) 
{
	std::stringstream ss;
	ss << "Error: " << errcode << "\nCode: " << message;
	std::string buffer = ss.str();
	auto log = std::ofstream("log.txt");
	log.write(buffer.c_str(),buffer.length());
	MessageBox(NULL, "An error has occurred: please read the \"log.txt\" file.\nThe game will now close.", "Uh oh", MB_OK | MB_ICONEXCLAMATION);
	Discord_Shutdown();
	exit(-1);
}

void handleDiscordJoin(const char* secret) {}

void handleDiscordSpectate(const char* secret) {}

void handleDiscordJoinRequest(const DiscordJoinRequest* request) {}

void RPC_Init()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.errored = handleDiscordError;
	handlers.disconnected = handleDiscordDisconnected;
	handlers.joinGame = handleDiscordJoin;
	handlers.spectateGame = handleDiscordSpectate;
	handlers.joinRequest = handleDiscordJoinRequest;
	Discord_Initialize("APP_ID", &handlers, 1, NULL);
}

void UpdatePresence(const char* message, const char* state, const char* largeImageKey, const char* largeImageText, const char* smallImageKey, const char* smallImageText, int partySize, int partyMax)
{
	char buffer[256];
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence)); 
	if (strcmp(message, "0") != 0)
		discordPresence.details = message;
	if (strcmp(state, "0") != 0)
		discordPresence.state = state;
	if (strcmp(largeImageKey, "0") != 0)
	    discordPresence.largeImageKey = largeImageKey;
	if (strcmp(largeImageText, "0") != 0)
	    discordPresence.largeImageText = largeImageText;
	if (strcmp(smallImageKey, "0") != 0)
	    discordPresence.smallImageKey = smallImageKey;
	if (strcmp(smallImageText, "0") != 0)
	    discordPresence.smallImageText = smallImageText;
	discordPresence.partySize = partySize;
	discordPresence.partyMax = partyMax;
	//discordPresence.matchSecret = "hash";
	//discordPresence.spectateSecret = "hash";
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}
