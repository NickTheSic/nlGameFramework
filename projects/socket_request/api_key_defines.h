#ifndef __API_KEY_DEFINES_H___
#define __API_KEY_DEFINES_H___

#include "private/nl_debug.h"

#ifndef LOOT_LOCKER_GAME_KEY
//#warning NEED TO SET LOOT_LOCKER_GAME_KEY BEFORE COMPILING
#   define LOOT_LOCKER_GAME_KEY 0
#endif
#define LOOT_LOCKER_GAME_KEY_NAME VALUE_TO_STR(LOOT_LOCKER_GAME_KEY)

#ifndef WHALEPASS_PUBLISH_KEY
//#warning NEED TO SET WHALEPASS_PUBLISH_KEY BEFORE COMPILING
#   define WHALEPASS_PUBLISH_KEY 0
#endif
#define WHALEPASS_PUBLISH_KEY_NAME VALUE_TO_STR(WHALEPASS_PUBLISH_KEY)

#ifndef WHALEPASS_SERVER_KEY
//#warning NEED TO SET WHALEPASS_SERVER_KEY BEFORE COMPILING
#   define WHALEPASS_SERVER_KEY 0
#endif
#define WHALEPASS_SERVER_KEY_NAME VALUE_TO_STR(WHALEPASS_SERVER_KEY)

#ifndef WHALEPASS_GAME_ID
//#warning NEED TO SET WHALEPASS_GAME_ID BEFORE COMPILING
#   define WHALEPASS_GAME_ID 0
#endif
#define WHALEPASS_GAME_ID_NAME VALUE_TO_STR(WHALEPASS_GAME_ID)

#endif//__API_KEY_DEFINES_H___