#include "common.h"

extern int func_L01_003165E8(void *, int, int, int, int);
extern int func_001163B0(void);
extern float func_00282E80(void *, void *);
extern int func_002A77E0(int);
extern void func_L01_00337A60(void *, void *,void *,int);
extern int func_002761F8(void *, void *, int, void *, int);
extern char *D_L01_001FE180[];
extern char D_L01_001BF920[];

typedef int TI128 __attribute__((mode(TI)));

typedef struct L01_003BDF28_BUF {
    float x;
    float y;
    int z;
} L01_003BDF28_BUF;

typedef struct L01_003BC490_OBJ {
    char pad[0x10];
    TI128 f10;
} L01_003BC490_OBJ;

typedef struct L01_003BDBB0_OWNED {
    char pad0[0x250];
    void *f250;
    int f254;
} L01_003BDBB0_OWNED;

typedef struct L01_003BDBB0_OBJ {
    char pad0[0x68];
    L01_003BDBB0_OWNED *f68;
} L01_003BDBB0_OBJ;

typedef struct L01_003BE488_OWNED {
    char pad0[0x202];
    short f202;
    int f204;
} L01_003BE488_OWNED;

typedef struct L01_003BE488_OBJ {
    char pad0[0x68];
    L01_003BE488_OWNED *f68;
} L01_003BE488_OBJ;

typedef struct L01_003BFDC8_OBJ {
    char pad0[0x43];
    unsigned char f43;
    char pad1[0x48 - 0x44];
    float f48;
} L01_003BFDC8_OBJ;

extern int func_00282948(void *);

extern void func_00291450(int);

extern float func_002A7878(float, float);

extern void func_002A0F48(char *);

extern void *func_0029EFD0(int);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern char D_00189EA0[];

extern void func_L01_003BDBE8(void *);

extern float func_002A7940(void);

extern int func_002A7820(int, int);

extern void func_L01_0032EF38(void *, int, int, float, float, int);

extern void func_002A7470();

void func_L01_003BDF28(char *a0)
{
    char *s2 = a0;
    char *s0 = *(char **)(s2 + 0x68);
    char *s1 = s0 + 0x1E0;
    L01_003BDF28_BUF buf;

    *(float *)(s0 + 0x1E0) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * (float)*(unsigned char *)(s0 + 0x201);
    *(float *)(s0 + 0x1E4) = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * (float)*(unsigned char *)(s0 + 0x201);
    *(int *)(s0 + 0x1E8) = 0;
    func_00282CC0(s1, s1, s0 + 0x1D0);
    *(float *)(s0 + 0x1E8) = *(float *)(s0 + 0x1E8) + 1.7f;
    if (*(int *)(s0 + 0x23C) != 0) {
        func_00282CF0(&buf, s1, D_00189EA0);
        buf.z = 0;
        func_00282F20(&buf, &buf, 8.0f);
        func_00282CC0(s1, s1, &buf);
    }
    func_L01_003BDBE8(s2);
}

/* func_L01_003BB9D0 is in L01_003BB9D0-ocean-g8.c. */

/* func_L01_003BBF68 is in L01_003BBF68-g8.c. */


/* func_L01_003BC540 is in L01_003BB9D0-debris-g8.c. */

/* func_L01_003BCA38 is in L01_003BCA38.c. */

INCLUDE_ASM("asm/levels", func_L01_003BCEC8);


/* func_L01_003BD410 */
void func_L01_003BD410(char *object)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, i;

    state = *(char **)(object + 0x68);
    for (i = 0; i < 5; i++) {
        angle = func_002A7940();
        radius = func_002A7878(0.0f, 0.8f);
        first = func_002A7878(0.0f, 1.5f);
        second = func_002A7878(1.5f, 5.7f);
        life = func_002A7820(100, 180);
        position[0] = func_00283180(angle) * radius;
        position[1] = func_00283198(angle) * radius;
        position[2] = 0.0f;
        func_00282CC0(position, position, object + 0x10);
        position[2] = *(float *)(state + 0x224) + 0.025f;
        func_L01_0032EF38(position, 0x38002028, 0x2020, first, second, life);
    }
}



/* func_L01_003BD6B0 is in L01_003BD6B0-g8.c. */

typedef struct {
    char pad0[0x280];
    int f280;
    int f284;
} L01_003BDB28_STATE;

extern void func_002A8598(int, int);

void func_L01_003BDB28(char *obj)
{
    L01_003BDB28_STATE *s0 = *(L01_003BDB28_STATE **)(obj + 0x68);

    if (*(unsigned char *)(obj + 0x21) != 0xFF) {
        func_002A8598(*(unsigned char *)(obj + 0x21), 1);
    }
    if (s0->f280 != -1) {
        func_002A8598(s0->f280, 1);
    }
    if (s0->f284 != -1) {
        func_002A8598(s0->f280, 1);
    }
    *(unsigned char *)(obj + 0xBC) = 1;
}

/* func_L01_003BDBB0 */

void func_L01_003BDBB0(L01_003BDBB0_OBJ *a0)
{
    L01_003BDBB0_OWNED *p = a0->f68;

    if (p->f254 != 0) {
        func_00282948(p->f250);
        p->f254 = 0;
    }
}

void func_L01_003BDBE8(void *object)
{
    char *obj = object;
    char *s = *(char **)(obj + 0x68);
    int index = -1;
    float offset, coordinate;

    if (*(unsigned char *)(obj + 0x20) < 7) {
        index = (*(int *)(s + 0x214) != -1) ? *(int *)(s + 0x214) : *(int *)(s + 0x210);
    } else {
        index = *(int *)(s + 0x210);
    }
    *(int *)(s + 0xCC) = index;
    if (!func_L01_003165E8(s + 0x1E0, index, *(int *)(s + 0x218), *(int *)(s + 0x21C), -1)) {
        if ((func_001163B0() & 1) || *(int *)(s + 0x114) != 1 || *(int *)(s + 0x23C)) {
            if (func_00282E80(s + 0x1E0, obj + 0x10) < 0.5f || !func_002A77E0(1)) {
                qcopy(s + 0x1E0, s + 0x1D0);
                *(float *)(s + 0x1E8) += 1.7f;
            }
            func_L01_00337A60(s + 0x1E0, s + 0x1E0, D_L01_001FE180[index] + 0x10, *(int *)D_L01_001FE180[index]);
        } else {
            *(float *)(s + 0x1E0) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 1.2f;
            *(float *)(s + 0x1E4) = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 1.2f;
            *(int *)(s + 0x1E8) = 0;
            func_00282CC0(s + 0x1E0, s + 0x1E0, D_00189EA0);
            *(float *)(s + 0x1E8) += 1.7f;
            func_L01_00337A60(s + 0x1E0, s + 0x1E0, D_L01_001FE180[index] + 0x10, *(int *)D_L01_001FE180[index]);
        }
        if ((*(int *)(s + 0x23C) && func_00282E80(s + 0x1E0, D_00189EA0) < 3.0f) || func_00282E80(s + 0x1E0, obj + 0x10) < 0.5f) {
            offset = func_002A7878(3.0f, 5.0f);
            coordinate = *(float *)(s + 0x1E0);
            *(float *)(s + 0x1E0) = (func_001163B0() & 1) ? coordinate - offset : coordinate + offset;
            offset = func_002A7878(3.0f, 5.0f);
            coordinate = *(float *)(s + 0x1E4);
            *(float *)(s + 0x1E4) = (func_001163B0() & 1) ? coordinate - offset : coordinate + offset;
        }
    }
    if (func_002761F8(obj + 0x10, s + 0x1E0, 2, obj, 0)) {
        func_00282CF0(s + 0x1E0, D_L01_001BF920, s + 0x1E0);
        func_00282F20(s + 0x1E0, s + 0x1E0, 2.0f);
        func_00282CC0(s + 0x1E0, s + 0x1E0, D_L01_001BF920);
    }
}

/* func_L01_003BE058 is in L01_003BB9D0-steer.c. */

/* func_L01_003BE488 */

void func_L01_003BE488(L01_003BE488_OBJ *a0)
{
    L01_003BE488_OWNED *p = a0->f68;

    if (p->f202 != -1) {
        p->f204 = 0;
        func_00291450(p->f202);
        p->f202 = -1;
    }
}

typedef struct L01_003BE4D0_OBJ {
    char pad0[0x20];
    unsigned char f20;
    char pad21[0x68 - 0x21];
    struct L01_003BE4D0_STATE *f68;
    char pad6C[0x96 - 0x6C];
    unsigned short f96;
    char pad98[0xBC - 0x98];
    unsigned char fBC;
} L01_003BE4D0_OBJ;

typedef struct L01_003BE4D0_STATE {
    char pad0[0x114];
    int f114;
    char pad118[0x230 - 0x118];
    int timer230;
    char pad234[0x238 - 0x234];
    int timer238;
    int timer23C;
    char pad240[0x290 - 0x240];
    int f290;
} L01_003BE4D0_STATE;

extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A0488(void *, int, int, int);
extern int func_002E4600(unsigned int, unsigned int, float);

void func_L01_003BE4D0(L01_003BE4D0_OBJ *obj)
{
    L01_003BE4D0_STATE *s = obj->f68;
    int red, green, blue;
    unsigned int target;
    int color;

    if (obj->fBC != 0) {
        obj->fBC = 0;
        if (s->timer238 < 200) {
            s->timer238 = func_002A7820(300, 360);
        }
    }
    if (s->f114 != 1) {
        func_00282948(&s->timer238);
    }
    if (obj->f96 <= 0xFFFD) {
        obj->f96 = obj->f96 + 1;
    }
    func_00282948(&s->timer230);
    func_00282948(&s->timer23C);
    /* Pack the current colour as 0x80BBGGRR, then blend it towards the target. */
    func_002A04B8(obj, &red, &green, &blue);
    {
        unsigned int alpha_green = (green << 8) | 0x80000000u;
        unsigned int alpha_blue_green = (blue << 16) | alpha_green;
        color = alpha_blue_green | red;
    }
    if (s->f290 != 0 && obj->f20 < 9) {
        target = 0x8040E0F0;
        color = func_002E4600(color, target, 0.05f);
    } else {
        target = 0x00404040;
        color = func_002E4600(color, target, 0.08f);
    }
    red = color & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = (color >> 16) & 0xFF;
    func_002A0488(obj, red, green, blue);
}

/* func_L01_003BE628 is in L01_003BE628.c. */

/* func_L01_003BFDC8 */

void func_L01_003BFDC8(L01_003BFDC8_OBJ *a0, int a1, int a2, int a3)
{
    L01_003BFDC8_OBJ *p = a0;

    if (p->f43 != a1) {
        func_002A7470(a0);
    }
    if (a1 != 12) {
        p->f48 = 0.6666667f;
    }
    if ((unsigned int)(a1 - 6) < 3) {
        p->f48 = p->f48 * 1.25f;
    }
}

/* func_L01_003BFE48 is in L01_003BFE48-g8.c. */

/* func_L01_003C01C0 is in L01_003C01C0-g8.c. */

/* func_L01_003C0408 is in L01_003C0408-g8.c. */

/* func_L01_003C08A0 is in L01_003C08A0.c. */


/* func_L01_003C2680 is in L01_003C2680-g8.c. */


/* func_L01_003C97D8 is in L01_003C97D8-draw.c. */

/* func_L01_003C9D00 is in L01_003C9D00.c. */
