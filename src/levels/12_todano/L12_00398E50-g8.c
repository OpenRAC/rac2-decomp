#include "common.h"

extern u8 *D_L12_001B2E9C __attribute__((sda));

extern u16 *D_L12_001FB960[];

extern s32 D_L12_001B09F4 __attribute__((sda));

extern s32 func_31DEF0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

extern void func_31E1D0(void *arg0, s32 arg1, s32 arg2);

extern void func_2F1958(f32 *buf, u8 *arg1, u8 *arg2);

extern void func_323F98(f32 *buf, f32 x);

extern void func_2F1928(u8 *arg0, u8 *arg1, f32 *buf);

extern void func_321940(u8 *arg0, s32 arg1, f32 x, f32 y);

extern void func_3239B8(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);

extern s32 D_L12_001B1838 __attribute__((sda));

extern s32 D_L12_001B183C __attribute__((sda));

extern s32 D_L12_001B1840 __attribute__((sda));

extern u16 D_L12_001B1834 __attribute__((sda));

extern f32 D_L12_001B1858 __attribute__((sda));

extern s32 func_2F15C8(void *arg0);

extern s32 func_31E2E0(s32 arg0, s32 arg1);

extern void func_3296A8(void *arg0, void *arg1, s32 arg2, f32 x, s32 arg3);

/* Walks the measured table of the given index down to its terminator. */
s32 func_L12_003E09C8(s32 index) {
    u16 *entry = D_L12_001FB960[index];
    u16 packed;
    u8 *base;

    if (entry == 0)
        return 1;
    base = D_L12_001B2E9C;
    do {
        u8 *record;
        packed = *entry;
        record = base + (packed & 0x7FFF) * 0x100;
        if (*(s16 *)(record + 0xAA) == 0xBB8) {
            if (*(u8 *)(record + 0x20) != 1)
                return 0;
        }
        entry++;
    } while ((s16)packed >= 0);
    return 1;
}

/* Arms the measured sub-object on the first entry. */
void func_L12_003E0A38(u8 *object, u8 *arg1, u8 *arg2, s32 arg3) {
    f32 buffer[4];
    u16 flags;

    if (*(u8 *)(object + 0x43) != 0xA)
        func_31DEF0(object, 0xA, 0, 5);
    if (*(u8 *)(object + 0xBC) != 8)
        func_31E1D0(object, 8, 1);
    func_2F1958(buffer, arg1, object + 0x10);
    func_323F98(buffer, 0.16666667f);
    func_2F1928(object + 0x10, object + 0x10, buffer);
    func_321940(object + 0xF8, 0, *(f32 *)(arg2 + 8), 0.20943954f);
    if (arg3 != 0) {
        flags = *(u16 *)(object + 0x34);
        D_L12_001B09F4 = D_L12_001B09F4 + 1;
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (flags | 0x41) & 0xEFFF;
        func_3239B8(object, object + 0x10, -1, 1.0f, 0.0f);
        func_31E1D0(object, 1, 0);
    }
}

/* Steps the measured slot timer and restarts the tracked sub-object. */
void func_L12_00413F68(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    if (*(u8 *)(state + 0x2EA) != 0) {
        *(u8 *)(state + 0x2EA) = 0;
        if (*(s16 *)(state + 0x2E0) < D_L12_001B1838)
            *(u16 *)(state + 0x2E0) = func_31E2E0(D_L12_001B183C, D_L12_001B1840);
    }
    if (func_2F15C8(state + 0x2E0) == 0)
        *(u16 *)(state + 0x2E8) = D_L12_001B1834;
    func_2F15C8(state + 0x2E2);
    func_2F15C8(state + 0x2E6);
    func_2F15C8(state + 0x2E8);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
    func_3296A8(*(void **)(state + 0x2F8), state + 0x420, 3, D_L12_001B1858, 1);
}

extern u8 *D_L12_001B090C __attribute__((sda));

extern u8 *D_L12_001B1360 __attribute__((sda));

/* Whether the tracked object is in a state that still counts as open. */
s32 func_L12_003DE4B0(void) {
    u8 *object = D_L12_001B090C;
    s32 result = 1;

    if (object == 0) {
        result = 0;
    } else {
        if (*(u8 *)(object + 0x20) == 6 || *(s8 *)(object + 0x20) < 0
            || *(u8 *)(object + 0x20) == 8)
            result = 0;
    }
    return result;
}

/* The same test, with one more state in the closed set. */
s32 func_L12_00404778(void) {
    u8 *object = D_L12_001B1360;
    s32 result = 1;

    if (object == 0) {
        result = 0;
    } else {
        if (*(u8 *)(object + 0x20) == 6) {
            result = 0;
        } else if (*(u8 *)(object + 0x20) == 5 || *(u8 *)(object + 0x20) == 8
                 || *(s8 *)(object + 0x20) < 0) {
            result = 0;
        }
    }
    return result;
}


extern int func_00283CF0(float);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *,void *,int);
extern void func_L12_003E1AA8(void *);
extern int func_002B3BA8(void *,int,int,int,float,float);
extern int func_002A8AF0(void *,void *,int,float);
extern void func_002B0990(void *,void *,int,int,float);
extern u8 D_L12_001B9E00[];
extern u8 *D_0018C0B0 NOT_SDA;
extern u8 *D_L12_001FEAC0[];
extern float D_L12_001B0A40 __attribute__((sda));

/* Sets up the object's AI parameters on its first update, then refreshes its target state and
   clears it when the target leaves the object's zone. */
void func_L12_003E1638(u8 *o) {
    u8 *d=*(u8 **)(o+0x68);
    if(!o[0x20]) {
        *(short *)(*(u8 **)(o+0x24)+0x46)=5;
        *(u16 *)(o+0x34)|=0x1000;
        d[0x48]=FloatToInt(15.0f);d[0x4A]=FloatToInt(6.0f);
        d[0x29]=1;
        d[0x70]=8; *(int *)(d+0xA8)=3; d[0x71]=11; d[0x72]=11;
        d[0x76]=13; d[0x77]=14;
        *(float *)(d+0x7C)=1.0f/6.0f; *(float *)(d+0x80)=1.0f/12.0f;
        *(float *)(d+0x84)=0.0055555557f;
        *(float *)(d+0x88)=1.0f/120.0f; *(float *)(d+0x8C)=1.0f/240.0f;
        *(float *)(d+0x90)=0.5f; *(float *)(d+0x94)=0.5f; *(float *)(d+0x9C)=0.4f;
        d[0xCC]=7; d[0xCD]=10; d[0xCE]=7; d[0xCF]=10; d[0xD2]=8; d[0xD3]=12;
        if(*(float *)(d+0x36C)==0) *(float *)(d+0x36C)=16;
        if(*(float *)(d+0x370)==0) *(float *)(d+0x370)=24;
        if(*(int *)(d+0x140)) *(float *)(d+0x20)=1;
        d[0x28]=3;
        qcopy_nc(d+0x340,o+0x10);
        *(u8 **)(d+0x198)=d+0x240;*(u8 **)(d+0x19C)=d+0x2C0;
        *(float *)(d+0x184)=1;*(float *)(d+0x154)=0.25f;*(float *)(d+0x150)=0.5f;
        *(float *)(d+0x158)=0.4f;*(float *)(d+0x15C)=0.4f;
        *(float *)(d+0x160)=0.78539824f;*(float *)(d+0x180)=0.52359885f;
        *(float *)(d+0x17C)=0.0055555557f;
        if(*(int *)(d+0x378)!=-1) func_002A7750(o,14,5);
        else if(*(int *)(d+0x13C)==-1) {
            func_002A7750(o,1,0);
            if(o[0x43]) func_002A7470(o,0,0,0);
        } else {
            func_002A7750(o,9,4);
            if(o[0x43]!=14) func_002A7470(o,14,0,0);
            *(float *)(o+0x18)+=4;*(int *)(o+0x98)=0;
            *(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|0x41)&0xEFFF;
        }
    }
    if(o[0x31] && fast_vec_dist(o+0x10,D_L12_001B9E00)<24) {func_002A93B0(o);o[0x6F]=22;}
    if(func_002B0ED8(o,d+0x60,0)) func_L12_003E1AA8(o);
    *(short *)(d+0x364)=func_002B3BA8(o,-1,0,0,*(float *)(d+0x36C),3);
    if(*(u8 **)(d+0x120)) *(u8 **)(d+0x368)=*(u8 **)(d+0x120); else *(u8 **)(d+0x368)=D_0018C0B0;
    if(*(short *)(d+0x364)==1) {
        float range=D_L12_001B0A40;
        if(*(int *)(d+0x130)!=-1) {
            u8 *zone=D_L12_001FEAC0[*(int *)(d+0x130)];
            if(!point_in_path_xy(*(u8 **)(d+0x120)+0x10,zone+0x10,*(int *)zone,range)) *(short *)(d+0x364)=0;
        }
    }
    func_002B0990(o,d+0x3C0,1,1,D_L12_001B0A40);
}

/* The subtitle history (src/game/00289178.c): per record, its play count, the time it was last
   played and the levels it was played in (bit 31: played at all). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern void func_00288E18(int,int);

/* Plays subtitle lines, each gated on its record in the subtitle history (the record index is
   the second argument of func_00288E18). */

extern u8 D_00189EA0[];
extern SubtitleHistory D_0018C958[];
extern u8 D_001A7AF8[] __attribute__((sda));
extern u32 D_001A7390;
extern int D_001A79F0[] __attribute__((sda));
extern int D_0018C0B4 NOT_SDA;
extern int func_002ACBC8(void *,int);
extern void func_00282948(void *);

/* Plays subtitle lines, each gated on its record in the subtitle history (the record index is
   the second argument of func_00288E18). */
void func_L12_003EB470(u8 *o) {
    u8 *d = *(u8 **)(o + 0x68);

    switch (o[0x20]) {
    case 0:
        o[0x30] = 255;
        *(int *)(d + 0x10) = -1;
        func_002A7750(o, 1, -1);
        break;
    case 1:
        if (IsPointInCuboid(D_00189EA0, *(int *)d) && *(int *)(D_00189EA0 + 0x540)
            && !D_0018C958[121].count)
            func_00288E18(0xA22, 121);
        if (IsPointInCuboid(D_00189EA0, *(int *)(d + 4)) && !D_001A7AF8[0x33]) {
            if (D_0018C958[92].count) {
                u32 now = D_001A7390;
                u32 old = D_0018C958[92].time;

                if (now - old > 0x438 || old == 0)
                    func_00288E18(0xA05, 92);
                else if (old < now)
                    D_0018C958[92].time = now;
            } else {
                if (D_0018C958[92].count < 65535)
                    D_0018C958[92].count++;
                if (D_0018C958[92].time < D_001A7390)
                    D_0018C958[92].time = D_001A7390;
                D_0018C958[92].levels = (D_0018C958[92].levels | (1u << D_001A79F0[0])) | 0x80000000u;
            }
        }
        if (IsPointInCuboid(D_00189EA0, *(int *)(d + 8))) {
            u8 *p = D_L12_001B2E9C + (*(int *)(d + 0xC) << 8);

            if (p && *(s16 *)(p + 0xAA) == 0xFB8 && p[0x20] != 254 && p[0x20] != 253) {
                if (*(int *)(d + 0x10) < 0)
                    *(int *)(d + 0x10) = 0x2A30;
                else if (!*(int *)(d + 0x10)) {
                    u32 seen = D_0018C958[93].levels & (1 << D_001A79F0[0]);

                    if (!seen)
                        func_00288E18(0xA06, 93);
                }
            }
        }
        if (D_001A7AF8[7] && D_0018C0B4 != 0x6F) {
            u32 seen = D_0018C958[127].levels & (1 << D_001A79F0[0]);

            if (!seen)
                func_00288E18(0xA28, 127);
        }
        if (*(int *)(d + 0x10) >= 0)
            func_00282948(d + 0x10);
        break;
    }
}
