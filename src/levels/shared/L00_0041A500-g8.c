/* Per-frame step over a ring of 35 entries of 0x40 bytes: now and then hands one entry to a
   helper, and now and then fires a second helper on it. */
#include "common.h"

extern char *D_L00_001B144C __attribute__((sda));
extern int func_001163B0(void);
extern void func_L00_0041ACA0(char *object, void *entry);
extern void func_002BE278(void *entry, void *next, int zero, float scale);

void func_L00_0041A500(char *object)
{
    char *state = *(char **)(object + 0x68);
    int first = *(int *)(state + 0x48);
    int last = *(int *)(state + 0x44);
    int end;
    int index;
    int random;
    end = first + 2;
    index = end - last;
    if (index <= -1)
        index += 0x23;

    random = Rand();
    if (random % 7 == 0)
        SpawnLavaGunEntryEffect(object, gLavaGunRingEntries + (index << 6));

    random = Rand();
    if (random % 0x16 == 0) {
        char *entry = gLavaGunRingEntries + (index << 6);
        SpawnWhiteFlashParticle(entry, entry + 0x10, 0, -1.0f);
    }
}
