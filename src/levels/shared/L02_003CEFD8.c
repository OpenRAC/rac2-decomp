#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *g_moby_l02_pool __attribute__((sda));
extern char *g_entity_group_lists[];
extern int D_L02_001B35B8 __attribute__((sda));

struct L02PairWordB {
    int a;
    int b;
};

extern struct L02PairWordB D_L02_001B00C8;

extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

struct L02Vec4 {
    float x, y, z, w;
};

struct L02PushBlock {
    char pad0[0x220];
    char m[0x104];
    float f324;
    char pad1[4];
    float f32C;
};

struct L02PushEntity {
    char pad0[0x20];
    unsigned char state;
    char pad1[0x10];
    unsigned char f31;
    char pad2[0x36];
    struct L02PushBlock *obj;
    char pad3[0x3E];
    short type;
};

struct L02PushObject {
    char pad[0x21];
    unsigned char group;
};

/* For every live entity of kind 0xA4E in the object's group (not in state 0xFE/0xFD), builds
   a vector from the unit scaled by the entity's block, transforms it by the block's matrix
   and hands it, with the block's random word, to the shared emitter. */
void chickenbot_emit_sparks(struct L02PushObject *a0)
{
    struct L02Vec4 vec;
    struct L02PairWordB k;
    float tmp[4];
    unsigned short *q;
    unsigned short *p;
    struct L02PushEntity *e;
    struct L02PushBlock *o;
    int r;

    if (a0->group == 0xFF)
        return;
    q = (unsigned short *)g_entity_group_lists[a0->group];
    if (q == 0)
        return;
    *(TI128 *)&vec = 0;
    vec.x = 0.25f;
    vec.z = 0.1f;
    vec.w = 1.0f;
    k = D_L02_001B00C8;
    p = (unsigned short *)g_entity_group_lists[a0->group];
    while (a0->group != 0xFF && a0->group <= D_L02_001B35B8 && p != 0 &&
           ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)g_entity_group_lists[a0->group])) {
        e = (struct L02PushEntity *)(g_moby_l02_pool + ((*p & 0x7FFF) << 8));
        if (e == 0)
            break;
        if (e->f31 != 0 && e->type == MOBY_CLASS_MEGACORP_CHICKENBOT && e->state != 0xFE && e->state != 0xFD) {
            o = e->obj;
            FastVecScale(tmp, &vec, o->f324);
            transform_vector(tmp, tmp, (char *)o + 0x220);
            r = FastTweenColor(k.a, k.b, o->f32C);
            gfx_l00_draw_billboard_quad(tmp, r, o->f324 * 0.2f, 0.08f);
        }
        p++;
    }
}
