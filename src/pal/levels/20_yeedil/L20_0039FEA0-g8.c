#include "include_asm.h"

#include "common.h"
extern float D_L20_001AECF0 __attribute__((sda));
extern float D_L20_001AECF4 __attribute__((sda));
extern float D_L20_001AECF8 __attribute__((sda));
extern float D_L20_001AECFC __attribute__((sda));
extern void func_002B60B0(void *, float, float, float, float);
extern void func_L20_00330A68(void *, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void *func_002A9640(void *, u32, s32);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_0029F338(void *);
extern int func_002B3BA8(void *, int, int, int, float, float);
typedef struct {
    char pad0[0x10];
    unsigned char b10, b11, b12;
    char pad13[3];
    unsigned char b16;
    char pad17[5];
    float f1C, f20, f24, f28, f2C, f30, f34, f38, f3C;
    char pad40[8];
    int i48;
    char pad4C[0x20];
    unsigned char b6C, b6D, b6E, b6F;
    char pad70[2];
    unsigned char b72, b73;
    char pad74[2];
    unsigned char b76;
} Damage0039D340;
typedef struct {
    char pad0[0x20];
    float f20;
    short s24;
    char pad26[0x8];
    unsigned char b2E;
    char pad2F[0x21];
    float f50, f54, f58, f5C, f60;
    char pad64[0x1C];
    float f80, f84;
    char pad88[0xB8];
    Damage0039D340 damage;
    char pad1B8[0x38];
    float f1F0[4];
    void *p200;
    char pad204[0x2C];
    int i230;
    char pad234[0x20];
    void *p254;
    void *children[2];
    char pad260[0x20];
    unsigned char *p280;
} State0039D340;
typedef struct {
    char pad0[0x20];
    unsigned char b20;
    char pad21[0x13];
    unsigned short h34;
    char pad36[0xD];
    unsigned char b43;
    char pad44[0x24];
    State0039D340 *state;
    char pad6C[0x10];
    short h7C;
    char pad7E[0x1A];
    int i98;
    char pad9C[0xC];
    unsigned char bA8;
} Object0039D340;

void func_PAL_L20_003A0288(Object0039D340 *object) {
    State0039D340 *st = object->state;
    unsigned char *event;
    unsigned char *target;
    void **child;
    int count;

    if (object->b20 == 0) {
        st->damage.b10 = 5;
        st->damage.b11 = 18;
        st->damage.b12 = 17;
        st->damage.b16 = 20;
        st->damage.b6C = 5;
        st->damage.b6D = 9;
        st->damage.b6E = 4;
        st->damage.b6F = 7;
        st->damage.b72 = 10;
        st->damage.b73 = 17;
        st->damage.b76 = 0;
        st->damage.f30 = 0.5f;
        st->damage.f28 = 0.012f;
        st->f58 = 0.40000000596046448f;
        st->damage.i48 = 1;
        st->damage.f34 = 0.5f;
        st->damage.f3C = 0.15000000596046448f;
        st->damage.f1C = 0.40000004f;
        st->damage.f20 = 0.14000002f;
        st->damage.f24 = 0.006f;
        st->damage.f2C = 0.012f;
        st->f54 = 0.20000000298023224f;
        st->f50 = 0.82499998807907104f;
        st->f5C = 0.40000000596046448f;
        st->f60 = 1.5707964897155762f;
        st->f80 = 0.52359884977340698f;
        st->f84 = 0.10000000149011612f;
        object->h7C = 15;
        func_002B60B0(object, D_L20_001AECF4 * 0.00040000002f,
                     D_L20_001AECF0 * 0.020000001f,
                     D_L20_001AECFC * 6.981318e-06f,
                     D_L20_001AECF8 * 0.0003490659f);
        if (st->s24 == 0) {
            st->s24 = 10;
            st->f20 = 10.0f;
        }
        func_L20_00330A68(object, 0xD0F);
        func_002A7750(object, 6, 2);
        if (object->b43) func_PAL_002A7E68(object, 0, 0, 0);
        object->h34 = (object->h34 | 0x4000) & 0xFFFB;
    }
    event = func_002A9640(object, 0x10000, 0);
    if (event && *(unsigned char **)(event + 0x20) && *(short *)(*(unsigned char **)(event + 0x20) + 0xAA) == 0xD0F)
        object->bA8 = 255;
    func_PAL_002B1A50(object, &st->damage, 0);
    if (st->b2E == 2) {
        func_002A7750(object, 6, 2);
        object->i98 = 0;
        object->h34 = (object->h34 | 0x41) & 0xEFFF;
        child = st->children;
        for (count = 0; count < 2; count++) {
            if (*child) {
                func_0029F338(*child);
                *child = 0;
            }
            ++child;
        }
        if (st->p254) func_0029F338(st->p254);
        st->p254 = 0;
    }
    st->b2E = 1;
    target = st->p280;
    if (target) {
        st->p200 = target;
        qcopy(&st->f1F0, target + 0x10);
        st->f1F0[2] += 0.5f;
    } else {
        func_002B3BA8(object, st->i230, 0, 0, 128.0f, 0.0f);
    }
}
