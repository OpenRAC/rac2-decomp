/*
 * Retained manually written near miss; historical evidence only.
 * No linked-image equality or complete retail semantics is established.
 * Compiler: game EE-GCC 2.9-ee-991111b (project profile).
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por.
 * Reported final C / retail: 1228 / 1256 bytes; size equality is not a match.
 * us: 0/1 placements; 1228/1256 bytes.
 * us2: absent from catalogue (not a match).
 * pal: absent from catalogue (not a match).
 * Residual: 1228 bytes versus1256; changed register allocation, global-base lifetime and frame D0 versus E0.
 * Reopening condition: Recover the original scene/global and local aggregate declaration or an independently qualified allocation remedy.
 * Where listed, tools/check.py measurements predate retention; no compilation was rerun for this copy.
 */

/* Manual reconstruction retained after measured nonmatching checks.
   Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por.
   1228 bytes versus1256; changed register allocation, global-base lifetime and frame D0 versus E0.
   Reopen: Recover the original scene/global and local aggregate declaration or an independently qualified allocation remedy.
   This is an unqualified draft, not an exact match or native behavior proof.
*/
typedef unsigned char u8;
typedef unsigned short u16;
typedef int Quadword __attribute__((mode(TI)));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_L16_001BD800[];
extern float D_L16_001B2564;
extern float D_L16_001B9D30[16];
extern float D_L16_001B9B00[4];
extern char D_L16_001A8F20[];
extern u8 *D_L16_001FF754;
extern void func_L00_002FC980(void);
extern void func_002E64A0(char *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern int func_00282C30(int);
extern void func_0029FC20(char *, int, char *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern char *func_002C65A0(void *, void *, int, int, int, int, int, int, float, float, float);
extern char *func_0029EFD0(short);
extern unsigned long long func_002B37E8(char *, char *);
extern void func_002AEC18(void *, int);
extern void func_00283098(void *, void *, void *);
extern void func_002B0A68(char *, int, int, u8, float, float, float, float);
extern void func_0029F338(char *);

void func_L16_002F60B8(void)
{
    union { Quadword q; float f[4]; } position;
    float orientation[16], step[4], randomPosition[4];
    unsigned char *scene;
    char *object;
    int i = 0;
    char **objects;
    func_L00_002FC980();
    scene = D_L16_001BD800;
    if (*(short *)(scene + 0x44) > 0) {
        objects = (char **)(scene + 0x18c);
        do {
            object = *objects;
            if (object && *(short *)(object + 0xaa) == 0xe29)
                *(u16 *)(object + 0x34) |= 0x800;
            if (*(short *)(object + 0xaa) == 0xd54)
                func_002E64A0(object);
            if (object && *(short *)(object + 0xaa) == 4000 && *(char **)(object + 0x68))
                func_L00_00326048(object, (float *)(*(char **)(object + 0x68) + 12), 0x80aaaad2, 0x80396464, 0.06108653545379639f);
            i++;
            objects++;
        } while (i < *(short *)(scene + 0x44));
    }
    if (D_001A79F0 == 16 && *(int *)(scene + 0x30) == 1) {
        object = *(char **)(scene + 0x1a4);
        *(int *)(object + 0x78) = 0xff0020ff;
        *(u16 *)(object + 0x34) |= 16;
        if (func_00282C30(*(int *)(scene + 0x34) - 0x334) < 4) {
            float fade = (float)func_00282C30(*(int *)(scene + 0x34) - 0x334) * 0.333f;
            if (fade > 1.0f) fade = 1.0f;
            else if (fade < 0.0f) fade = 0.0f;
            D_L16_001B2564 = 1.0f - fade;
        }
        if (*(int *)(scene + 0x34) == 0x336) {
            position.q = 0;
            position.f[0] = 0.2f;
            position.f[3] = 1.0f;
            func_0029FC20(object, 0, (char *)orientation);
            func_002830C0(&position, &position, orientation);
            func_00282D30(step, orientation + 8, 0.15f);
            func_00282CC0(&position, &position, step);
            func_00282D30(step, orientation + 8, -0.03333333507180214f);
            i = 29;
            do {
                int random;
                char *particle;
                randomPosition[0] = position.f[0] + func_002A78D8(0.0f, 0.05f);
                randomPosition[1] = position.f[1] + func_002A78D8(0.0f, 0.05f);
                randomPosition[2] = position.f[2] + func_002A78D8(0.0f, 0.05f);
                random = func_002A77E0(255);
                func_002C65A0(randomPosition, D_L16_001A8F20, 20, 0x808080, random, 127, 0, 0, 42000.0f, 42000.0f, 0.0f);
                particle = func_002C65A0(&position, D_L16_001A8F20, 30, 0x406080, random, 16, 0, 0, 273000.0f, 273000.0f, 0.0f);
                if (particle) particle[2] = *D_L16_001FF754;
                i--;
                func_00282CC0(&position, &position, step);
            } while (i >= 0);
        } else if (*(int *)(scene + 0x34) == 0x366) {
            object = func_0029EFD0(0xa79);
            if (object) {
                func_002B37E8(object, 0);
                func_002AEC18(object, 0x80000000);
                *(float *)(object + 0x2c) = *(float *)(*(char **)(object + 0x24) + 0x24) * 0.333f;
                position.q = 0;
                position.f[0] = -3.0f;
                position.f[1] = 2.0f;
                func_00283098(&position, &position, D_L16_001B9D30);
                func_00282CC0(&position, &position, D_L16_001B9B00);
                *(Quadword *)(object + 0x10) = position.q;
                func_002B0A68(object, 0xfff, (int)D_L16_001A8F20, 255, 3.0f, 9.0f, -3.0f, 3.0f);
                func_002B0A68(object, 0xfff, (int)D_L16_001A8F20, 255, 3.0f, 9.0f, -3.0f, 3.0f);
                func_0029F338(object);
            }
        }
    }
}
