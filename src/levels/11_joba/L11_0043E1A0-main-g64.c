/* func_L11_0043E1A0 in its own unit (-G64 -Wa,-G64: the 56-byte class table is small data).
 * What decided the match:
 * - The state block and the object are real structs (JobaState, JobaObj), not byte views.
 * - Globals by retail form: lui/load in ordinary flow plus $gp in delay slots = a plain
 *   sized scalar; $gp everywhere = sda with its measured size; explicit %hi/%lo = an
 *   incomplete array. 0x001B3774 is element 1 of the sound pair D_L11_001B3770[2] (a
 *   symbol+offset access never fills a slot); the height band's bounds are two sda scalars.
 * - The clear loops count up; the marks and limits loops share one counter.
 * - Case 2's shared tail is written out per arm; case 9's 13-or-5 code per arm with the
 *   timer store in each arm (cross-jumping keeps retail's then-arm + b).
 * - The sound-slot blocks read st->sound before the slot test and pass the second slot's
 *   buffer as a pointer plus 0xE0; index-first sums where retail adds the index first.
 * - Case 8's wave end reads the class as (u16) into cls3 right after cls1.
 * - func_L00_0030DD70 is called for its effect only and declared void here: its ignored
 *   $v0 result otherwise takes v0 from the case-9 light/lamp chain in local-alloc.
 *   (Its definition in src/levels/shared/L00_002FC7A0.c returns its argument or the
 *   helper's value.)
 * - Case 9's start flags are set D_L11_001A8FF4 first, then D_L11_001A8FF0.
 */
#include "common.h"

/* func_L11_0043E1A0: the level's scripted-encounter driver, dispatched on the object's state
   byte 0x20.  Built -G8 in its own unit: the class tables and their constants sit in the level's
   small data and are reached through $gp, while the controls declared MACRO_ADDR are macro
   operands that the assembler expands to lui/low-half in ordinary flow and to one $gp access in
   a delay slot. */

/* The hero block at D_00189E20; 0x80 is the position read as D_00189EA0 elsewhere. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

/* The object's own fields (state 0x20, timer 0x96, phase 0xBC) and the state block at 0x68. */
typedef struct JobaState {
    u8 pad000[0x90];
    f32 delay[4];        /* 0x90 */
    f32 phase[4];        /* 0xA0 */
    f32 speed[4];        /* 0xB0 */
    u8 pad0C0[0x20];
    s32 limits[6];       /* 0xE0 */
    u8 pad0F8[8];
    s32 counts[8];       /* 0x100 */
    u8 *slots[8];        /* 0x120 */
    s32 lost;            /* 0x140 */
    u8 pad144[0xC];
    s32 trigger1;        /* 0x150 */
    s32 trigger2;        /* 0x154 */
    u8 pad158[0x14];
    s32 camera;          /* 0x16C */
    u8 pad170[0x10];
    s32 sound;           /* 0x180 */
    s32 owner;           /* 0x184 */
    s32 frames;          /* 0x188 */
    s32 slot;            /* 0x18C */
    u8 pad190[0xC];
    f32 heading;         /* 0x19C */
    u8 pad1A0[0x18];
    s32 door;            /* 0x1B8 */
    u8 pad1BC[4];
    s32 light;           /* 0x1C0 */
    u8 pad1C4[0xC];
    s32 lamp;            /* 0x1D0 */
    s32 gate1;           /* 0x1D4 */
    s32 gate2;           /* 0x1D8 */
    s32 gate3;           /* 0x1DC */
    u8 pad1E0[4];
    s32 zone;            /* 0x1E4 */
    s16 result;          /* 0x1E8 */
    u8 pad1EA[6];
    s16 cls;             /* 0x1F0 */
    s16 wave;            /* 0x1F2 */
    s16 fade;            /* 0x1F4 */
    u8 pad1F6[4];
    s16 mode;            /* 0x1FA */
    u8 pad1FC[0xA4];
    s16 marks[0x28];     /* 0x2A0 */
    s32 music;           /* 0x2F0 */
    u8 pad2F4[4];
    s32 volume;          /* 0x2F8 */
    u8 pad2FC[4];
    s32 track;           /* 0x300 */
    s32 trackVolume;     /* 0x304 */
} JobaState;

typedef struct {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x68 - 0x21];
    JobaState *st;       /* 0x68 */
    u8 pad6C[0x96 - 0x6C];
    u16 timer;           /* 0x96 */
    u8 pad98[0xBC - 0x98];
    u8 phase;            /* 0xBC */
} JobaObj;

typedef int TI128 __attribute__((mode(TI)));

/* One 26-byte class record: the six target counts, then the flag bytes. */
typedef struct {
    s16 h[10];
    u8 b[6];
} JobaRecord;

typedef struct {
    s16 count;
    JobaRecord *records;
    s32 id;
} JobaClass;

typedef struct {
    u8 pad0[0x284];
    s32 owner;
    s32 timer;
} JobaFlags;

/* A moby record of the level's moby array (0x100 bytes). */
typedef struct {
    u8 pad0[0x18];
    f32 y;
    u8 pad1[0x31 - 0x1C];
    u8 hidden;
    u8 pad2[2];
    u16 flags;
    u8 pad3[0x100 - 0x36];
} JobaMoby;

/* A 0x40-byte record of the level's light table. */
typedef struct {
    u8 pad0[0x30];
    f32 pos[2];
    f32 height;
    u8 pad1[0x40 - 0x3C];
} JobaLight;

extern char D_00189E20[];
extern u8 D_001395B8[];
extern u8 D_00139586[];
extern s32 D_00139700[];
extern s32 D_001A7904;
extern u16 D_001A65D2[];
extern s32 D_001A7A00;
extern s32 D_001A7BC0;
extern s32 D_001A7390;
extern u8 D_001A63A8[];

extern f32 D_L11_001A7CD8;
extern s32 D_L11_001A8F00;
extern s32 D_L11_001A8FF0;
extern s32 D_L11_001A8FF4;
extern s32 D_L11_001A9010;
extern u16 **D_L11_001A9014;
extern s32 D_L11_001AA170;
extern u8 D_L11_001B14B0[8] __attribute__((sda));
extern s32 D_L11_001B14B8[6] __attribute__((sda));
extern s32 D_L11_001B14D0[2] __attribute__((sda));
extern s32 D_L11_001B14D8[8] __attribute__((sda));
extern JobaClass *D_L11_001B14F8[14] __attribute__((sda));
extern f32 D_L11_001B1570[4] __attribute__((sda));
extern f32 D_L11_001B1580 __attribute__((sda));
extern f32 D_L11_001B1584 __attribute__((sda));
extern s32 D_L11_001B1588 __attribute__((sda));
extern f32 D_L11_001B1590[2];
extern f32 D_L11_001B1598[2];
extern char D_L11_001B15A0[];
extern f32 D_L11_001B2FE0;
extern s32 D_L11_001B30C8;
extern JobaMoby *D_L11_001B359C;
extern s32 D_L11_001B3680;
extern u8 *D_L11_001B368C;
extern s32 D_L11_001B3770[2];
extern JobaLight *D_L11_001B3C1C;
extern JobaFlags D_L11_001BA780;
extern s32 D_L11_001CAE40[];
extern u8 D_L11_001FFA78[];
/* One 0xE0-byte record of the level's selection table. */
typedef struct {
    u8 pad0[4];
    u8 enabled;
    u8 pad5[0xE0 - 5];
} JobaChoice;

extern JobaChoice D_L11_00279BA0[];

extern int func_00115DA8(char *, const char *, ...);
extern void func_00282A60(void *, int, int);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283CE0(s32);
extern s32 func_00288D58(void);
extern s32 func_00288FB8(s32);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002ACBC8(void *, s32);
extern void func_002AD860(s32);
extern void func_002B0C28(s32, s32, s32);
extern s32 func_002B3868(u8 *);
extern void func_002DF3F8(void *, void *);
extern void func_00335438(char *, char *, int, int, int);
extern void func_003355A8(int);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern void func_L00_002C8BA8(s32);
extern void func_L00_002D40A0(void *, int, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_00303530(int, int);
/* Defined returning int (L00_002FC7A0.c), but retail compiled this caller as a void call, as
   the registers after the call show: the original header evidently declared it void. */
extern void func_L00_0030DD70(int, int);
extern int func_L00_003206B8(void *, int);
extern void func_L00_003294F0(u8 *, s32);
extern void func_L00_003672F8(void);
extern void func_L00_003DF6B0(int, int);
extern void func_L00_003E4948(void);
extern void func_L00_004028C0(char *, int);
extern void func_L01_00323310(s32, s32);
extern s32 func_L02_003D77B8(u8 *);
extern void func_L02_003FF698(void *);
extern s32 func_L11_002D8EF8(s32, s32);
extern int func_L11_0043E090(unsigned int);
extern int func_L11_0043E108(unsigned int);
extern void func_L11_00440160(u8 *);
extern void func_L11_004401C0(u8 *);
extern void func_L11_00440238(u8 *);
extern void func_L11_00440360(u8 *);
extern s32 func_L11_00440790(u8 *, s32, s32);
extern s32 func_L11_00440868(u8 *, s32, s32);
extern void func_L11_00440E18(u8 *);
extern void func_L11_00441090(u8 *);
extern void func_L11_00441108(u8 *);
extern void func_L11_004411C8(u8 *);
extern void func_L11_00441350(u8 *);
extern u8 *func_L11_004417E8(u8 *);
extern void func_L11_00441A58(u8 *, s32);
extern void func_L11_00441D08(u8 *, s32);
extern void func_L11_00442170(u8 *);
extern void func_L11_004423F8(u8 *);
extern s32 func_L11_00442710(u8 *);
extern void func_L11_004427B8(char *, int);
extern void func_L11_00442C80(u8 *);
extern void func_L11_00442E38(u8 *);
extern void func_L11_00443380(u8 *);
extern void func_L11_004433D8(u8 *);
extern void func_L11_00443498(u8 *);
extern void func_L11_00444400(u8 *);
extern void func_L11_00445990(char *);
extern s32 func_L11_00445D28(u8 *, s32);
extern void func_L11_00445B30(u8 *);
extern void func_L11_00446020(u8 *);
extern void func_L11_004461E8(u8 *);
extern void func_L11_00446C78(u8 *);
extern void func_L11_00446EB8(u8 *);
extern void func_L11_00447018(u8 *, s32);
extern void func_L11_004471A8(u8 *, void *);
extern void func_L11_00447360(char *);

#define HERO ((Hero *)D_00189E20)
#define TABLE D_L11_001B14F8
#define OBJ ((JobaObj *)obj)

void func_L11_0043E1A0(u8 *obj) {
    JobaState *st;
    JobaRecord *rec1;
    JobaRecord *rec3;
    JobaRecord *rec2;
    JobaRecord *rec6;
    JobaRecord *rec8;
    JobaRecord *rec9;
    s32 ok1;
    s32 ok2;
    s32 sum1;
    s32 sum2;
    s32 sum3;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 cls1;
    s32 cls2;
    u32 cls3;
    JobaLight *lt1;
    JobaLight *lt2;
    JobaLight *lt3;
    JobaLight *lt4;
    JobaMoby *m1;
    JobaMoby *m2;
    JobaMoby *m3;
    u8 *e1;
    u8 *e2;
    f32 f1;
    f32 f2;
    u8 *p1;
    u8 *q1;
    s32 slot1;
    s32 k1;
    s32 k2;
    s32 k3;
    s32 k4;
    s32 k5;
    s32 k6;
    s32 k7;
    s32 k8;
    s32 k9;
    s32 k10;
    s32 c10;
    s32 c11;
    s32 k11;
    s32 k12;
    s32 k13;
    s32 sel;
    s32 code;
    JobaClass *cl1;
    s32 w1;
    JobaRecord *next1;
    s32 snd1;
    u8 *buf2;
    u8 *buf3;
    s32 snd2;
    s32 snd3;

    st = OBJ->st;
    func_L00_003E4948();
    D_L11_001A9010 = 1;
    switch (OBJ->state) {
    case 0:
        func_L11_004401C0(obj);
        func_L11_00442C80(obj);
        D_L11_001A8FF0 = 0;
        D_L11_001A8FF4 = 0;
        D_L11_001B359C[st->door].flags |= 1;
        D_L11_001B359C[st->door].hidden = 0;
        if (D_001A7904 == 2) {
            D_001A7904 = 0;
            func_002A7750(obj, 2, -1);
            func_L00_003672F8();
            st->fade = D_001A65D2[0];
            func_L00_002E6CF0(func_L11_00445B30, obj);
            OBJ->timer = 0x1F;
        }
        break;
    case 1:
        if (func_L00_003206B8(&HERO->f[0x80 / 4], st->zone) != 0) {
            func_002A7750(obj, 4, -1);
        } else if (func_002ACBC8(&HERO->f[0x80 / 4], st->trigger1) != 0) {
            func_002B0C28(4, 0x2F3C, 1);
            func_L02_003FF698(obj);
        } else if (D_001395B8[func_L11_0043E108(1)] != 0) {
            if (func_002ACBC8(&HERO->f[0x80 / 4], st->trigger2) != 0) {
                func_002B0C28(4, 0x2F3C, 1);
                func_L02_003FF698(obj);
            }
        }
        if (D_001A7904 == 2) {
            D_001A7904 = 0;
            func_002A7750(obj, 2, -1);
            func_L00_003672F8();
            st->fade = D_001A65D2[0];
            func_L00_002E6CF0(func_L11_00445B30, obj);
            OBJ->timer = 0x1F;
        }
        D_L11_001A9010 = 0;
        break;
    case 2:
        if (func_002B3868(obj) != 0) {
            func_L11_00441A58(obj, 0);
            func_L11_00441D08(obj, 0);
            OBJ->phase = 0;
            D_L11_001B359C[st->door].flags |= 1;
            D_L11_001B359C[st->door].hidden = 0;
            lt3 = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
            m1 = &D_L11_001B359C[st->lamp];
            lt3->height = 419.766f;
            m1->y = 419.766f;
        } else if (OBJ->phase == 0) {
            if (OBJ->timer < 0x1F) {
                D_L11_001B2FE0 = func_00283CE0(OBJ->timer) * 0.05f < 1.0f
                                     ? func_00283CE0(OBJ->timer) * 0.05f
                                     : 1.0f;
            } else {
                f32 v[4] __attribute__((aligned(16)));

                st->fade = D_001A65D2[0];
                func_L00_002E6CF0(func_L11_00445B30, obj);
                if (D_L11_001CAE40[0] != 1) {
                    func_L00_00303530(1, st->music);
                }
                p1 = D_L11_001B368C + (st->camera << 7);
                func_L00_002B9D60(p1 + 0x30, p1 + 0x70, 0x6F, 1);
                func_002DF3F8(&HERO->f[0x80 / 4], &HERO->f[0x90 / 4]);
                func_L01_00323310(st->music, st->volume);
                *(TI128 *)v = *(TI128 *)(D_L11_001B368C + ((st->camera << 7) + 0x30));
                v[2] += 2.0f;
                func_00335438((char *)v, (char *)(D_L11_001B368C + (st->camera << 7) + 0x70), 1, 0, 0);
                OBJ->phase = 2;
            }
        } else if (OBJ->phase == 2) {
            func_L00_002E6EF8(func_L11_00445B30, obj);
            D_L11_001B2FE0 = 0.0f;
            if (st->fade <= 0) {
                OBJ->phase = 3;
                func_L00_002C8BA8(0);
                func_L00_002D40A0(func_L11_004417E8(obj), 0, 0.0f);
            }
        } else if (OBJ->phase == 3) {
            if (func_00282E80(&HERO->f[0x80 / 4], func_L11_004417E8(obj)) < 10.0f) {
                if (D_001395B8[0x4A] == 0) {
                    D_001395B8[0x4A] = 1;
                    OBJ->phase = 1;
                    func_L00_003294F0((u8 *)&D_L11_001B359C[st->gate1], 1);
                    OBJ->timer = 0;
                } else if (D_001395B8[func_L11_0043E108(0)] != 0) {
                    func_002A7750(obj, 4, -1);
                } else {
                    func_L00_002B9D60(func_L11_004417E8(obj), D_L11_001B1570, 0, 1);
                    st->cls = 0;
                    st->wave = 0;
                    func_002A7750(obj, 8, -1);
                    func_003355A8(2);
                }
            }
        } else if (OBJ->phase == 1) {
            if (OBJ->timer >= 0x3D && D_L11_001A8F00 != 2) {
                if (D_001395B8[func_L11_0043E108(0)] == 0) {
                    func_L00_002B9D60(func_L11_004417E8(obj), D_L11_001B1570, 0, 1);
                    st->cls = 0;
                    st->wave = 0;
                    func_002A7750(obj, 8, -1);
                    func_003355A8(2);
                } else {
                    func_002A7750(obj, 4, -1);
                }
            }
        }
        break;
    case 5:
        if (OBJ->timer < 0xB4) {
            func_L11_00441A58(obj, 0);
            func_L11_00441D08(obj, 0);
            HERO->f[0x24A4 / 4] = 300.0f;
            func_L11_00442170(obj);
            break;
        }
    case 4:
        if (func_002B3868(obj) != 0) {
            if (OBJ->state == 5) {
                func_L11_004427B8((char *)obj, st->cls);
            }
            D_L11_001B359C[st->door].flags |= 1;
            D_L11_001B359C[st->door].hidden = 0;
            func_L11_00442C80(obj);
            func_L11_004411C8(obj);
            func_L11_00441A58(obj, 0);
            func_L11_00441D08(obj, 0);
            func_L00_002B9D60(func_L11_004417E8(obj), D_L11_001B1570, 0x6F, 1);
            func_002DF3F8(&HERO->f[0x80 / 4], &HERO->f[0x90 / 4]);
            func_L11_00443380(obj);
            st->mode = 5;
            func_L11_004461E8(obj);
            D_L11_001A8FF4 = 0;
            D_L11_001A8FF0 = 0;
        }
        func_L11_004433D8(obj);
        break;
    case 11:
        if (OBJ->timer < 0x168) {
            func_L11_00441A58(obj, 0);
            func_L11_00441D08(obj, 0);
            if (OBJ->timer >= 0xB5) {
                HERO->f[0x24A4 / 4] = 200.0f;
            }
            func_L11_00442170(obj);
        } else {
            func_002A7750(obj, 4, -1);
        }
        break;
    case 12:
    case 13:
        if (func_002B3868(obj) != 0) {
            func_L11_00441A58(obj, 0);
            func_L11_00441D08(obj, 0);
            OBJ->phase = 0;
        }
        if (OBJ->phase == 0) {
            if (OBJ->timer < 0xB4) {
                HERO->f[0x24A4 / 4] = 200.0f;
                func_L11_00442170(obj);
                break;
            }
            if (OBJ->state == 12) {
                func_L00_003294F0((u8 *)&D_L11_001B359C[st->gate2], 1);
            } else if (OBJ->state == 13) {
                func_L00_003294F0((u8 *)&D_L11_001B359C[st->gate3], 1);
            }
            OBJ->timer = 0;
            OBJ->phase = 1;
        } else if (HERO->i[0x24CC / 4] > 0 && D_L11_001A8F00 != 2 && OBJ->timer >= 0xF1) {
            func_L11_004427B8((char *)obj, st->cls);
            OBJ->state = 5;
            D_L11_001B359C[st->door].flags |= 1;
            D_L11_001B359C[st->door].hidden = 0;
            func_L11_00442C80(obj);
            func_L11_004411C8(obj);
            func_L11_00441A58(obj, 0);
            func_L11_00441D08(obj, 0);
            func_L00_002B9D60(func_L11_004417E8(obj), D_L11_001B1570, 0x6F, 1);
            func_002DF3F8(&HERO->f[0x80 / 4], &HERO->f[0x90 / 4]);
            func_L11_00443380(obj);
            D_L11_001A8FF4 = 0;
            D_L11_001A8FF0 = 0;
        }
        break;
    case 6:
        func_L11_00445990((char *)obj);
        break;
    case 7:
        if (func_002B3868(obj) != 0) {
            sel = D_001395B8[0x49];
            if (sel != 0 && (D_001395B8[func_L11_0043E108(TABLE[sel]->id)] == 0 ||
                             (sel >= 11 && func_00288D58() == 0) ||
                             (sel == 8 && D_00139586[0][D_L11_00279BA0].enabled == 0))) {
                sel = 0;
            }
            st->result = sel;
        }
        func_L11_00443498(obj);
        break;
    case 8:
        func_L11_0043E108(1);
        if (func_002B3868(obj) != 0) {
            st->wave = 0;
            for (k1 = 0; k1 < 8; k1++) {
                st->counts[k1] = 0;
            }
            st->frames = 0;
            st->lost = 0;
            func_L11_00442C80(obj);
            func_L11_00440238(obj);
            func_L11_00442E38(obj);
            rec1 = &TABLE[st->cls]->records[st->wave];
            func_L11_00441A58(obj, rec1->h[7]);
            func_L11_00441D08(obj, rec1->h[6]);
            for (k3 = 0; k3 < 40; k3++) {
                st->marks[k3] = 0;
            }
            for (k3 = 0; k3 < 6; k3++) {
                st->limits[k3] = D_L11_001B14B0[k3];
            }
            HERO->i[0x24CC / 4] = D_001A7A00;
            func_L11_00447360((char *)obj);
            D_L11_001B359C[st->door].flags |= 1;
            D_L11_001B359C[st->door].hidden = 0;
            if (st->cls == 7) {
                r1 = HERO->i[0x18D4 / 4];
                HERO->i[0x18D4 / 4] = 0;
                D_L11_001B1588 = r1;
            } else if (st->cls == 8) {
                r2 = HERO->i[0x18D4 / 4];
                HERO->i[0x18D4 / 4] = 0;
                D_00139700[0] = 300;
                D_L11_001B1588 = r2;
            }
        }
        rec2 = &TABLE[st->cls]->records[st->wave];
        if (rec2->b[3] != 0) {
            func_002A7750(obj, 9, -1);
            return;
        }
        func_L11_00440360(obj);
        if (func_L11_00442710(obj) != 0) {
            st->wave++;
            for (k4 = 0; k4 < 7; k4++) {
                st->counts[k4] = 0;
            }
            st->lost = 0;
            if (D_L11_001BA780.owner == st->owner) {
                D_L11_001BA780.owner = 0;
            }
            cls1 = st->cls;
            cls3 = (u16)st->cls;
            st->sound = 0;
            st->owner = 0;
            if (st->wave >= TABLE[cls1]->count) {
                if (cls3 - 7U < 2) {
                    HERO->i[0x18D4 / 4] = D_L11_001B1588;
                }
                st->result = st->cls;
                if (st->result == 0 && D_001395B8[func_L11_0043E108(0)] == 0) {
                    func_002A7750(obj, 12, -1);
                    return;
                }
                func_002A7750(obj, 5, -1);
                func_L00_003DF6B0(1, -1);
                func_L00_004028C0((char *)1, -1);
                return;
            }
            if (cls1 >= 13) {
                st->cls = 0;
            }
            func_L11_00442E38(obj);
            rec3 = &TABLE[st->cls]->records[st->wave];
            func_L11_00441A58(obj, rec3->h[7]);
            func_L11_00441D08(obj, rec3->h[6]);
        }
        st->frames++;
        if (st->cls == 5) {
            if (st->frames >= 0x1519) {
                char buf[0x70];

                sum1 = 0;
                for (k5 = 0; k5 < 6; k5++) {
                    sum1 += st->counts[k5];
                }
                func_00115DA8(buf, D_L11_001B15A0, func_00288FB8(0x3269), D_L11_001B14B8[st->wave] + sum1 - st->lost,
                              func_00288FB8(0x2F61));
                func_L00_0030DD70((int)buf, -1);
                func_002A7750(obj, 11, -1);
                func_L00_003DF6B0(1, -1);
                func_L00_004028C0((char *)1, -1);
                return;
            }
        }
        if (st->cls == 9 && st->frames >= 0x2A31) {
            func_L00_0030DD70(func_00288FB8(0x3269), -1);
            func_002A7750(obj, 11, -1);
            func_L00_003DF6B0(1, -1);
            func_L00_004028C0((char *)1, -1);
            return;
        }
        if (st->cls == 8) {
            if (st->frames >= 0xE11) {
                char buf[0x70];

                sum2 = 0;
                for (k6 = 0; k6 < 6; k6++) {
                    sum2 += st->counts[k6];
                }
                func_00115DA8(buf, D_L11_001B15A0, func_00288FB8(0x3269), D_L11_001B14D0[st->wave] + sum2 - st->lost,
                              func_00288FB8(0x2F61));
                func_L00_0030DD70((int)buf, -1);
                func_002A7750(obj, 11, -1);
                func_L00_003DF6B0(1, -1);
                func_L00_004028C0((char *)1, -1);
                return;
            }
        }
        if ((st->cls == 3 || st->cls == 11) && HERO->i[0x24CC / 4] < D_001A7A00) {
            func_L00_0030DD70(func_00288FB8(0x326A), -1);
            func_002A7750(obj, 11, -1);
            func_L00_003DF6B0(1, -1);
            func_L00_004028C0((char *)1, -1);
            return;
        }
        rec2 = &TABLE[st->cls]->records[st->wave];
        if (OBJ->timer >= 0x3D || rec2->b[0] != 0) {
            ok1 = 0;
            func_L11_00441108(obj);
            func_L11_00440E18(obj);
            e1 = st->slots[st->slot];
            if (e1 != 0 && func_L02_003D77B8(e1) != 0) {
                for (k7 = st->counts[3]; k7 < rec2->h[3]; k7++) {
                    ok1 |= func_L11_00440790(obj, 0xDF7, 0);
                }
                for (k7 = st->counts[1]; k7 < rec2->h[1]; k7++) {
                    ok1 |= func_L11_00440790(obj, 0xDCF, 0);
                }
                for (k7 = st->counts[2]; k7 < rec2->h[2]; k7++) {
                    ok1 |= func_L11_00440790(obj, 0xDF4, 0);
                }
                for (k7 = st->counts[0]; k7 < rec2->h[0]; k7++) {
                    ok1 |= func_L11_00440790(obj, 0xD98, 0);
                }
                for (k7 = st->counts[4]; k7 < rec2->h[4]; k7++) {
                    ok1 |= func_L11_00440790(obj, 0xDF9, 0);
                }
                for (k7 = st->counts[5]; k7 < rec2->h[5]; k7++) {
                    ok1 |= func_L11_00440790(obj, 0xD37, 0);
                }
            }
            if (st->counts[6] == 0 && rec2->b[0] != 0) {
                r3 = func_L11_00440868(obj, 0xD4A, 0);
                st->sound = r3;
                st->owner = r3;
                if (D_L11_001BA780.owner == 0) {
                    D_L11_001BA780.owner = r3;
                    D_L11_001BA780.timer = 0;
                }
                snd1 = st->sound;
                if (D_L11_001B3770[0] == 0) {
                    D_L11_001B3770[0] = snd1;
                    func_00282A60(D_L11_001FFA78, 0, 0xE0);
                }
                func_L11_00445D28(obj, 10);
                func_L01_00323310(st->track, st->trackVolume);
            }
            if (rec2->b[0] == 0) {
                if (D_001A63A8[0x48] != st->music && D_001A63A8[0x3C] != st->music) {
                    func_L01_00323310(st->music, st->volume);
                }
            }
            if (ok1 != 0) {
                func_L11_00441090(obj);
            }
        }
        if (st->cls == 7) {
            func_002AD860(10);
            HERO->b[0x22B7] = 1;
        }
        if (st->cls == 8) {
            func_002AD860(30);
        }
        func_L00_002E6CF0(func_L11_00444400, obj);
        func_L11_004423F8(obj);
        func_L11_00446020(obj);
        if ((D_001A7BC0 & 3) == 0) {
            func_L11_00441350(obj);
        }
        func_L11_00442170(obj);
        if (func_L11_0043E090(st->cls) != -1) {
            D_L11_001AA170 = func_L11_0043E090(st->cls);
            D_L11_001B3680 = D_001A7390;
        }
        break;
    case 9:
        func_L11_0043E108(1);
        if (func_002B3868(obj) != 0) {
            if (st->counts[7] == 0) {
                if (TABLE[st->cls]->records[st->wave].b[1] != 0) {
                    r4 = func_L11_00440868(obj, 0xB3A, 0);
                    st->sound = r4;
                    st->owner = r4;
                    if (D_L11_001BA780.owner == 0) {
                        D_L11_001BA780.owner = r4;
                        D_L11_001BA780.timer = 0;
                    }
                    snd2 = st->sound;
                    if (D_L11_001B3770[1] == 0) {
                        D_L11_001B3770[1] = snd2;
                        buf2 = D_L11_001FFA78;
                        func_00282A60(buf2 + 0xE0, 0, 0xE0);
                    }
                    func_L11_00445D28(obj, 4);
                    func_L01_00323310(st->track, st->trackVolume);
                }
            }
            st->mode = 1;
            OBJ->phase = 0;
            func_L11_00445D28(obj, func_002A77E0(2) + 0x1B);
            for (k8 = 0; k8 < 4; k8++) {
                st->phase[k8] = (f32)k8 * 0.25f;
                st->speed[k8] = func_002A7878(D_L11_001B1590[0], D_L11_001B1590[1]) * 0.016666668f;
                st->delay[k8] = func_002A7878(D_L11_001B1598[0], D_L11_001B1598[1]);
            }
        } else if (OBJ->phase == 0) {
            func_L11_004461E8(obj);
            func_L11_00440360(obj);
            lt1 = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
            q1 = (u8 *)&D_L11_001B359C[st->lamp];
            if (lt1->height < 421.266f) {
                f1 = lt1->height + 0.008333334f;
                lt1->height = f1;
                *(f32 *)(q1 + 0x18) = f1;
            }
            if (HERO->ptr[0x33C / 4] == (void *)q1 && HERO->i[0x340 / 4] != 0 &&
                (HERO->i[0x2294 / 4] == 7 || OBJ->timer >= 0x12D)) {
                HERO->i[0xF0 / 4] = 0;
                D_L11_001A7CD8 = 80.0f;
                HERO->i[0xF4 / 4] = 0;
                if (HERO->i[0x2294 / 4] != 7) {
                    if (HERO->i[0x2294 / 4] != 0x81) {
                        func_L11_002D8EF8(7, 1);
                    }
                } else {
                    func_L11_002D8EF8(0x81, 1);
                }
                if (func_00282E80(&HERO->f[0x80 / 4], lt1->pos) < 0.01f) {
                    HERO->f[0x84 / 4] += 0.01f;
                }
            }
            ok2 = 0;
            func_L11_00441108(obj);
            func_L11_00440E18(obj);
            e2 = st->slots[st->slot];
            if (e2 != 0 && func_L02_003D77B8(e2) != 0) {
                for (k9 = st->counts[1]; k9 < 4; k9++) {
                    ok2 |= func_L11_00440790(obj, 0xDCF, 0);
                }
                for (k9 = st->counts[2]; k9 < 4; k9++) {
                    ok2 |= func_L11_00440790(obj, 0xDF4, 0);
                }
                for (k9 = st->counts[0]; k9 < 4; k9++) {
                    ok2 |= func_L11_00440790(obj, 0xD98, 0);
                }
            }
            func_L11_00446C78(obj);
            func_L00_002E6CF0(func_L11_00446EB8, obj);
            if (ok2 != 0) {
                func_L11_00441090(obj);
            }
            if (D_L11_001A8FF4 == 0) {
                if (HERO->f[0x88 / 4] > 480.0f && HERO->f[0x180 / 4] < 0.033333335f) {
                    D_L11_001A8FF4 = 1;
                    D_L11_001A8FF0 = 1;
                    func_L11_00447360((char *)obj);
                    func_L11_00447018(obj, 5);
                }
                if (D_L11_001A8FF4 == 0) {
                    if (HERO->f[0x88 / 4] < D_L11_001B1580 && D_L11_001B1584 < HERO->f[0x88 / 4]) {
                        HERO->h[0x1F0 / 2] = 1;
                    }
                    if (D_L11_001A8FF4 == 0) {
                        goto tail9;
                    }
                }
            }
            func_L11_00447018(obj, 0);
            if (D_L11_001A8FF4 != 0 && st->mode == 3) {
                OBJ->timer = 0;
                OBJ->phase = 1;
                rec6 = &TABLE[st->cls]->records[st->wave];
                for (c10 = 0; c10 < 6; c10++) {
                    st->counts[c10] = 0;
                }
                st->heading = func_00283248(HERO->f[0x80 / 4] - ((f32 *)func_L11_004417E8(obj))[0],
                                           HERO->f[0x84 / 4] - ((f32 *)func_L11_004417E8(obj))[1]);
                st->heading = func_00283B98(st->heading, -1.5707965f);
                for (k10 = st->counts[3]; k10 < rec6->h[3]; k10++) {
                    func_L11_00440790(obj, 0xDF7, 1);
                }
                for (k10 = st->counts[5]; k10 < rec6->h[5]; k10++) {
                    func_L11_00440790(obj, 0xD37, 1);
                }
                for (k10 = st->counts[1]; k10 < rec6->h[1]; k10++) {
                    func_L11_00440790(obj, 0xDCF, 1);
                }
                for (k10 = st->counts[2]; k10 < rec6->h[2]; k10++) {
                    func_L11_00440790(obj, 0xDF4, 1);
                }
                for (k10 = st->counts[0]; k10 < rec6->h[0]; k10++) {
                    func_L11_00440790(obj, 0xD98, 1);
                }
            }
        } else if (OBJ->phase == 1) {
            func_L11_00440360(obj);
            func_L11_004461E8(obj);
            if (TABLE[st->cls]->records[st->wave].b[4] != 0) {
                func_L11_004471A8(obj, &TABLE[st->cls]->records[st->wave]);
            }
            func_L11_00447018(obj, 0);
            if (func_L11_00442710(obj) != 0) {
                for (c11 = 0; c11 < 8; c11++) {
                    st->counts[c11] = 0;
                }
                st->lost = 0;
                cl1 = TABLE[st->cls];
                w1 = st->wave;
                next1 = &cl1->records[w1 + 1];
                if (w1 + 1 < cl1->count && next1->b[3] != 0) {
                    st->heading = func_00283248(HERO->f[0x80 / 4] - ((f32 *)func_L11_004417E8(obj))[0],
                                               HERO->f[0x84 / 4] - ((f32 *)func_L11_004417E8(obj))[1]);
                    st->heading = func_00283B98(st->heading, -1.5707965f);
                    st->wave++;
                    rec8 = &TABLE[st->cls]->records[st->wave];
                    for (k11 = st->counts[3]; k11 < rec8->h[3]; k11++) {
                        func_L11_00440790(obj, 0xDF7, 1);
                    }
                    for (k11 = st->counts[5]; k11 < rec8->h[5]; k11++) {
                        func_L11_00440790(obj, 0xD37, 1);
                    }
                    for (k11 = st->counts[1]; k11 < rec8->h[1]; k11++) {
                        func_L11_00440790(obj, 0xDCF, 1);
                    }
                    for (k11 = st->counts[2]; k11 < rec8->h[2]; k11++) {
                        func_L11_00440790(obj, 0xDF4, 1);
                    }
                    for (k11 = st->counts[0]; k11 < rec8->h[0]; k11++) {
                        func_L11_00440790(obj, 0xD98, 1);
                    }
                    if (st->counts[7] == 0 && rec8->b[1] != 0) {
                        r5 = func_L11_00440868(obj, 0xB3A, 0);
                        st->sound = r5;
                        st->owner = r5;
                        if (D_L11_001BA780.owner == 0) {
                            D_L11_001BA780.owner = r5;
                            D_L11_001BA780.timer = 0;
                        }
                        snd3 = st->sound;
                        if (D_L11_001B3770[1] == 0) {
                            D_L11_001B3770[1] = snd3;
                            buf3 = D_L11_001FFA78;
                            func_00282A60(buf3 + 0xE0, 0, 0xE0);
                        }
                        func_L11_00445D28(obj, 4);
                    }
                } else {
                    func_L11_002D8EF8(0x6F, 1);
                    OBJ->phase = 2;
                    st->mode = 4;
                    OBJ->timer = 0;
                    func_L00_003DF6B0(1, -1);
                    func_L00_004028C0((char *)1, -1);
                }
            }
            st->frames++;
            if (st->cls == 12) {
                if (st->frames >= 0x1771) {
                    char buf[0x70];

                    sum3 = 0;
                    for (k12 = 0; k12 < 6; k12++) {
                        sum3 += st->counts[k12];
                    }
                    func_00115DA8(buf, D_L11_001B15A0, func_00288FB8(0x3269), D_L11_001B14D8[st->wave] + sum3 - st->lost,
                                  func_00288FB8(0x2F61));
                    func_L00_0030DD70((int)buf, -1);
                    lt4 = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
                    m2 = &D_L11_001B359C[st->lamp];
                    lt4->height = 419.766f;
                    m2->y = 419.766f;
                    func_002A7750(obj, 11, -1);
                    func_L00_003DF6B0(1, -1);
                    func_L00_004028C0((char *)1, -1);
                    return;
                }
            }
        } else if (OBJ->phase == 2) {
            func_L11_004461E8(obj);
            if (OBJ->timer >= 0xB5) {
                HERO->h[0x348 / 2] = 0;
                D_L11_001A7CD8 = 5.0f;
                func_L11_002D8EF8(0x81, 1);
                OBJ->phase = 3;
            }
        } else if (OBJ->phase == 3) {
            D_L11_001A8FF4 = 0;
            D_L11_001A8FF0 = 0;
            if (HERO->f[0x88 / 4] < D_L11_001B1580 && D_L11_001B1584 < HERO->f[0x88 / 4]) {
                HERO->h[0x1F0 / 2] = 1;
            }
            func_L11_004461E8(obj);
            lt2 = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
            m3 = &D_L11_001B359C[st->lamp];
            if (lt2->height > 419.766f) {
                f2 = lt2->height - 0.008333334f;
                lt2->height = f2;
                m3->y = f2;
            }
            if (st->mode == 0) {
                st->wave++;
                for (k13 = 0; k13 < 7; k13++) {
                    st->counts[k13] = 0;
                }
                st->lost = 0;
                if (D_L11_001BA780.owner == st->owner) {
                    D_L11_001BA780.owner = 0;
                }
                cls2 = st->cls;
                st->sound = 0;
                st->owner = 0;
                if (st->wave >= TABLE[cls2]->count) {
                    if (cls2 == 1 && D_001395B8[func_L11_0043E108(1)] == 0) {
                        func_002A7750(obj, 13, -1);
                        OBJ->timer = 0xB4;
                    } else {
                        func_002A7750(obj, 5, -1);
                        OBJ->timer = 0xB4;
                    }
                    func_L00_003DF6B0(1, -1);
                    func_L00_004028C0((char *)1, -1);
                    st->result = st->cls;
                    return;
                }
                if (cls2 >= 13) {
                    st->cls = 0;
                }
                func_L11_00442E38(obj);
                rec9 = &TABLE[st->cls]->records[st->wave];
                func_L11_00441A58(obj, rec9->h[7]);
                func_L11_00441D08(obj, rec9->h[6]);
                OBJ->state = 8;
            }
        }
    tail9:
        slot1 = (s32)obj >> 8;
        func_L00_002E6CF0(func_L11_00444400, obj);
        func_L11_004423F8(obj);
        func_L11_00446020(obj);
        if ((D_L11_001B30C8 & 7) == (slot1 & 7)) {
            func_L11_00442170(obj);
        }
        if ((D_L11_001B30C8 & 0x3F) == (slot1 & 0x3F)) {
            func_L11_00441350(obj);
        }
        if (func_L11_0043E090(st->cls) != -1) {
            D_L11_001AA170 = func_L11_0043E090(st->cls);
            D_L11_001B3680 = D_001A7390;
        }
        break;
    }
    func_L11_00440160(obj);
}

