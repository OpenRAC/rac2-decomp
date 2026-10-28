/* func_0027D160 - 464 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft = whole new file src/game/0027D160-g8.c, flags line
   (config/cflags.txt): `src/game/0027D160-g8.c<TAB>-O2 -G8 -ffunction-
   sections`; remove marker from src/game/0027B948.c.
   480 B vs 464 B. The hdr/sd/edge/color part and the reflect math match
   structurally. Differences:
   - mine CSEs the gp address of D_001A87A0 (declared `float [2]
   __attribute__((sda))`, the only spelling that yields `addiu $r,$gp,off`)
   from the first loop into $s6 for the whole function (extra sd/ld $s6 and a
   daddu); retail makes a fresh `addiu $v0,$gp,-0x6850` in the first loop and
   `addiu $s5,$gp,-0x6850` for the second loop.
   - loop shapes: retail uses `a2` countdown 3..0 with all three pointers
   advancing; mine too but separate registers for the loop counter ($a0 vs
   retail $a2).
   Tried: struct (Plane) indexing (lui/addiu, wrong), float* pointer walk
   (current), Plane* pointer walk for the second loop (no change). */

#include "include_asm.h"
#include "common.h"

typedef struct {
    float x, y, z, w;
} V4_27D160;

typedef struct {
    float nx, ny;
    float ex, ey;
} Plane_27D160;

typedef struct {
    V4_27D160 p;
    V4_27D160 n;
} Item_27D160;

extern float D_001A87A0[2] __attribute__((sda));
extern int D_001B163C;
extern Item_27D160 D_001BA640[];

extern unsigned long long func_0027C878(int);
extern void func_00282F20(void *, void *, float);
extern void func_00280B90(void *, int, int);

void func_0027D160(void)
{
    struct {
        V4_27D160 tmp[4];
        unsigned int color[4];
        float edge[8];
        unsigned long long hdr[4];
        V4_27D160 n;
    } L;
    int i, k;
    float *pl;
    float *e;
    unsigned int *c;
    V4_27D160 *t;

    L.hdr[1] = func_0027C878(0);
    L.hdr[2] = 0xFF9000000260ULL;
    L.hdr[0] = 5;
    L.hdr[3] = 0x8000000044ULL;
    pl = D_001A87A0;
    e = L.edge;
    c = L.color;
    for (k = 3; k >= 0; k--) {
        e[0] = pl[2];
        e[1] = pl[3];
        *c = 0x40808080;
        pl += 4;
        e += 2;
        c++;
    }
    for (i = 0; i < D_001B163C; i++) {
        float w;
        qcopy(&L.n, &D_001BA640[i].n);
        func_00282F20(&L.n, &L.n, 1.0f);
        w = D_001BA640[i].p.w;
        pl = D_001A87A0;
        t = L.tmp;
        for (k = 3; k >= 0; k--) {
            float dot = pl[0] * L.n.x + pl[1] * L.n.y;
            qcopy(t, &D_001BA640[i].p);
            t->x += (pl[0] - L.n.x * dot) * w;
            t->y += (pl[1] - L.n.y * dot) * w;
            t->z -= L.n.z * dot * w;
            pl += 4;
            t++;
        }
        func_00280B90(L.tmp, 0, 0);
    }
}
