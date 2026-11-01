/* SPDX-License-Identifier: MIT
 *
 * Near miss: func_L00_003A98E8, the level's shared "spawn a projectile"
 * helper, 876 bytes in every level, 27 places.
 *
 * Profile: -O2 -G0 -ffunction-sections, in a source unit named
 * L00_003A98E8.c. No small data is read here, so the default profile is
 * right.
 *
 * Result: 748/876 bytes, 0/27 places in USA v1.01. The record allocation, the
 * record's header, the three stored speeds, the spread steps (the game's
 * angle pairs of pi/3600, pi/1800 and pi/450 with their halves), the two
 * branches on the surface kind (0xC87 and 0xECC) and the copy of the position
 * are reconstructed and read as the retail code reads them.
 *
 * What is missing is the twelve-argument call to func_002ABBB8: retail passes
 * four integers in the argument registers, four more in the saved argument
 * registers, four on the stack (1, an inherited $s7, 0 and 0x810001) and four
 * floats (f12 to f15), and it leaves three more floats live in $f16 to $f18
 * that no argument register holds. This source passes twelve integers and no
 * floats, so the call and the six float constants around it are missing, which
 * accounts for the 128 bytes and for the frame (0x80 here, 0xE0 in retail).
 * The `por $v0, $zero, $zero' that retail uses to make the zero it stores on
 * the stack is not reproduced either.
 *
 * The next experiment is the argument shape of that call: the six float
 * constants (0.033333335f twice, 6.0f, 3.0f, 9.0f and 15.0f) and the four
 * stack words.
 */

#include "common.h"

/* func_L00_003A98E8: the level's shared "spawn a projectile" helper.
 *
 * It takes the shooter's position, the aim direction and a second point, a
 * flag and three speeds, allocates a record of the game's own size, fills in
 * the record's header and the three stored speeds, copies the position and
 * the aim point into it, and finally lets the game move the record along the
 * aim. When the surface under the shot is one of two special kinds it takes
 * the other path: it asks the game to start the projectile with a unit speed
 * and lets the caller finish.
 *
 * The addresses the function names differ from program to program: the boot
 * keeps its helpers at their own places, and each level has its own copy of
 * them. The names below are the boot's; the build reads each program's own
 * value from the retail bytes under the relocations.
 */
extern void *func_0029EFD0(int size);
extern float func_002A7940(int mode);
extern float func_002A78D8(float, float);
extern void func_00282F20(float *, float *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DB0(void *, void *);
extern void func_00283028(void *, void *, void *);
extern int func_002ABBB8(void *, void *, void *, int, int, int, int, int,
                         int, void *, int, int);
extern int func_0029F338(void *, void *);
extern int func_002AFFD8(void *, void *, int);
extern int func_002FED90(void *, void *, float, float);
extern int func_L00_003A9798(void *, void *, void *, int);
extern int D_001B8FF0;

void *func_L00_003A98E8(void *position, void *direction, void *other, int flag,
                         float speed, float turn, float rise)
{
    char *record;
    char *state;
    short kind;

    record = (char *)func_0029EFD0(0x5D8);
    if (record == 0)
        return 0;

    record[0x20] = 0;
    record[0x30] = 0xFF;
    record[0x32] = 0xFF;
    record[0x31] = 1;
    state = *(char **)(record + 0x68);

    func_002A7940(1);
    *(float *)(record + 0xF8) = func_002A7940(1);
    *(float *)(record + 0xF4) = func_002A7940(1);
    *(float *)(record + 0xF0) = func_002A7940(1);

    *(float *)(record + 0x2C) = *(float *)(*(char **)(record + 0x24) + 0x24) * 0.5f;

    qcopy(record + 0x10, position);
    func_00282F20((float *)state, (float *)direction, speed);
    qcopy(state + 0x50, state);

    /* The three steps of the shot's spread, as the game measures them. */
    *(int *)(state + 0x2C) = func_002A78D8(0.0008726647357f, 0.004363323562f);
    *(float *)(state + 0x30) = func_002A78D8(0.001745329471f, 0.008726647124f);
    *(float *)(state + 0x34) = func_002A78D8(0.006981317885f, 0.03490658849f);

    *(short *)(state + 0x16) = (short)flag;
    *(float *)(state + 0x1C) = speed;
    *(float *)(state + 0x18) = turn;
    *(float *)(state + 0x20) = rise;
    *(short *)(state + 0x14) = 0;
    *(short *)(state + 0x2E) = 0;
    *(int *)(state + 0x24) = 0;
    *(int *)(state + 0x28) = 0;

    kind = *(short *)(*(char **)(record + 0x24) + 0xAA);
    if (kind == 0xC87 || kind == 0xECC) {
        func_002FED90(record, 0, 1.0f, 1.0f);
        if (D_001B8FF0 == 0)
            return record;
        *(int *)(state + 0x48) = 0;
        func_002AFFD8(direction, (void *)(record + 0x50), 1);
        func_00282DB0((void *)(record + 0x50), direction);
        func_00282D30((void *)(record + 0x60), (void *)(record + 0x50), 0.0f);
        func_00282CF0(state, state, (void *)(record + 0x60));
        qcopy(state + 0x50, state);
        return record;
    }

    qcopy(direction, (char *)other + 0x20);
    func_00283028((void *)(record + 0x40), (void *)(record + 0x20), (char *)other + 0x40);
    func_00282F20((void *)(record + 0x40), (void *)(record + 0x40), 0.033333335f);
    func_00282D30((void *)(record + 0x40), (void *)(record + 0x40), 0.0f);

    func_002ABBB8(record, (void *)(record + 0x40), 0, 0xA, 3, 9, -1, 1,
                  1, 0, 0, 0x810001);
    func_L00_003A9798(record, state, direction, 0);
    func_0029F338(record, 0);
    return record;
}
