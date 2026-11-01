#include "include_asm.h"

#include "common.h"
extern char D_001B27B0[] __attribute__((section(".sdata")));
extern int D_001B27C0 MACRO_ADDR;
extern char *D_001B27CC[] MACRO_ADDR;
extern char *D_001B27CC_gp SDATA(D_001B27CC);
extern int D_001B27C4;
extern int D_001B27C8;
extern float D_001B00F8 __attribute__((sda)), D_001B0108 __attribute__((sda)), D_001B010C __attribute__((sda));
extern int D_001B00FC __attribute__((sda)), D_001B0100 __attribute__((sda));
extern int D_001A8BB0 __attribute__((sda));
extern int D_001A8CFC[] MACRO_ADDR;
extern int D_0018C0B4[], D_00138324[];
extern char *D_001AD7EC[] MACRO_ADDR;
extern char *D_001B5390[];
extern char D_001BAFC0[], D_001BAF80[];
typedef struct { char pad[0x2290]; char *target; int state; } PlayerState;
extern PlayerState D_00189E20_9;
extern float D_0022AC90[][2];
extern void func_L00_003252A8(char *, char *, int);
extern void func_002FE8D8(char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int func_002761F8(char *, char *, int, char *, int);
extern int func_00278E78(void);
extern int func_002B0CE0(int, int, int);
extern float func_002A7940(void), func_002A78D8(float, float);
extern void func_US2_0029C548(int, void (*)(void));
extern void func_L00_003DDEC8(void), func_L00_0042ABF8(void), func_L00_003B8138(void);
extern void func_002FEE70(char *, char *, int);
extern void func_00300190(char *, char *), func_00300248(char *, char *);
extern void func_002FE880(char *, char *, float);
extern void func_00282C88(char *);
extern void func_US2_L00_002C4560(int, int);
extern void func_00335798(char *, char *, char *);
extern void func_002A7470(char *, int, int, int);
extern void func_002E5CF8(int, int, char *);
extern void func_US2_00327AB0(char *), func_00327848(char *), func_00326D90(char *), func_L00_003DF030(char *);
extern void func_00326BD8(void);
extern int func_00282948(char *), func_002FE9D0(char *), func_00300540(int);
extern float func_00282DF0(char *);
extern void func_0032DA58(char *, char *, char *, float);
extern void func_00327B40(char *), func_002FEE50(int), func_0029F338(char *);
extern void func_0027D098(void (*)(char *), char *), func_00327D08(char *);
extern void func_00283658(char *, char *);
extern void func_002AB6D8(char *, char *);
extern int func_002AD0E0(char *, char *, char *, char *, char *, char *);
extern void func_002833F0(char *, char *), func_002A9288(char *, float);
extern void func_L00_003DDEC8(void), ref_US2_L00_003DEAF8_00(void), func_L00_003B8138(void);

void func_US2_L00_003DEAF8(char *object)
{
    char oldpos[16], ahead[16], behind[16];
    char *data = *(char **)(object + 0x68);
    PlayerState *player;
    int i, result;
    float (*randoms)[2];
    if ((unsigned char)object[0x20] >= 2) {
        func_L00_003252A8(object, D_001B27B0, 1);
    } else {
        char *p = object + 0x10;
        func_002FE8D8(p, D_001B27B0);
    }
    func_00282D30(D_001B27B0, D_001B27B0, -1.0f);
    func_00282D30(ahead, object + 0xE0, D_001B0108);
    func_00282CC0(ahead, object + 0x10, ahead);
    func_00282D30(behind, object + 0xE0, -1.0f);
    func_00282CC0(behind, object + 0x10, behind);
    if (func_002761F8(ahead, behind, 2, object, 0)) {
        if (func_00278E78() == 2) {
            func_00282D30(D_001B27B0, D_001BAFC0, 0.0009765625f);
            func_00282F20(D_001B27B0, D_001B27B0, -1.0f);
            *(int *)(D_001B27B0 + 0x14) = 1;
        } else D_001B27C4 = 0;
        if (func_00278E78() == 6)
            D_001B27C8 = 1;
        else D_001B27C8 = 0;
    } else {
        D_001B27C4 = 0;
        *(int *)(D_001B27B0 + 0x18) = 0;
    }
    func_002B0CE0(6, 0, 1);
    /* Each case is its own block: the address-taken locals leave their stack slots when the
     * switch ends, and the attachment block below reuses that space. */
    switch ((unsigned char)object[0x20]) {
    case 0: {
        object[0x20] = 1;
        *(int *)(data + 0x18) = 0;
        *(float *)(object + 0x2C) = 0.00025f;
        D_001B27C0 = 1800;
        *(int *)(object + 0x98) = 0;
        randoms = D_0022AC90;
        i = 97;
        do {
            i--;
            (*randoms)[0] = func_002A7940();
            (*randoms)[1] = func_002A78D8(720.0f, 2160.0f) * 0.0002908882452175021f;
            randoms++;
        } while (i >= 0);
        if (D_001A8CFC[0]) func_US2_0029C548(0, func_L00_003DDEC8);
    }
        /* fall through */
    case 1: {
        player = &D_00189E20_9;
        if (player->state == 98 || D_001A8BB0 == 2 || player->state == 111 || player->state == 100 || player->state == 99 ||
            player->state == 23 || player->state == 24 || player->state == 129 || player->state == 39) {
            ref_US2_L00_003DEAF8_00();
            object[0x20] = 7;
            func_L00_003B8138();
            *(int *)(data + 0x20) = 0;
            break;
        }
        *(float *)(object + 0x2C) += 0.01f;
        if (*(float *)(object + 0x2C) > 0.0181099995970726f)
            *(float *)(object + 0x2C) = 0.0181099995970726f;
        qcopy(oldpos, object + 0x10);
        func_00282CC0(object + 0x10, object + 0x10, data);
        func_002FEE70(D_001B27CC[0], data, 0);
        func_00300190(object + 0x10, object + 0x10);
        func_00300248(data, data);
        func_002FE880(object + 0x10, data, 0.003055555745959282f);
        if (func_002761F8(oldpos, object + 0x10, 2, object, 0)) {
            char *hitinfo = D_001BAF80;
            char *hit = *(char **)(hitinfo + 0x18);
            if (hit && (hit == player->target || *(short *)(hit + 0xAA) == 0x907)) break;
            qcopy(object + 0x10, hitinfo + 0x20);
            func_00282C88(data);
            func_002B0CE0(6, 0, 1);
            func_US2_L00_002C4560(28, 1);
            func_00335798(object + 0x10, object + 0xF0, object);
            object[0x20] = 2;
            func_002A7470(object, 1, 0, 10);
            *(int *)(object + 0x48) = 0;
            return;
        }
        break;
    }
    case 2: {
        object[0x20] = 3;
        func_002E5CF8(2, 0, object);
        if (D_0018C0B4[0] != 28 || D_001A8BB0 == 2) {
            ref_US2_L00_003DEAF8_00();
            object[0x20] = 9;
            *(int *)(data + 0x20) = 0;
        }
        break;
    }
    case 3: {
        func_US2_00327AB0(object);
        func_00327848(object);
        func_00326D90(object);
        func_L00_003DF030(object);
        func_00326BD8();
        if (func_00282948((char *)&D_001B27C0)) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 10;
        }
        if (D_00138324[0] & 0x20) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 10;
        }
        if (D_0018C0B4[0] != 28 || D_001A8BB0 == 2) {
            ref_US2_L00_003DEAF8_00();
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
        func_00282CC0(object + 0x10, object + 0x10, data);
        func_002FE880(object + 0x10, data, 0.006111111491918564f);
        func_00300190(object + 0x10, object + 0x10);
        func_00300248(data, data);
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
        result = func_002FE9D0((char *)&collision);
        qcopy(object + 0x10, collision.end);
        qcopy(data, collision.velocity);
        if (result == 2) {
            if (func_00300540(collision.surface) || collision.surface == 12) {
                object[0x20] = 9;
                *(int *)(data + 0x20) = 10;
            } else {
                object[0x20] = result;
                func_00282C88(data);
            }
        } else if (func_00282DF0(data) > 0.4f) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 10;
        }
        break;
    }
    case 9: {
        object[0x20] = 5;
        func_L00_003B8138();
    }
        /* fall through */
    case 5: {
        char direction[16];
        if (func_00282948(data + 0x20)) {
            func_00282F20(direction, object + 0xC0, 1.0f);
            func_0032DA58(object, object + 0x10, direction, *(float *)(object + 0x18));
            func_002E5CF8(1, 0, object);
            object[0x20] = 6;
            *(unsigned short *)(object + 0x34) |= 0x41;
            if (D_0018C0B4[0] != 28 || D_001A8BB0 == 2) {
                ref_US2_L00_003DEAF8_00();
                *(int *)(data + 0x20) = 0;
            } else *(int *)(data + 0x20) = D_001B0100;
            *(int *)(data + 0x24) = 0;
        }
        break;
    }
    case 6: {
        func_00327B40(object);
        *(float *)(data + 0x24) += D_001B00F8 * (1.0f / 60.0f);
        if (func_00282948(data + 0x20) && !*(int *)(data + 0x28)) object[0x20] = 8;
        break;
    }
    case 7: {
        if (func_00282948(data + 0x20)) object[0x20] = 8;
        break;
    }
    case 8: {
        if (D_0018C0B4[0] == 28) func_US2_L00_002C4560(0, 1);
        if (*(short *)(D_001B5390[0] + 0x86) == 27) ref_US2_L00_003DEAF8_00();
        D_001B00FC = 0;
        func_US2_0029C548(0, 0);
        func_002FEE50((int)D_001B27CC_gp);
        func_0029F338(object);
        return;
    }
    }
    func_0027D098(func_00327D08, object);
    if ((unsigned char)object[0x20] >= 2 && D_001AD7EC[0]) {
        char angles[16], adjusted[16], matrix[64];
        func_00283658(matrix, object + 0xC0);
        func_002AB6D8(matrix, angles);
        func_002AD0E0(object, D_001AD7EC[0], object + 0x10, angles, object + 0x10, adjusted);
        func_002833F0(object + 0xC0, adjusted);
    }
    func_002A9288(object, D_001B010C);
}
