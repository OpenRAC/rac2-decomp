#include "include_asm.h"
#include "names.h"


extern unsigned char g_swingshot_peer_flag;
extern int D_L00_002A27F0[];
extern void anim_start_blended(void *, int, int, int);
extern void moby_mark_spawned(void *);
extern void func_002A10E8(void *);
extern void moby_mark_spawned(void *);

void swingshot_hook_update_pal(unsigned char *self)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    unsigned char *peer;
    unsigned char *data;
    int state;

    if (self == 0)
        return;
    data = *(unsigned char **)(self + 0x68);
    if (data == 0)
        return;
    peer = *(unsigned char **)data;
    if (peer == 0 || *(short *)(peer + 0xAA) != 0xD0 || peer[0x20] == 0xFE ||
        peer[0x20] == 0xFD || *(unsigned char **)(*(unsigned char **)(peer + 0x68) + 0x14) != self)
        goto destroy;
    if ((*(unsigned short *)(peer + 0x34) & 1) || g_swingshot_peer_flag != 0)
        *(unsigned short *)(self + 0x34) |= 0x41;
    else
        *(unsigned short *)(self + 0x34) &= 0xFFBE;
    state = self[0x20];
    if ((unsigned int)state < 8)
        goto *D_L00_002A27F0[state];
    goto activate_one;
c0:
    if (self[0x60] & 2) {
        if (self[0x43] != 1)
            anim_start_blended(self, 1, 0, 8);
        self[0x20] = 1;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c1:
    if ((*(unsigned char **)data)[0x20] == 2) {
        if (self[0x43] != 3)
            anim_start_blended(self, 3, 0, 8);
        self[0x20] = 3;
        *(float *)(self + 0x48) = 1.0f;
    } else if ((*(unsigned char **)data)[0x20] == 8) {
        if (self[0x43] != 2)
            anim_start_blended(self, 2, 0, 8);
        self[0x20] = 2;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c2:
    if (!(self[0x60] & 2))
        goto finish;
destroy:
    moby_mark_spawned(self);
    return;
c3:
    if (self[0x60] & 2) {
        if (self[0x43] != 4)
            anim_start_blended(self, 4, 0, 8);
        self[0x20] = 4;
    }
    goto finish;
c4:
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 3) < 3) {
        if (self[0x43] != 5)
            anim_start_blended(self, 5, 0, 8);
        self[0x20] = 5;
    }
    goto finish;
c5:
    if (self[0x60] & 2)
        *(float *)(self + 0x48) = 0.0f;
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 6) < 2) {
        *(float *)(self + 0x48) = 1.0f;
        if (self[0x43] != 7)
            anim_start_blended(self, 7, 0, 8);
        self[0x20] = 7;
    }
    goto finish;
c7:
    if (!(self[0x60] & 2))
        goto finish;
activate_one:
    if (self[0x43] != 1)
        anim_start_blended(self, 1, 0, 8);
    self[0x20] = 1;
c6:
finish:
    func_002A10E8(self);
}

extern char *g_turret_target_moby __attribute__((sda));
extern float g_tick_time_scale[] __attribute__((sda));
extern void moby_carry_with_surface(char *, char *);
extern int cam_moby_update(unsigned char *);
extern int math_random_int_below(int);
extern void moby_set_state(unsigned char *, unsigned char, int);

void moby_fade_out_update_pal(unsigned char *self)
{
    if (g_turret_target_moby != 0)
        moby_carry_with_surface((char *)self, g_turret_target_moby);
    switch (self[0x20]) {
    case 0:
        if (cam_moby_update(self) != 0 ||
            (g_tick_time_scale[0] > 0.949999988079071044921875f && math_random_int_below(10) == 0)) {
            moby_set_state(self, 1, -1);
            *(unsigned short *)(self + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update(self);
        if (self[0x23] < 2)
            moby_mark_spawned(self);
        else
            self[0x23] -= 2;
        break;
    }
}

