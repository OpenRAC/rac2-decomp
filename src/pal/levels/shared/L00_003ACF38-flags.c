#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
extern s32 coll_process_hit(f32, s32, s32, s32, s32);
extern void vec_scale_to_length(void *, void *, float);
extern int func_PAL_0032F0B8(int, int, int);
extern int g_hero_moby;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_weapon_l00_table[];
extern unsigned int g_area_hit_targets[];
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float pos[4];
    unsigned int obj;
    unsigned int magic;
    unsigned char kind;
    unsigned char kind2;
    unsigned short id;
    float len;
    unsigned int count;
} Trail_3A9798;
typedef struct {
    unsigned char pad0[4];
    unsigned char flag;
} Entry262570;

void func_PAL_L00_003ACF38(char *a0, char *a1, char *a2)
{
    Trail_3A9798 s;
    int count;
    int i;
    unsigned int *p;

    s.magic = 0x810000;
    s.len = *(float *)(a1 + 0x18);
    s.count = 1;
    s.obj = (unsigned int)a0;
    *(TI128 *)s.pos = *(TI128 *)a1;
    vec_scale_to_length(&s, &s, 1.0f);
    s.pos[3] = 5627.9248046875f;
    s.kind = 3;
    s.kind2 = 2;
    s.id = *(unsigned short *)(a0 + 0xAA);
    count = coll_process_hit(6.0f, (int)a2, 1, g_hero_moby, (int)&s);
    if (((Entry262570 *)(g_weapon_l00_table + g_item_slot_to_record[0x19] * 224))->flag != 0) {
        p = g_area_hit_targets;
        for (i = 0; i < count; i++)
            func_PAL_0032F0B8(g_area_hit_targets[i], 0x46, *(int *)(a0 + 0xB8));
    } else {
        p = g_area_hit_targets;
        for (i = 0; i < count; i++)
            func_PAL_0032F0B8(g_area_hit_targets[i], 0x19, *(int *)(a0 + 0xB8));
    }
}
