/* functional: low. Written from the assembly alone: the control flow and every call follow retail, but what the record fields mean is a guess. */
extern unsigned char D_00189E20[];
extern int D_001A79F0;
extern unsigned char D_0019B2E8[];
extern unsigned char D_001A7BC8[];
extern unsigned int D_00139768[];
extern int *D_L20_002AE830[];
extern char D_L20_001B1DD0[];
extern char D_L20_002B5770[];
extern char D_L20_001C01C0[];
extern int D_L20_001B2AC8;
extern int D_L20_001A8F00;
extern char *D_L20_001B308C;
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern int func_002B38B8(void *);
extern int func_002ACBC8(void *, int);
extern int func_00288AA0(void *, int);
extern void func_0026FEB8(const char *, ...);
extern void func_00288BE8(void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_00288CB0(int, int);
extern void func_0029B3E0(int, int);

/* One step of the object's state machine (state byte at +32, five states, record pointer at +104).
   Each state reads its record's bytes (+8 .. +15, a word at +0 and +4) and calls the step functions;
   states 3 and 4 share most of their body. */
void func_L20_00438F98(void *object)
{
    char *obj = object;
    unsigned char *s1;
    int state = (unsigned char)obj[32];
    int s2 = 0, flag;

    s1 = *(unsigned char **)(obj + 104);
    if (state >= 5) {
        return;
    }
    switch (state) {
    case 0: {
        int v1 = (signed char)s1[9];

        if (v1 != -1) {
            if (D_001A7BC8[v1] != 0) {
                func_0029F338(obj);
                return;
            }
        }
        v1 = (unsigned char)obj[176];
        if (v1 != 255) {
            if (D_0019B2E8[v1 + (D_001A79F0 << 4)] & 0x80) {
                func_0029F338(obj);
                return;
            }
        }
        func_002A7750(obj, 1, -1);
    }
    /* falls into state 1 */
    case 1:
        if (s1[10] == 0) {
            if (func_002B38B8(obj) == 0) {
                if ((unsigned char)obj[188] == 0) {
                    return;
                }
            }
        }
        s1[10] = 1;
        func_002A7750(obj, 2, -1);
    /* falls into state 2 */
    case 2: {
        unsigned char *hero = D_00189E20;
        int idx, row, t0, count, s5 = 1, s6 = 1;
        int *table;

        if (s1[10] == 0) {
            func_002A7750(obj, 1, -1);
            return;
        }
        if (*(int *)(hero + 0x2294) == 28) {
            return;
        }
        if (*(int *)(hero + 0x24CC) <= 0) {
            return;
        }
        if (D_L20_001A8F00 != 0) {
            return;
        }
        if (*(int *)s1 != -1) {
            if (func_002ACBC8(hero + 128, *(int *)s1) == 0) {
                return;
            }
        }
        idx = D_001A79F0;
        row = (unsigned char)s1[8];
        table = D_L20_002AE830[idx];
        if (table != 0 && table[row] != 0 && *(short *)table[row] != -1) {
            s5 = 0;
            count = 0;
            t0 = row;
            for (;;) {
                short *list = (short *)D_L20_002AE830[idx][t0];
                int entry = list[count];
                int skip = 0;

                if (s1[13] == 0) {
                    if (*(unsigned int *)((unsigned char *)D_00139768 + ((entry >> 2) << 2)) & (1u << (entry & 0x1F))) {
                        skip = 1;
                    }
                }
                if (!skip) {
                    int found = func_00288AA0(D_L20_001C01C0, entry);

                    idx = D_001A79F0;
                    if (found == 0 && count == 0) {
                        func_0026FEB8(D_L20_002B5770, *(short *)(obj + 170), *(short *)(obj + 178), D_001A79F0, (int)s1[8], entry);
                        return;
                    }
                    s6 = 0;
                    t0 = s1[8];
                }
                count++;
                list = (short *)D_L20_002AE830[idx][t0];
                if (list[count] == -1) {
                    break;
                }
            }
        }
        if (s5 != 0) {
            func_0026FEB8(D_L20_001B1DD0, D_001A79F0, (int)s1[8]);
        }
        if (s6 != 0) {
            s1[15] = 0;
            func_002A7750(obj, 4, -1);
        } else {
            s1[15] = 1;
            func_00288BE8(D_L20_001C01C0);
            if (D_L20_001B2AC8 < 5 || (D_001A79F0 == 6 && s1[8] == 0)) {
                func_002F5CC8();
            }
            func_002A7750(obj, 3, -1);
        }
        return;
    }
    case 3:
        if (func_002F5D10() == 0) {
            if (*(int *)(s1 + 4) != -1) {
                char *base = D_L20_001B308C + *(int *)(s1 + 4) * 128;

                func_L00_002B9D60(base + 48, base + 112, 0, 1);
            }
            func_002A7750(obj, 4, -1);
        }
        if (D_001A79F0 != 0) {
            return;
        }
        if ((signed char)s1[9] == -1) {
            return;
        }
        if (func_002F5D10() != 0) {
            return;
        }
        s2 = 0;
        if ((signed char)s1[9] != -1) {
            func_002AD7B8((signed char)s1[9]);
            s2 = 1;
            if ((signed char)s1[9] != 24) {
                func_002AF0A8((signed char)s1[9]);
            }
        }
        flag = (unsigned char)obj[176];
        if (flag != 255) {
            if ((D_0019B2E8[flag + (D_001A79F0 << 4)] & 0x80) == 0) {
                func_002A0430(flag);
                s2 = 1;
            }
        }
        if ((signed char)s1[11] != 0) {
            if ((*(int *)(s1 + 12) & 0xFFFF0000) != 0) {
                if (*(int *)(s1 + 4) != -1) {
                    char *base = D_L20_001B308C + *(int *)(s1 + 4) * 128;

                    func_002DF3F8(base + 48, base + 112);
                } else {
                    func_002DF3F8(obj + 16, obj + 240);
                }
            }
        }
        if ((signed char)s1[12] != -1) {
            func_00288CB0((signed char)s1[12], 1);
            return;
        }
        if (s2 == 0 && s1[15] == 0) {
            return;
        }
        func_0029B3E0(0, -1);
        return;
    case 4:
        s2 = 0;
        if ((signed char)s1[9] != -1) {
            func_002AD7B8((signed char)s1[9]);
            s2 = 1;
            if ((signed char)s1[9] != 24) {
                func_002AF0A8((signed char)s1[9]);
            }
        }
        flag = (unsigned char)obj[176];
        if (flag != 255) {
            if ((D_0019B2E8[flag + (D_001A79F0 << 4)] & 0x80) == 0) {
                func_002A0430(flag);
                s2 = 1;
            }
        }
        if ((signed char)s1[11] > 0) {
            if ((*(int *)(s1 + 12) & 0xFFFF0000) != 0) {
                if (*(int *)(s1 + 4) != -1) {
                    char *base = D_L20_001B308C + *(int *)(s1 + 4) * 128;

                    func_002DF3F8(base + 48, base + 112);
                } else {
                    func_002DF3F8(D_00189E20 + 128, D_00189E20 + 144);
                }
            }
        }
        if ((signed char)s1[12] != -1) {
            func_00288CB0((signed char)s1[12], 1);
        } else if (s2 != 0 || s1[15] != 0) {
            if ((signed char)s1[11] != -1) {
                func_0029B3E0(0, -1);
            }
        }
        func_0029F338(obj);
        return;
    }
}
