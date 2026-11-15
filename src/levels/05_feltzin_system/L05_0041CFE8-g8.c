/* Built with -G8 (the beam texture is reached through $gp) and -fno-strength-reduce, which
   keeps the record counter counting up as in retail. */
#include "common.h"

/* The 128 interpolation records: position, next, offset, origin, then the
   owner at +0x40; 0x50 bytes each. */
extern char D_L05_002681E0[];
extern int D_L05_001B1340 __attribute__((sda));
extern float func_002A7940(void);
/* func_L05_0041D218(start, end, color, texture, width): the width is declared before the
   texture; each register bank keeps its order (a0-a3, f12). */
extern void func_L05_0041D218(void *, void *, unsigned int, float, int);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);

/* Draws a two-layer beam from position to next and four glow sprites at origin and next for
   every interpolation record the object owns. */
void func_L05_0041CFE8(char *obj)
{
    char *table = D_L05_002681E0;
    char *next = table + 0x10;
    char *origin = table + 0x30;
    char *position = table;
    int i;

    for (i = 0; i < 128; i++) {
        if (*(char **)(origin + 0x10) == obj) {
            DrawBeamStrip_L05_2(position, next, 0x807F7F7F, 0.025f, D_L05_001B1340);
            DrawBeamStrip_L05_2(position, next, 0x60008000, 0.05f, D_L05_001B1340);
            DrawBillboardQuad_00281EB8(origin, 0x31, 0x60008000, 1, 1.35f, 0.35f, RandomAngle());
            DrawBillboardQuad_00281EB8(origin, 0x31, 0x807F7F7F, 1, 1.0f, 0.35f, RandomAngle());
            DrawBillboardQuad_00281EB8(next, 0x31, 0x60008000, 1, 0.125f, 0.08f, RandomAngle());
            DrawBillboardQuad_00281EB8(next, 0x31, 0x807F7F7F, 1, 0.08f, 0.08f, RandomAngle());
        }
        origin += 0x50;
        next += 0x50;
        position += 0x50;
    }
}
