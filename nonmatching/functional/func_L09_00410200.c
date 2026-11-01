/* functional: medium. Written from the assembly (the jump table for states 0 to 6 read from the program's bytes); plain floats, the three 4-float scratch vectors are one local array; the data words named by their addresses are retail's tuning values and are not re-checked. */

extern float D_L09_001B17B0, D_L09_001B17B4, D_L09_001B17B8, D_L09_001B17BC;
extern float D_L09_001B17C0, D_L09_001B17C4, D_L09_001B17C8, D_L09_001B17CC;
extern float D_L09_001B17D0, D_L09_001B17D4, D_L09_001B17E8;
extern int D_L09_001B17A8, D_L09_001B17AC, D_L09_001B17D8, D_L09_001B17DC;
extern int D_L09_001B17E0, D_L09_001B17E4;
extern int D_001A79F0;                      /* the level number */
extern char D_00188660[];                   /* records of 112 bytes */
extern char D_00189E20[];
extern int D_00138324;
extern int D_L09_001A8FB4;
extern char D_001395B8[];
extern char D_L09_001BFC00[];
extern int D_L09_001B25A8;

extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CD8(void *, void *, void *);
extern int func_002A7820(int, int);
extern int func_00283D38(int, int, float);
extern int func_001163B0(void);
extern void func_002C2210(void *, unsigned int, unsigned int, unsigned int, int, float *, float, float, float, int);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002B0C28(int, int, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_00288CB0(int, int);

/* Per-frame update of a moby (`m`, its variables at +104). Every frame it first spawns one
   effect (func_002C2210) with a random offset and random values from the tuning words, then
   steps by state byte +32: 0 starts animation 1 and clears the handle at vars+8; 1 keeps that
   handle alive (func_002E5CF8) and, when the player at D_00189E20 is on it, starts one of the
   level's messages and (with the right button bit and mode 4) animation 2 or 4; 2 waits for
   func_00288AA0 and starts animation 3; 3 and 4 wait for func_002F5D10 and then show the object
   (byte 49) and set the level's two flag bytes. The frame counter at +150 stops at 0xFFFF. */
void func_L09_00410200(char *m)
{
    char *vars = *(char **)(m + 104);
    float buf[12];
    float amount, fa, fb;
    int a, b, sign;
    char *entry;

    amount = func_002A7878(D_L09_001B17B0, D_L09_001B17B4);
    buf[0] = func_00283180(func_002A7940()) * amount;
    buf[1] = func_00283198(func_002A7940()) * amount;
    buf[2] = 0.0f;
    func_00282CD8(buf + 8, buf, m + 16);
    buf[2] = buf[2] - D_L09_001B17E8;
    buf[4] = 0.0f;
    buf[5] = 0.0f;
    buf[6] = 0.0f;
    buf[7] = 0.0f;
    buf[6] = func_002A7878(D_L09_001B17B8, D_L09_001B17BC) * 0.016666668f;
    a = func_002A7820(D_L09_001B17A8, D_L09_001B17AC);
    fa = func_002A7878(D_L09_001B17C8, D_L09_001B17CC);
    fb = func_002A7878(D_L09_001B17D0, D_L09_001B17D4);
    b = func_00283D38(D_L09_001B17D8, D_L09_001B17DC, func_002A7878(0.0f, 1.0f));
    sign = func_002A7820(D_L09_001B17E0, D_L09_001B17E4);
    if ((func_001163B0() & 1) != 0) {
        sign = -sign;
    }
    func_002C2210(buf, a, b, 2, sign, buf + 4, fa, fb,
                  -(func_002A7878(D_L09_001B17C0, D_L09_001B17C4) * 0.000277777785f), 0);

    switch (m[32]) {
    case 0:
        func_002A7750(m, 1, -1);
        *(int *)(vars + 8) = -1;
        break;
    case 1:
        entry = D_00188660 + *(int *)(vars + 8) * 112;
        if (*(char **)(entry + 136) != m || entry[116] == 0) {
            *(int *)(vars + 8) = func_002E5CF8(0, 4, m);
        }
        if (*(char **)(D_00189E20 + 828) != m) {
            break;
        }
        if (*(short *)(D_00189E20 + 846) != 0) {
            break;
        }
        if ((unsigned char)D_00189E20[8884] == 0) {
            if (D_001A79F0 == 9) {
                func_002B0C28(4, 10182, 1);
            } else if (D_001A79F0 == 18) {
                func_002B0C28(4, 10221, 1);
            }
        } else if ((unsigned char)D_00189E20[8884] == 2) {
            func_002B0C28(4, 10164, 1);
        }
        if ((D_00138324 & 0x10) == 0) {
            break;
        }
        if (D_L09_001A8FB4 != 4) {
            break;
        }
        func_002A7750(m, (D_001A79F0 == 9 || D_001A79F0 == 18) ? 2 : 4, -1);
        break;
    case 2: {
        int id;

        if (D_001A79F0 == 9) {
            id = 100;
        } else if (D_001A79F0 == 18) {
            id = 146;
        } else {
            break;
        }
        if (func_00288AA0(D_L09_001BFC00, id) == 0) {
            break;
        }
        func_00288BE8(D_L09_001BFC00);
        func_002A7750(m, 3, -1);
        break;
    }
    case 3:
        if (func_002F5D10() != 0) {
            D_L09_001B25A8 = 1;
            break;
        }
        /* fall through */
    case 4:
        D_L09_001B25A8 = 0;
        m[49] = 1;
        *(unsigned short *)(m + 52) = *(unsigned short *)(m + 52) & 0xFFFE;
        if (D_001A79F0 == 9) {
            D_001395B8[45] = 1;
            D_001395B8[29] = 1;
        } else if (D_001A79F0 == 18) {
            D_001395B8[159] = 1;
            D_001395B8[135] = 1;
        }
        func_00288CB0(*(int *)vars, 1);
        break;
    default:
        break;
    }

    if (*(unsigned short *)(m + 150) <= 0xFFFE) {
        *(unsigned short *)(m + 150) = *(unsigned short *)(m + 150) + 1;
    }
}
