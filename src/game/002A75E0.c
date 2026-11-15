#include "common.h"

typedef struct {
    u8 pad00[0x11];
    u8 f11;
} Anim_2A75E0;

typedef struct {
    u8 pad00[0x48];
    Anim_2A75E0 *anims[1];
} Class_2A75E0;

typedef struct {
    u8 pad00[0x24];
    Class_2A75E0 *cls;
    u8 pad28[0x40 - 0x28];
    u8 slot;
    u8 f41;
    u8 f42;
    u8 anim;
    f32 f44;
    f32 f48;
    f32 f4C;
    s32 f50;
    s32 f54;
    u8 pad58[0x60 - 0x58];
    u8 f60;
    u8 pad61[0x6C - 0x61];
    u8 f6C;
    u8 pad6D[0x80 - 0x6D];
    f32 f80[4];
    u8 pad90[0xA9 - 0x90];
    u8 fA9;
} Moby_2A75E0;

extern f32 D_001CD540[][4];
extern void func_002A7398(Moby_2A75E0 *, int, int);
extern int func_0029FA88(void *);
extern void func_002A2450(Moby_2A75E0 *, int);
extern void func_0029F390(void *);
extern float func_00283CE0(int);

/* Start an animation blended over a number of frames (or at once when there are none). */
void func_002A75E0(Moby_2A75E0 *m, int anim, int f41, int frames, int flags)
{
    if (frames <= 0) {
        StartAnimationImmediate(m, anim, f41);
        return;
    }
    if (m->f44 > 0.025f || m->f50 != 0 || m->f54 != 0 || (flags & 4)) {
        int slot = AllocObjectSlot(m);
        if (slot >= 0) {
            int slotFlags = slot;
            if (flags & 1) slotFlags |= 0x100;
            if (flags & 2) slotFlags |= 0x200;
            func_002A2450(m, slotFlags);
            qcopy(D_001CD540[slot], m->f80);
            if (m->f42 != 0xFF) m->fA9 = m->f42;
            m->f42 = 0xFF;
            m->slot = slot;
        }
    }
    m->f41 = f41;
    m->anim = anim;
    update_moby_animation_state(m);
    m->f48 = 1.0f;
    m->f4C = 1.0f / IntToFloat(frames);
    m->f44 = 0;
    m->f60 &= ~2;
    m->f6C = m->cls->anims[anim]->f11;
}
