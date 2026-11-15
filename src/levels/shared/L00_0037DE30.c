#include "names.h"
extern int pair_find_owner_key_value(char *key, char *owner);

/* the owner in list[0..count) with the lowest score for key (-1 = no score), optionally only
   those whose kind at +0x46 of their +0x24 block is the given one */
char *pair_pick_owner_lowest_score(char *key, char **list, int count, int kind)
{
    char *found = 0;
    int best = 0x270F;
    int i;

    for (i = 0; i < count; i++) {
        int score;

        if (kind <= 0 || *(short *)(*(char **)(list[i] + 0x24) + 0x46) == kind) {
            score = pair_find_owner_key_value(key, list[i]);
            if (score < best && score != -1) {
                found = list[i];
                best = score;
            }
        }
    }
    return found;
}
