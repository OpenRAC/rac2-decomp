/* func_L00_002A7DE8 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
extern char D_00189E20[];
extern void func_L00_002A7A10(void);
typedef struct {
    char pad[0x2080];
    Quad ring[8];
    int value[8];
    float first[8];
    float second[8];
    short index;
} Ring_L00_002A7DE8;

/* Adds a glow point to the hero effect queue, storing its position, color and two size values. The queue has room for eight. */
void func_L00_002A7DE8(Quad *position, int color, float size, float fade)
{
    Ring_L00_002A7DE8 *hero = (Ring_L00_002A7DE8 *)gHeroState;
    int index = hero->index;

    hero->ring[index] = *position;
    hero->value[index] = color;
    hero->first[hero->index] = size;
    hero->second[hero->index] = fade;
    QueueHeroGlowDrawRoutine();
    hero->index++;
}
