#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 dir[12];
    f32 decay;
    u32 color;
    s32 flags;
    s16 frames;
    s16 pad1A;
    f32 fade;
} Puff2BDBC0;
typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u32 color;
    u8 f8;
    u8 f9;
    s16 frames;
    f32 size;
    f32 pos[4];
    Puff2BDBC0 p;
} Effect2BDBC0;
extern u8 *g_part_tex_growing_puff_table[];
extern Effect2BDBC0 *part_alloc(int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int func_001163B0(void);

/* Spawns a growing puff of smoke that starts small and grows to the given size over the given frames. */
void part_spawn_growing_puff_pal(void *pos, void *dir, u32 color, s32 flags, s32 frames, f32 size) {
    Puff2BDBC0 *p;
    Effect2BDBC0 *e;
    f32 len;
    f32 d;

    e = part_alloc(0x16);
    if (e != 0) {
        p = &e->p;
        e->color = color;
        e->f9 = FloatToInt(4.0f) + 0x70;
        e->f1 = 0;
        e->f3 = 0x44;
        e->size = size * 0.2f;
        e->f8 = func_001163B0();
        e->f2 = *g_part_tex_growing_puff_table[0];
        e->frames = frames;
        p->frames = frames;
        len = IntToFloat(frames);
        d = size - e->size;
        p->color = color;
        p->flags = flags;
        p->fade = d / len;
        qcopy(p, dir);
        qcopy(e->pos, pos);
        p->decay = 0.00049600005f;
    }
}
