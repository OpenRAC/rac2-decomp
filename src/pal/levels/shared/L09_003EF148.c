#include "include_asm.h"
#include "names.h"


extern int PlayMobySound(int a, int b, char *c);
extern void SetDeathBits(char *a, int b, int c);
extern void moby_mark_spawned(void *entry);
extern char *SpawnExplosion(void *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                          float f1, float f2, int s1, int s2, int s3, int s4);
extern void moby_mark_spawned(void *entry);

void func_PAL_L09_003EF588(char *object)
{
    PlayMobySound(2, 0, object);
    SetDeathBits(object, 0, 3);
    SpawnExplosion(object + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                  1.0f, 20.0f, 1, 1, 0, 0);
    moby_mark_spawned(object);
}

