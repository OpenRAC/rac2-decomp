#include "names.h"
typedef struct { unsigned char prefix[0x1C]; int active; unsigned char suffix[0x10]; } EffectSlot48;
typedef struct { unsigned char prefix[0x44]; int active; unsigned char suffix[0x08]; } EffectSlot80;
typedef struct { unsigned char prefix[0x2290]; unsigned char *object; } EffectPlayer;
extern unsigned char *D_L00_001B08D0 __attribute__((sda));
extern EffectSlot48 D_L00_0024F9C0[12] __attribute__((nosda));
extern EffectSlot80 D_L00_0024FC00[128] __attribute__((nosda));
extern unsigned char g_hero_state[] __attribute__((nosda));
extern unsigned char *CreateMoby(int);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);

/* Creates the single effect controller moby (class 3303) and its two helper mobys (classes
   3307 and 3308), and clears the effect slot tables. Does nothing if the controller already
   exists. */
void effect_controller_spawn(void) {
    unsigned char *object;
    unsigned char *state;
    int i;
    if (D_L00_001B08D0)
        return;
    object = CreateMoby(0xCE7 /* moby class 3303 */);
    if (!object)
        return;
    object[0x30] = 0xFF;
    *(short *)(object + 0x32) = 0xFF;
    state = *(unsigned char **)(object + 0x68);
    object[0x20] = 0;
    for (i = 11; i >= 0; i--)
        D_L00_0024F9C0[i].active = 0;
    for (i = 127; i >= 0; i--)
        D_L00_0024FC00[i].active = 0;
    *(int *)(state + 0x10) = part_l00_alloc_effect_slot_2(((EffectPlayer *)g_hero_state)->object + 0x10, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    *(unsigned char **)(state + 8) = CreateMoby(0xCEB);
    *(unsigned char **)(state + 12) = CreateMoby(0xCEC);
    if (*(unsigned char **)(state + 8)) {
        **(int **)(*(unsigned char **)(state + 8) + 0x68) = 0;
        (*(unsigned char **)(state + 8))[0x30] = 0xFF;
        *(short *)(*(unsigned char **)(state + 8) + 0x32) = 0xFF;
    }
    if (*(unsigned char **)(state + 12)) {
        **(int **)(*(unsigned char **)(state + 12) + 0x68) = 0;
        (*(unsigned char **)(state + 12))[0x30] = 0xFF;
        *(short *)(*(unsigned char **)(state + 12) + 0x32) = 0xFF;
    }
    D_L00_001B08D0 = object;
}
