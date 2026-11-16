#include "include_asm.h"

#include "common.h"
extern int trooper_spawn_parts(char *, int);
extern void *func_00325040(int);
extern void func_0033E708(char *, char *);
extern char *func_00338198(char *);
extern void func_00326528(char *, int, char *);
extern f32 func_00303270(f32, f32);
extern void func_00327AD0(void *);
extern void func_003381E0(void *, void *);
extern void func_00338830(void *, u32, int, int);
extern void func_0032F2D0(void *, int, int, int);
extern f32 vec_distance_xy(void *, void *);

/* Creates the torso and leg parts if asked, then puts them on the trooper pose. Returns 0 if a part cannot be made. */
int trooper_spawn_parts_pal(char *moby_arg, int create_parts) {
    char *part;
    char *part_slot;
    char *moby = moby_arg;
    char *state;
    char *work;
    int part_index;
    char *part_ptr;
    int six;
    int result;

    state = *(char **)(moby + 0x68);
    if (create_parts != 0) {
        if (*(char **)(state + 0x254) == 0) {
            part = (char *)func_00325040(0xD0E);
            if (part == 0) {
                result = 0;
                goto out;
            }
            func_0033E708(part, moby);
            *(u16 *)(part + 0x7C) = 0x3FF;
            *(char **)(state + 0x254) = part;
        }
        work = 0;
        part_slot = state + 0x258;
        while ((int)work < 2) {
            if (*(u32 *)part_slot == 0) {
                part = (char *)func_00325040(0xD66);
                if (part == 0) {
                    result = 0;
                    goto out;
                }
                func_0033E708(part, moby);
                *(u32 *)part_slot = (u32)part;
            }
            work++;
            part_slot += 4;
        }
    }
    work = (char *)func_00338198(moby);
    if (*(char **)(state + 0x254) != 0) {
        func_00326528(moby, 0, *(char **)(state + 0x254) + 0x10);
        *(f32 *)(*(char **)(state + 0x254) + 0xF8) = func_00303270(*(f32 *)(moby + 0xF8), *(f32 *)(state + 0x288));
        func_00327AD0(*(char **)(state + 0x254));
        func_003381E0(*(char **)(state + 0x254), work);
        if (*(u8 *)(*(char **)(state + 0x254) + 0x43) != *(u8 *)(moby + 0x43)) {
            func_0032F2D0(*(char **)(state + 0x254), *(u8 *)(moby + 0x43), *(u8 *)(moby + 0x41), 0x8);
        }
    }
    part_index = 0;
    six = 6;
    part_ptr = state + 0x258;
    while (part_index < 2) {
        if (*(u32 *)part_ptr != 0) {
            func_00338830(*(char **)(state + 0x254), *(u32 *)part_ptr, part_index, (part_index == 1) ? six : 0);
            func_003381E0(*(u32 *)part_ptr, work);
        }
        part_index++;
        part_ptr += 4;
    }
    result = 1;
out:
    return result;
}

