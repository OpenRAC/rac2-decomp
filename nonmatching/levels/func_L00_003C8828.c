/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections.
 * Emitted/retail size: 560/560 bytes.
 * us: 0 of 27 places match.
 * pal: ABSENT.
 * us2: 0 of 27 places match.
 * No strict linked build was run for this draft.
 * The object, state and configuration pointers have different register lifetimes. Delaying hero-pointer construction fixes the initial address hoist but not allocation. Reopen with allocator evidence for the matched target-query twins.
 */
#include "common.h"
extern void func_0029FCC0(char *, int, void *);
extern void func_002FDF40(void *, void *, void *, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(void *);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_0038A748(void *, void *, void *);
extern void func_L00_002AF7D0(void);
extern void func_L00_003C8A58(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern char D_00189E20[];
extern u32 D_00138324;

void func_L00_003C8828(unsigned char *object)
{
    float position[4];
    float config[4];
    char *state = *(char **)(object + 0x68);
    char *hero;
    int allowed;
    float range;
    func_0029FCC0((char *)object, 0, position);
    hero = D_00189E20;
    range = *(int *)(hero + 0x2294) == 29 ? 11.0f : 4.5f;
    func_002FDF40(config, position, 0, 0, 1.5f, range, 0.25f, 0.003055555746f);
    allowed = 1;
    *(int *)(state + 0x24) = func_002FE5A0(position, config, state, state + 0x10, object, 0, 0, 0.003055555746f);
    if (*(int *)(hero + 0x2294) == 29) {
        if (func_00282948(hero + 0x2534) == 0)
            allowed = 0;
    } else {
        *(int *)(hero + 0x2534) = 40;
    }
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((D_00138324 & *(u32 *)(hero + 0x1230)) && (unsigned char)hero[0x22bc] == 0 && allowed) {
            if (func_L00_002D3F30(-1, 1)) {
                func_L00_002AF568();
                object[0x20] = 2;
                *(int *)(state + 0x20) = 20;
            } else {
                func_002E5CF8(2, 0, (char *)object);
            }
        }
        break;
    case 2:
        if (func_00282948(state + 0x20)) {
            func_002E5CF8(0, 0, (char *)object);
            func_L00_0038A748(object, position, config);
            func_L00_002AF7D0();
            object[0x20] = 3;
            *(int *)(state + 0x20) = 10;
        }
        break;
    case 3:
        if (func_00282948(state + 0x20))
            object[0x20] = 1;
        break;
    }
    func_L00_002E6EF8(func_L00_003C8A58, object);
}
