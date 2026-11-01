#include "include_asm.h"

#include "common.h"
typedef union {
    u8 b[0x3F4];
    u16 uh[0x1FA];
    s32 i[0xFD];
    float f[0xFD];
    u8 *p[0xFD];
} EnemyStateView;
typedef union {
    s16 h[0x114C];
    s32 i[0x8A6];
} PlayerView;
typedef union {
    u16 uh[0x150];
    u32 ui[0xA8];
} HistoryView;
typedef union {
    u8 b[0x20];
    float f[8];
} PositionView;
extern PlayerView D_00189E20;
extern HistoryView D_0018C360;
extern u8 D_001A79F8[] __attribute__((sda));
extern unsigned D_001A7390[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern PositionView D_L18_001B97C0;
extern int D_L18_001AFBB0 __attribute__((sda));
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern int D_L18_001B1290 __attribute__((sda));
extern float D_L18_001B1294 __attribute__((sda));
extern float D_L18_001B12FC;
extern int func_L18_00427688(void *);
extern void func_0029F338(void *);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_002AEC48(void *,void *,int,float,float);
extern int func_002B0ED8(void *,void *,int);
extern void func_L18_00426F78(void *);
extern void func_L18_00427B48(void *,int);
extern void func_US2_002A7AA8(void *,int,int);
extern void func_L18_004273F0(void *);
extern void func_002A7750(void *,int,int);
extern int func_002B3BA8(void *, int, float, float, void *, int);
extern int func_002B38B8(void *);
extern void func_US2_0029C548(int,int);
extern void func_00335438(void *,void *,int,int,int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_US2_L18_002E02E8(int,int);
extern float func_00282E80(void *,void *);
extern void func_L00_003294F0(void *,int);
extern void func_L18_00426F28(void *,int,int,float);
extern void func_002B0C28(int,int,int);

/* Refreshes targeting and combat reactions, including the player capture transition. */
void func_US2_L18_004290D0(u8 *o) {
    EnemyStateView *s = *(EnemyStateView **)(o + 0x68);
    int hit;
    if (!o[0x95]) {
        s->i[0x3F0/4] = -1;
        if (func_L18_00427688(o)) {
            func_0029F338(o);
            return;
        }
    }
    if (o[0x31] && func_00282E48(o+0x10, &D_L18_001B97C0) < 24.0f) {
        func_002A93B0(o);
        o[0x6F] = 22;
    }
    if (!(s->b[0x3B1] & 0x80) || *(s16 *)(o+0xAA) != 0xEE1) {
        s->f[0x2B0/4] = 0.0f;
        func_002AEC48(o, s->b+0x240,4,1.0f,1.0f);
    } else if (D_001A79F8[0x4F]) {
        s->f[0x2B0/4] = 0.5f / D_L18_001B12FC;
        func_002AEC48(o,s->b+0x240,4,1.0f,1.0f);
    }
    if (o[0x95] != 8 && o[0xBC] != 1 && o[0x95] != 7 && !D_L18_001AFBB0 && D_00189E20.i[0x2294/4] != 111) {
        hit = func_002B0ED8(o,s->b+0x50,0);
        if (hit) {
            func_L18_00426F78(o);
            func_L18_00427B48(o,o[0x21]);
            if (hit == 4) {
                func_US2_002A7AA8(o,0,3);
                func_L18_004273F0(o);
                func_002A7750(o,12,10);
            }
        }
        s->b[0x3B2] = s->b[0x3B3];
        func_002B3BA8(o, s->i[0x37C / 4], 0.0f, 0.0f, 0, 0);
        {
            int id = *(s16 *)(s->p[0x230/4]+0xAA);
            s->b[0x3B3] = id == 0xEC0 || id == 0xED4 || id == 0xEE1;
        }
        if (!o[0xBC] && o[0x95] != 7 && func_002B38B8(o)) {
            o[0x30] = 255;
            func_US2_0029C548(0,0);
            func_L18_00426F78(o);
            func_00335438(&D_L18_001B97C0,D_L18_001B97C0.b+0x10,1,0,0);
            func_00335370(&D_L18_001B97C0);
            func_003353C8(D_L18_001B97C0.b+0x10);
            if (D_00189E20.i[0x2294/4] == 1 || D_00189E20.i[0x2294/4] == 29)
                func_US2_L18_002E02E8(0, 1);
            D_00189E20.h[0x1E0/2] = 20;
            s->f[0x3B8/4] = (func_00282E80(o+0x10,&D_L18_001B97C0)-D_L18_001B1294) / D_L18_001B1290;
            if (D_0018C360.uh[0x294/2] < 65535)
                ++D_0018C360.uh[0x294/2];
            if (D_001A7390[0] > D_0018C360.ui[0x298/4])
                D_0018C360.ui[0x298/4] = D_001A7390[0];
            D_0018C360.ui[0x29C/4] = (D_0018C360.ui[0x29C/4] | (1 << D_001A79F0[0])) | 0x80000000;
            func_L00_003294F0(o,0);
            s->uh[0x396/2] = *(u16 *)&D_L18_001B1290;
            func_L18_00426F28(o,16,0,10.0f);
            D_L18_001AFBB0 = 1;
            func_002B0C28(6,0,20);
            func_002A7750(o,0,7);
        }
    }
    o[0xA8] = 255;
    if (!s->i[0x1D8/4])
        func_002A7750(o, 12, 10);
    if (s->b[0x3E9] && (D_0019B2E8[o[0xB0]+(D_001A79F0_gp<<4)] & 0x80))
        func_002A7750(o, 12, 10);
    if (s->b[0x2E] == 2) {
        func_L18_00426F78(o);
        func_L18_00427B48(o,o[0x21]);
        func_L18_004273F0(o);
        func_002A7750(o,11,10);
    }
}
