#include "include_asm.h"

#include "common.h"
extern char D_L00_001B2B30[] __attribute__((section(".sdata")));
extern int D_L00_001B2B40 MACRO_ADDR;
extern char *D_L00_001B2B4C[] MACRO_ADDR;
extern char *D_L00_001B2B4C_gp SDATA(D_L00_001B2B4C);
extern int D_L00_001B2B44;
extern int D_L00_001B2B48;
extern float D_L00_001B0438 __attribute__((sda)), D_L00_001B0448 __attribute__((sda)), D_L00_001B044C __attribute__((sda));
extern int D_L00_001B043C __attribute__((sda)), D_L00_001B0440 __attribute__((sda));
extern int D_L00_001A8F00 __attribute__((sda));
extern int D_L00_001A904C[] MACRO_ADDR;
extern int D_0018C0B4[], D_00138324[];
extern char *D_L00_001ADB2C[] MACRO_ADDR;
extern char *D_L00_001B8E10[];
extern char D_L00_001BF240[], D_L00_001BF200[];
typedef struct { char pad[0x2290]; char *target; int state; } PlayerState;
extern PlayerState D_00189E20_9;
extern float D_L00_002474F0[][2];
extern void ref_L00_003DD6A8_00(char *, char *, int);
extern void ref_L00_003DD6A8_01(char *, char *);
extern void ref_L00_003DD6A8_02(char *, char *, float);
extern void ref_L00_003DD6A8_03(char *, char *, char *);
extern void ref_L00_003DD6A8_06(char *, char *, float);
extern int ref_L00_003DD6A8_04(char *, char *, int, char *, int);
extern int ref_L00_003DD6A8_05(void);
extern int ref_L00_003DD6A8_07(int, int, int);
extern float ref_L00_003DD6A8_08(void), ref_L00_003DD6A8_09(float, float);
extern void ref_L00_003DD6A8_10(int, void (*)(void));
extern void ref_L00_003DD6A8_41(void), ref_L00_003DD6A8_11(void), ref_L00_003DD6A8_12(void);
extern void ref_L00_003DD6A8_13(char *, char *, int);
extern void ref_L00_003DD6A8_14(char *, char *), ref_L00_003DD6A8_15(char *, char *);
extern void ref_L00_003DD6A8_16(char *, char *, float);
extern void ref_L00_003DD6A8_17(char *);
extern void ref_L00_003DD6A8_18(int, int);
extern void ref_L00_003DD6A8_19(char *, char *, char *);
extern void ref_L00_003DD6A8_20(char *, int, int, int);
extern void ref_L00_003DD6A8_21(int, int, char *);
extern void ref_L00_003DD6A8_22(char *), ref_L00_003DD6A8_23(char *), ref_L00_003DD6A8_24(char *), ref_L00_003DD6A8_25(char *);
extern void ref_L00_003DD6A8_26(void);
extern int ref_L00_003DD6A8_27(char *), ref_L00_003DD6A8_28(char *), ref_L00_003DD6A8_29(int);
extern float ref_L00_003DD6A8_30(char *);
extern void ref_L00_003DD6A8_31(char *, char *, char *, float);
extern void ref_L00_003DD6A8_32(char *), ref_L00_003DD6A8_33(int), ref_L00_003DD6A8_34(char *);
extern void ref_L00_003DD6A8_35(void (*)(char *), char *), ref_L00_003DD6A8_42(char *);
extern void ref_L00_003DD6A8_36(char *, char *);
extern void ref_L00_003DD6A8_37(char *, char *);
extern int ref_L00_003DD6A8_38(char *, char *, char *, char *, char *, char *);
extern void ref_L00_003DD6A8_39(char *, char *), ref_L00_003DD6A8_40(char *, float);

void func_PAL_L01_003E4058(char *object)
{
    char oldpos[16], ahead[16], behind[16];
    char *data = *(char **)(object + 0x68);
    PlayerState *player;
    int i, result;
    float (*randoms)[2];
    if ((unsigned char)object[0x20] >= 2) {
        ref_L00_003DD6A8_00(object, D_L00_001B2B30, 1);
    } else {
        char *p = object + 0x10;
        ref_L00_003DD6A8_01(p, D_L00_001B2B30);
    }
    ref_L00_003DD6A8_02(D_L00_001B2B30, D_L00_001B2B30, -1.0f);
    ref_L00_003DD6A8_02(ahead, object + 0xE0, D_L00_001B0448);
    ref_L00_003DD6A8_03(ahead, object + 0x10, ahead);
    ref_L00_003DD6A8_02(behind, object + 0xE0, -1.0f);
    ref_L00_003DD6A8_03(behind, object + 0x10, behind);
    if (ref_L00_003DD6A8_04(ahead, behind, 2, object, 0)) {
        if (ref_L00_003DD6A8_05() == 2) {
            ref_L00_003DD6A8_02(D_L00_001B2B30, D_L00_001BF240, 0.0009765625f);
            ref_L00_003DD6A8_06(D_L00_001B2B30, D_L00_001B2B30, -1.0f);
            *(int *)(D_L00_001B2B30 + 0x14) = 1;
        } else D_L00_001B2B44 = 0;
        if (ref_L00_003DD6A8_05() == 6)
            D_L00_001B2B48 = 1;
        else D_L00_001B2B48 = 0;
    } else {
        D_L00_001B2B44 = 0;
        *(int *)(D_L00_001B2B30 + 0x18) = 0;
    }
    ref_L00_003DD6A8_07(6, 0, 1);
    /* Each case is its own block: the address-taken locals leave their stack slots when the
     * switch ends, and the attachment block below reuses that space. */
    switch ((unsigned char)object[0x20]) {
    case 0: {
        object[0x20] = 1;
        *(int *)(data + 0x18) = 0;
        *(float *)(object + 0x2C) = 0.00025f;
        D_L00_001B2B40 = 1500;
        *(int *)(object + 0x98) = 0;
        randoms = D_L00_002474F0;
        i = 97;
        do {
            i--;
            (*randoms)[0] = ref_L00_003DD6A8_08();
            (*randoms)[1] = ref_L00_003DD6A8_09(720.0f, 2160.0f) * 0.0003490659f;
            randoms++;
        } while (i >= 0);
        if (D_L00_001A904C[0]) ref_L00_003DD6A8_10(0, ref_L00_003DD6A8_41);
    }
        /* fall through */
    case 1: {
        player = &D_00189E20_9;
        if (player->state == 98 || D_L00_001A8F00 == 2 || player->state == 111 || player->state == 100 || player->state == 99 ||
            player->state == 23 || player->state == 24 || player->state == 129 || player->state == 39) {
            ref_L00_003DD6A8_11();
            object[0x20] = 7;
            ref_L00_003DD6A8_12();
            *(int *)(data + 0x20) = 0;
            break;
        }
        *(float *)(object + 0x2C) += 0.01f;
        if (*(float *)(object + 0x2C) > 0.0181099995970726f)
            *(float *)(object + 0x2C) = 0.0181099995970726f;
        qcopy(oldpos, object + 0x10);
        ref_L00_003DD6A8_03(object + 0x10, object + 0x10, data);
        ref_L00_003DD6A8_13(D_L00_001B2B4C[0], data, 0);
        ref_L00_003DD6A8_14(object + 0x10, object + 0x10);
        ref_L00_003DD6A8_15(data, data);
        ref_L00_003DD6A8_16(object + 0x10, data, 0.0044f);
        if (ref_L00_003DD6A8_04(oldpos, object + 0x10, 2, object, 0)) {
            char *hitinfo = D_L00_001BF200;
            char *hit = *(char **)(hitinfo + 0x18);
            if (hit && (hit == player->target || *(short *)(hit + 0xAA) == 0x907)) break;
            qcopy(object + 0x10, hitinfo + 0x20);
            ref_L00_003DD6A8_17(data);
            ref_L00_003DD6A8_07(6, 0, 1);
            ref_L00_003DD6A8_18(28, 1);
            ref_L00_003DD6A8_19(object + 0x10, object + 0xF0, object);
            object[0x20] = 2;
            ref_L00_003DD6A8_20(object, 1, 0, 10);
            *(int *)(object + 0x48) = 0;
            return;
        }
        break;
    }
    case 2: {
        object[0x20] = 3;
        ref_L00_003DD6A8_21(2, 0, object);
        if (D_0018C0B4[0] != 28 || D_L00_001A8F00 == 2) {
            ref_L00_003DD6A8_11();
            object[0x20] = 9;
            *(int *)(data + 0x20) = 0;
        }
        break;
    }
    case 3: {
        ref_L00_003DD6A8_22(object);
        ref_L00_003DD6A8_23(object);
        ref_L00_003DD6A8_24(object);
        ref_L00_003DD6A8_25(object);
        ref_L00_003DD6A8_26();
        if (ref_L00_003DD6A8_27((char *)&D_L00_001B2B40)) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 8;
        }
        if (D_00138324[0] & 0x20) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 8;
        }
        if (D_0018C0B4[0] != 28 || D_L00_001A8F00 == 2) {
            ref_L00_003DD6A8_11();
            object[0x20] = 9;
            *(int *)(data + 0x20) = 0;
        }
        break;
    }
    case 4: {
        struct {
            char start[16], end[16], velocity[16];
            char *owner;
            int flags, mode;
            float radius, friction, elasticity;
            int field48, field4c, enabled, surface, field58;
        } collision;
        qcopy(oldpos, object + 0x10);
        ref_L00_003DD6A8_03(object + 0x10, object + 0x10, data);
        ref_L00_003DD6A8_16(object + 0x10, data, 0.0088f);
        ref_L00_003DD6A8_14(object + 0x10, object + 0x10);
        ref_L00_003DD6A8_15(data, data);
        qcopy(collision.start, oldpos);
        qcopy(collision.end, object + 0x10);
        qcopy(collision.velocity, data);
        collision.radius = 0.2f;
        collision.friction = 0.85f;
        collision.elasticity = 0.75f;
        collision.enabled = 1;
        collision.owner = object;
        collision.flags = 0;
        collision.mode = 0;
        collision.field48 = 0;
        collision.field4c = 0;
        collision.field58 = 0;
        result = ref_L00_003DD6A8_28((char *)&collision);
        qcopy(object + 0x10, collision.end);
        qcopy(data, collision.velocity);
        if (result == 2) {
            if (ref_L00_003DD6A8_29(collision.surface) || collision.surface == 12) {
                object[0x20] = 9;
                *(int *)(data + 0x20) = 8;
            } else {
                object[0x20] = result;
                ref_L00_003DD6A8_17(data);
            }
        } else if (ref_L00_003DD6A8_30(data) > 0.4f) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 8;
        }
        break;
    }
    case 9: {
        object[0x20] = 5;
        ref_L00_003DD6A8_12();
    }
        /* fall through */
    case 5: {
        char direction[16];
        if (ref_L00_003DD6A8_27(data + 0x20)) {
            ref_L00_003DD6A8_06(direction, object + 0xC0, 1.0f);
            ref_L00_003DD6A8_31(object, object + 0x10, direction, *(float *)(object + 0x18));
            ref_L00_003DD6A8_21(1, 0, object);
            object[0x20] = 6;
            *(unsigned short *)(object + 0x34) |= 0x41;
            if (D_0018C0B4[0] != 28 || D_L00_001A8F00 == 2) {
                ref_L00_003DD6A8_11();
                *(int *)(data + 0x20) = 0;
            } else *(int *)(data + 0x20) = ((s32)D_L00_001B0440 * 5 + 2) / 6;
            *(int *)(data + 0x24) = 0;
        }
        break;
    }
    case 6: {
        ref_L00_003DD6A8_32(object);
        *(float *)(data + 0x24) += D_L00_001B0438 * (0.020000001f);
        if (ref_L00_003DD6A8_27(data + 0x20) && !*(int *)(data + 0x28)) object[0x20] = 8;
        break;
    }
    case 7: {
        if (ref_L00_003DD6A8_27(data + 0x20)) object[0x20] = 8;
        break;
    }
    case 8: {
        if (D_0018C0B4[0] == 28) ref_L00_003DD6A8_18(0, 1);
        if (*(short *)(D_L00_001B8E10[0] + 0x86) == 27) ref_L00_003DD6A8_11();
        D_L00_001B043C = 0;
        ref_L00_003DD6A8_10(0, 0);
        ref_L00_003DD6A8_33((int)D_L00_001B2B4C_gp);
        ref_L00_003DD6A8_34(object);
        return;
    }
    }
    ref_L00_003DD6A8_35(ref_L00_003DD6A8_42, object);
    if ((unsigned char)object[0x20] >= 2 && D_L00_001ADB2C[0]) {
        char angles[16], adjusted[16], matrix[64];
        ref_L00_003DD6A8_36(matrix, object + 0xC0);
        ref_L00_003DD6A8_37(matrix, angles);
        ref_L00_003DD6A8_38(object, D_L00_001ADB2C[0], object + 0x10, angles, object + 0x10, adjusted);
        ref_L00_003DD6A8_39(object + 0xC0, adjusted);
    }
    ref_L00_003DD6A8_40(object, D_L00_001B044C);
}
