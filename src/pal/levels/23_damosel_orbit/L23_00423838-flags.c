#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI16 __attribute__((mode(TI)));
extern void vec_scale_to_length(float *, float *, float);
typedef struct {
    u8 pad[0x18];
    u8 *f18;
} L23Block1C0A80;
extern L23Block1C0A80 g_last_ray_hit;
typedef struct {
    float v[4];
} L23Vec __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x18];
    u8 b18;
    u8 b19;
    u16 h1A;
    u8 pad1C[0x14];
} L23Hit;
extern u8 *g_hero_moby;
extern s32 CollLine(void *, void *, s32, void *, s32);
extern void make_hit_descriptor(float, L23Hit *, u8 *, s32, L23Vec *);
extern void QueueMobyImpact(u8 *, L23Hit *);
extern int queue_copy_record_by_index(s32);
extern void part_start_random_scale_effect(void *, s32, s32);

/* the object's first record is set up against the table entry, then its marker byte is set */
void shot_update_hit_check_pal(u8 *shot, void *ray_start) {
    u8 *payload = *(u8 **)(shot + 0x68);
    L23Vec dir;
    L23Hit hit;
    u8 *hit_moby;

    if (CollLine(ray_start, shot + 0x10, 0, shot, 0) == 0) {
        return;
    }
    hit_moby = g_last_ray_hit.f18;
    if (hit_moby != 0) {
        if (*(s16 *)(hit_moby + 0xAA) == 0x7E5) {
            return;
        }
        vec_scale_to_length(dir.v, (float *)payload, 1.0f);
        make_hit_descriptor(*(float *)(payload + 0x1C), &hit, shot, 0x8B0003, &dir);
        hit.b18 = 5;
        hit.b19 = 3;
        hit.h1A = *(u16 *)(shot + 0xAA);
        if (g_last_ray_hit.f18 == g_hero_moby) {
            QueueMobyImpact(g_last_ray_hit.f18, &hit);
            queue_copy_record_by_index(0x2B);
        }
        part_start_random_scale_effect(shot + 0x10, 0xA, 1);
    } else {
        *(TI16 *)&dir = *(TI16 *)(shot + 0x10);
        part_start_random_scale_effect(&dir, 0xF, 0);
    }
    shot[0x20] = 2;
}
