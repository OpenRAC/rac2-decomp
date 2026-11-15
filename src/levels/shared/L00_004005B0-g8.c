#include "include_asm.h"
#include "names.h"

/* func_L00_004005B0 is a unit of its own: it needs the opt-in quadword-copy profile and
   its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which
   give retail's grouped `lq`/`sq` with register addresses and keep the instructions
   around the copy on their own side of it.  The unit is a -G8 one: the body reaches the
   level's globals through $gp. */

typedef int TI128 __attribute__((mode(TI)));

extern char *CreateMoby(int id);
extern void euler_rotation_basis(char *a, char *b);
extern int slot_alloc_for_object(char *a, int b);
extern void vec_clear_128(char *a);
extern int part_alloc_effect_slot(char *a, int b, float x, float y, float z);
extern int func_002A0F48(char *a);
extern float g_hero_state[];
extern char *D_L00_001B0CA0 __attribute__((sda));
extern int D_L00_001B2C28;

/* Looks the actor up, resets its two state fields, copies the two 16-byte vectors it was
   given, then sets the record's vector and flags. */
/* Creates the Turret Spider Bot (moby class 3705) at the given position with the given starting speed, and returns it. */
char *spider_bot_create(char *position, char *velocity)
{
    char *obj = CreateMoby(0xE79 /* Turret Spider Bot */);
    char *rec;
    TI128 tmp;
    int iv;
    unsigned short v;

    if (obj != 0) {
        rec = *(char **)(obj + 0x68);

        v = 0xFF;
        *(unsigned short *)(obj + 0x32) = v;
        *(unsigned char *)(obj + 0x30) = v;
        *(TI128 *)(obj + 0x10) = *(TI128 *)position;
        *(TI128 *)rec = *(TI128 *)velocity;

        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) * 0.25f;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        obj[0x20] = 0;

        *(float *)(obj + 0xF0) = g_hero_state[0x24];
        *(float *)(obj + 0xF4) = g_hero_state[0x25];
        *(float *)(obj + 0xF8) = g_hero_state[0x26];
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);

        *(int *)(rec + 0x5C) = 0x7F000000;
        D_L00_001B0CA0 = obj;
        iv = slot_alloc_for_object(obj, 0);
        *(int *)(rec + 0x6C) = iv;
        *(int *)(rec + 0x70) = slot_alloc_for_object(obj, 4);
        *(int *)(rec + 0x74) = slot_alloc_for_object(obj, 3);

        vec_clear_128(rec + 0x10);
        *(float *)(rec + 0x10) = 1.0f;
        *(TI128 *)(rec + 0x20) = *(TI128 *)(rec + 0x10);

        D_L00_001B2C28 = part_alloc_effect_slot(obj, 0, 1.0f, 1.0f, 1.0f);
        *(float *)(rec + 0x7C) = 1.75f;
        func_002A0F48(obj);
    }
    return obj;
}
