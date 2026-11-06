/* func_PAL_00287018, the PAL copy of func_00286738: the same C at 50 Hz timings, where
 * the mode 1 accept path also runs when D_001A7424 & 0x600 and func_PAL_00299518() hold,
 * and clears those flags with func_PAL_00299520() before closing.
 * It needs its own unit: -O2 -G8 -ffunction-sections -frac2-zero-ti-por
 * (config/cflags.txt). D_001B17D0's sda declaration gives retail's repeated
 * lui/addiu; D_0018C0D4, D_001F29A0 and D_001F2930 need absolute addressing;
 * D_001B1680 uses an incomplete sda view for its absolute store macro.
 * func_002AA548 returns float; func_0028B3D0 and func_PAL_002E5898 return int.
 * In USA v1.01 ref_00286738_00 is 0x1A8A44 in the boot and 0x1A8D94 in every level, where
 * func_L00_003A0C00 uses the name D_001A8A44 for a different word at 0x1A8A44.
 */

#include "common.h"

/* Modal state observed by the menu and camera transition handlers. */
typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    float cameraPosition[4];
    float cameraAngles[4];
    float returnPosition[4];
    float returnAngles[4];
    int mode;
    int countdown;
    char reserved48[12];
    int selection;
    int phase;
    int elapsed;
    int inputDelay;
    int reserved64;
    int pending;
    float fraction;
    float angle;
    char reserved74[8];
    short timer;
    short cameraActive;
    int savedValue;
    short result;
    short reserved86;
    int enabled;
    unsigned int acceptMask;
    unsigned int cancelMask;
    int gameState;
} ModalState;

typedef struct {
    char reserved00[0x100];
    float roll;
    char reserved104[0x44];
    float horizontal;
    float vertical;
    char reserved150[0x54];
    unsigned int buttons;
    char reserved1A8[0x18];
    unsigned int held;
    unsigned int pressed;
} ModalInput;

typedef struct CameraObject CameraObject;
struct CameraObject {
    char reserved00[0x64];
    void (*update)(CameraObject *);
    char reserved68[0x42];
    short kind;
    char reservedAC[0x54];
};

extern ModalState D_001BAC80;
extern ModalInput D_00138180;
extern int D_001B170C;
extern int D_001A7420;
extern int D_001A7424;
extern int D_001A8C88;
extern int D_001A8C8C;
extern int D_001F29A0 NOT_SDA;
typedef struct {
    char reserved00[0x18];
    int selection;
    char reserved1C[0xE4];
    int savedSelection;
} ModalSelection;
extern ModalSelection D_001F2840;
extern int *D_001F2930 NOT_SDA;
extern unsigned short D_0018C958[];
extern unsigned char D_001B1F10;
typedef struct {
    char reserved00[8];
    int status;
    char reserved0C[4];
    int result;
} ModalCardState;
extern ModalCardState D_001393E0;
extern int D_0013955C[];
extern int D_001A8B84 __attribute__((sda));
extern int D_001B1680[] __attribute__((sda));
extern int D_001A8A78 __attribute__((sda));
extern float D_001A8A7C __attribute__((sda));
typedef struct {
    float position[4];
    float angles[4];
    char reserved20[0x210];
    float matrix[16];
} ModalCamera;
extern ModalCamera D_001B5340;
extern float D_001B17D0[4] __attribute__((sda));
extern unsigned char D_001A7A44;
extern int D_001A79F0;
extern CameraObject *D_001B1B5C;
extern CameraObject *D_001B1B60;
extern unsigned char D_0018C0D4 NOT_SDA;
extern int D_001A8A40 __attribute__((sda));
extern int ref_00286738_00 __attribute__((sda));
extern int D_001A8A48 __attribute__((sda));
extern int D_001A8A60 __attribute__((sda));
extern int D_001A7BB8;

extern int func_PAL_002E5898(void);
extern int func_002B49E0(int, int, int, int, unsigned char *);
extern void func_0027D330(int);
extern int func_00288D80(void);
extern void func_00288D68(void);
extern int func_PAL_00299518(void);
extern void func_PAL_00299520(void);
extern void func_00287E80(void);
extern int func_002DF1D0(void);
extern int func_002C9A50(void);
extern void func_00298D28(int *);
extern void func_00287EA8(void);
extern int func_002B4B70(int, int);
extern void func_PAL_002997A0(void);
extern void func_002F64A8(void);
extern void func_PAL_002DF760(int);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00282DF0(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_PAL_002884F0(char *, int);
extern void func_00283098(void *, const void *, const void *);
extern void func_002AC9F8(float *, float);
extern void func_00282D30(void *, const void *, float);
extern void func_00287D98(char *);
extern void func_PAL_00288638(float *);
extern void func_00283698(void *, const void *);
extern void func_002AB6D8(float *, float *);
extern void func_00282D08(void *, const void *, const void *, float);
extern void func_002A91F0(void *, float *);
extern void func_00283810(void *, const void *, const void *, float);
extern void func_00283958(const void *, void *);
extern void func_PAL_0026F620(void);
extern void func_00290670(void);
extern void func_00287E60(void);
extern int func_0028B3D0(int, int, void (*)(unsigned char *), void (*)(), void (*)(), int, int);
extern void func_0028BDB0(unsigned char *);
extern void func_0028BE00();
extern void func_0028C6D0();
extern void func_0028CC98(unsigned char *);
extern void func_0028CCE0();
extern void func_0028D1E8();
extern void func_PAL_0029D7D0(void);
extern void func_PAL_0029C0B8(int);
extern void func_0029B698(int);
extern void func_00290728(void);
extern void func_00290720(void);
extern void func_PAL_002B5570(int);
extern int func_002E5E58(int, int, void *);
extern void func_002857B8(void);

/* Run the active modal dialog, camera return, or display-confirmation phase. */
void func_PAL_00287018(void)
{
    float delta[4], target[4], transform[16];
    float distance;
    ModalState *loadDialog, *saveDialog, *phaseDialog;
    ModalInput *saveInput;

    func_PAL_002E5898();
    D_001B170C = D_001BAC80.gameState;
    if (D_001BAC80.countdown)
        --D_001BAC80.countdown;
    if (D_001BAC80.timer)
        --D_001BAC80.timer;
    switch (D_001BAC80.mode) {
    case 2:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 75 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (D_001A7420 == 2) {
            func_002B49E0(4, 2, 1, 0, 0);
            break;
        }
        if (D_001BAC80.elapsed >= 101 && (D_00138180.buttons & 0x40)) {
            if (!D_0018C958[0x84 / 2])
                D_0018C958[0x84 / 2] = 1;
            { func_002B4B70(0, 0); break; }
        }
        break;
    case 5:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 25 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
            D_001A7424 &= ~0x40;
            D_0013955C[0] = 0;
            { func_PAL_002DF760(-1); func_002F64A8(); break; }
        }
        break;
    case 4:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 25 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
            D_0013955C[0] = 0;
            { func_PAL_002DF760(-1); func_002F64A8(); break; }
        }
        break;
    case 3:
        switch (D_001BAC80.phase) {
        case 0:
            if (!D_001BAC80.countdown)
                D_001BAC80.phase = 1;
            break;
        case 1:
            if (D_00138180.buttons & 0x10)
                { func_002B4B70(0, 0); break; }
            if (D_00138180.buttons & 0x40) {
                func_0027D330(4);
                D_001B1F10 = 0;
                D_001BAC80.phase = 2;
                D_001BAC80.elapsed = 500;
            }
            break;
        case 2:
            if (!D_001BAC80.elapsed || --D_001BAC80.elapsed == 0) {
                D_001B1F10 = 1;
                D_001BAC80.phase = 3;
                break;
            }
            if (D_00138180.buttons & 0x10) {
                func_0027D330(4);
                D_001B1F10 = 1;
                { func_002B4B70(0, 0); break; }
            } else if (D_00138180.buttons & 0x40) {
                D_001B1F10 = 0;
                { func_002B4B70(0, 0); break; }
            }
            break;
        case 3:
            if (!(D_00138180.buttons & 0x40))
                break;
        default:
            { func_002B4B70(0, 0); break; }
        }
        break;
    case 1:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 25 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (func_00288D80() || ((D_001A7424 & 0x600) && func_PAL_00299518())) {
            if (!(D_00138180.buttons & 0x40))
                break;
            func_00288D68();
            D_001A7424 &= ~0x640;
            func_PAL_00299520();
            func_00287E80();
            { func_002B4B70(0, 0); break; }
        }
        switch (D_001A7420) {
        case 2:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
                D_001BAC80.result = 2;
                D_001A7424 &= ~1;
                { func_002B4B70(0, 0); break; }
            }
            break;
        case 6:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x20)) {
                D_001A7424 |= 8;
                D_001BAC80.result = 2;
                break;
            }
            if (D_001BAC80.countdown || !(D_00138180.buttons & 0x10))
                break;
            if (D_001A8C8C) {
                D_001BAC80.result = 2;
                { func_PAL_002DF760(-1); func_002F64A8(); break; }
            }
            D_001A7424 |= 0x20;
            if (!func_002DF1D0())
                D_001A7424 &= ~2;
            D_001A7424 &= ~4;
            D_001BAC80.result = 1;
            if (!D_001A8C88) {
                func_002B4B70(0, 0);
                break;
            }
            break;
        case 13:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x20)) {
                D_001A7424 |= 0x10;
                D_001BAC80.result = 2;
                break;
            }
            if (D_001BAC80.countdown || !(D_00138180.buttons & 0x10))
                break;
            if (D_001A8C8C) {
                D_001BAC80.result = 2;
                { func_PAL_002DF760(-1); func_002F64A8(); break; }
            }
            D_001A7424 |= 0x20;
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
            D_001BAC80.result = 1;
            if (!D_001A8C88)
                { func_002B4B70(0, 0); break; }
            break;
        case 20:
            if (D_001BAC80.inputDelay || !(D_00138180.buttons & 0x40))
                break;
            D_001A7424 &= ~0x40;
                D_001A7424 &= ~0x400;
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
            D_001BAC80.result = 2;
            if (!D_001A8C88) {
                if (func_002C9A50()) {
                    func_00298D28(D_001F2930);
                    func_002B4B70(0, 0);
                } else {
                    D_0013955C[0] = 0;
                    D_001B1680[0] = -1;
                    D_001A8B84 = 1;
                }
                break;
            }
            func_002B4B70(0, 0);
            break;
        case 17:
        case 18:
        case 21:
            if (D_001BAC80.pending > 0) {
                if (--D_001BAC80.pending <= 0) {
                    if (D_001393E0.status == 2) {
                        if (!D_001393E0.result) {
                            D_001A7420 = 9;
                        } else if (D_001393E0.result == -1) {
                            D_001A7420 = 9;
                            D_001393E0.result = 0;
                        } else if (D_001393E0.result == -2) {
                            D_001A7420 = 5;
                        } else {
                            D_001A7420 = 12;
                        }
                        func_002B4B70(0, 0);
                    } else {
                        D_001BAC80.result = 2;
                        func_00287EA8();
                        func_PAL_002DF760(-1);
                        func_002F64A8();
                    }
                    break;
                }
            } else {
                if (D_001BAC80.inputDelay || !(D_00138180.buttons & 0x40))
                    break;
                func_00287EA8();
                if (D_001A8C8C) {
                    D_001BAC80.pending = 12;
                } else {
                    D_001BAC80.result = 2;
                    D_001A7424 &= ~0x40;
                    D_001A7424 &= ~0x400;
                    D_001A7424 &= ~2;
                    D_001A7424 &= ~4;
                    func_002B4B70(0, 0);
                }
            }
            break;
        case 1:
        case 16:
            func_002B4B70(0, 0);
            D_001F2840.selection = D_001BAC80.selection;
            D_001F2840.savedSelection = D_001BAC80.selection;
            break;
        case 12:
            if (!D_001F29A0)
                break;
        case 3:
        case 5:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x10)) {
                D_001BAC80.result = 1;
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
                { func_002B4B70(0, 0); break; }
            }
            break;
        case 19:
            if (D_001A8C88 && !D_001F29A0) {
                /* Set once, unlike a shared pointer, so alias analysis knows its
                 * base and the cancel arm's store has no tie to D_001A7424. The
                 * accept body below merges with case 23's copy at jump2. */
                ModalState *pickDialog = &D_001BAC80;
                if (pickDialog->inputDelay)
                    break;
                if (D_00138180.buttons & 0x40) {
                    func_PAL_002997A0();
                    pickDialog->result = 2;
                    D_001A7424 &= ~2;
                    D_001A7424 &= ~4;
                    D_001A7424 |= 0x20;
                    func_002F64A8();
                    break;
                }
                if (!(D_00138180.buttons & 0x10))
                    break;
                pickDialog->result = 1;
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
                { func_002B4B70(0, 0); break; }
            }
            if (D_001A8C8C)
                goto acceptReload;
            {
                if (D_001BAC80.inputDelay)
                    break;
                if (!(D_00138180.buttons & 0x40) || D_001F29A0) {
                    if (!(D_00138180.buttons & 0x10) || !D_001F29A0)
                        break;
                }
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
                D_001BAC80.result = 1;
                { func_002B4B70(0, 0); break; }
            }
        case 23:
        case 24:
            loadDialog = &D_001BAC80;
            if (loadDialog->inputDelay)
                break;
            if (D_00138180.buttons & 0x40) {
                func_PAL_002997A0();
                loadDialog->result = 2;
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
                D_001A7424 |= 0x20;
                func_002F64A8();
                break;
            }
            if (D_00138180.buttons & 0x10) {
                loadDialog->result = 1;
                D_001A7424 |= 0x20;
                { func_002B4B70(0, 0); break; }
            }
            break;
        case 4:
            if (D_001A8C88) {
                if (!D_001F29A0) {
                    saveDialog = &D_001BAC80;
                    if (saveDialog->inputDelay)
                        break;
                    saveInput = &D_00138180;
                    if (saveInput->buttons & 0x40) {
                        func_PAL_002997A0();
                        saveDialog->result = 2;
                        D_001A7424 &= ~2;
                        D_001A7424 &= ~4;
                        func_002F64A8();
                    }
                    if (!saveDialog->inputDelay && (saveInput->buttons & 0x10)) {
                        saveDialog->result = 1;
                        D_001A7424 |= 0x20;
                        D_001A7424 &= ~2;
                        D_001A7424 &= ~4;
                        func_002B4B70(0, 0);
                    }
                    break;
                }
            } else if (D_001A8C8C) {
acceptReload:
                if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
                    D_001BAC80.result = 2;
                    func_PAL_002DF760(-1);
                    func_002F64A8();
                }
                break;
            }
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x10)) {
                D_001BAC80.result = 1;
                D_001A7424 |= 0x20;
                D_001A7424 &= ~2;
                D_001A7424 &= ~4;
                func_002B4B70(0, 0);
            }
            break;
        case 9:
            if (!(D_001A7424 & 6))
                { func_002B4B70(0, 0); break; }
            break;
        }
        break;
    case 6:
        switch (D_001BAC80.phase) {
        case 0:
            qcopy(D_001BAC80.cameraPosition, D_001B5340.position);
            qcopy(D_001BAC80.cameraAngles, D_001B5340.angles);
            D_001BAC80.phase = 1;
            break;
        case 1:
            D_001B170C = 3;
            func_00282CF0(delta, D_001B5340.position, D_001B17D0);
            distance = func_00282DF0(delta);
            func_002AA548(&distance, &D_001BAC80.fraction, (float)D_001A8A78,
                    0.060000002f, 0.060000002f, 6.0000005f);
            func_00282F20(delta, delta, distance);
            func_00282CC0(D_001B5340.position, delta, D_001B17D0);
            func_PAL_002884F0((char *)&D_001BAC80.angle, 0);
            if ((float)D_001A8A78 <= distance)
                D_001BAC80.phase = 2;
            break;
        case 2:
            D_001B170C = 3;
            if (D_00138180.horizontal != 0.0f || D_00138180.vertical != 0.0f) {
                *(Quadword *)target = 0;
                target[1] = D_00138180.horizontal;
                target[2] = D_00138180.vertical;
                *(Quadword *)delta = *(Quadword *)target;
                func_00283098(delta, delta, D_001B5340.matrix);
                func_002AC9F8(delta, 1.0f);
                func_00282D30(delta, delta,
                        (float)-D_001A8A78 * 0.0003490659f * D_001A8A7C);
                func_00287D98((char *)delta);
            }
            func_PAL_002884F0((char *)&D_001BAC80.angle, 1);
            func_PAL_00288638(&D_00138180.roll);
            break;
        case 3: {
            float speed;
            D_001B170C = 3;
            speed = (float)D_001A8A78 * 0.0003490659f * D_001A8A7C;
            func_00282CF0(target, D_001BAC80.cameraPosition, D_001B17D0);
            func_00282F20(target, target, (float)D_001A8A78);
            func_00282CC0(target, target, D_001B17D0);
            func_00282CF0(delta, target, D_001B5340.position);
            func_00283698(transform, D_001B5340.matrix);
            func_00283098(delta, delta, transform);
            delta[0] = 0.0f;
            if (delta[1] == 0.0f && delta[2] == 0.0f)
                delta[1] = 1.0f;
            func_002AC9F8(delta, speed);
            func_00283098(delta, delta, D_001B5340.matrix);
            func_00287D98((char *)delta);
            func_PAL_002884F0((char *)&D_001BAC80.angle, 1);
            if (func_00282DF0(delta) < speed - 0.01f) {
                /* The transition publishes its separate state word before capturing the return pose. */
                { extern int D_001B1710; D_001B1710 = 2; }
                qcopy(D_001BAC80.returnPosition, D_001B5340.position);
                if (D_001A7A44) {
                    func_00282D30(D_001B5340.matrix + 4, D_001B5340.matrix + 4, -1.0f);
                    func_002AB6D8(D_001B5340.matrix, D_001BAC80.returnAngles);
                    func_00282D30(D_001B5340.matrix + 4, D_001B5340.matrix + 4, -1.0f);
                } else {
                    func_002AB6D8(D_001B5340.matrix, D_001BAC80.returnAngles);
                }
                D_001BAC80.phase = 4;
            }
            break;
        }
        case 4:
            D_001B170C = 3;
            func_002AA548(&D_001BAC80.fraction, &D_001BAC80.angle,
                    1.0f, 0.00080000004f, 0.00080000004f, 0.030000001f);
            func_00282D08(D_001B5340.position, D_001BAC80.returnPosition,
                    D_001BAC80.cameraPosition, D_001BAC80.fraction);
            func_002A91F0(delta, D_001BAC80.returnAngles);
            func_002A91F0(target, D_001BAC80.cameraAngles);
            func_00283810(transform, delta, target, D_001BAC80.fraction);
            func_00283958(transform, D_001B5340.matrix);
            if (D_001A7A44)
                func_00282D30(D_001B5340.matrix + 4, D_001B5340.matrix + 4, -1.0f);
            if (D_001BAC80.fraction >= 1.0f)
                func_002B4B70(0, 0);
            break;
        }
        D_001BAC80.cameraActive = 1;
        if ((D_00138180.buttons & 0x500) && D_001BAC80.phase == 2) {
            D_001BAC80.fraction = 0.0f;
            D_001BAC80.phase = 3;
            D_001BAC80.angle = 0.0f;
        }
        if ((unsigned)(D_001A79F0 - 22) < 2) {
            CameraObject *object = D_001B1B5C;
            if (object < D_001B1B60) {
                do {
                    if (object->kind == 0xD3D && object->update)
                        object->update(object);
                    ++object;
                } while (object < D_001B1B60);
            }
        }
        break;
    case 7:
        switch (D_001BAC80.phase) {
        case 0:
            D_001BAC80.cameraActive = 1;
            D_001BAC80.phase = 1;
            if (D_0018C0D4 != 1)
                func_PAL_0026F620();
            D_001A8A48 = 0;
            D_001A8A40 = ref_00286738_00;
            func_00290670();
            func_00287E60();
            break;
        case 1:
            if (D_0018C0D4 != 1) {
                func_PAL_0026F620();
                func_0028B3D0(0x23, 0, func_0028BDB0, func_0028BE00, func_0028C6D0, 0, 0);
            } else {
                func_0028B3D0(0x23, 0, func_0028CC98, func_0028CCE0, func_0028D1E8, 0, 0);
            }
            func_PAL_0029D7D0();
            func_PAL_0029C0B8(300);
            func_0029B698(150);
            func_00290670();
            {
                int remaining = D_001A8A40;
                if (remaining > 0) {
                    D_001A8A40 = remaining - 1;
                    remaining = D_001A8A40;
                }
                D_001A8A40 = remaining;
            }
            --D_001A8A60;
            if (D_001A8A60 < 0)
                D_001A8A60 = 0;
            if (!D_001A8A60)
                ++D_001BAC80.phase;
            break;
        case 2:
            if (D_0018C0D4 != 1) {
                func_PAL_0026F620();
                func_0028B3D0(0x23, 0, func_0028BDB0, func_0028BE00, func_0028C6D0, 0, 0);
            } else {
                func_0028B3D0(0x23, 0, func_0028CC98, func_0028CCE0, func_0028D1E8, 0, 0);
            }
            func_PAL_0029D7D0();
            func_PAL_0029C0B8(300);
            func_0029B698(150);
            func_00290670();
            {
                int remaining = D_001A8A40;
                if (remaining > 0) {
                    D_001A8A40 = remaining - 1;
                    remaining = D_001A8A40;
                }
                D_001A8A40 = remaining;
            }
            if (D_001A8A40 <= 0) {
                D_001A8A40 = 0;
                ++D_001BAC80.phase;
            }
            break;
        case 3:
            if (D_0018C0D4 != 1)
                func_PAL_0026F620();
            func_00290728();
            func_00290720();
            { func_002B4B70(0, 0); break; }
        }
        break;
    case 8:
        phaseDialog = &D_001BAC80;
        if (phaseDialog->phase != 2) {
            if (phaseDialog->phase >= 3)
                break;
            if (phaseDialog->phase < 0)
                break;
            ++phaseDialog->phase;
            break;
        }
        func_002B49E0(3, 2, phaseDialog->selection, 0, 0);
        func_PAL_002B5570(3);
        goto advanceModalPhase;
    case 9:
        phaseDialog = &D_001BAC80;
        switch (phaseDialog->phase) {
        case 1:
            if (D_00138180.pressed & phaseDialog->acceptMask) {
                phaseDialog->result = 2;
                func_002B4B70(0, 0);
            } else if (D_00138180.held & phaseDialog->cancelMask) {
                phaseDialog->result = 1;
                func_002B4B70(0, 0);
            }
            break;
        case 0:
            goto initializeDialog;
        }
        break;
    case 10:
        phaseDialog = &D_001BAC80;
        switch (phaseDialog->phase) {
        case 0:
initializeDialog:
            func_00287E80();
advanceModalPhase:
            ++phaseDialog->phase;
            break;
        case 1:
            if (D_00138180.pressed & phaseDialog->acceptMask) {
                phaseDialog->result = 2;
                func_002E5E58(0x12, 0, 0);
                func_002B4B70(0, 0);
            }
            break;
        default:
            break;
        }
        break;
    case 11:
        switch (D_001BAC80.phase) {
        case 0:
            func_00287E80();
            ++D_001BAC80.phase;
            if (D_001A7BB8) {
                D_001A7BB8 = !D_001A7BB8;
                func_002857B8();
                { func_002B4B70(0, 0); break; }
            }
            break;
        case 1:
            if (D_00138180.pressed & 0x40) {
                D_001BAC80.result = 2;
                ++D_001BAC80.phase;
            } else if (D_00138180.held & 0x10) {
                D_001BAC80.result = 1;
                { func_002B4B70(0, 0); break; }
            }
            break;
        case 2:
            D_001BAC80.elapsed = 750;
            D_001BAC80.inputDelay = 0;
            ++D_001BAC80.phase;
            D_001BAC80.result = 0;
            D_001A7BB8 = !D_001A7BB8;
            func_002857B8();
            break;
        case 3:
            if (D_00138180.pressed & 0x40)
                D_001BAC80.result = 2;
            else if (D_00138180.pressed & 0x10)
                D_001BAC80.result = 1;
            --D_001BAC80.elapsed;
            if (D_001BAC80.elapsed <= 0)
                goto advanceConfirmation;
            if (!D_001BAC80.result)
                break;
            goto advanceConfirmation;
        case 4:
            if (D_001BAC80.result < 0)
                goto advanceConfirmation;
            if (D_001BAC80.result < 2) {
                D_001A7BB8 = !D_001A7BB8;
                func_002857B8();
            }
advanceConfirmation:
            ++D_001BAC80.phase;
            break;
        case 5:
            func_002B4B70(0, 0);
            break;
        }
        break;
    }

}
