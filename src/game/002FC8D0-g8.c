#include "include_asm.h"

extern int ref_L00_00300248_00 __attribute__((sda));
extern unsigned char D_0018C0B0[];
extern void func_002AD250(int, int, int, int);

typedef int s32;

typedef float f32;

/* func_00300048 lives in the boot and in every level, but the vector it scales, the
   four constants it passes and the five functions it calls all sit at a different
   address in every program.  They are therefore named without an address: the
   linker reads their value from the retail bytes of the program it builds.
   The four constants are small data, so they are reached through $gp. */

extern float ref_L00_00300048_06 __attribute__((sda));

extern float ref_L00_00300048_07 __attribute__((sda));

extern float ref_L00_00300048_08 __attribute__((sda));

extern float ref_L00_00300048_09 __attribute__((sda));

extern float ref_L00_00300048_00[];

extern void ref_L00_00300048_01(f32 *, f32 *, f32);

extern void ref_L00_00300048_02(f32 *, f32 *, f32 *);

extern void ref_L00_00300048_03(f32 *, f32, f32);

extern int ref_L00_00300048_04(int, int);

extern void ref_L00_00300048_05(f32 *, f32 *, int, int, int, int, int, int, f32, f32, f32, f32);

/* The carrying USA preview callers supply their object in a0; retail
 * ignores that input while generating the shared effect. */
void func_00300048(void *unused_object)
{
    f32 a[4], b[4], c[4], d[4];
    f32 *p = ref_L00_00300048_00;
    f32 *q = p - 140;
    s32 i;
    s32 ret;

    i = 5;
    do {
        ref_L00_00300048_01(a, p, 9.0f);
        ref_L00_00300048_02(b, q, a);
        ref_L00_00300048_03(c, 0.1f, 3.0f);
        ref_L00_00300048_01(a, p, 3.0f);
        ref_L00_00300048_02(d, q, a);
        ref_L00_00300048_02(c, d, c);
        ret = ref_L00_00300048_04(8, 12);
        ref_L00_00300048_05(b, c, ret, 0x00808080, 0x00808080, 0x00FF1010, 0x00FF1010,
                            0x00FF1010, ref_L00_00300048_06, ref_L00_00300048_07,
                            ref_L00_00300048_08, ref_L00_00300048_09);
        i--;
    } while (i >= 0);
}

void func_00300248(int a0, int a1) {
    int state = ref_L00_00300248_00;
    if (state != 0)
        func_002AD250(*(int *)D_0018C0B0, state, a1, a0);
}

typedef unsigned short u16;

/* The 16-byte box the walk below steps through: three coordinates and two
   half extents, the last two read as unsigned shorts. */
typedef struct {
    int x;
    int y;
    int z;
    u16 halfwidth;
    u16 halfheight;
} Box2FCFC8;

/* The 0x1190-byte record the boxes select: two coordinates at the front and
   a set of flags at 0x1E.  The walk keeps its byte offset in a register, so
   the record's size has to be 0x1190. */
typedef struct {
    float x;
    float y;
    char pad0[0x1E - 0x08];
    u16 flags;
    char pad1[0x1190 - 0x20];
} Record2FCFC8;

extern int D_001B22D8;
extern Box2FCFC8 *D_001B22D4;
extern Record2FCFC8 *D_001B22D0;
extern float D_001AD5C8;
extern float D_001AD5CC;
extern float D_001AD5D0;
extern float D_001AD5D4;
extern int func_00283CF0(float value);

/* The three coordinates arrive scaled by 1024 and are truncated to the grid
   the boxes are laid out in.  The walk returns the index of the first box
   that holds the point, or -1 when none does.  The count of the boxes is read
   again on every pass, and the record a box selects is reached through the
   byte offset the loop carries. */
int func_002FCFC8(float x, float y, float z) {
    int px = func_00283CF0(x * 1024.0f);
    int py = func_00283CF0(y * 1024.0f);
    int pz = func_00283CF0(z * 1024.0f);
    Box2FCFC8 *box = (Box2FCFC8 *)D_001B22D4;
    int i;

    for (i = 0; i < D_001B22D8; i++, box++) {
        if (px >= box->x && py >= box->y && pz >= box->z &&
            px < box->x + box->halfwidth && py < box->y + box->halfheight &&
            pz < box->z + 0x800) {
            Record2FCFC8 *record = D_001B22D0 + i;
            int r1 = func_00283CF0((x - (record->x + D_001AD5C8)) / D_001AD5D0);
            int r2 = func_00283CF0((y - (record->y + D_001AD5CC)) / D_001AD5D4);
            unsigned int mask = 1 << (((r1 >> 2) & 3) | (r2 & 0xC));
            if (record->flags & mask) {
                return i;
            }
        }
    }
    return -1;
}
