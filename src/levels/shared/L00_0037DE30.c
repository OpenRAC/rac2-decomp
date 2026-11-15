#include "names.h"
extern int func_L00_0037DDE8(char *key, char *owner);

/* the owner in list[0..count) with the lowest score for key (-1 = no score), optionally only
   those whose kind at +0x46 of their +0x24 block is the given one */
char *func_L00_0037DE30(char *key, char **list, int count, int kind)
{
    char *found = 0;
    int best = 0x270F;
    int i;

    for (i = 0; i < count; i++) {
        int score;

        if (kind <= 0 || *(short *)(*(char **)(list[i] + 0x24) + 0x46) == kind) {
            score = FindOwnerKeyValue(key, list[i]);
            if (score < best && score != -1) {
                found = list[i];
                best = score;
            }
        }
    }
    return found;
}
