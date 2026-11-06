/* func_PAL_L09_00427530, the PAL copy of func_L09_00421D60: the same C, where rename func_002A7750 becomes func_002A7820; rename-macro func_L00_002EC248 becomes func_PAL_L00_002ED7E8; scale func_316A68(0, 0xF0); scale func_316A68(0x78, 0xF0); rename func_316A68 becomes func_002A7820; rename func_316958 becomes func_002A7750; rename func_2EA0E0 becomes func_00282948; rename func_2E8450 becomes func_PAL_L00_002ED7E8. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern void func_L09_004081F0(char *a0, s32 a1, char *a2, s32 a3);

extern void func_L09_00408138(char *a0, char *a1, s32 a2, s32 a3, s32 a4);

extern void func_L09_00406BA0(s32 a0, u8 a1);

/* func_L09_0040AC48 is in L09_0040AC48-g8.c. */

/* func_L09_0040B0C8 is defined in L09_003FEA48-g8.c (it reads small data through $gp). */

/* func_L09_0041D650 is in L09_0041D650-g8.c. */

/* func_L09_00421B80 is in L09_003FEA48-zp-g8.c. */

extern int func_316A68(int a, int b);
extern void func_316958(char *a0, int a1, int a2);
extern int func_2EA0E0(char *p);
extern void func_2E8450(char *a0, float *a1, float *a2, int a3, int a4, float f12, float f13, float f14, float f15, float f16);

/* func_L09_003FEA48 is defined in L09_003FEA48-g8.c (this unit has no $gp access for it). */

/* func_L09_003FEAE8 is defined in L09_003FEAE8-g8.c. */

/* func_L09_003FEF00 is in L09_003FEA48-patrol-g8.c. */

/* func_L09_00402D50 is in L09_00402D50-g8.c. */

/* Level 09 helpers. */
/* func_L09_00403270 reads small data through $gp, so it is defined in
   L09_003FEA48-g8.c. */

/* func_L09_00403700: 152 bytes, one register off - the loop's trip test compares
   into $v0 where retail compares into $v1.  Deposited in
   nonmatching/levels/func_L09_00403700.c. */

/* func_L09_00403798 is in L09_00403798-g8.c. */

/* func_L09_00404C50 is in L09_00404C50-g8.c. */

/* Defined in L09_004050E0.c. */

/* func_L09_004052F8 is defined in L09_003FEA48-g8.c (it reads the group count through $gp). */

/* func_L09_00405490 is defined in L09_003FEA48-g8.c (it reads small data through $gp). */

/* func_L09_00405610 is defined in L09_00405610-g8.c (small data through $gp, and its own .rodata). */

void func_L09_00406BA0(s32 a0, u8 a1);

/* func_L09_00406BF8: 112 bytes against retail's 108, one saved register too many.
   Deposited in nonmatching/levels/func_L09_00406BF8.c. */

/* func_L09_00406CC0 is defined in L09_003FEA48-g8.c (it reads the object table through $gp). */

/* func_L09_00406E78 is defined in L09_003FEA48-g8.c (it reads the object table through $gp). */

/* func_L09_00406FC8 is in L09_00406FC8-g8.c. */

/* Sets an entity's colour key, or hands an off-kind entity to the shared body. */
void func_L09_00408138(char *a0, char *a1, s32 a2, s32 a3, s32 a4);

/* Hands the record's colour key to every entry the index names, negating the
   three offsets when the caller asks for it. */
void func_L09_004081F0(char *a0, s32 a1, char *a2, s32 a3);

/* func_L09_004082D0 is in L09_004082D0.c. */

/* func_L09_00408478 reads D_001A7AF8[k] and stores D_L09_001B25A0[2] as elements of sda arrays:
 * (mem (const (plus sym k))) is a two-word move, so these stay out of delay slots. */
typedef struct { char pad[0x5c]; int state; int flags; } DobboPlayerFlags;
extern DobboPlayerFlags D_00139768;
extern int D_001A79F8 SDATA(D_001A79F8);
extern int D_001A79F0 SDATA(D_001A79F0);
extern char *D_L09_001B294C SDATA(D_L09_001B294C);
/* func_L09_00409308 is in L09_00409308.c. */

/* func_L09_0040A2E8 is in L09_0040A2E8-g8.c. */

void func_PAL_L09_00427530(char *a0) {
    char *s2 = *(char **)(a0 + 0x68);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(int *)s2 = (((int)(func_316A68(0, 0xF0)) * 5 + 2) / 6);
        func_316958(a0, 1, -1);
        break;
    case 1:
        if (func_2EA0E0(s2)) {
            if (*(u8 *)(a0 + 0x31)) {
                EffectVector a;
                EffectVector b;
                a.bits = 0;
                b.bits = 0;
                a.value[1] = -0.040000003f;
                a.value[2] = 0.020000001f;
                b.value[2] = 2.0f;
                func_2E8450(a0, b.value, a.value, func_316A68(3, 7), 0, 0.0f, 0.040000003f, 0.7f, 15.0f, 1.0f);
            }
            *(int *)s2 = (((int)(func_316A68(0x78, 0xF0)) * 5 + 2) / 6);
        }
        break;
    }
}
