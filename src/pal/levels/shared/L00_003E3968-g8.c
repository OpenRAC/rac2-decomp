/* func_PAL_L00_003E3968, the PAL copy of func_L00_003DF710: the same C, where func_002ABBB8
   becomes func_PAL_002AC718. */
#include "include_asm.h"
#include "common.h"

struct BFObject {
    char pad[0x30];
    unsigned char field_30;
    unsigned char field_31;
    unsigned short field_32;
};

extern struct BFPlayer { char pad[0xbf8]; char *target; } D_00189E20 NOT_SDA;

extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A8C00(void *, int, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_002A8C28(int, float, void *, int, float, float, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002AD330(void *, int, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_002AD0E0(void *, int, void *, void *, void *, void *);
extern void func_002AD250(void *, int, void *, void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int,
                          float, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_003DFDC0(void *);
extern int D_L00_001BF218 NOT_SDA;
extern int D_L00_001B0518 __attribute__((sda));
extern char D_L00_001A8F20[] MACRO_ADDR;

/* state 0: advances the object by its data's velocity; a collision deals damage and destroys it unless
   D_L00_001BF218 equals the data's type, otherwise it spawns three trail particles and grows its scale
   factor; state 1: spawns an explosion and deletes the object */
void func_PAL_L00_003E3968(char *object)
{
    float scale[4];
    float next[4];
    char query[48];
    float velocity[4];
    float zero[4];
    float pos[4];
    char *data = *(char **)(object + 0x68);
    float size0, size1, size2, spread;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(float *)(data + 0x18) = func_00283B98(*(float *)(data + 0x18), *(float *)(data + 0x1c));
        func_00282C88(scale);
        scale[1] = *(float *)(data + 0x18) * 0.25f;
        scale[0] = *(float *)(data + 0x18) * 0.5f;
        scale[2] = *(float *)(data + 0x18);
        func_002833F0(object + 0xc0, scale);
        func_00282CC0(next, object + 0x10, data);
        func_002A8C00(query, *(int *)(data + 0x10), 1, data, *(float *)(data + 0x14));
        *(unsigned short *)(query + 0x1a) = *(unsigned short *)(object + 0xaa);
        if (func_002761F8(object + 0x10, next, 0, object, query) || func_00277258(object + 0x10, 0, object, 0.3f)) {
            if (D_L00_001BF218) {
                if (D_L00_001BF218 != *(int *)(data + 0x10)) {
                    func_002A8C28(*(int *)(data + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(data + 0x14), 0, 0, 1, 0);
                    func_002A7750(object, 1, -1);
                    return;
                }
            } else {
                func_002A8C28(*(int *)(data + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(data + 0x14), 0, 0, 1, 0);
                func_002A7750(object, 1, -1);
                return;
            }
        }
        qcopy(object + 0x10, next);
        func_00282D30(velocity, data, -0.5f);
        func_00282C88(zero);
        if (*(int *)(data + 0x24)) {
            func_002AD330(object, *(int *)(data + 0x24), object + 0x10, pos);
            func_00282CC0(velocity, velocity, pos);
        }
        size0 = func_002A7878(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = func_002A7878(0.2f, 0.4f);
        func_002C65A0(object + 0x10, velocity, 5, D_L00_001B0518, 3, 0x4f, 0, size0,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        qcopy(pos, object + 0x10);
        pos[0] += func_002A78D8(0.0f, 0.15f);
        pos[1] += func_002A78D8(0.0f, 0.15f);
        pos[2] += func_002A78D8(0.0f, 0.15f);
        size1 = func_002A7878(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = func_002A7878(0.1f, 0.3f);
        func_002C65A0(pos, velocity, 5, D_L00_001B0518, 7, 0x5f, 0, size1,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        pos[0] += func_002A78D8(0.0f, 0.15f);
        pos[1] += func_002A78D8(0.0f, 0.15f);
        pos[2] += func_002A78D8(0.0f, 0.15f);
        size2 = func_002A7878(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = func_002A7878(0.2f, 0.4f);
        func_002C65A0(pos, velocity, 5, D_L00_001B0518, 12, 0x7f, 0, size2,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        if (*(int *)(data + 0x24)) {
            func_002AD0E0(object, *(int *)(data + 0x24), object + 0x10, object + 0xf0, object + 0x10, object + 0xf0);
            func_002AD250(object, *(int *)(data + 0x24), data, data);
        }
        break;
    case 1:
        func_PAL_002AC718(object, D_L00_001A8F20, object + 0x10, 0.0f, 0.0f, 10, 0, 16, 0.0f, 0.0f, 9.0f, 1.0f, -1,
                      15.0f, 0, 9, -1, 0, 0x810001);
        func_0029F338(object);
        return;
    }
    if (*(float *)(data + 0x20) < 1.0f)
        *(float *)(data + 0x20) += 0.025f;
    *(float *)(object + 0x2c) = func_002A7878(0.01f, 0.0125f) * *(float *)(data + 0x20);
    func_L00_002E6EF8(func_L00_003DFDC0, object);
}
