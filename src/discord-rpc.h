#pragma once
#pragma comment(lib, "discord-rpc.lib")
#include <stdint.h>
#if defined(DISCORD_DYNAMIC_LIB)
#  if defined(_WIN32)
#    if defined(DISCORD_BUILDING_SDK)
#      define DISCORD_EXPORT __declspec(dllexport)
#    else
#      define DISCORD_EXPORT __declspec(dllimport)
#    endif
#  else
#    define DISCORD_EXPORT __attribute__((visibility("default")))
#  endif
#else
#  define DISCORD_EXPORT
#endif
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct DiscordRichPresence {
		const char* state;
		const char* details;
		int64_t startTimestamp;
		int64_t endTimestamp;
		const char* largeImageKey;
		const char* largeImageText;
		const char* smallImageKey;
		const char* smallImageText;
		const char* partyId;
		int partySize;
		int partyMax;
		const char* matchSecret;
		const char* joinSecret;
		const char* spectateSecret;
		int8_t instance;
	} DiscordRichPresence;

	typedef struct DiscordJoinRequest {
		const char* userId;
		const char* username;
		const char* avatar;
	} DiscordJoinRequest;

	typedef struct DiscordEventHandlers {
		void(*ready)();
		void(*disconnected)(int errorCode, const char* message);
		void(*errored)(int errorCode, const char* message);
		void(*joinGame)(const char* joinSecret);
		void(*spectateGame)(const char* spectateSecret);
		void(*joinRequest)(const DiscordJoinRequest* request);
	} DiscordEventHandlers;
#define DISCORD_REPLY_NO 0
#define DISCORD_REPLY_YES 1
#define DISCORD_REPLY_IGNORE 2
	DISCORD_EXPORT void Discord_Initialize(const char* applicationId,
		DiscordEventHandlers* handlers,
		int autoRegister,
		const char* optionalSteamId);
	DISCORD_EXPORT void Discord_Shutdown(void);
	DISCORD_EXPORT void Discord_RunCallbacks(void);
#ifdef DISCORD_DISABLE_IO_THREAD
	DISCORD_EXPORT void Discord_UpdateConnection(void);
#endif
	DISCORD_EXPORT void Discord_UpdatePresence(const DiscordRichPresence* presence);
	DISCORD_EXPORT void Discord_Respond(const char* userid, /* DISCORD_REPLY_ */ int reply);
#ifdef __cplusplus
}
#endif
