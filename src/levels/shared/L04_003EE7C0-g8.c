#include "include_asm.h"
/* func_L04_003EE7C0: the level-04 copy of func_L00_003C2FC8 (aim-assist target query),
 * over level 04's tuning block and tables. Same -g unit reasons as the twin. */
typedef int AimWord128 __attribute__((mode(TI)));
typedef union { AimWord128 word; float f[4]; } AimVector;
typedef struct { unsigned int words[5]; } AimQueryConfig;
typedef struct { char prefix[0x54]; float cooldown; char suffix[0xE0-0x58]; } AimTuning;
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; unsigned char *ptr[0x980]; } Hero;
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)
struct Rac2Native_5f824a0e369ccf7b_src_record {
    unsigned char b0,b1,b2,b3;
    unsigned short s4,s6,s8,s10,s12;
    unsigned char e,f;
};
extern AimQueryConfig D_L04_001B01B0;
extern AimTuning D_L04_0027B470[];
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L04_002BA6C0[];
extern unsigned char D_00189E20[];
extern unsigned char D_00138180[];
extern unsigned char D_00139592[];
extern float D_L04_001B01A0 __attribute__((sda));
extern float D_L04_001B01A4 __attribute__((sda));
extern float D_L04_001B01A8 __attribute__((sda));
extern float D_L04_001B01AC __attribute__((sda));
extern int D_L04_001B2F38;
extern void func_0029FCC0(char *, int, char *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_002AB1F0(unsigned char *);
extern int func_00282948(void *);
extern unsigned char *func_002AF580(void *, void *, void *, float, float, int, int, int, float, float, float, int, AimQueryConfig *);
extern void func_002FDF40(void *, void *, void *, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern void func_L00_002AF7D0(void);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void);
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_003E7650(int, char *, char *);
extern int func_L00_002D4040(int);
extern void func_L00_002D6B70(int);
extern int func_002829D8(void *);
extern void func_L00_003C33E0(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);

/* Moby update: Mini-Nuke (class 2650). */
void func_L04_003EE7C0(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *target;
    char *info;
    AimVector position;
    AimQueryConfig config;
    AimVector scratch;
    int allowed;
    func_0029FCC0((char *)object, 0, (char *)&position);
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        func_002A75E0(object, 1, 0, 2, 0);
    target = 0;
    if (H->ptr[0x1450 / 4] && H->ptr[0x1450 / 4][0x20] != 0xFE && H->ptr[0x1450 / 4][0x20] != 0xFD) {
        info = (char *)func_002AB1F0(H->ptr[0x1450 / 4]);
        if (info && *(float *)info > 0.0f)
            target = H->ptr[0x1450 / 4];
    }
    allowed = 1;
    if (H->i[0x2294 / 4] == 0x1D || H->i[0x2294 / 4] == 1) {
        if (func_00282948(&H->i[0x2534 / 4]) == 0)
            allowed = 0;
    } else {
        H->i[0x2534 / 4] = 0x28;
        if (!target) {
            config = D_L04_001B01B0;
            target = func_002AF580(&position, &H->b[0x760], &scratch, 0.392699093f, 0.785398185f,
                                  0, 0, 0, 11.1f, 0.0f, 0.0f, 0, &config);
        }
    }
    func_002FDF40(&config, &position, target, 0, D_L04_001B01A4, D_L04_001B01A0,
                   D_L04_001B01AC * 0.016666668f, D_L04_001B01A8 * 0.00027777778f);
    *(int *)(state + 0x24) = func_002FE5A0(&position, &config, state, state + 0x10, object, 0, 0,
                                          D_L04_001B01A8 * 0.00027777778f);
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        *(int *)(state + 0x2C) = -1;
        *(float *)(state + 0x20) = 0.0f;
        *(int *)(state + 0x28) = 0;
    case 1:
        if (H->i[0x1D8 / 4] >= 21)
            func_L00_002AF7D0();
        if (allowed && *(float *)(state + 0x20) == 0.0f && !H->b[0x22BC] && (PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) && H->i[0x1240 / 4] >= 23) {
            if (func_L00_002D3F30(-1, 1)) {
                D_L04_001B2F38 = 1;
                func_L00_002AF568();
                *(int *)(state + 0x2C) = func_L00_002D6998(D_L04_002BA6C0);
                func_002A75E0(object, 2, 0, 2, 0);
                func_L00_003E7650((int)object, (char *)&position, (char *)&config);
                func_002E5CF8(0, 0, (char *)object);
                {
                AimTuning *tu = &D_L04_0027B470[D_00139592[0]];
                *(float *)(state + 0x20) = 1.0f / tu->cooldown;
            }
            } else if ((PAD->u[0x1A4 / 4] & H->u[0x1230 / 4]) || D_L04_001B2F38 == 1) {
                func_002E5CF8(1, 0, (char *)object);
                D_L04_001B2F38 = 0;
            }
            if (!(PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) || !func_L00_002D4040(-1) || !H->b[0x22B8]) {
                if (*(int *)(state + 0x2C) >= 0) {
                    func_L00_002D6B70(*(int *)(state + 0x2C));
                    *(int *)(state + 0x2C) = -1;
                }
            }
        }
    }
    func_002829D8(state + 0x20);
    func_L00_002E6EF8(func_L00_003C33E0, object);
}
