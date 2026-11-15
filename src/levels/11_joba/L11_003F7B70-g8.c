#include "common.h"

extern s32 FloatToInt(f32 a0);
extern u8 *g_moby_l11_table;
extern u8 D_L11_00188660[];
extern void *g_group_id_lists[];
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern s32 PlayMobySound(s32, s32, u8 *);
extern void snd_stop_voice(s32);
extern s32 D_L11_001B0808 __attribute__((sda));

/* Once the linked object is in state 2 and the shared step counter is in phase, moves the object
   through one cycle along its vector from its start position, keeping its sound playing; when its
   trigger value is set, flags the objects of the two listed groups (0xCF5, 0xCF6, 0xD07) and sets
   its own state to 4.
   The two sound lookups are separate values, and the early exits return without stepping the
   shared counter, as retail does. */
void pulsing_platform_trigger_update(u8 *moby_arg) {
    f32 offset[4];
    u8 *moby_table = g_moby_l11_table;
    u8 *self = moby_arg;
    u8 *vars = *(u8 **)(self+0x68);
    u8 *target = moby_table + *(s32 *)(vars+8)*256;
    u8 *sound_slot;
    s16 *victims;
    s16 *group_list;
    u8 *victim;
    switch (*(u8 *)(self+0x20)) {
    case 0:
        *(u8 *)(self+0x20) = 1;
        *(f32 *)(vars+0xC) = 3.1415927410125732f;
        *(s32 *)(vars+0x10) = 0;
        D_L11_001B0808 = 0;
        qcopy(vars+0x20,self+0x10);
        *(s32 *)(vars+0x1C) = 0;
        /* fall through */
    case 1:
        if (*(s32 *)vars && *(u8 *)(target+0x20) == 2 &&
            D_L11_001B0808 == FloatToInt(*(f32 *)(vars+4)*15.0f)) {
            *(u8 *)(self+0x20) = 2;
            *(f32 *)(vars+0xC) = 3.1415927410125732f;
            *(s32 *)(vars+0x10) = 0;
        }
        break;
    case 2: {
        s32 handle;
        *(f32 *)(vars+0x10) += 0.05235988646745682f;
        *(f32 *)(vars+0xC) = FastAddRotations(*(f32 *)(vars+0xC),0.05235988646745682f);
        handle = *(s32 *)(vars+0x30);
        sound_slot = D_L11_00188660 + handle * 0x70;
        if (*(u8 **)(sound_slot+0x88) != self || !*(u8 *)(sound_slot+0x74))
            *(s32 *)(vars+0x30) = PlayMobySound(0,4,self);
        if (*(f32 *)(vars+0x10) >= 6.2831854820251465f) {
            if (*(u8 *)(target+0x20) != 2) {
                *(u8 *)(self+0x20) = 1;
                if (*(s32 *)(vars+0x30) != -1) {
                    u8 *sound = D_L11_00188660 + *(s32 *)(vars+0x30)*0x70;
                    if (*(u8 **)(sound+0x88) == self && *(u8 *)(sound+0x74))
                        snd_stop_voice(*(s32 *)(vars+0x30));
                }
                *(s32 *)(vars+0x30) = -1;
            }
            *(s32 *)(vars+0x10) = 0;
            *(f32 *)(vars+0xC) = 3.1415927410125732f;
            qcopy(self+0x10,vars+0x20);
        } else {
            vec_scale_to_length(offset,self+0xD0,-(math_fast_sin_or_cos_a(*(f32 *)(vars+0xC))+1.0f)*2.2f);
            FastVecAdd(self+0x10,offset,vars+0x20);
        }
        break;
    }
    }
    if (*(f32 *)(vars+4) == 1337.0f) {
        if (*(u8 *)(target+0x20) == 2) {
            if (*(s32 *)(vars+0x1C) == 0) {
                *(s32 *)(vars+0x1C) = 1;
                if (*(s32 *)(vars+0x14) == 255 || (group_list = g_group_id_lists[*(s32 *)(vars+0x14)]) == 0) {
                    *(u8 *)(self+0x20) = 4;
                    return;
                }
                victims = group_list;
                do {
                    victim = g_moby_l11_table + ((*victims & 0x7FFF) << 8);
                    if (*(s8 *)(victim+0x20) >= 0) {
                        s32 kind = *(s16 *)(victim+0xAA);
                        if (kind == MOBY_CLASS_JOBA_TRIBESMAN) *(u8 *)(victim+0x95) = 1;
                        else if (kind == 0xCF6 /* moby class 3318 */) *(u8 *)(victim+0x95) = 1;
                        else if (kind == MOBY_CLASS_JOBIAN_SAUR_BEAST) *(u8 *)(victim+0x95) = 1;
                    }
                } while (*victims++ >= 0);
                if (*(s32 *)(vars+0x18) == 255 || (group_list = g_group_id_lists[*(s32 *)(vars+0x18)]) == 0) {
                    *(u8 *)(self+0x20) = 4;
                    return;
                }
                victims = group_list;
                do {
                    victim = g_moby_l11_table + ((*victims & 0x7FFF) << 8);
                    if (*(s8 *)(victim+0x20) >= 0) {
                        s32 kind = *(s16 *)(victim+0xAA);
                        if (kind == MOBY_CLASS_JOBIAN_SAUR_BEAST) *(u8 *)(victim+0x95) = 1;
                        else if (kind == 0xCF6 /* moby class 3318 */) *(u8 *)(victim+0x95) = 1;
                        else if (kind == MOBY_CLASS_JOBA_TRIBESMAN) *(u8 *)(victim+0x95) = 1;
                    }
                } while (*victims++ >= 0);
                *(u8 *)(self+0x20) = 4;
            }
            if (++D_L11_001B0808 > 104) D_L11_001B0808 = 0;
        } else D_L11_001B0808 = 0;
    }
}
