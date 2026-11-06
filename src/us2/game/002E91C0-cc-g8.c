/* func_US2_002E91C0, the USA v2.00 copy of func_002E8368: the same C, where rename func_002EC1C0 becomes func_US2_002ED018; rename func_002E64A0 becomes func_US2_002E72D8; rename func_00132A10 becomes func_001329F0; rename func_00132AC8 becomes func_00132AA0; rename func_00132828 becomes func_00132818. */
#include "common.h"
#define W(p, o)  (*(int *)((char *)(p) + (o)))
#define H(p, o)  (*(short *)((char *)(p) + (o)))
#define B(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define F(p, o)  (*(float *)((char *)(p) + (o)))

extern void func_002F5220(void);
extern void func_002F52B8(void);
extern void func_00133220(void);
extern void func_00133230(void);
extern int func_00132028(void);
extern void func_001329F0(int, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_0029F390(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002A0F48(void *);
extern void func_002A10E8(void *);
extern void func_US2_002ED018(void);
extern char D_00240450[];
extern void func_002ED260(void *);
extern void func_00132AA0(void);
extern int func_001163B0(void);
extern void func_00132858(int);
extern void func_00132818(void);
extern void func_002E80B0(void);
extern void func_00282A60(void *, int, int);
extern void func_00294070(int);
extern void func_002E6A60(void);
extern void func_0027AB40(void);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_US2_002E72D8(int);

typedef struct {
 char pad0[0x10]; float position[4]; char pad20[4]; char *definition;
 char pad28[4]; float scale; char pad30[2]; short draw_flags; char pad34[12];
 unsigned char key, next_key, current_anim, next_anim; float blend;
 char pad48[0x19]; unsigned char alpha, cached_frame, flags; char pad64[4];
 char *keys; char pad6c[0x29]; unsigned char opacity; char pad96[0x14]; short type;
} TransitionActor;
extern float D_001B15A0 MACRO_ADDR;
typedef struct {
 char pad[0xc]; unsigned char count; char gap[0x3b]; void *animations[1];
} AnimationClass;
typedef struct { char pad[0x24]; AnimationClass *definition; } AnimationObject;
typedef struct {
 char pad[0x34]; int frame, tick, page; short duration, pad42, count;
 char pad46[0xe]; int id; char pad58[0x14]; int start, end;
 int entries[70]; char *objects[17];
} TransitionScene;
extern TransitionScene D_001B8840;        /* controller state */
typedef struct {
 char pad[0x2c]; short flag; char pad2e[0x36]; int index, phase;
} TransitionMenu;
extern TransitionMenu D_00152C00;        /* mode block: +0x64 index, +0x68 phase */
extern int D_001B2130_first SDATA(D_001B2130);

extern int D_001B2130[] MACRO_ADDR __attribute__((sda));         /* [0] +0, [1] +4, [3] +0xC */
extern int D_001B2148[] __attribute__((sda));
extern int D_001B2148_first[] __asm__("D_001B2148") __attribute__((sda));         /* null-terminated entity list */
typedef struct { char pad[0x24]; float scale; } ScaleClass;
typedef struct { char pad[0x24]; ScaleClass *definition; int pad28; float scale; } ScaleEntity;
extern ScaleEntity *D_00214920[];         /* null-terminated entity list */
extern int D_001ABEB0 __attribute__((sda));
extern int D_001A7280;
extern int D_001A7280_block[] __asm__("D_001A7280") MACRO_ADDR __attribute__((sda));
extern int D_001B22B0;
typedef struct { int pad, data_offset; char gap[0x48]; int scenes[5]; } TransitionHeader;
typedef struct { int offset, size; } TransitionChunk;
typedef struct { char pad[12]; int start, end, pad14; TransitionHeader *data; } TransitionArchive;
extern TransitionArchive D_001BAEC0;
extern int D_001886D0[];
extern char D_00261F30[];        /* 16-byte entries */
typedef struct { float x, y, z, w; } TransitionVector;
typedef struct { char pad[0xc0]; TransitionVector basis[3]; } MatrixEntity;
extern TransitionVector D_001B20D0 MACRO_ADDR;
extern char D_001AC0C0[] SDATA(D_001AC0C0);
extern char D_001AC0D0[] SDATA(D_001AC0D0);
extern char D_001AC120[] SDATA(D_001AC120);
extern float D_001AC150[] SDATA(D_001AC150);
extern float D_001AC168[] SDATA(D_001AC168);
extern float D_001ABDD4 MACRO_ADDR;
extern float D_001ABF10 __attribute__((sda));
typedef struct { char pad[0xb0]; float fov; } TransitionView;
extern TransitionView D_001B9040;        /* view: +0xB0 float */

int func_US2_002E91C0(void)
{
    float sp0[4], sp10[4], sp20[16];
    float f20;
    int i, fp;

    func_002F5220();
    {
        float v = D_001B15A0 - 0.25f;
        D_001B8840.tick = D_001B8840.tick + 1;
        D_001B8840.frame = D_001B8840.frame + 1;
        D_001B15A0 = v;
        if (v < 0.0f)
            D_001B15A0 = 0.0f;
    }
    if (D_001B8840.frame == 1) {
        int n;
        func_00133220();
        n = D_00152C00.index;
        func_001329F0(D_001B2130[n], 0, 0x400, 0, 0, 0, 0, (int)D_001886D0 + n * 0x70);
        func_00133230();
        func_00132028();
    }
    if (D_001B8840.frame < D_001B8840.duration) {
        goto running;
    }
    /* the phase has ended */
    for (i = 0; i < D_001B8840.count; i++) {
        AnimationObject *p = (AnimationObject *)D_001B8840.objects[i];
        if (p != 0) {
            p->definition->count--;
            p->definition->animations[p->definition->count] = 0;
            func_0029F338(p);
        }
    }
    if (D_001ABEB0 != 0) {
        func_US2_002ED018();
        D_001ABEB0 = 0;
    }
    func_002ED260(D_00240450);
    if (D_001A7280 < 2)
        D_00152C00.phase = 0;
    if (D_00152C00.phase < 2) {
        if (D_00152C00.index != 2) {
            func_00132AA0();
            while (func_00132028() != 0)
                ;
        }
        if (D_00152C00.phase == 0) {
            int r = ((func_001163B0() >> 16) % 3) + 1;
            D_00152C00.index = (D_00152C00.index + r) & 3;
        } else {
            D_00152C00.index = 4;
            func_00133220();
            func_00132858(D_001B2130_first);
            func_00132858(D_001B2130[1]);
            func_00132858(D_001B2130[3]);
            func_00133230();
            while (func_00132028() != 0)
                ;
            func_00132818();
            D_001A7280_block[1] = 0;
            func_002E80B0();
        }
        D_00152C00.phase = D_00152C00.phase + 1;
        qcopy(D_001AC0D0, D_001AC0C0);
        func_00282A60(&D_001B8840, 0, 0x1D0);
        {
            int workspace_offset = D_001B22B0;
            TransitionHeader *header;
            TransitionChunk *chunk;
            int data_base;
            int k;
            D_001B8840.start = D_001BAEC0.start + workspace_offset;
            D_001B8840.end = D_001BAEC0.end + workspace_offset;
            header = D_001BAEC0.data;
            data_base = (int)header + header->data_offset;
            chunk = (TransitionChunk *)(data_base + header->scenes[D_00152C00.index]);
            for (k = 0; k < 70 && chunk->size != 0; k++) {
                int offset = chunk->offset + 0x800;
                D_001B8840.entries[k] = data_base + header->scenes[D_00152C00.index] + offset;
                chunk++;
            }
        }
        func_00294070(0);
        goto after;
    } else {
        if (D_001A7280_block[1] == 0)
            return 1;
        D_001A7280_block[1] = 0;
        return 1;
    }

running:
    if (!(D_001B8840.tick < 0x60)) {
        D_001B8840.page = D_001B8840.page + 1;
        func_00294070(D_001B8840.page);
    }
after:
    func_002E6A60();
    {
        float current = D_001B9040.fov;
        float t = D_001AC168[D_00152C00.index];
        if (current < t)
            D_001B9040.fov = t;
    }
    func_0027AB40();
    f20 = 1.0f;
    if (D_00152C00.index == 4) {
        f20 = (float)(D_001B8840.duration - D_001B8840.frame) / (float)D_001B8840.duration;
        func_00282D30(sp0, D_001AC120, f20);
        func_00282CC0(D_001AC0D0, D_001AC0D0, sp0);
    }
    func_00282D30(&D_001B20D0, D_00261F30 + D_00152C00.index * 16, (float)(D_001B8840.frame - 0x78) * (f20 * 20.0f));
    D_001ABDD4 = D_001AC150[D_00152C00.index];
    for (i = 0; i < D_001B8840.count; i = fp) {
        TransitionActor *o;
        int s1, s2;
        float r;
        char *s0m;
        s1 = D_001B8840.tick >> 1;
        o = (TransitionActor *)D_001B8840.objects[i];
        fp = i + 1;
        r = func_00283CE0(D_001B8840.tick & 1);
        s2 = s1 + 1;
        o->blend = r * 0.5f;
        s0m = (char *)o->keys;
        func_00282D30(sp0, s0m + s1 * 16, 1.0f - o->blend);
        func_00282D30(sp10, s0m + s2 * 16, o->blend);
        func_00282CC0(o->position, sp0, sp10);
        {
            char *d = (char *)o->definition;
            o->current_anim = B(d, 0xC) - 1;
            o->next_anim = B(d, 0xC) - 1;
            o->key = s1;
            o->next_key = s2;
        }
        func_0029F390(o);
        o->draw_flags = 0x1FF;
        if (o->type == 0xD54) {
            if (D_001B2148_first[0] != 0) {
                func_0029FC20(o, 0, sp20);
                {
                    int a3 = 0;
                    o->flags = 0;
                    o->draw_flags = 0;
                    if (D_001B2148_first[0] != 0) {
                        do {
                            int k;
                            B((char *)D_001B2148[a3], 0x63) = 0;
                            H((char *)D_001B2148[a3], 0x32) = 0x1FF;
                            qcopy((char *)D_001B2148[a3] + 0x10, o->position);
                            for (k = 0; k < 3; k++) {
                                ((MatrixEntity *)D_001B2148[a3])->basis[k].x = sp20[k * 4];
                                ((MatrixEntity *)D_001B2148[a3])->basis[k].y = sp20[k * 4 + 1];
                                ((MatrixEntity *)D_001B2148[a3])->basis[k].z = sp20[k * 4 + 2];
                            }
                            func_002A10E8((void *)D_001B2148[a3]);
                            a3 = a3 + 1;
                        } while (D_001B2148[a3] != 0);
                    }
                }
            } else {
                func_US2_002E72D8(D_001B8840.id);
            }
            o->opacity = 0xE8;
        }
        o->cached_frame = 0xFF;
        {
            {
                o->alpha = 0xFF;
            }
        }
        func_002A0F48(o);
        {
            char *d = (char *)o->definition;
            o->current_anim = B(d, 0xC) - 1;
            o->next_anim = B(d, 0xC) - 1;
            if (D_00152C00.index == 4) {
                int a0 = D_001B8840.duration;
                int v1 = D_001B8840.frame;
                if (a0 - 0x28 < v1) {
                    float f1 = (float)(a0 - v1 - 4) * 0.027777778f;
                    if (f1 < 0.0f)
                        f1 = 0.0f;
                    o->scale = F(d, 0x24) * f1;
                    D_001ABF10 = f1;
                    if (D_001B2148_first[0] != 0) {
                        char *e = (char *)D_001B2148_first[0];
                        F(e, 0x2C) = F((char *)W(e, 0x24), 0x24) * f1;
                    }
                    o->opacity = (int)(f1 * 232.0f);
                    if (o->type == 0xD54) {
                        if (D_001B2148_first[0] == 0) {
                            int j;
                            D_00152C00.flag = 1;
                            if (D_00214920[0] != 0) {
                                j = 0;
                                do {
                                    ScaleEntity *e = D_00214920[j];
                                    j++;
                                    e->scale = e->definition->scale * f1;
                                } while (D_00214920[j] != 0);
                            }
                        }
                    }
                }
            }
        }
    }
    func_002F52B8();
    return 0;
}
