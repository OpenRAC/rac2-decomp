/* func_PAL_L00_0035B058, the PAL copy of func_L00_00358B30: the same C, where rename func_L00_00303530 becomes func_PAL_L00_00305110; rename func_L00_002B2A40 becomes func_PAL_L00_002B2958. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    unsigned char pad00[0x80];
    Quadword position;
    Quadword rotation;
    unsigned char padA0[0x21F0];
    unsigned char *moby;
    unsigned char pad2294[0x32];
    unsigned char state;
} Hero;
extern Hero D_00189E20;
typedef struct {
    unsigned char pad00[0x64];
    int field64;
    unsigned char field68, field69, field6A, field6B;
} GameState;
extern GameState D_00188660;
extern unsigned short D_001A63F0[];
typedef struct {
    int active, reserved04[3];
    Quadword position, rotation;
    int field30, field34, field38;
    unsigned char field3C, field3D, field3E, field3F, field40, field41;
    unsigned char reserved42[2];
    float field44, field48, field4C, field50;
    int field54, field58, field5C;
    unsigned char reserved60[0xC04];
    unsigned short fieldC64, reservedC66;
    int fieldC68, reservedC6C;
} SavedState;
extern SavedState D_L00_0021DDB0;
extern unsigned char D_L00_0021D140[0xC70];
extern int D_L00_001C9340[];
extern unsigned char D_L00_001B1980[] __attribute__((sda));
extern unsigned char D_L00_001B1981[] __attribute__((sda));
extern unsigned char D_L00_001B1982[] __attribute__((sda));
extern float D_L00_001B1984[] __attribute__((sda));
extern float D_L00_001B1988[] __attribute__((sda));
extern float D_L00_001B198C[] __attribute__((sda));
extern float D_L00_001B1990;
extern unsigned char *D_L00_001B1E9C[] __attribute__((sda));
extern unsigned char *D_L00_001B1EA0[] __attribute__((sda));
extern void *func_00282A60(void *, int, unsigned int);
extern void *func_00282AB0(void *, const void *, unsigned int);
extern void func_PAL_L00_00305110(int, int);
extern void func_00282A28(void);
extern void func_PAL_L00_002B2958(int, int, void *);
extern void func_002A0F48(void *);
extern void func_002833F0(void *, const void *);
extern void func_L00_002D9D98(void);
extern void func_L00_00358E50(void);

void func_PAL_L00_0035B058(void) {
    unsigned char *entity;
    int kind;
    int i;
    D_00189E20.state = 15;
    if (D_L00_0021DDB0.active == 0) {
        func_00282A60(D_L00_0021D140, 0, 0xC70);
        return;
    }
    func_00282AB0(D_L00_0021D140, &D_L00_0021DDB0, 0xC70);
    qcopy(&D_00189E20.position, &D_L00_0021DDB0.position);
    qcopy(&D_00189E20.rotation, &D_L00_0021DDB0.rotation);
    *(int *)(D_00189E20.moby + 0x38) = D_L00_0021DDB0.field30;
    *(int *)(D_00189E20.moby + 0x3C) = D_L00_0021DDB0.field34;
    D_00188660.field64 = D_L00_0021DDB0.field38;
    D_00188660.field68 = D_L00_0021DDB0.field3C;
    D_00188660.field69 = D_L00_0021DDB0.field3D;
    D_00188660.field6A = D_L00_0021DDB0.field3E;
    D_00188660.field6B |= 7;
    D_001A63F0[0] = D_L00_0021DDB0.fieldC64;
    if (D_L00_001C9340[0] != D_L00_0021DDB0.fieldC68)
        func_PAL_L00_00305110(D_L00_0021DDB0.fieldC68, *(int *)&D_L00_0021DDB0.fieldC64);
    D_L00_001B1980[0] = D_L00_0021DDB0.field3F;
    D_L00_001B1981[0] = D_L00_0021DDB0.field40;
    D_L00_001B1982[0] = D_L00_0021DDB0.field41;
    D_L00_001B1984[0] = D_L00_0021DDB0.field44;
    D_L00_001B1988[0] = D_L00_0021DDB0.field48;
    D_L00_001B198C[0] = D_L00_0021DDB0.field4C;
    D_L00_001B1990 = D_L00_0021DDB0.field50;
    if (D_L00_0021DDB0.field54 != 0 && D_L00_0021DDB0.field54 != 3) {
        kind = 0;
        switch (D_L00_0021DDB0.field54) {
        case 1:
            kind = 0x57;
            break;
        case 2:
            kind = 0x1A3;
            break;
        default:
            func_00282A28();
        }
        for (i = 0; (entity = D_L00_001B1E9C[0] + (i << 8)) < D_L00_001B1EA0[0]; i++) {
            if (*(short *)(entity + 0xAA) == kind) {
                func_PAL_L00_002B2958(D_L00_0021DDB0.field54, D_L00_0021DDB0.field5C, entity);
                break;
            }
        }
    }
done:
    func_002A0F48(D_00189E20.moby);
    func_002833F0(D_00189E20.moby + 0xC0, &D_00189E20.rotation);
    func_L00_002D9D98();
    func_L00_00358E50();
}
