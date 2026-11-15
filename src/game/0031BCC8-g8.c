#include "include_asm.h"
#include "common.h"

/* -G8 unit for func_0031BCC8, which reads D_001B1B5C absolutely
   (003173B0-g8.c declares it sda). */

/* Notes for this match (USA v1.01 and v2.00, boot and level 00):
   - The tuning stores are written so sched1 keeps retail's order: stores whose
     constant dies issue first, so the shared-constant uses that must come later
     (0x84, 0x9C, 0xCC..0xD2, 0x118) are written before their last use, and
     0x77 = 24 is written last among the bytes so it gets $v1.
   - Retail keeps a copy of data + 0x350 for both qcopy targets: written as an
     expression each time, gcse's reaching register survives because cse does
     not rewrite the qcopy asm inputs.
   - oldpos/origin/route are set before the event code; written as expressions,
     gcse would insert them on the group loop's entry edges, and loop.c would no
     longer move the 0x264 exit block out of the loop.
   - The child's 0x38 field is stored as an array element (an in-struct store),
     so the sda scalar D_001AFAF8 is read ahead of it. */

extern void three_part_turret_alert_group(char *);
extern unsigned short *D_001EE5A0[];
extern char *D_001B1B5C;
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern int CollLine(void *, void *, int, void *, int);
extern char D_001BAFA0[];
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern char *D_001B1C4C;
extern char *CreateMoby(int);
extern float D_001AFAF8 __attribute__((sda));
extern void func_002A0F48(void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void moby_transform_joint_point(void *, int, void *);
extern void vec_clear_128(void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern int D_001B1B78 __attribute__((sda));
extern int moby_count_group_not_in_state(int, int);
extern int hero_check_distance_zones(void *, int *, int, int, void *, float, float);

/* Sets up the object on its first frame and creates its three attached parts. Every frame it keeps the parts in place and, when hit or lifted, alerts the other members of its group. */
void three_part_turret_init_update(unsigned char *self)
{
    char local[0x40] __attribute__((aligned(16)));
    char *data = *(char **)(self + 0x68);
    char *position;
    char *oldpos;
    int *route;
    char *origin;
    int state;
    unsigned short *member;
    char *other;
    char *otherdata;
    if ((unsigned char)self[0x20] == 0) {
        *(char **)(data + 0x18) = data + 0x110;
        *(int *)(data + 0x290) = 1;
        *(int *)(data + 0x27C) = 0;
        *(int *)(data + 0x28C) = 0;
        *(float *)(data + 0x254) *= 0.01745329424738884f;
        {
            char *spawn = data + 0x5A0;
            position = self + 0x10;
            qcopy(spawn, position);
        }
        *(int *)(data + 0x294) = 0;
        *(int *)(data + 0x298) = 0;
        *(float *)(data + 0x90) = 0.5f;
        *(float *)(data + 0x94) = 0.5f;
        *(float *)(data + 0x114) = 0.5f;
        *(float *)(data + 0x84) = 0.004166666883975267f;
        *(float *)(data + 0x9C) = 0.4000000059604645f;
        *(char *)(data + 0xCC) = -1;
        *(char *)(data + 0xCD) = -1;
        *(char *)(data + 0xCE) = -1;
        *(char *)(data + 0xCF) = -1;
        *(char *)(data + 0xD2) = -1;
        *(float *)(data + 0x118) = 0.4000000059604645f;
        *(char *)(data + 0x70) = 15;
        *(int *)(data + 0xA8) = 5;
        *(char *)(data + 0x71) = 19;
        *(char *)(data + 0x72) = 21;
        *(char *)(data + 0x76) = 23;
        *(char *)(data + 0x77) = 24;
        *(float *)(data + 0x7C) = 0.10000000894069672f;
        *(float *)(data + 0x80) = 0.06666667014360428f;
        *(float *)(data + 0x88) = 0.008333333767950535f;
        *(float *)(data + 0x8C) = 0.004166666883975267f;
        *(char *)(data + 0xD3) = -1;
        *(float *)(data + 0x110) = 0.800000011920929f;
        *(float *)(data + 0x11C) = 0.4000000059604645f;
        *(float *)(data + 0x120) = 1.134464144706726f;
        *(float *)(data + 0x140) = 0.523598849773407f;
        *(float *)(data + 0x13C) = 0.0055555556900799274f;
        moby_set_controller_speed_limits(self, 0.004444444552063942f, 0.13333334028720856f, 0.0011635529808700085f, 0.10471977293491364f);
        qcopy(data + 0x200, position);
        *(int *)(data + 0x250) = 0;
        *(float *)(data + 0x210) = 1.0f;
        *(float *)(data + 0x21C) = 5.0f;
        *(float *)(data + 0x220) = 10.0f;
        data[0x28] = 3;
        moby_transform_joint_to_world(self, 3, data + 0x350);
        *(float *)(data + 0x358) += 20.0f;
        moby_transform_joint_to_world(self, 3, data + 0x360);
        if (CollLine(data + 0x360, data + 0x350, 0, self, 0))
            qcopy(data + 0x350, D_001BAFA0);
        if (*(int *)(data + 0x24C) == 0 && *(int *)(data + 0x258) == -1) {
            *(float *)(self + 0x18) = coll_probe_ground_height_below(position, 0, 0.5f);
            moby_set_state(self, 1, 0);
            if ((unsigned char)self[0x43] != 0) anim_start_blended(self, 0, 0, 0);
        } else {
            moby_set_state(self, 3, 2);
            if ((unsigned char)self[0x43] != 12) anim_start_blended(self, 12, 0, 0);
        }
        if (*(int *)(data + 0x258) != -1) {
            moby_set_state(self, 2, 0);
            qcopy(data + 0x350, D_001B1C4C + (*(int *)(data + 0x258) << 7) + 0x30);
            *(unsigned char *)(self + 0x30) = 0x80;
        }
        *(char **)(data + 0x270) = CreateMoby(0xAA2);
        (*(char **)(data + 0x270))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x270) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x270))[0x31] = 1;
        ((long long *)*(char **)(data + 0x270))[7] = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x270) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x270));
        moby_copy_joint_transform_to_object(self, *(char **)(data + 0x270), 0, 0);
        *(char **)(data + 0x274) = CreateMoby(0xAA2);
        (*(char **)(data + 0x274))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x274) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x274))[0x31] = 1;
        ((long long *)*(char **)(data + 0x274))[7] = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x274) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x274));
        moby_copy_joint_transform_to_object(self, *(char **)(data + 0x274), 1, 0);
        *(char **)(data + 0x278) = CreateMoby(0xAA2);
        (*(char **)(data + 0x278))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x278) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x278))[0x31] = 1;
        ((long long *)*(char **)(data + 0x278))[7] = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x278) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x278));
        moby_copy_joint_transform_to_object(self, *(char **)(data + 0x278), 2, 0);
    }
    oldpos = data + 0x5A0;
    origin = self + 0x10;
    route = (int *)(data + 0x248);
    moby_transform_joint_to_world(self, 3, data + 0x360);
    moby_transform_joint_to_world(self, 4, data + 0x370);
    moby_transform_joint_to_world(self, 5, data + 0x380);
    moby_transform_joint_point(self, 6, local);
    vec_clear_128(data + 0x390);
    *(int *)(data + 0x398) = 0;
    *(float *)(data + 0x390) = 0.25f;
    transform_vector(data + 0x390, data + 0x390, local);
    FastVecAdd(data + 0x390, data + 0x390, local + 0x30);
    moby_copy_joint_transform_to_object(self, *(char **)(data + 0x270), 0, 0);
    moby_copy_joint_transform_to_object(self, *(char **)(data + 0x274), 1, 0);
    moby_copy_joint_transform_to_object(self, *(char **)(data + 0x278), 2, 0);
    state = moby_apply_damage_to_object(self, data + 0x60, 0);
    if (state) {
        if (state == 5) {
            *(int *)(data + 0xF0) = 0;
            *(float *)(data + 0xF4) = 0.8377581834793091f;
        }
        three_part_turret_alert_group(self);
        if ((unsigned)(state - 4) < 2 && D_001B1B78 >= (unsigned char)self[0x21] && moby_count_group_not_in_state((unsigned char)self[0x21], -1) >= 2) {
            member = D_001EE5A0[(unsigned char)self[0x21]];
            for (;;) {
                other = D_001B1B5C + ((*member & 0x7FFF) << 8);
                if (*(short *)(other + 0xAA) == 0x9B4) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x2A4) == 0) {
                        *(int *)(otherdata + 0x2A4) = 1;
                        break;
                    }
                } else if (*(short *)(other + 0xAA) == 0x9B5) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x264) == 0) {
                        *(int *)(otherdata + 0x264) = 1;
                        goto group_done_0;
                    }
                }
                if (*(short *)member++ < 0) goto group_done_0;
            }
        group_done_0:;
        }
    }
    if (*(float *)(self + 0x18) - coll_probe_ground_height_below(origin, 0, 0.5f) > 20.0f && D_001B1B78 >= (unsigned char)self[0x21] && !*(int *)(data + 0x298)) {
        *(int *)(data + 0x298) = 1;
        if (moby_count_group_not_in_state((unsigned char)self[0x21], -1) >= 2) {
            member = D_001EE5A0[(unsigned char)self[0x21]];
            for (;;) {
                other = D_001B1B5C + ((*member & 0x7FFF) << 8);
                if (*(short *)(other + 0xAA) == 0x9B4) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x2A4) == 0) {
                        *(int *)(otherdata + 0x2A4) = 1;
                        break;
                    }
                } else if (*(short *)(other + 0xAA) == 0x9B5) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x264) == 0) {
                        *(int *)(otherdata + 0x264) = 1;
                        goto group_done_1;
                    }
                }
                if (*(short *)member++ < 0) goto group_done_1;
            }
        group_done_1:;
        }
    }
    *(short *)(data + 0x244) = hero_check_distance_zones(self, route, *(int *)(data + 0x230), *(int *)(data + 0x234), oldpos, *(float *)(data + 0x238), *(float *)(data + 0x23C));
}
