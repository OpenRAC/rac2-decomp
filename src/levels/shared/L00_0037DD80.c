#include "include_asm.h"

extern int D_L05_00231E40_1[][4];

typedef unsigned char u8;

typedef int s32;

typedef unsigned int u32;

typedef struct {
    u32 field00,field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;

extern u8 D_L00_00231340[];

extern u8 D_L00_001B26B4[];

extern int func_00282948(void *p);

extern void func_L00_0037FE08(void);

extern void func_L00_00387F98(void);

extern void func_L00_0038A9E0(void);

/* shared native body of family 954231c412 */
int func_L00_0037DD80(int a0, int a1)
{
    int i;
    int r = 1;

    for (i = 0; i < 32; i++)
        if (D_L05_00231E40_1[i][1] == a0 && D_L05_00231E40_1[i][0] == a1) {
            r = 0;
            break;
        }
    return r;
}

/* searches 32 sixteen-byte records for matching key and owner words and returns the value word or minus one */
s32 func_L00_0037DDE8(u32 key,u32 owner) {
    OrbitalPairTableView16 *entry=(OrbitalPairTableView16 *)D_L00_00231340;
    s32 checked=0;
    do {
        ++checked;
        if(entry->field04==key && entry->field00==owner) return entry->field08;
        ++entry;
    } while(checked<32);
    return -1;
}

extern int func_L00_0037DD80(int a0, int a1);
extern int func_L00_0037DE30(char *a0, char **a1, int a2, int a3);

int func_L00_0037DEF8(char *a0, char **a1, int a2, int *a3, int a4)
{
    int i;

    *a3 = 1;
    for (i = 0; i < a2; i++) {
        if (a4 > 0 && *(short *)(*(int *)(a1[i] + 0x24) + 0x46) != a4)
            continue;
        if (func_L00_0037DD80((int)a0, (int)a1[i]) == 1)
            return (int)a1[i];
    }
    if (a2 < 2)
        return 0;
    {
        int result = func_L00_0037DE30(a0, a1, a2, a4);

        if (result != 0)
            *a3 = 0;
        return result;
    }
}

/* clears the second word of every sixteen-byte record whose second word equals a0 */
void func_L00_0037E0C0(int a0)
{
    OrbitalPairTableView16 *entry = (OrbitalPairTableView16 *)D_L00_00231340;
    u32 *field = &entry->field04;
    int i;

    for (i = 31; i >= 0; i--) {
        if (*field == (u32)a0)
            *field = 0;
        field += 4;
    }
}

/* func_L00_0037E418 is built with -G8: see L00_0037DD80-init-g8.c. */

/* runs the three per-frame passes in the order the level expects */
void func_L00_0037E5C0(void)
{
    func_L00_00387F98();
    func_L00_0038A9E0();
    func_L00_0037FE08();
}

/* func_L00_0037E5F0 is built with -G8: see L00_0037DD80-g8.c. */

/* func_L00_0037E640 is matched in L00_0037E640.c (built with -mno-split-addresses). */
