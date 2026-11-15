#include "common.h"

/* The two per-path sizes are an array member: indexing it adds the index to the base
   (base first), as retail does. */
typedef struct {
    u8 pad0[0x260];
    f32 unk260[2];
} L11ArcData;

extern s32 func_002A7820(s32, s32);
extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern void func_002A7A00(void *, f32, f32);
extern void func_L11_003F4198(void *, s32, void *, f32);
extern void func_L11_003F4490(void *, s32, s32, s32, s32, f32, f32);
extern void func_002ACB48(void *, f32);
extern void func_0029FCC0(u8 *, s32, void *);
/* Integer and FP arguments interleaved in the ABI's per-bank order (a0-a3/t0, f12/f13):
   retail sets the size before the life count. */
extern void func_L02_003FFC48(void *, s32, f32, s32, f32, s32, s32);
extern f32 D_L11_001B0610 __attribute__((sda));
extern f32 D_L11_001B05E8 __attribute__((sda));
extern s32 D_L11_001B060C __attribute__((sda));
extern s32 D_L11_001B05E4 __attribute__((sda));
extern f32 D_L11_001B0624 __attribute__((sda));
extern f32 D_L11_001B0628 __attribute__((sda));
extern f32 D_L11_001B05FC __attribute__((sda));
extern f32 D_L11_001B0600 __attribute__((sda));
extern f32 D_L11_001B062C __attribute__((sda));
extern f32 D_L11_001B0630 __attribute__((sda));
extern f32 D_L11_001B0604 __attribute__((sda));
extern f32 D_L11_001B0608 __attribute__((sda));
extern s32 D_L11_001B05B4 __attribute__((sda));
extern s32 D_L11_001B05B8 __attribute__((sda));
extern s32 D_L11_001B0634 __attribute__((sda));
extern f32 D_L11_001B063C __attribute__((sda));
extern f32 D_L11_001B0640 __attribute__((sda));
extern f32 D_L11_001B0644 __attribute__((sda));
extern f32 D_L11_001B0648 __attribute__((sda));
extern f32 D_L11_001B064C __attribute__((sda));
extern f32 D_L11_001B0650 __attribute__((sda));
extern f32 D_L11_001B0638 __attribute__((sda));
extern s32 D_L11_001B05BC __attribute__((sda));
extern s32 D_L11_001B05C0 __attribute__((sda));
extern f32 D_L11_001B05D8 __attribute__((sda));
extern f32 D_L11_001B05D4 __attribute__((sda));
extern s32 D_L11_001B05CC __attribute__((sda));
extern f32 D_L11_001B05C8 __attribute__((sda));
extern f32 D_L11_001B05C4 __attribute__((sda));
extern s32 D_L11_001B05D0 __attribute__((sda));

/* Emits the two articulated effect paths and their joint effects. */
void func_L11_003F3CB8(u8 *object)
{
    u8 frame[0xA0] __attribute__((aligned(16)));
    u8 *data = *(u8 **)(object + 0x68);
    s16 *state = (s16 *)(data + 0x278);
    s32 i;
    for (i = 0; i < 2; i++, state++) {
        if (*state != 0) {
            s32 group = (u16)(*(u16 *)state - 3) < 3;
            s32 small = (u16)(*(u16 *)state - 3) < 2;
            f32 amplitude = group ? D_L11_001B0610 : D_L11_001B05E8;
            s32 count = group ? D_L11_001B060C : D_L11_001B05E4;
            f32 points[count][4];
            s32 duration = small ? func_002A7820(0x30, 0x80) : func_002A7820(0x30, 0x50);
            f32 width = small ? func_002A7878(D_L11_001B0624, D_L11_001B0628) : func_002A7878(D_L11_001B05FC, D_L11_001B0600);
            f32 scale = small ? func_002A7878(D_L11_001B062C, D_L11_001B0630) : func_002A7878(D_L11_001B0604, D_L11_001B0608);
            u8 *path = data + 0xA0 + i * 0xA0;
            func_L11_003F4198(points, count, path, amplitude);
            DrawDualQuadStrip(points, count, duration, D_L11_001B05B4, D_L11_001B05B8, width, scale);
            if ((u16)(*(u16 *)state - 3) < 2) {
                f32 extra[D_L11_001B0634][4];
                s32 pick = func_002A7820(count - 6, count - 3);
                qcopy_nc(frame, points[pick]);
                qcopy_nc(frame + 0x10, points[count - 2]);
                func_002ACB48(frame + 0x10, 1.0f);
                func_002A7A00(frame + 0x20, D_L11_001B063C, D_L11_001B0640);
                func_002A7A00(frame + 0x30, D_L11_001B063C, D_L11_001B0640);
                duration = func_002A7820(0x30, 0x60);
                width = func_002A7878(D_L11_001B0644, D_L11_001B0648);
                scale = func_002A7878(D_L11_001B064C, D_L11_001B0650);
                func_L11_003F4198(extra, D_L11_001B0634, frame, D_L11_001B0638);
                DrawDualQuadStrip(extra, D_L11_001B0634, duration, D_L11_001B05BC, D_L11_001B05C0, width, scale);
            }
            if (group) {
                f32 jitter = func_002A7878(-D_L11_001B05D8, D_L11_001B05D8);
                f32 size = D_L11_001B05D4 + jitter;
                s32 life = func_002A7820(0x50, 0x60);
                f32 angle = func_002A7940();
                func_L02_003FFC48(path, D_L11_001B05CC, size, life, angle, 0x31, 2);
            }
        }
        {
            f32 size = D_L11_001B05C4 + D_L11_001B05C8 * ((L11ArcData *)data)->unk260[i];
            f32 half;
            s32 life;
            f32 angle;
            func_0029FCC0(object, i, frame);
            half = size * 0.5f;
            life = func_002A7820(0x50, 0x60);
            angle = func_002A7940();
            func_L02_003FFC48(frame, D_L11_001B05CC, half, life, angle, 0x31, 2);
            size *= 0.7f;
            life = func_002A7820(8, 0x16);
            angle = func_002A7940();
            func_L02_003FFC48(frame, D_L11_001B05D0, size, life, angle, 0xB, 2);
        }
    }
}
