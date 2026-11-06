#include "common.h"

typedef struct {
    unsigned char pad[12];
    unsigned char flag;
    unsigned char padD[3];
    float values[4];
} CutsceneCamKey_002F5AF8;
typedef struct {
    char pad[0x38];
    int index;
    char pad3C[0x2C];
    CutsceneCamKey_002F5AF8 *keys;
} CutsceneCamCtl_002F5AF8;
typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars_002F5AF8;
typedef struct { float x, y, z, w; } CameraVec_002F5AF8;
typedef struct { char pad[0x370]; CameraVec_002F5AF8 rows[3]; } CameraBlock_002F5AF8;
extern void func_0027AB40(void);

extern int D_L05_001B1FC8;

extern int D_L05_001B1FD0;

extern int D_L05_001B1FD4;

extern int D_L05_001B1FCC;

extern int D_L05_001B1FF8;

extern int D_L05_001B1FFC;

extern int D_L05_001A8F00;

extern int D_L05_001A8F08;

extern unsigned char D_0018C0D4[];

extern int D_00138320[];

extern short D_L05_001B225C;

extern short D_L05_001B225E;

extern short D_L05_001B2260;

extern short D_L05_001B2262;

extern short D_L05_001B2264;

#ifndef RAC2_T_F32_F2144BF3D
#define RAC2_T_F32_F2144BF3D
typedef float f32_F2144bf3d;
#endif

#ifndef RAC2_T_S32_F2144BF3D
#define RAC2_T_S32_F2144BF3D
typedef int s32_F2144bf3d;
#endif

/* Resident record reached through a fixed core symbol: the retail body keeps
   the base in a register and addresses every field by displacement. */
#ifndef RAC2_T_RESIDENT138180_F2144BF3D
#define RAC2_T_RESIDENT138180_F2144BF3D
typedef struct {
    char  pad0[0x100];
    f32_F2144bf3d   f100;                 /* 0x100 */
    f32_F2144bf3d   f104;                 /* 0x104 */
    f32_F2144bf3d   f108;                 /* 0x108 */
    f32_F2144bf3d   f10C;                 /* 0x10C */
    char  pad1[0x1A0 - 0x110];
    s32_F2144bf3d   i1A0;                 /* 0x1A0 */
} Resident138180_F2144bf3d;
#endif

extern char D_00138180[];

extern s32_F2144bf3d D_0018D198[];

extern s32_F2144bf3d D_L06_001AD3A0 __attribute__((sda));

extern s32_F2144bf3d D_001A7390;

extern s32_F2144bf3d D_001A79F0;

extern s32_F2144bf3d D_L06_001B2348;

extern s32_F2144bf3d D_L06_001A8FC0;

extern s32_F2144bf3d D_L06_001B2900;

extern s32_F2144bf3d D_L06_001AA0F0;

void func_002F5220(void)
{
    unsigned char mode;

    D_L05_001B1FC8 = 0;
    mode = D_0018C0D4[0];
    D_L05_001B1FD0 = 0;
    D_L05_001B1FD4 = 0;
    D_L05_001B1FCC = 0;
    D_L05_001B1FF8 = 0;
    D_L05_001B1FFC = 0;

    if (mode == 1)
    {
        if ((D_00138320[0] & 0x10) == 0)
        {
            if (D_L05_001A8F00 != 4 && D_L05_001A8F08 != 4)
            {
                D_L05_001B225C = 0;
                D_L05_001B225E = 0;
                D_L05_001B2260 = 0;
                D_L05_001B2262 = 0;
                D_L05_001B2264 = 0;
            }
        }
    }
}

void func_002F52B8(void)
{
    Resident138180_F2144bf3d *p = (Resident138180_F2144bf3d *)D_00138180;

    if (p->i1A0 != 0) goto mismatch;
    if (p->f108 != 0.0f) goto mismatch;
    if (p->f10C != 0.0f) goto mismatch;
    if (p->f100 != 0.0f) goto mismatch;
    if (p->f104 == 0.0f) goto match;
mismatch:
    D_L06_001AD3A0 = 0;
    goto gated;
match:
    D_L06_001AD3A0 = D_L06_001AD3A0 + 1;
gated:
    D_L06_001B2348 = D_L06_001B2348 + 1;
    D_001A7390 = D_001A7390 + 1;

    if (D_L06_001A8FC0 != 0) {
        if (D_L06_001AD3A0 < 900) {
            D_0018D198[D_001A79F0] = D_0018D198[D_001A79F0] + 1;
        }
    }

    if (D_L06_001B2900 != D_001A7390 - 1) {
        D_L06_001AA0F0 = -1;
    }
}


/* Applies the current cutscene camera key and returns its flag byte. */
#include "common.h"

typedef struct { u8 pad00[0xC]; u8 kind; u8 pad0D[3]; f32 w0[4]; } CamRec_2F5AF8;
typedef struct { u8 pad00[0x38]; s32 index; u8 pad3C[0x68 - 0x3C]; CamRec_2F5AF8 *recs; } CamList_2F5AF8;
typedef struct { u8 pad[0xB0]; f32 scale; } CamView_2F5AF8;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x370 - 0x150];
    f32 row0[3];
    f32 pad37C;
    f32 row1[3];
    f32 pad38C;
    f32 row2[3];
} Cam_2F5AF8;

extern CamList_2F5AF8 D_001B8840;
extern CamView_2F5AF8 D_001B9040;
extern Cam_2F5AF8 D_001B5200;
extern u8 D_001A7A40;
extern f32 D_001A8C74;
extern f32 D_001A8C78;
extern f32 D_001B5360[12];
extern void func_0027AB40(void);
extern void func_00129178(f32 *);
extern void func_001292C0(f32 *, f32 *, f32);
extern void func_00129368(f32 *, f32 *, f32);
extern void func_00129218(f32 *, f32 *, f32);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_00282CF0(f32 *, f32 *, f32 *);
extern void func_00271958(f32 *, int);

u8 func_002F5AF8(void)
{
    f32 m[16] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    CamRec_2F5AF8 *rec;
    f32 *w;
    f32 scale;
    f32 k;
    u8 kind;

    rec = &D_001B8840.recs[D_001B8840.index];
    w = rec->w0;
    kind = rec->kind;
    scale = w[3];
    D_001B9040.scale = scale;
    if (D_001A7A40 != 0)
        D_001B9040.scale = scale * D_001A8C74;
    func_0027AB40();
    qcopy(D_001B5200.pos, rec);
    func_00129178(m);
    func_001292C0(m, m, w[0]);
    func_00129368(m, m, w[1]);
    func_00129218(m, m, w[2]);
    D_001B5200.row0[0] = -m[8];
    D_001B5200.row1[0] = -m[0];
    D_001B5200.row2[0] = m[4];
    D_001B5200.row0[1] = -m[9];
    D_001B5200.row1[1] = -m[1];
    D_001B5200.row2[1] = m[5];
    D_001B5200.row0[2] = -m[10];
    D_001B5200.row1[2] = -m[2];
    D_001B5200.row2[2] = m[6];
    if (D_001A7A40 != 0 && (k = D_001A8C78) != 0.0f) {
        qcopy(t, D_001B5200.row0);
        func_00282F20(t, t, k);
        func_00282CF0(D_001B5200.pos, D_001B5200.pos, t);
    }
    func_00271958(&D_001B5360[0], 0);
    func_00271958(&D_001B5360[4], 1);
    func_00271958(&D_001B5360[8], 2);
    return kind;
}

extern int D_001A8C80[] __attribute__((sda));
extern int D_001A8C84 __attribute__((sda));

void func_002F5CB8(int first, int second) {
    D_001A8C80[0] = first;
    D_001A8C84 = second;
}

extern float D_001A8C7C __attribute__((sda));
extern float D_001B15A0;
extern void func_0027D330(int);

/* Publishes the slow-down factor and, while the frame rate is below one, asks
   for the six-frame path. */
void func_002F5CC8(void)
{
    D_001A8C7C = 1.2f;
    if (D_001B15A0 < 1.0f)
        func_0027D330(6);
}

int func_002F5D10(void)
{
    return D_L05_001A8F08 == 2 || D_L05_001A8F00 == 2;
}

extern void func_002F5E20(int sector, int size, int file, int mode, int flag);
extern int D_001B220C;
extern int D_001BAD40[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
/* The table of contents read into 0x14B540: a base sector, then sector/size pairs, two per
   entry. The extent of the pairs is not known, so the buffer stays incomplete. */
typedef struct { int sector; int size; } TocFile_002F5D40;
typedef struct {
    int header;
    int base;
    TocFile_002F5D40 files[0];
} Toc_002F5D40;
extern char D_0014B540[];
#define TOC_002F5D40 ((Toc_002F5D40 *)D_0014B540)

/* Hands entry n of the table of contents to func_002F5E20; n < 0 only clears D_001B220C.
   Marks n in the shared flag table (bit n & 0x1F of the word at n >> 2, below 0xB1) and
   passes the entry's second file (sector relative to the base, size), the entry itself,
   D_001A7BB4 or 0 when D_001BAD40[0] is set, and whether n is 0xBF. */
extern int D_00139768[];
extern int func_002EF010(int);
extern void func_00288B38(void *);

void func_002F5D40(int n)
{
    int index;
    int flag;

    if (n < 0) {
        D_001B220C = 0;
        return;
    }
    index = func_002EF010(n);
    flag = 0;
    if (n == 0xBF)
        flag = 1;
    if ((unsigned)n < 0xB1) {
        int mask = 1 << (n & 31);
        D_00139768[(unsigned)n >> 2] |= mask;
    }
    func_00288B38(D_001BAD40);
    func_002F5E20(TOC_002F5D40->files[index * 2 + 1].sector + TOC_002F5D40->base,
                  TOC_002F5D40->files[index * 2 + 1].size,
                  (int)&TOC_002F5D40->files[index * 2],
                  D_001BAD40[0] ? 0 : D_001A7BB4[0], flag);
}
#undef TOC_002F5D40


extern int D_001A7478;
extern int D_001B221C;
extern unsigned char D_00188660[];
extern int D_001BAD78[];
extern int D_001A8BB8;
extern void (*ref_L00_002F5EF8_00)(int);
extern int ref_L00_002F5EF8_01;
extern void func_002B6E78(int, int, int);
extern void func_002B7320(void);
extern void func_002FC1D8(void);

void func_002F5EF8(void)
{
    if (D_001A7478 == 2)
        *(volatile int *)&D_001A7478 = 0;
    func_0027D330(4);
    func_002B6E78(D_001B221C, 1, 0x400);
    func_002B7320();
    D_00188660[0x6B] |= 0x10;
    func_002FC1D8();
    if (ref_L00_002F5EF8_00 != 0 && D_001BAD78[0] == 0) {
        if (D_001A8BB8 == 2)
            goto done;
        if (D_001A8BB8 == 1)
            goto done;
        {
            ref_L00_002F5EF8_00(D_001A8C84);
            *(void (*volatile *)(int))&ref_L00_002F5EF8_00 = 0;
            *(volatile int *)&ref_L00_002F5EF8_01 = 0;
        }
    }
done:
    ;
}

INCLUDE_ASM("asm/game", func_002F5FB8);

extern void func_288CB0(int, int);
void func_002F6458(void) { char *base = D_00138180 + 0x1260; int index = *(int *)(base + 0x148); if (index != -1) { if (*(short *)(base + index * 0xA0 + 0x18) >= 0) *(int *)(base + 0x17C) = 1; } func_288CB0(0, 0); }



/* func_002F6510: the copied records have the measured 0xE0-byte extent. */
typedef int F6510Quad __attribute__((mode(TI)));
typedef union {
    F6510Quad raw[14];
    struct { char prefix[0x80]; int value; char tail[0x5C]; } fields;
} F6510Record;
typedef struct { int type; char pad[12]; int locked; int active; } F6510Row;
typedef struct { char pad[0x80]; int selected; char pad84[0xBC]; F6510Row rows[1]; } F6510State;
extern F6510State D_L00_0022F7C0;
extern unsigned char D_00139568[];
extern F6510Record D_L00_00262570[];
extern int func_00288870(void *, int, int);

int func_002F6510(void)
{
    F6510Record local;
    int offset = D_L00_0022F7C0.selected * 24;
    int result = 0;

    if (*(int *)((char *)&D_L00_0022F7C0 + offset + 0x154) != 0) {
        int first = 0;
        switch (*(int *)((char *)&D_L00_0022F7C0 + offset + 0x140)) {
        case 12:
        case 14:
        case 17:
        case 18:
        case 53:
            first = 1;
            break;
        default:
            break;
        }
        if (first) {
            if (func_00288870(&local, *(int *)((char *)&D_L00_0022F7C0 + D_L00_0022F7C0.selected * 24 + 0x140), 1))
                result = local.fields.value;
        } else {
            if (func_00288870(&local, *(int *)((char *)&D_L00_0022F7C0 + D_L00_0022F7C0.selected * 24 + 0x140), 2))
                result = local.fields.value;
        }
    } else if (*(int *)((char *)&D_L00_0022F7C0 + offset + 0x150) == 0) {
        result = D_L00_00262570[D_00139568[*(int *)((char *)&D_L00_0022F7C0 + offset + 0x140)]].fields.value;
    }
    return result;
}


extern unsigned char D_001A7AB8[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern unsigned char D_001A7A80[] MACRO_ADDR;
typedef struct { int active; char pad4[0x10]; int info; char pad18[0x80]; int channels[3]; char padA4[0x3C]; } F73Record;
extern F73Record D_00239BA0[];
typedef struct { char pad[0x140]; int rows[96][4]; int count; } F73StateType;
extern F73StateType D_0021F240_rows __asm__("D_0021F240");
extern int func_002F7320(int owner, int key, int channel);
extern int func_00288D58(void);
extern int D_L00_0022FF00[];

void func_002F73A8(void)
{
    D_L00_0022FF00[0] = 0;
    {
        int key, channel, available;
        for (key = 0; key < 56; key++) {
            int offset = D_00139568[key] * 224;
            if (((F73Record *)((char *)D_00239BA0 + offset))->active != 0) {
                for (channel = 0; channel < 3; channel++) {
                    if (func_002F7320(D_001A79F0, key, channel) != 0)
                        goto mark_available;
                    switch (channel) {
                    case 0: available = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[0]; break;
                    case 1: available = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[1]; break;
                    case 2: available = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[2]; break;
                    default: available = 0; break;
                    }
                    if (!available) continue;
                    if (!func_00288D58()) continue;
mark_available:
                    D_001A7AB8[key] |= 1 << channel;
                }
            }
        }
    }
    {
        int key, channel, available;
        char *entry;
        for (key = 0; key < 56; key++) {
            if (key == 0) continue;
            if (D_00239BA0[D_00139568[key]].active == 0) continue;
            if (D_001A7AF8[key] == 0) continue;
            for (channel = 0; channel < 3; channel++) {
                {
                    unsigned int mask = 1U << channel;
                    if (!(D_001A7AB8[key] & mask)) continue;
                }
                switch (channel) {
                case 0: available = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[0]; break;
                case 1: available = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[1]; break;
                case 2: available = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[2]; break;
                default: available = 0; break;
                }
                if (!available) continue;
                {
                    unsigned char mask = 1 << (channel * 2);
                    if (D_001A7A80[key] & mask) continue;
                }
                D_0021F240_rows.rows[D_0021F240_rows.count][0] = channel;
                {
                    int stored_value;
                    switch (channel) {
                    case 0: stored_value = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[0]; break;
                    case 1: stored_value = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[1]; break;
                    case 2: stored_value = ((F73Record *)((char *)D_00239BA0 + D_00139568[key] * 224))->channels[2]; break;
                    default: stored_value = 0; break;
                    }
                    D_0021F240_rows.rows[D_0021F240_rows.count][2] = stored_value;
                }
                entry = (char *)D_00239BA0 + D_00139568[key] * 224;
                D_0021F240_rows.rows[D_0021F240_rows.count][1] = key;
                D_0021F240_rows.rows[D_0021F240_rows.count][3] = *(int *)(entry + 0x14);
                ++D_0021F240_rows.count;
            }
        }
    }
}
typedef struct { unsigned char pad0[0x3C]; char *destination; unsigned char pad1[0x24]; int clear; } Func_002F88D8State;
extern Func_002F88D8State ref_L00_002F88D8_00;
extern void func_00115DA8(char *, const char *, ...);
extern const char D_001AD2B8[];

void func_002F88D8(void *arg) { func_00115DA8(ref_L00_002F88D8_00.destination, D_001AD2B8, arg); ref_L00_002F88D8_00.clear = 0; }


typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { Quad_002F9198 a, b, c; } Three_002F9198;
typedef struct { int words[5]; } Five_002F9198;
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
typedef struct { char *moby; char pad4[0x14]; int a; char pad1C[0x14]; int b; } HeroMenu_002F9198;
extern Shop_002F9198 D_0021F240;
extern char D_001B5350[];
/* Its address is one `la` (assembler lui/addiu pair), not a split %hi/%lo: retail
   schedules the pair as one insn ahead of dst + 0x220. */
extern Three_002F9198 D_001B2250 MACRO_ADDR;
extern float D_001AD234 __attribute__((sda));
extern float D_001AD238 __attribute__((sda));
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int D_001AD230 __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern unsigned short D_001AD1BC __attribute__((sda)), D_001AD1C0 __attribute__((sda));
/* 0x40-byte block that func_002DE990 saves and restores whole. */
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 D_001A79F8 MACRO_ADDR;
extern Five_002F9198 D_001AD308;
extern HeroMenu_002F9198 D_00152C00;
extern int D_001A7AF0;
extern unsigned short D_001A7AF2;
extern void func_002FC138(void);
extern int func_002E5CF8(int, int, void *);
extern void func_002923C0(int);
extern int func_00288FB8(int);
extern void func_0029CC98(int, int);
extern void func_002925F0(int);
extern void func_002926B8(int);
extern void func_002E6178(int);

void func_002F9198(void)
{
    Shop_002F9198 *s = &D_0021F240;
    Five_002F9198 table;
    func_002FC138();
    func_002E5CF8(5, 17, s->moby);
    if (s->restore) {
        qcopy(D_001B5350, &s->saved);
        { Quad_002F9198 *dst = (Quad_002F9198 *)(D_001B5350 + 0x220);
          Three_002F9198 *src = &D_001B2250;
          dst[0] = src->a; dst[1] = src->b; dst[2] = src->c; }
    }
    *(unsigned short *)(s->moby + 0x34) |= 0x100;
    D_0021F240.state = 2;
    D_001AD234 = 1.0f;
    D_001AD238 = 1.1f;
    D_001AD230 = 0;
    D_001B2290 = 0; D_001B2294 = 0; D_001B2298 = 0;
    D_001B2284 = 96;
    D_001B2288 = 96;
    D_001B228C = 85;
    if (D_0021F240.mode == 3) {
        if (D_001AD1B8) D_001A79F8.level = D_001AD1BC; else D_001A79F8.level = D_001AD1C0;
        func_002923C0(D_001A79F8.level);
        table = D_001AD308;
        if (D_001AD1B8) func_0029CC98(func_00288FB8(table.words[D_001A79F8.level]), -1);
    }
    if (D_0021F240.mode == 2) {
        if (D_00152C00.a != D_001A7AF0) {
            char *m;
            func_002925F0(D_001A7AF0 & 3);
            m = D_00152C00.moby;
            if (m && *(int *)(m + 0x98)) *(int *)(m + 0x98) = *(int *)(*(char **)(m + 0x24) + 0x10);
        }
        if (D_00152C00.b != (D_001A7AF2 & 31)) func_002926B8(D_001A7AF2 & 31);
        func_002E6178(0);
    }
}


extern int D_001B2240, D_001B223C;
extern int D_001B2244 __attribute__((sda));
extern int D_00139688[];
extern void func_0028B6C8(int, unsigned int);
extern int func_002F6510(void);
extern void func_002F9198(void);

typedef struct { int id, kind; int fields[4]; } ShopRow_93;
typedef struct {
    char pad0[0x28]; char *moby; char pad2C[0x24];
    int mode; char pad54[0x18]; int scroll;
    char pad70[8]; int handle; char pad7C[4]; int selected;
    int busy; int animated; char pad8C[4]; int animation;
    char pad94[0xAC]; ShopRow_93 rows[64]; int count;
} ShopInput_93;
extern ShopInput_93 F93State __asm__("D_0021F240");
typedef struct { char pad[0x1C4]; int buttons; } Input_93;
void func_002F93B0(void)
{
    ShopInput_93 *state = &F93State;
    int cost;
    char *record;
    if (state->busy) return;
    {
        Input_93 *input = (Input_93 *)D_00138180;
        if ((input->buttons & 0x2000) ||
                (D_001B2240 >= 16 && D_001B2240 % 10 == 1)) {
            if (state->scroll < 57) {
                int moved = 0;
                if (state->selected < state->count - 1) {
                    ++state->selected;
                    moved = 1;
                }
                if (moved) {
                    if (state->animated) {
                        int animation = 3;
                        if (state->mode != 2) animation = 1;
                        state->animation = animation;
                    }
                    state->scroll += 56;
                    func_002E5CF8(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            func_0028B6C8(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)D_00138180;
        ShopInput_93 *state;
        if ((input->buttons & 0x8000) ||
                (D_001B223C >= 16 && D_001B223C % 10 == 1)) {
            state = &F93State;
            if (state->scroll >= -56) {
                int moved = 0;
                if (state->selected > 0) {
                    --state->selected;
                    moved = 1;
                }
                if (moved) {
                    if (state->animated) {
                        int animation = 3;
                        if (state->mode != 2) animation = 1;
                        state->animation = animation;
                    }
                    state->scroll -= 56;
                    func_002E5CF8(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            func_0028B6C8(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)D_00138180;
        ShopInput_93 *state;
        if (((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode != 3) ||
            ((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode == 3 &&
             *(int *)((char *)&F93State + 0x144 + F93State.selected * 12) != 0)) {
                state = &F93State;
                if (state->mode == 0) {
                    int stride = sizeof(ShopRow_93);
                    int *kinds = &state->rows[0].kind;
                    if (*(int *)((char *)kinds + state->selected * stride) == 0) {
                        cost = func_002F6510();
                        if ((*(int *)&D_001A79F8) >= cost) goto activate;
                    }
                    if (*(int *)((char *)kinds + state->selected * stride) != 1) goto rejected;
                    {
                        int id = state->rows[state->selected].id;
                        int owned = D_00139688[id];
                        record = (char *)D_00239BA0 + D_00139568[id] * 224;
                        if (owned >= *(unsigned short *)(record + 0x8E)) goto rejected;
                    }
                    if ((*(int *)&D_001A79F8) < *(unsigned short *)(record + 0x88)) goto rejected;
                }
activate:
                {
                    ShopInput_93 *active = &F93State;
                    if (active->animated) active->animation = 1;
                    active->busy = 1;
                    func_002E5CF8(0, 17, active->moby);
                    goto finish;
                }
rejected:
                func_002E5CF8(2, 17, F93State.moby);
        }
    }
finish:
    if (((Input_93 *)D_00138180)->buttons & 0x10) func_002F9198();
}

extern void func_002F93B0(void);

void func_002F9778(void)
{
    func_002F93B0();
}


/* One font glyph: its texture cell, its top offset and its advance. */
typedef struct { u8 u, v; signed char top, adv; } Glyph_002F97A0;

extern Glyph_002F97A0 D_00263EF0[];
extern u64 func_0027C878(int);
extern float func_00283CE0(int);
extern void func_0027E1A0(float, float, float, float, int, int, int, int, u32 *, u64);

/* Prints up to `limit` characters of `text` from (x, y) at `scale`, in the large font, fading
   each glyph's left and right edges out with their distance from the screen centre (215 on
   the second screen layout, 256 elsewhere, three quarters as fast). Characters 0x80..0xa7
   draw their entry 0x40 later; control characters below 0x20 draw a grey 24-pixel sprite. */
void func_002F97A0(u64 color, u8 *text, int limit, float x, float y, float scale)
{
    u32 colors[4];
    u32 gray[4];
    Glyph_002F97A0 *glyphs;
    Shop_002F9198 *shop = &D_0021F240;
    Glyph_002F97A0 *g;
    u64 texture;
    int count = 0;
    float size;
    float top;
    float dx;
    float dy;
    double d;
    int left;
    int right;
    int shade;
    int tint;
    u8 *cursor;
    u32 c;

    texture = func_0027C878(2);
    size = scale * 16.0f;
    glyphs = D_00263EF0;
    color &= 0xFFFFFF;
    if (limit == 0 || *text == 0)
        return;
    cursor = text;
    do {
        if (glyphs[*cursor].adv != 0) {
            top = func_00283CE0(glyphs[*cursor].top) * scale;
            if (shop->mode == 2) {
                d = 215.0f - x;
                if (d < 0)
                    d = -d;
                left = 0x80 - (int)d;
                d = 215.0f - (x + size);
                if (d < 0)
                    d = -d;
                right = 0x80 - (int)d;
            } else {
                d = 256.0f - x;
                if (d < 0)
                    d = -d;
                left = 0x80 - (int)(d * 0.75);
                d = 256.0f - (x + size);
                if (d < 0)
                    d = -d;
                right = 0x80 - (int)(d * 0.75);
            }
            if (left < 0)
                left = 0;
            c = color;
            if (right < 0)
                right = 0;
            left <<= 24;
            right <<= 24;
            colors[0] = left | c;
            colors[1] = right | c;
            colors[2] = left | c;
            colors[3] = right | c;
            if (*cursor < 0x20) {
                c = colors[0];
                shade = (c & 0xFF) + ((c >> 8) & 0xFF) + ((c >> 16) & 0xFF);
                shade /= 3;
                tint = (int)(c & 0xFF000000);
                tint += shade << 16;
                tint += shade << 8;
                shade += tint;
                gray[0] = shade;
                gray[1] = shade;
                gray[2] = shade;
                gray[3] = shade;
                func_0027E1A0(x, y + top, scale * 24.0f, scale * 16.0f, glyphs[*cursor].u,
                              glyphs[*cursor].v, 24, 16, gray, texture);
            }
            if ((u8)(*cursor + 0x80) < 0x28) {
                g = (Glyph_002F97A0 *)((((u8)*cursor + 0x40) << 2) + (int)glyphs);
                dx = func_00283CE0(g->adv) * scale;
                dy = func_00283CE0(g->top) * scale;
                func_0027E1A0(x + dx, y + dy, size, size, g->u, g->v, 16, 16, colors, texture);
            } else if ((u8)*cursor > 0x20) {
                func_0027E1A0(x, y + top, size, size, glyphs[*cursor].u, glyphs[*cursor].v, 16, 16,
                              colors, texture);
            }
            x += func_00283CE0(glyphs[*cursor].adv) * scale;
        }
        count++;
        if (count == limit)
            break;
        cursor++;
    } while (*cursor != 0);
}
