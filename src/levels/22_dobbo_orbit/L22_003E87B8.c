/* func_L22_003E87B8 (120 bytes): spawns into the caller's object, paints a font-mode
   string and arms its animation, like func_L22_003D4320. func_002E5DA0 returns a value;
   declaring it void reorders the argument setup of its call. */
#include "common.h"

extern void *func_002A9640(void *, int, int);
extern char *func_002A77E0(int);
extern int func_002E5DA0(char *, int, void *, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *object);

/* Shows a text message at the object and starts its effect. Does nothing if the object has no target. */
void func_L22_003E87B8(u8 *moby, int unusedA, int unusedB) {
    u8 *mobyCopy = moby;
    void *target;
    target = FindOwnedEffectSlot(moby, -1, 0);
    if (target == 0)
        return;
    PlaySoundFromClassBank(0xC + RandomIntBelow(3), 0, mobyCopy, 0xE0B);
    SpawnExplosionWithSparks(mobyCopy, mobyCopy + 0x10, -1, 2.0f, 13.0f);
    MarkMobySpawned(mobyCopy);
}
