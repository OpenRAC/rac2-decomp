#include "include_asm.h"

/* func_US2_L16_002F6CE0, the USA v2.00 copy of func_L16_002F60B8: the same C and the same unit
   flags (-G8, the quadword copy profile, gcse on), where the first loop's last test also skips
   level 0x33. Holding class 4000 in a local gives its constant a longer life, so loop's first
   pass still hoists it before the object pointer's giv; the 0x33 misses that pass's threshold
   and comes after the giv in the rerun. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef int Quadword __attribute__((mode(TI)));
extern int D_001A79F0[] __attribute__((sda));
typedef struct SnivelakScene {
    unsigned char pad0[0x30];
    int state;
    int frame;
    unsigned char pad38[0xC];
    short objectCount;
    unsigned char pad46[0x146];
    char *objects[0];
} SnivelakScene;
extern SnivelakScene D_L16_001BD800;
extern float D_L16_001B2564;
/* Partial view of the position and transform used by the scene effect. */
typedef struct {
    float position[4];
    unsigned char pad10[0x220];
    float matrix[16];
} SceneEffectTransform;
extern SceneEffectTransform D_L16_001B9B00;
extern char D_L16_001A8F20[] __attribute__((sda));
typedef struct { unsigned char prefix[0xD4]; u8 *material; } SceneEffectMaterial;
extern SceneEffectMaterial D_L16_001FF680;
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
extern char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *func_0029EFD0(short);
extern void func_002B37E8(char *, char *);
extern void func_002AEC18(void *, int);
extern void func_00283098(void *, void *, void *);
extern void func_002B0A68(char *, int, void *, float, float, float, float, u8);
extern void func_0029F338(char *);

void func_US2_L16_002F6CE0(void)
{
    union { Quadword q; float f[4]; } position;
    float orientation[16], step[4], randomPosition[4];
    char *object;
    int i = 0;
    func_L00_002FC980();
    for (; i < D_L16_001BD800.objectCount; i++) {
        char *entry = D_L16_001BD800.objects[i];
        if (entry && *(short *)(entry + 0xaa) == 0xe29)
            *(u16 *)(entry + 0x34) |= 0x800;
        if (*(short *)(entry + 0xaa) == 0xd54)
            func_002E64A0(entry);
        if (entry) {
            int wantedClass = 4000;
            if (*(short *)(entry + 0xaa) == wantedClass && D_001A79F0[0] != 0x33 && *(char **)(entry + 0x68))
                func_L00_00326048(entry, (float *)(*(char **)(entry + 0x68) + 12), 0x80aaaad2, 0x80396464, 0.06108653545379639f);
        }
    }
    if (D_001A79F0[0] == 16 && D_L16_001BD800.state == 1) {
        object = D_L16_001BD800.objects[6];
        *(int *)(object + 0x78) = 0xff0020ff;
        *(u16 *)(object + 0x34) |= 16;
        if (func_00282C30(D_L16_001BD800.frame - 0x334) < 4) {
            float fade = (float)func_00282C30(D_L16_001BD800.frame - 0x334) * 0.333f;
            if (fade > 1.0f) fade = 1.0f;
            else if (fade < 0.0f) fade = 0.0f;
            D_L16_001B2564 = 1.0f - fade;
        }
        if (D_L16_001BD800.frame == 0x336) {
            int particleIndex;
            position.q = 0;
            position.f[0] = 0.2f;
            position.f[3] = 1.0f;
            func_0029FC20(object, 0, (char *)orientation);
            func_002830C0(&position, &position, orientation);
            func_00282D30(step, orientation + 8, 0.15f);
            func_00282CC0(&position, &position, step);
            func_00282D30(step, orientation + 8, -0.03333333507180214f);
            particleIndex = 29;
            do {
                int random;
                float scale;
                char *particle;
                randomPosition[0] = position.f[0] + func_002A78D8(0.0f, 0.05f);
                randomPosition[1] = position.f[1] + func_002A78D8(0.0f, 0.05f);
                randomPosition[2] = position.f[2] + func_002A78D8(0.0f, 0.05f);
                random = func_002A77E0(255);
                scale = 42000.0f;
                func_002C65A0(randomPosition, D_L16_001A8F20, 20, 0x808080, random, 127, 0, scale, scale, 0.0f, 0);
                scale = 273000.0f;
                particle = func_002C65A0(&position, D_L16_001A8F20, 30, 0x406080, random, 16, 0, scale, scale, 0.0f, 0);
                if (particle) particle[2] = *D_L16_001FF680.material;
                func_00282CC0(&position, &position, step);
                particleIndex--;
            } while (particleIndex >= 0);
        } else if (D_L16_001BD800.frame == 0x366) {
            object = func_0029EFD0(0xa79);
            if (object) {
                func_002B37E8(object, 0);
                func_002AEC18(object, 0x80000000);
                *(float *)(object + 0x2c) = *(float *)(*(char **)(object + 0x24) + 0x24) * 0.333f;
                position.q = 0;
                position.f[0] = -3.0f;
                position.f[1] = 2.0f;
                func_00283098(&position, &position, D_L16_001B9B00.matrix);
                func_00282CC0(&position, &position, D_L16_001B9B00.position);
                *(Quadword *)(object + 0x10) = position.q;
                func_002B0A68(object, 0xfff, D_L16_001A8F20, 3.0f, 9.0f, -3.0f, 3.0f, 255);
                func_002B0A68(object, 0xfff, D_L16_001A8F20, 3.0f, 9.0f, -3.0f, 3.0f, 255);
                func_0029F338(object);
            }
        }
    }
}
