#include "include_asm.h"

#include "common.h"
extern int func_002E5CF8(int, int, char *);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_00283CF0(float);
extern float func_00283248(float, float);
extern float func_002A7940(void);
extern void func_L06_0041EF08(char *);
extern void func_L06_0041FAF8(char *);
extern int func_002A7820(int, int);
extern int func_002B1C20(char *, char *);
extern void func_US2_002A7AA8(char *, int, int);
extern void func_L01_003E9CF8(char *, int, int);
extern float func_00283C80(float, float);
extern int *D_L06_001FE500[];
extern int func_00282978(char *);
extern void func_L06_00458138(char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int func_L06_0041FC58(char *, char *);
extern int func_L06_0041F2A0(char *, char *, float, float, float, float);
extern float func_0029F530(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A89A8(char *, int, float);
extern int func_00277258(char *, int, char *, float);
extern char *D_L06_001BFC98;
extern float func_00282E80(char *, char *);
extern float func_002A78D8(float, float);
extern int func_US2_002AF9C8(char *, float);
extern void func_0029FCC0(char *, int, void *);
extern void *D_L06_001B3760[6];
extern void func_L06_0041F818(float *, int);
extern void func_L06_00458E10(char *, float *, float *, int, float);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00282E48(void *, void *);
extern void func_002A8C28(char *, void *, int, int, int, int, float, float, float);
extern void func_L06_0041F558(char *);

/* Updates the actor's alert mode, movement and attack animation states. */
void func_US2_L06_0041F460(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    int *sequence;
    int hit;
    float pos[4], target[4], direction[4];
    float frame, saved_w, ground;
    int i;

    func_L06_0041EF08(obj);
    sequence = D_L06_001FE500[*(int *)(st + 0x23C)];
    switch (*(unsigned char *)(obj + 0x95)) {
    case 0:
        if (*(int *)(st + 0x228) == 1) {
            if (*(int *)(st + 0x5C8)) {
                *(int *)(st + 0x5C8) = 0;
                func_002E5CF8(11, 0, obj);
            }
            func_L06_0041FAF8(obj);
            if (*(int *)(st + 0x5C0)) {
                *(int *)(st + 0x238) = *(int *)(st + 0x234);
                *(int *)(st + 0x220) = *(int *)(st + 0x224);
            }
        } else if (*(int *)(st + 0x258)) {
            func_L06_0041FAF8(obj);
        }
        break;
    case 1:
        if (*(int *)(st + 0x228) == 1 || *(int *)(st + 0x22C) == 1)
            func_L06_0041FAF8(obj);
        else if (*(short *)(st + 0x24A) == 0)
            obj[0x95] = 0;
        *(int *)(st + 0x258) = 0;
        break;
    case 2:
        if (*(int *)(st + 0x228) != 1 && *(int *)(st + 0x22C) != 1 && (obj[0x60] & 2)) {
            if (*(int *)(st + 0x23C) != -1)
                *(int *)(st + 0x478) = sequence[0] - 1;
            *(float *)(st + 0x494) = 2.0f;
            func_002A7750(obj, 14, 4);
            *(short *)(st + 0x24A) = func_002A7820(580, 600);
        }
        break;
    case 3:
        hit = func_002B1C20(obj, st + 0x60);
        if (hit & 1) {
            func_US2_002A7AA8(obj, 0, 3);
            func_L01_003E9CF8(obj, 0, 0);
            return;
        }
        if (hit & 2) {
            if (*(int *)(st + 0x228) == 1 || *(int *)(st + 0x22C) == 1) {
                if (func_00283C80(*(float *)(obj + 0xF8),
                        func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                    func_002A7750(obj, 11, 2);
                    if (*(unsigned char *)(obj + 0x43) != 9)
                        func_002A7470(obj, 9, 0, 2);
                    st[0x48] = func_00283CF0(20.0f);
                    st[0x4A] = func_00283CF0(8.0f);
                } else {
                    func_002A7750(obj, 9, 2);
                    if (*(unsigned char *)(obj + 0x43) != 18)
                        func_002A7470(obj, 18, 0, 10);
                    st[0x48] = func_00283CF0(20.0f);
                    st[0x4A] = func_00283CF0(24.0f);
                }
            } else {
                *(short *)(st + 0x24A) = func_002A7820(580, 600);
                func_002A7750(obj, 5, 1);
                if (*(unsigned char *)(obj + 0x43) != 18)
                    func_002A7470(obj, 18, 0, 20);
                st[0x48] = func_00283CF0(20.0f);
                st[0x4A] = func_00283CF0(24.0f);
            }
        }
        break;
    case 4:
        if (*(float *)(st + 0x494) <= 0.0f) {
            *(float *)(st + 0x5A4) = func_002A7940();
            qcopy(st + 0x5B0, st + 0x460);
            *(short *)(st + 0x24C) = 270;
            func_002A7750(obj, 4, -1);
            if (*(unsigned char *)(obj + 0x43) != 6)
                func_002A7470(obj, 6, 0, 10);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(24.0f);
            func_002A7750(obj, 5, 1);
        }
        break;
    }
    switch (*(unsigned char *)(obj + 0x20)) {
    case 1:
        if (func_00282978(st + 0x24C) && *(short *)(st + 0x492) == 0) {
            if (*(unsigned char *)(obj + 0x43) != 2)
                func_002A7470(obj, 2, 0, 20);
            *(short *)(st + 0x24C) = func_002A7820(900, 1200);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(24.0f);
        } else if ((obj[0x60] & 2) && *(short *)(st + 0x492) == 0) {
            if (*(unsigned char *)(obj + 0x43) != 1)
                func_002A7470(obj, 1, 0, 5);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(8.0f);
        }
        break;
    case 2:
    case 3:
        break;
    case 5:
        if (obj[0x60] & 2) {
            *(float *)(st + 0x5A4) = func_002A7940();
            func_L06_0041FC58(obj, st);
            *(short *)(st + 0x24C) = 270;
            func_002A7750(obj, 4, -1);
            if (*(unsigned char *)(obj + 0x43) != 6)
                func_002A7470(obj, 6, 0, 10);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(24.0f);
        }
        break;
    case 4:
        if (func_L06_0041F2A0(obj, st + 0x5B0, *(float *)(st + 0x5A4), 4.0f,
                              0.25f, *(float *)(st + 0x47C)) ||
            func_00282978(st + 0x24C)) {
            func_002A7750(obj, 5, -1);
            if (*(unsigned char *)(obj + 0x43) != 7)
                func_002A7470(obj, 7, 0, 10);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(8.0f);
        }
        break;
    case 7:
        if (obj[0x60] & 2) {
            obj[0x20] = 9;
            if (*(unsigned char *)(obj + 0x43) != 18)
                func_002A7470(obj, 18, 0, 20);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(24.0f);
            *(int *)(st + 0x5A0) = 0;
        } else if (*(int *)(st + 0x5C4)) {
            frame = func_0029F530(obj);
            if ((unsigned char)obj[0x42] == (unsigned char)obj[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                saved_w = *(float *)(obj + 0x1C);
                pos[0] = func_00283180(*(float *)(obj + 0xF8)) * 0.16f;
                pos[1] = func_00283198(*(float *)(obj + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                func_00282CC0(obj + 0x10, (char *)pos, obj + 0x10);
                ground = func_002A89A8(obj + 0x10, 0, 0.5f);
                *(float *)(obj + 0x18) -= 0.1666666716337204f;
                if (*(float *)(obj + 0x18) < ground)
                    *(float *)(obj + 0x18) = ground;
                *(float *)(obj + 0x1C) = saved_w;
            }
            qcopy(pos, obj + 0x10);
            pos[2] += 0.6f;
            target[0] = func_00283180(*(float *)(obj + 0xF8));
            target[1] = func_00283198(*(float *)(obj + 0xF8));
            target[2] = 0.0f;
            func_00282CC0((char *)pos, (char *)target, (char *)pos);
        } else {
            frame = func_0029F530(obj);
            if ((unsigned char)obj[0x42] == (unsigned char)obj[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                saved_w = *(float *)(obj + 0x1C);
                pos[0] = func_00283180(*(float *)(obj + 0xF8)) * 0.16f;
                pos[1] = func_00283198(*(float *)(obj + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                func_00282CC0(obj + 0x10, (char *)pos, obj + 0x10);
                *(float *)(obj + 0x1C) = saved_w;
            }
            qcopy(pos, obj + 0x10);
            pos[2] += 0.6f;
            target[0] = func_00283180(*(float *)(obj + 0xF8));
            target[1] = func_00283198(*(float *)(obj + 0xF8));
            target[2] = 0.0f;
            func_00282CC0((char *)pos, (char *)target, (char *)pos);
            if (func_00277258((char *)pos, 0, obj, 0.5f)) {
                char *hit_obj = D_L06_001BFC98;
                if (hit_obj && *(short *)(hit_obj + 0xAA) == 0xFDC)
                    func_L06_00458138(hit_obj);
            }
        }
        break;
    case 6:
        if (obj[0x60] & 2) {
            func_002A7750(obj, 9, 2);
            if (*(unsigned char *)(obj + 0x43) != 18)
                func_002A7470(obj, 18, 0, 20);
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(24.0f);
        }
        break;
    case 8:
        if (*(int *)(st + 0x23C) != -1) {
            char *waypoint = (char *)(sequence + 4) + *(int *)(st + 0x478) * 16;
            func_L06_0041F2A0(obj, waypoint,
                func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                            *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
                8.0f, 0.25f, 0.0f);
            if (func_00282E80(obj + 0x10, (char *)(sequence + 4) + *(int *)(st + 0x478) * 16) < 1.5f)
                ++*(int *)(st + 0x478);
            {
                int count = sequence[0];
                if (*(int *)(st + 0x478) >= count) {
                    *(int *)(st + 0x5A0) = 0;
                    *(int *)(st + 0x478) = count - 1;
                    if (func_00283C80(*(float *)(obj + 0xF8),
                        func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                        qcopy(st + 0x460, obj + 0x10);
                        func_002A7750(obj, 10, -1);
                        if (*(unsigned char *)(obj + 0x43) != 21)
                            func_002A7470(obj, 21, 0, 16);
                        st[0x48] = func_00283CF0(20.0f);
                        st[0x4A] = func_00283CF0(8.0f);
                    }
                }
            }
        } else {
            func_002A7750(obj, 9, -1);
        }
        break;
    case 9:
        if (*(unsigned short *)(obj + 0x96) < 2)
            *(float *)(st + 0x47C) = func_002A78D8(10.0f, 25.0f) * 0.01745329424738884f;
        if (func_L06_0041F2A0(obj, st + 0x200,
            func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                        *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
            8.0f, 16.0f, *(float *)(st + 0x47C))) {
            if (func_00283C80(*(float *)(obj + 0xF8),
                func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                            *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                func_002A7750(obj, 10, -1);
                if (*(unsigned char *)(obj + 0x43) != 21)
                    func_002A7470(obj, 21, 0, 16);
                st[0x48] = func_00283CF0(20.0f);
                st[0x4A] = func_00283CF0(8.0f);
            }
        }
        break;
    case 10:
        func_L06_0041F2A0(obj, obj + 0x10,
            func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                        *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
            6.0f, 6.0f, 0.0f);
        if (obj[0x60] & 2) {
            if (func_00282E80(obj + 0x10, st + 0x200) < 3.0f) {
                func_002A7750(obj, 12, -1);
                if (*(unsigned char *)(obj + 0x43) != 13)
                    func_002A7470(obj, 13, 10, 20);
                st[0x48] = func_00283CF0(20.0f);
                st[0x4A] = func_00283CF0(24.0f);
            } else {
                func_002A7750(obj, 11, -1);
                if (*(unsigned char *)(obj + 0x43) != 9)
                    func_002A7470(obj, 9, 0, 2);
                st[0x48] = func_00283CF0(20.0f);
                st[0x4A] = func_00283CF0(8.0f);
            }
        }
        break;
    case 11:
        if (obj[0x60] & 2) {
            func_002A7750(obj, 13, -1);
            if (*(unsigned char *)(obj + 0x43) != 10)
                func_002A7470(obj, 10, 0, func_002A7820(10, 30));
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(8.0f);
        } else if (func_US2_002AF9C8(obj, 2.0f)) {
            func_0029FCC0(obj, 0, pos);
            qcopy(target, st + 0x200);
            func_00282CF0((char *)direction, (char *)target, (char *)pos);
            func_00282F20((char *)direction, (char *)direction, 0.1666666716337204f);
            *(int *)(st + 0x498) = -1;
            for (i = 0; i < 6; i++) {
                if (!D_L06_001B3760[i]) {
                    *(int *)(st + 0x498) = i;
                    break;
                }
            }
            if (*(int *)(st + 0x498) != -1) {
                func_L06_0041F818(pos, 10);
                func_L06_00458E10(obj, direction, pos, *(int *)(st + 0x498),
                                  (float)*(unsigned char *)(st + 0x35));
                *(int *)(st + 0x498) = -1;
            }
            st[0xD7] = 0;
        }
        break;
    case 12:
        frame = func_0029F530(obj);
        if ((unsigned char)obj[0x42] == (unsigned char)obj[0x43] && frame >= 17.0f && frame <= 25.0f) {
            st[0xD7] = 0;
            func_0029FCC0(obj, 0, pos);
            qcopy(target, obj + 0x10);
            target[2] += 2.0f;
            func_00282D08(direction, pos, target, 0.5f);
            direction[3] = func_00282E48(direction, target) * 0.75f;
            func_002A8C28(obj, direction, 1, 0, 1, 0, direction[3], *(float *)(st + 0x5AC), 1.0f);
        } else if (obj[0x60] & 2) {
            func_002A7750(obj, 13, -1);
            if (*(unsigned char *)(obj + 0x43) != 11)
                func_002A7470(obj, 11, 0, func_002A7820(10, 30));
            st[0x48] = func_00283CF0(20.0f);
            st[0x4A] = func_00283CF0(24.0f);
        }
        break;
    case 13:
        if (obj[0x60] & 2) {
            if ((unsigned char)obj[0x95] == 4) {
                *(float *)(st + 0x494) -= 1.0f;
                func_002A7750(obj, 14, -1);
            } else {
                func_002A7750(obj, 9, -1);
                if (*(unsigned char *)(obj + 0x43) != 18)
                    func_002A7470(obj, 18, 0, 10);
                st[0x48] = func_00283CF0(20.0f);
                st[0x4A] = func_00283CF0(24.0f);
            }
            if (func_00282E80(obj + 0x10, st + 0x200) < 16.0f) {
                if (func_00283C80(*(float *)(obj + 0xF8),
                    func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                    func_002A7750(obj, 10, -1);
                    if (*(unsigned char *)(obj + 0x43) != 21)
                        func_002A7470(obj, 21, 0, 16);
                    st[0x48] = func_00283CF0(20.0f);
                    st[0x4A] = func_00283CF0(8.0f);
                }
            }
        }
        break;
    case 14:
        func_002A7750(obj, 10, -1);
        if (*(unsigned char *)(obj + 0x43) != 21)
            func_002A7470(obj, 21, 0, 16);
        st[0x48] = func_00283CF0(20.0f);
        st[0x4A] = func_00283CF0(8.0f);
        break;
    }
    func_L06_0041F558(obj);
}
