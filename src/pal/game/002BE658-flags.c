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
extern u8 *D_001F2598[];
extern Effect2BDBC0 *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_001163B0(void);

void func_PAL_002BE880(void *pos, void *dir, u32 color, s32 flags, s32 frames, f32 size) {
    Puff2BDBC0 *p;
    Effect2BDBC0 *e;
    f32 len;
    f32 d;

    e = func_002B9030(0x16);
    if (e != 0) {
        p = &e->p;
        e->color = color;
        e->f9 = func_00283CF0(4.0f) + 0x70;
        e->f1 = 0;
        e->f3 = 0x44;
        e->size = size * 0.2f;
        e->f8 = func_001163B0();
        e->f2 = *D_001F2598[0];
        e->frames = frames;
        p->frames = frames;
        len = func_00283CE0(frames);
        d = size - e->size;
        p->color = color;
        p->flags = flags;
        p->fade = d / len;
        qcopy(p, dir);
        qcopy(e->pos, pos);
        p->decay = 0.00049600005f;
    }
}
