#include "include_asm.h"
#include "common.h"
extern u8 D_L03_001A8F20[] MACRO_ADDR;
extern int func_00283D38(int, int, float);
typedef struct { float v[4]; } __attribute__((aligned(16))) VecF720;
typedef struct { VecF720 v[4]; int color[4]; float uv[4][2]; u64 r70, tex, r80, r88; } QuadF720;
extern float D_L03_001B1C10[4] __attribute__((sda));
extern float D_L03_001B1C20[4] __attribute__((sda));
extern VecF720 D_L03_001BFDE0, D_L03_001B9980;
extern int D_L03_001B1C78[2] __attribute__((sda));
extern int D_L03_001B1C80 __attribute__((sda)), D_L03_001B1C84 __attribute__((sda));
extern int D_L03_001B1C88 __attribute__((sda));
extern float D_L03_001B1C90 __attribute__((sda));
extern float D_L03_001B1C98[2] __attribute__((sda));
extern float D_L03_001B1CA0[8] __attribute__((sda));
extern float D_L03_001B1CA4[] MACRO_ADDR;
extern int D_L03_001B1CC0[2] __attribute__((sda));
extern int D_L03_001B2548, D_L03_001B1C8C;
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern u64 func_0027C878(int);
extern void func_00280B90(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern int func_002E59B0(void *, int);
void func_L03_0041F720(u8 *obj)
{
    QuadF720 q[2];
    VecF720 cross, delta, side, start, end;
    u8 hit[0x30] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    int j, k, n, c, trail, mask;
    float alpha, scale, w;

    D_L03_001B1C20[0] = *(float *)(state + 0x33C);
    func_00283098(&start, &D_L03_001B1C10, obj + 0xC0);
    func_00282CC0(&start, &start, obj + 0x10);
    func_00283098(&end, &D_L03_001B1C20, obj + 0xC0);
    func_00282CC0(&end, &end, obj + 0x10);
    {
        VecF720 *verts = q[0].v;
        int i;

        mask = 1;
        if (obj[0x95] == 2) mask = 0x10001;
        func_002A8C00(hit, obj, mask, &D_L03_001A8F20, (float)state[0x34]);
        {
            int found = func_002761F8(&start, &end, 0, obj, hit);
            QuadF720 *quads = q;

            if (found) qcopy(&end, &D_L03_001BFDE0);
            scale = 1.0f;
            func_00282CF0(&delta, &D_L03_001B9980, &start);
            func_00282CF0(&side, &end, &start);
            func_00282DD8(&cross, &side, &delta);
            func_00282F20(&cross, &cross, scale);
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 4; j++) {
                    w = 1.0f;
                    q[i].color[j] = func_00283D38(D_L03_001B1CC0[i] & 0xFF000000,
                                                 D_L03_001B1CC0[i], *(float *)(state + 0x330));
                    q[i].uv[j][0] = D_L03_001B1CA0[j * 2];
                    q[i].uv[j][1] = D_L03_001B1CA4[j * 2];
                    if (j & 1) func_00282D30(&q[i].v[j], &cross, D_L03_001B1C98[i]);
                    else func_00282D30(&q[i].v[j], &cross, -D_L03_001B1C98[i]);
                    if (j < 2) {
                        func_00282CC0(&q[i].v[j], &q[i].v[j], &start);
                    } else {
                        func_00282CC0(&q[i].v[j], &q[i].v[j], &end);
                    }
                    q[i].v[j].v[3] = w;
                }
                q[i].tex = func_0027C878(D_L03_001B1C78[i]);
                q[i].r80 = 0xFF9000000260ULL;
                q[i].r88 = ((u64)D_L03_001B1C80 << 2) | ((u64)D_L03_001B1C84 << 6) | 0x8000000000ULL;
                q[i].r70 = 0;
            }
            func_00280B90(&q[0], 0, 1);
            func_00280B90(quads + 1, 0, 1);
            for (n = 3, j = 0; n >= 0; n--, j++) { q[0].uv[j][0] = .5f; q[0].uv[j][1] = .5f; }
            alpha = .1f;
            if (D_L03_001B2548 & 1) alpha = 0;
            c = func_00283D38(D_L03_001B1C88, D_L03_001B1C8C, alpha);
            q[0].color[0] = q[0].color[1] = c;
            c = func_00283D38(D_L03_001B1C88, D_L03_001B1C8C, alpha + D_L03_001B1C90);
            q[0].color[2] = q[0].color[3] = c;
            {
                int span = *(s16 *)(state + 0x336) - 4;

                k = (*(s16 *)(state + 0x334) - span) % 4;
            }
            for (trail = 0; trail < *(s16 *)(state + 0x336); trail++) {
                qcopy(&q[0].v[0], state + 0x2A0 + k * 32);
                qcopy(&verts[1], state + 0x2B0 + k * 32);
                k = (k + 1) % 4;
                qcopy(&verts[2], state + 0x2A0 + k * 32);
                qcopy(&verts[3], state + 0x2B0 + k * 32);
                func_00280B90(&q[0], 0, 1);
                alpha += D_L03_001B1C90;
                c = func_00283D38(D_L03_001B1C88, D_L03_001B1C8C, alpha);
                q[0].color[0] = q[0].color[1] = c;
                c = func_00283D38(D_L03_001B1C88, D_L03_001B1C8C, alpha + D_L03_001B1C90);
                q[0].color[2] = q[0].color[3] = c;
            }
            qcopy(&q[0].v[0], state + 0x2A0 + k * 32);
            qcopy(&verts[1], state + 0x2B0 + k * 32);
            qcopy(&verts[2], &start);
            qcopy(&verts[3], &end);
            func_00280B90(&q[0], 0, 1);
            if (*(int *)(state + 0x340) == -1)
                *(int *)(state + 0x340) = func_002E5CF8(5, 4, obj);
            else if (!func_002E59B0(obj, *(int *)(state + 0x340)))
                *(int *)(state + 0x340) = func_002E5CF8(5, 4, obj);
        }
    }
}

extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern u8 *func_002A9640(void *, int, int);
extern int func_002B3868(void *);
extern int func_00282948(void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L03_00421930(void);
extern void func_L00_0032A530(void *, void *, void *, void *, int, int, int, int, int, int, void *);
typedef struct { u8 pad[0x120]; int entries[10]; int count; int active; } EntryGroup;
extern u8 D_L03_00259A30[];
typedef struct { u8 header[0x464]; u8 entries[0]; } TriggerTable;
extern TriggerTable D_L03_0021EA30;
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
typedef struct { unsigned short key; char reserved02[10]; } SelectorRow;
extern SelectorRow D_0018C958[];
extern int D_L03_001B2A38;
extern u8 *D_L03_001B2A1C;
extern u16 *D_L03_001FB5A0[];
extern float D_L03_001B1DA0[2] __attribute__((sda)), D_L03_001B1DA8[2] __attribute__((sda)), D_L03_001B1DB0[2] __attribute__((sda));
/* A four-state object. State 0 clears the 16 entry groups, then removes the object when its trigger
   entry is set or its 3-bit counter in the level's save bits (high nibble for an odd id, low nibble
   for an even one) is nonzero; otherwise it moves to state 1. State 1 waits for a hit from an object
   of class 0xCFC no lower than half a unit beneath it and sends every entity of its id list to state
   2. States 2 and 3 spawn rows of three explosions at rising heights on a timer, then state 3 raises
   the counter (up to 7), sets subtitle row 60's key to 0xFFFF, scatters the object's pieces and removes it. The row
   pointer is set at the store so the table keeps its own lui/addiu base, as retail has it. */
void func_L03_00421398(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 pos[16] __attribute__((aligned(16)));
    u8 *hit, *other;
    u16 *p;
    int i, j, index, bits;
    u8 *counter;
    SelectorRow *rows;

    if (!state) {
        func_0029F338(obj);
        return;
    }
    switch (obj[0x20]) {
    case 0: {
        int group;

        for (group = 0; group < 16; group++) {
            for (j = 0; j < ((EntryGroup *)(D_L03_00259A30 + group * 0x150))->count; j++)
                if (((EntryGroup *)(D_L03_00259A30 + group * 0x150))->entries[j])
                    ((EntryGroup *)(D_L03_00259A30 + group * 0x150))->entries[j] = 0;
            ((EntryGroup *)(D_L03_00259A30 + group * 0x150))->active = 0;
        }
        index = *(s16 *)(obj + 0xB2);
        if (D_L03_0021EA30.entries[index]) {
            func_0029F338(obj);
        } else {
            bits = D_0019B4A8[(index >> 1) + (D_001A79F0 << 10)];
            if (*(u16 *)(obj + 0xB2) & 1) {
                if ((bits >> 4) & 7) func_0029F338(obj);
                else func_002A7750(obj, 1, -1);
            } else {
                if (bits & 7) func_0029F338(obj);
                else func_002A7750(obj, 1, -1);
            }
        }
        break;
    }
    case 1:
        hit = func_002A9640(obj, 0x10000, 0);
        if (hit && (other = *(u8 **)(hit + 0x20)) && *(s16 *)(other + 0xAA) == 0xCFC &&
            *(float *)(obj + 0x18) <= *(float *)(other + 0x18) + 0.5f) {
            for (p = D_L03_001FB5A0[obj[0x21]];
                 obj[0x21] != 0xFF && obj[0x21] <= D_L03_001B2A38 && p != 0 &&
                 ((p != 0 && (s16)p[-1] >= 0) || p == D_L03_001FB5A0[obj[0x21]]); p++) {
                other = D_L03_001B2A1C + ((*p & 0x7FFF) << 8);
                if (!other) break;
                func_002A7750(other, 2, -1);
            }
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        if (func_002B3868(obj)) {
            *(int *)(state + 4) = 230;
            for (i = -1; i < 2; i++) {
                func_L00_00324F18(obj, pos, (float)(i << 3), -6.0f, 5.0f);
                func_0032C700(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 10;
        } else if (func_00282948(state + 4)) {
            for (i = -1; i < 2; i++) {
                func_L00_00324F18(obj, pos, (float)(i << 3), -6.0f, 15.0f);
                func_0032C700(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 10;
            func_002A7750(obj, 3, -1);
        }
        break;
    case 3:
        if (!func_00282948(state + 4)) break;
        for (i = -1; i < 2; i++) {
            func_L00_00324F18(obj, pos, (float)(i << 3), -6.0f, 25.0f);
            func_0032C700(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, i == 0, 0);
        }
        if (*(u16 *)(obj + 0xB2) & 1) {
            counter = D_0019B4A8 + ((*(s16 *)(obj + 0xB2) >> 1) + (D_001A79F0 << 10));
            if (((*counter >> 4) & 7) != 7) *counter += 16;
        } else {
            counter = D_0019B4A8 + ((*(s16 *)(obj + 0xB2) >> 1) + (D_001A79F0 << 10));
            if ((*counter & 7) != 7) *counter += 1;
        }
        rows = D_0018C958;
        rows[60].key = 0xFFFF;
        if (*(int *)state)
            func_L00_0032A530(obj, D_L03_001B1DB0, D_L03_001B1DA8, D_L03_001B1DA0,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, func_L03_00421930);
        else
            func_L00_0032A530(obj, D_L03_001B1DB0, D_L03_001B1DA8, D_L03_001B1DA0,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, 0);
        func_0029F338(obj);
        break;
    }
}
