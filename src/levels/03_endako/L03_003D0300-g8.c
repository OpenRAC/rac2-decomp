#include "common.h"
extern int func_2DC9B0(char *);
extern void func_31B920(char *, int, int);
extern int func_2E1C70(float, void *, int, void *, int);
extern float func_2EF190(void *, void *);
extern void func_311758(void *);
extern int g_frame_l03_counter;
extern char *D_L03_001C3E40[];
extern int D_L03_001B0580 __attribute__((sda));
/* Per-frame update of moby class 2516, a piece of debris thrown from a trash can: it flies, breaks when it hits a Megacorp bot or the hero, then fades away. */
void trash_can_debris_update(char *moby)
{
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        if (func_2DC9B0(moby)) {
            func_31B920(moby, 1, -1);
            *(u16 *)(moby + 0x34) |= 0x2000;
        }
        break;
    case 1:
        if ((g_frame_l03_counter & 15) == (((int)moby >> 8) & 15)) {
            int count = func_2E1C70(0.2f, moby + 0x10, 0, moby, 0);
            if (count > 0) {
                int remaining = count;
                char **nearby_list = D_L03_001C3E40;
                do {
                    int type = *(s16 *)(*nearby_list + 0xAA);
                    if (type == MOBY_CLASS_MEGACORP_SWEEPER_BOT || type == MOBY_CLASS_MEGACORP_LASER_BOT)
                        func_31B920(moby, 3, -1);
                    --remaining;
                    ++nearby_list;
                } while (remaining);
            }
        }
        if (func_2EF190(moby + 0x10, &D_L03_001B0580) < 0.3f)
            func_31B920(moby, 3, -1);
        {
            u32 timer = *(u16 *)(moby + 0x96);
            u32 old = timer++;
            *(u16 *)(moby + 0x96) = timer;
            if (old > 600 && !*(u8 *)(moby + 0x31))
                func_31B920(moby, 2, -1);
        }
        break;
    case 2:
    case 3: {
        int amount = *(u8 *)(moby + 0x20) == 2 ? 2 : 8;
        int alpha = *(u8 *)(moby + 0x23);
        if (alpha < amount) func_311758(moby);
        else *(u8 *)(moby + 0x23) = alpha - amount;
        break;
    }
    }
}
