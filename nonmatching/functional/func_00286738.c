/* functional: medium. The near-miss reconstruction compiles to 4944 bytes against retail's 5280 but does the same reads, writes and calls in the same order (fcheck SAME on 6 of 6 captured calls); byte layout only differs. */
/* Nonmatching modal-state reconstruction, 2026-10-23.
 * Game profile: -O2 -G8 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier -frac2-zero-ti-por, dedicated 00286738-g8.c trial.
 * US: 4944 versus retail 5280 bytes; 0/28 placements. Frame 0xB0 matches,
 * but the first difference is +0x4 (saved-register allocation). US2 and PAL
 * have no catalogue entry for this canonical function.
 * Ten bounded compiles examined separate modal paths, case ordering, copy/zero
 * profiles, camera object grouping, scoped modal views, signed flag types and
 * verified callback declarations. Earlier drafts were 4804..5012 bytes; equal
 * case-order/debug-policy outputs did not resolve the dispatch layout.
 * Remaining work: register lifetimes, switch block order and branch merges;
 * generated switch-table dependencies would also need real linked qualification.
 * Reopen with a measured large-switch layout remedy or recovered owner layouts.
 * Helper retail analysis establishes float return for func_002AA548 and integer
 * return for func_0028B3D0/func_002E4AC8. Update/draw callback parameters remain
 * unspecified here: this caller only passes their addresses to the registrar.
 */

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
extern int D_001F29A0;
extern int D_001F2940;
extern int D_001F2858;
extern int *D_001F2930;
extern unsigned short D_0018C9DC;
extern int D_001B1F10;
extern int D_001393E8;
extern int D_001393F0;
extern int D_0013955C[];
extern int D_001A8B84;
extern int D_001B1680;
extern int D_001A8A78 __attribute__((sda));
extern float D_001A8A7C __attribute__((sda));
typedef struct {
    float position[4];
    float angles[4];
    char reserved20[0x210];
    float matrix[16];
} ModalCamera;
extern ModalCamera D_001B5340;
extern float D_001B17D0[4];
extern unsigned char D_001A7A44;
extern int D_001A79F0;
extern CameraObject *D_001B1B5C;
extern CameraObject *D_001B1B60;
extern unsigned char D_0018C0D4;
extern int D_001A8A40;
extern int D_001A8A44;
extern int D_001A8A48;
extern int D_001A8A60;
extern int D_001A7BB8;

extern int func_002E4AC8(void);
extern int func_002B49E0(int, int, int, int, unsigned char *);
extern void func_0027D330(int);
extern int func_00288D80(void);
extern void func_00288D68(void);
extern void func_00287E80(void);
extern int func_002DF1D0(void);
extern int func_002C9A50(void);
extern void func_00298D28(int *);
extern void func_00287EA8(void);
extern int func_002B4B70(int, int);
extern void func_00298E08(void);
extern void func_002F64A8(void);
extern void func_002DE990(int);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00282DF0(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00287BD8(char *, int);
extern void func_00283098(void *, const void *, const void *);
extern void func_002AC9F8(float *, float);
extern void func_00282D30(void *, const void *, float);
extern void func_00287D98(char *);
extern void func_00287D20(float *);
extern void func_00283698(void *, const void *);
extern void func_002AB6D8(float *, float *);
extern void func_00282D08(void *, const void *, const void *, float);
extern void func_002A91F0(void *, float *);
extern void func_00283810(void *, const void *, const void *, float);
extern void func_00283958(const void *, void *);
extern void func_0026F7B0(void);
extern void func_00290670(void);
extern void func_00287E60(void);
extern int func_0028B3D0(int, int, void (*)(unsigned char *), void (*)(), void (*)(), int, int);
extern void func_0028BDB0(unsigned char *);
extern void func_0028BE00();
extern void func_0028C6D0();
extern void func_0028CC98(unsigned char *);
extern void func_0028CCE0();
extern void func_0028D1E8();
extern void func_0029CE38(void);
extern void func_0029B720(int);
extern void func_0029B698(int);
extern void func_00290728(void);
extern void func_00290720(void);
extern void func_002B49C0(int);
extern int func_002E5E58(int, int, void *);
extern void func_002857B8(void);

/* Run the active modal dialog, camera return, or display-confirmation phase. */
void func_00286738(void)
{
    float delta[4], target[4], transform[16];
    float distance;

    func_002E4AC8();
    D_001B170C = D_001BAC80.gameState;
    if (D_001BAC80.countdown)
        --D_001BAC80.countdown;
    if (D_001BAC80.timer)
        --D_001BAC80.timer;
    switch (D_001BAC80.mode) {
    case 2:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 90 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (D_001A7420 == 2) {
            func_002B49E0(4, 2, 1, 0, 0);
            return;
        }
        if (D_001BAC80.elapsed >= 121 && (D_00138180.buttons & 0x40)) {
            if (!D_0018C9DC)
                D_0018C9DC = 1;
            goto closeModal;
        }
        break;
    case 5:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 30 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
            D_001A7424 &= ~0x40;
            D_0013955C[0] = 0;
            goto reload;
        }
        break;
    case 4:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 30 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
            D_0013955C[0] = 0;
            goto reload;
        }
        break;
    case 3:
        if (D_001BAC80.phase == 1) {
            if (D_00138180.buttons & 0x10)
                goto closeModal;
            if (D_00138180.buttons & 0x40) {
                func_0027D330(4);
                D_001B1F10 = 0;
                D_001BAC80.phase = 2;
                D_001BAC80.elapsed = 600;
            }
            return;
        } else if (D_001BAC80.phase < 2) {
            if (D_001BAC80.phase == 0) {
                if (!D_001BAC80.countdown)
                    D_001BAC80.phase = 1;
                return;
            }
        } else if (D_001BAC80.phase == 2) {
            if (!D_001BAC80.elapsed || --D_001BAC80.elapsed == 0) {
                D_001B1F10 = 1;
                D_001BAC80.phase = 3;
                return;
            }
            if (D_00138180.buttons & 0x10) {
                func_0027D330(4);
                D_001B1F10 = 1;
            } else {
                if (!(D_00138180.buttons & 0x40))
                    return;
                D_001B1F10 = 0;
            }
        } else if (D_001BAC80.phase == 3 && !(D_00138180.buttons & 0x40)) {
            return;
        }
        goto closeModal;
    case 1:
        ++D_001BAC80.elapsed;
        if (D_001BAC80.elapsed > 30 && D_001BAC80.inputDelay)
            --D_001BAC80.inputDelay;
        if (func_00288D80()) {
            if (!(D_00138180.buttons & 0x40))
                return;
            func_00288D68();
            func_00287E80();
            goto closeModal;
        }
        switch (D_001A7420) {
        case 1:
        case 16:
            func_002B4B70(0, 0);
            D_001F2940 = D_001BAC80.selection;
            D_001F2858 = D_001BAC80.selection;
            break;
        case 2:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x40)) {
                D_001BAC80.result = 2;
                D_001A7424 &= ~1;
                goto closeModal;
            }
            return;
        case 3:
        case 5:
            goto cancelSelection;
        case 4:
            if (!D_001A8C88) {
                if (D_001A8C8C)
                    goto acceptReload;
            } else if (!D_001F29A0) {
                if (D_001BAC80.inputDelay)
                    return;
                if (D_00138180.buttons & 0x40) {
                    func_00298E08();
                    D_001BAC80.result = 2;
                    D_001A7424 &= ~6;
                    func_002F64A8();
                }
            }
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x10)) {
                D_001BAC80.result = 1;
                D_001A7424 = (D_001A7424 & ~6) | 0x20;
                goto closeModal;
            }
            return;
        case 6:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x20)) {
                D_001A7424 |= 8;
                D_001BAC80.result = 2;
                return;
            }
            if (D_001BAC80.countdown || !(D_00138180.buttons & 0x10))
                return;
            if (D_001A8C8C) {
                D_001BAC80.result = 2;
                goto reload;
            }
            D_001A7424 |= 0x20;
            if (!func_002DF1D0())
                D_001A7424 &= ~2;
            D_001A7424 &= ~4;
            goto finishSelection;
        case 9:
            if (!(D_001A7424 & 6))
                goto closeModal;
            return;
        case 12:
            if (D_001F29A0)
                goto cancelSelection;
            return;
        case 13:
            if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x20)) {
                D_001A7424 |= 0x10;
                D_001BAC80.result = 2;
                return;
            }
            if (D_001BAC80.countdown || !(D_00138180.buttons & 0x10))
                return;
            if (D_001A8C8C) {
                D_001BAC80.result = 2;
                goto reload;
            }
            D_001A7424 = (D_001A7424 & ~6) | 0x20;
finishSelection:
            D_001BAC80.result = 1;
            if (!D_001A8C88)
                goto closeModal;
            break;
        case 17:
        case 18:
        case 21:
            if (D_001BAC80.pending > 0) {
                if (--D_001BAC80.pending <= 0) {
                    if (D_001393E8 != 2) {
                        D_001BAC80.result = 2;
                        func_00287EA8();
                        goto reload;
                    }
                    D_001A7420 = 9;
                    if (D_001393F0) {
                        if (D_001393F0 == -1) {
                            D_001A7420 = 9;
                            D_001393F0 = 0;
                        } else {
                            D_001A7420 = 12;
                            if (D_001393F0 == -2)
                                D_001A7420 = 5;
                        }
                    }
                    goto closeModal;
                }
            } else {
                if (D_001BAC80.inputDelay || !(D_00138180.buttons & 0x40))
                    return;
                func_00287EA8();
                if (!D_001A8C8C) {
                    D_001BAC80.result = 2;
                    D_001A7424 &= ~0x446;
                    goto closeModal;
                }
                D_001BAC80.pending = 15;
            }
            break;
        case 19:
            if (D_001A8C88 && !D_001F29A0) {
                if (D_001BAC80.inputDelay)
                    return;
                if (D_00138180.buttons & 0x40)
                    goto acceptLoad;
                if (!(D_00138180.buttons & 0x10))
                    return;
                D_001BAC80.result = 1;
                D_001A7424 &= ~6;
                goto closeModal;
            }
            if (!D_001A8C8C) {
                if (D_001BAC80.inputDelay)
                    return;
                if (!(D_00138180.buttons & 0x40) || D_001F29A0) {
                    if (!(D_00138180.buttons & 0x10) || !D_001F29A0)
                        return;
                }
                D_001A7424 &= ~6;
                D_001BAC80.result = 1;
                goto closeModal;
            }
acceptReload:
            if (D_001BAC80.inputDelay || !(D_00138180.buttons & 0x40))
                return;
            D_001BAC80.result = 2;
            goto reload;
        case 20:
            if (D_001BAC80.inputDelay || !(D_00138180.buttons & 0x40))
                return;
            D_001A7424 &= ~0x446;
            D_001BAC80.result = 2;
            if (!D_001A8C88) {
                if (!func_002C9A50()) {
                    D_0013955C[0] = 0;
                    D_001A8B84 = 1;
                    D_001B1680 = -1;
                    return;
                }
                func_00298D28(D_001F2930);
            }
            goto closeModal;
        case 23:
        case 24:
            if (D_001BAC80.inputDelay)
                return;
            if (D_00138180.buttons & 0x40) {
acceptLoad:
                func_00298E08();
                D_001BAC80.result = 2;
                D_001A7424 = (D_001A7424 & ~6) | 0x20;
                func_002F64A8();
                return;
            }
            if (D_00138180.buttons & 0x10) {
                D_001BAC80.result = 1;
                D_001A7424 |= 0x20;
                goto closeModal;
            }
            break;
        }
        break;
    case 6:
        switch (D_001BAC80.phase) {
        case 0:
            *(Quadword *)D_001BAC80.cameraPosition = *(Quadword *)D_001B5340.position;
            *(Quadword *)D_001BAC80.cameraAngles = *(Quadword *)D_001B5340.angles;
            D_001BAC80.phase = 1;
            break;
        case 1:
            D_001B170C = 3;
            func_00282CF0(delta, D_001B5340.position, D_001B17D0);
            distance = func_00282DF0(delta);
            func_002AA548(&distance, &D_001BAC80.fraction, (float)D_001A8A78,
                    0.041666668f, 0.041666668f, 5.0000005f);
            func_00282F20(delta, delta, distance);
            func_00282CC0(D_001B5340.position, delta, D_001B17D0);
            func_00287BD8((char *)&D_001BAC80.angle, 0);
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
                        (float)-D_001A8A78 * 0.00029088825f * D_001A8A7C);
                func_00287D98((char *)delta);
            }
            func_00287BD8((char *)&D_001BAC80.angle, 1);
            func_00287D20(&D_00138180.roll);
            break;
        case 3: {
            float speed;
            D_001B170C = 3;
            speed = (float)D_001A8A78 * 0.00029088825f * D_001A8A7C;
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
            func_00287BD8((char *)&D_001BAC80.angle, 1);
            if (func_00282DF0(delta) < speed - 0.01f) {
                /* The transition publishes its separate state word before capturing the return pose. */
                { extern int D_001B1710; D_001B1710 = 2; }
                *(Quadword *)D_001BAC80.returnPosition = *(Quadword *)D_001B5340.position;
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
                    1.0f, 0.00055555557f, 0.00055555557f, 0.025000002f);
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
            D_001BAC80.angle = 0.0f;
            D_001BAC80.phase = 3;
            D_001BAC80.fraction = 0.0f;
        }
        if ((unsigned)(D_001A79F0 - 22) < 2 && D_001B1B5C < D_001B1B60) {
            CameraObject *object = D_001B1B5C;
            do {
                if (object->kind == 0xD3D && object->update)
                    object->update(object);
                ++object;
            } while (object < D_001B1B60);
        }
        break;
    case 7:
        if (D_001BAC80.phase == 1) {
            if (D_0018C0D4 == 1) {
                func_0028B3D0(0x23, 0, func_0028CC98, func_0028CCE0, func_0028D1E8, 0, 0);
            } else {
                func_0026F7B0();
                func_0028B3D0(0x23, 0, func_0028BDB0, func_0028BE00, func_0028C6D0, 0, 0);
            }
            func_0029CE38();
            func_0029B720(360);
            func_0029B698(180);
            func_00290670();
            if (D_001A8A40 > 0)
                --D_001A8A40;
            --D_001A8A60;
            if (D_001A8A60 < 0)
                D_001A8A60 = 0;
            if (D_001A8A60)
                return;
        } else {
            if (D_001BAC80.phase < 2) {
                if (D_001BAC80.phase == 0) {
                    D_001BAC80.phase = 1;
                    D_001BAC80.cameraActive = 1;
                    if (D_0018C0D4 != 1)
                        func_0026F7B0();
                    D_001A8A48 = 0;
                    D_001A8A40 = D_001A8A44;
                    func_00290670();
                    func_00287E60();
                }
                return;
            }
            if (D_001BAC80.phase != 2) {
                if (D_001BAC80.phase != 3)
                    return;
                if (D_0018C0D4 != 1)
                    func_0026F7B0();
                func_00290728();
                func_00290720();
                goto closeModal;
            }
            if (D_0018C0D4 == 1) {
                func_0028B3D0(0x23, 0, func_0028CC98, func_0028CCE0, func_0028D1E8, 0, 0);
            } else {
                func_0026F7B0();
                func_0028B3D0(0x23, 0, func_0028BDB0, func_0028BE00, func_0028C6D0, 0, 0);
            }
            func_0029CE38();
            func_0029B720(360);
            func_0029B698(180);
            func_00290670();
            if (D_001A8A40 > 0)
                --D_001A8A40;
            if (D_001A8A40 > 0)
                return;
            D_001A8A40 = 0;
        }
        ++D_001BAC80.phase;
        break;
    case 8:
        if (D_001BAC80.phase >= 0 && D_001BAC80.phase <= 1)
            ++D_001BAC80.phase;
        else if (D_001BAC80.phase == 2) {
            func_002B49E0(3, 2, D_001BAC80.selection, 0, 0);
            func_002B49C0(3);
            ++D_001BAC80.phase;
        }
        break;
    case 9:
        if (D_001BAC80.phase == 0) {
            func_00287E80();
            ++D_001BAC80.phase;
        } else if (D_001BAC80.phase == 1) {
            if (D_00138180.pressed & D_001BAC80.acceptMask) {
                D_001BAC80.result = 2;
            } else {
                if (!(D_00138180.held & D_001BAC80.cancelMask))
                    return;
                D_001BAC80.result = 1;
            }
            goto closeModal;
        }
        break;
    case 10:
        if (D_001BAC80.phase == 0) {
            func_00287E80();
            ++D_001BAC80.phase;
        } else if (D_001BAC80.phase == 1) {
            if (!(D_00138180.pressed & D_001BAC80.acceptMask))
                return;
            D_001BAC80.result = 2;
            func_002E5E58(0x12, 0, 0);
            goto closeModal;
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
                goto closeModal;
            }
            break;
        case 1:
            if (D_00138180.pressed & 0x40) {
                D_001BAC80.result = 2;
                ++D_001BAC80.phase;
            } else if (D_00138180.held & 0x10) {
                D_001BAC80.result = 1;
                goto closeModal;
            }
            break;
        case 2:
            D_001BAC80.elapsed = 900;
            ++D_001BAC80.phase;
            D_001BAC80.result = 0;
            D_001A7BB8 = !D_001A7BB8;
            D_001BAC80.inputDelay = 0;
            func_002857B8();
            return;
        case 3:
            if (D_00138180.pressed & 0x40)
                D_001BAC80.result = 2;
            else if (D_00138180.pressed & 0x10)
                D_001BAC80.result = 1;
            --D_001BAC80.elapsed;
            if (D_001BAC80.elapsed > 0 && !D_001BAC80.result)
                return;
            ++D_001BAC80.phase;
            break;
        case 4:
            if (D_001BAC80.result >= 0 && D_001BAC80.result < 2) {
                D_001A7BB8 = !D_001A7BB8;
                func_002857B8();
            }
            ++D_001BAC80.phase;
            break;
        case 5:
            func_002B4B70(0, 0);
            break;
        }
        break;
    }
    return;

cancelSelection:
    if (!D_001BAC80.inputDelay && (D_00138180.buttons & 0x10)) {
        D_001BAC80.result = 1;
        D_001A7424 &= ~6;
        goto closeModal;
    }
    return;
reload:
    func_002DE990(-1);
    func_002F64A8();
    return;
closeModal:
    func_002B4B70(0, 0);
}
