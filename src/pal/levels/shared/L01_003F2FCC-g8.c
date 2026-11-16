#include "include_asm.h"

#include "common.h"
extern void moby_release_and_reset_impact_slot(char *);
extern void anim_start_blended_pal(char *, int, int, int);
extern void anim_start_immediate(char *, int, int);
extern int math_fast_float_d(char *);
extern const int g_flashing_ring_color_a __attribute__((sda));
extern const int g_flashing_ring_color_b __attribute__((sda));
extern int math_fast_float_d(char *);

/* brings the ring out of the ground, then lets it spin and hand itself over */
void flashing_ring_update_pal(char *moby)
{
    char *vars;

    vars = *(char **)(moby + 0x68);
    moby_release_and_reset_impact_slot(moby);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(moby + 0x18) = *(float *)(moby + 0x18) + 1.0f;
        *(float *)(vars + 0x14) = *(float *)(moby + 0xF0);
        *(unsigned char *)(moby + 0x20) = 1;
        if (*(unsigned char *)(moby + 0x43) != 0)
            anim_start_blended_pal(moby, 0, 0, 0xA);
        *(int *)(vars + 0x50) = 0;
        *(unsigned short *)(moby + 0x34) |= 0x1000;
        break;
    case 1:
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            if (*(unsigned char *)(moby + 0x43) != 0)
                anim_start_immediate(moby, 0, 0);
        }
        if (*(unsigned char *)(moby + 0xBC) == 0)
            break;
        *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        anim_start_immediate(moby, 1, 0);
        if (*(int *)(vars + 0x0) != 0) {
            *(int *)(vars + 0x10) = 8;
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(vars + 0xC) = ((s32)(*(int *)(vars + 0x4)) * 5 + 2) / 6;
        } else {
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(moby + 0x78) = g_flashing_ring_color_b;
            *(int *)(vars + 0xC) = 0;
        }
        break;
    case 2:
        if (*(int *)(vars + 0x0) != 0) {
            if (math_fast_float_d(vars + 0x10) != 0) {
                if (*(int *)(moby + 0x78) == g_flashing_ring_color_a)
                    *(int *)(moby + 0x78) = g_flashing_ring_color_b;
                else
                    *(int *)(moby + 0x78) = g_flashing_ring_color_a;
                *(int *)(vars + 0x10) = 8;
            }
            if (math_fast_float_d(vars + 0xC) != 0)
                *(unsigned char *)(moby + 0xBC) = 0;
        }
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            if (*(unsigned char *)(moby + 0x43) == 1)
                anim_start_immediate(moby, 2, 0);
        }
        if (*(unsigned char *)(moby + 0xBC) != 0)
            break;
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            *(unsigned short *)(moby + 0x34) |= 0x1000;
            anim_start_immediate(moby, 3, 0);
            *(unsigned char *)(moby + 0x20) = 1;
            *(int *)(moby + 0x78) = g_flashing_ring_color_a;
        }
        break;
    }
}
