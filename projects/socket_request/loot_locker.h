#ifndef __LOOT_LOCKER_H__
#define __LOOT_LOCKER_H__

void ll_guest_login(const char* const game_key);
void ll_returning_user(const char* const game_key, const char* const player_id);

#endif//__LOOT_LOCKER_H__