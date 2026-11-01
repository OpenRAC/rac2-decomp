#include "include_asm.h"

#include "common.h"
struct BFObject {
    char pad[0x30];
    unsigned char field_30;
    unsigned char field_31;
    unsigned short field_32;
};
extern char *ref_L00_003DBF50_00(int);
extern float ref_L00_003DBF50_01(void);
extern float ref_L00_003DBF50_02(float, float);
extern int ref_L00_003DBF50_03 SDATA(ref_L00_003DBF50_03);
extern char *ref_L00_003DBF50_04;
extern char *ref_L00_003DBF50_05;
extern char *ref_L00_003DBF50_06;
extern char *ref_L00_003DBF50_07(char *);
extern void ref_L00_003DBF50_08(void);
extern struct BFPlayer { char pad[0xbf8]; char *target; } D_00189E20 NOT_SDA;
extern float ref_L00_003DBF50_10(char *);
extern void ref_L00_003DBF50_11(char *, char *, char *, float);
extern void ref_L00_003DBF50_12(char *, char *);
extern float ref_L00_003DBF50_13 SDATA(ref_L00_003DBF50_13);
extern float ref_L00_003DBF50_14 SDATA(ref_L00_003DBF50_14);
extern void ref_L00_003DBF50_15(void *, void *, float);
extern int ref_L00_003DBF50_16(char *, float, float, float, int);

/* Spawns moby class 0xB2E at pos for parent and sets its state up (the three shared buffers
 * on first use), hands dir to the target record at D_00189E20 + 0xBF8 when there is one,
 * and passes dir with a random spread and a random speed through ref_L00_003DBF50_15. */
char *func_PAL_L00_003E0120(char *parent, int arg, char *pos, char *dir)
{
    float velocity[4];
    char *object = ref_L00_003DBF50_00(0xb2e);
    char *state;
    float length;

    if (object) {
        object[0x20] = 0;
        state = *(char **)(object + 0x68);
        ((struct BFObject *)object)->field_30 = 255;
        ((struct BFObject *)object)->field_32 = 255;
        *(float *)(state + 0x64) = ref_L00_003DBF50_01();
        *(float *)(state + 0x68) = ref_L00_003DBF50_02(0.44680437f, 0.75398237f);
        *(int *)(state + 0x74) = *(short *)(parent + 0xaa);
        *(int *)(state + 0x7c) = 0;
        qcopy(object + 0x10, pos);
        *(float *)(object + 0x2c) = ref_L00_003DBF50_02(0.01f, 0.0125f);
        *(unsigned short *)(object + 0x34) |= 0x100;
        *(int *)(object + 0x78) = 0x7f4080ff;
        *(int *)(state + 0x70) = arg;
        {
            char *parentState = *(char **)(parent + 0x68);

            if (!ref_L00_003DBF50_03) {
                char *p = *(char **)(parentState + 8);

                ref_L00_003DBF50_04 = p;
                p = ref_L00_003DBF50_07(p + 0x100);
                ref_L00_003DBF50_05 = p;
                p = ref_L00_003DBF50_07(p + 0x4b00);
                ref_L00_003DBF50_06 = p;
                ref_L00_003DBF50_07(p + 0xa0);
                ref_L00_003DBF50_08();
                ref_L00_003DBF50_03 = 1;
            }
        }
        if (D_00189E20.target) {
            length = ref_L00_003DBF50_10(dir);
            if (length == 0.0f)
                length = 1.0f;
            ref_L00_003DBF50_11(D_00189E20.target, pos, dir, length);
            qcopy(state, dir);
        } else {
            ref_L00_003DBF50_12(object, state);
        }
        qcopy(velocity, dir);
        velocity[0] += ref_L00_003DBF50_02(-0.15f, 0.15f);
        velocity[1] += ref_L00_003DBF50_02(-0.15f, 0.15f);
        length = ref_L00_003DBF50_02(ref_L00_003DBF50_13 * (0.020000001f),
                                     ref_L00_003DBF50_14 * (0.020000001f));
        ref_L00_003DBF50_15(velocity, velocity, length * 0.5f);
        *(int *)(state + 0x6c) = 96;
        *(int *)(state + 0x60) = 567;
        *(int *)(state + 0x78) = ref_L00_003DBF50_16(object, 1.0f, 1.0f, 1.0f, 0);
    }
    return object;
}
