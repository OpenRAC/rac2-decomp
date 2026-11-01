#include "include_asm.h"

typedef struct {
    int value;
    int timer;
    int age;
    short reserved;
    short state;
} CounterRow;
typedef struct {
    CounterRow rows[2];
    int shown;
    int base;
    int pending;
    int active;
    int falling;
} CounterState;
extern CounterState D_001B1928 __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda));
extern int func_PAL_0029C118(void);
extern void func_0029CBA8(int);
extern void func_0028A278(void);
extern void func_0029B698(int);

/* Moves the shown bolt count (D_001A79F8 is the real one) to the real count: a change opens a
 * transition row, 60 frames without a further change commit it, and the pending amount is then
 * applied over 15 frames. */
void func_PAL_0028ACC0(void)
{
    CounterRow *row;
    int index;
    int falling;
    int previous;
    int delta;

    if (func_PAL_0029C118())
        return;
    func_0029CBA8((int)&D_001B1928.shown);
    if (D_001A8BB0[0] == 5 && D_001A79F8[0] < D_001B1928.shown) {
        func_0028A278();
    } else {
        falling = D_001B1928.falling;
        if (!falling && D_001B1928.active == -1 && D_001A79F8[0] < D_001B1928.shown) {
            index = D_001B1928.rows[0].state != 0;
            row = &D_001B1928.rows[index];
            falling = 1;
            row->state = falling;
            row->timer = 0;
            row->age = 0;
            row->value = D_001B1928.shown - D_001A79F8[0];
            D_001B1928.active = index;
            D_001B1928.falling = falling;
        } else if (!falling && D_001B1928.active == -1 && D_001B1928.shown + D_001B1928.pending < D_001A79F8[0]) {
            index = D_001B1928.rows[0].state != 0;
            row = &D_001B1928.rows[index];
            row->state = 1;
            row->timer = 0;
            row->age = 0;
            row->value = 0;
            D_001B1928.active = index;
            D_001B1928.falling = 0;
        }
    }
    index = D_001B1928.active;
    if (index != -1) {
        row = &D_001B1928.rows[index];
        if (row->state != 3) {
            previous = row->value;
            if (previous >= 0) {
                row->value = D_001A79F8[0] - D_001B1928.shown + D_001B1928.pending;
                if (row->value != previous)
                    row->timer = 0;
            }
            row->timer++;
            row->age++;
            if (row->timer > 50) {
                D_001B1928.pending = row->value;
                D_001B1928.base = D_001B1928.shown;
                row->timer = -1;
                row->state = 3;
            }
        }
    }
    if (index != -1 || D_001B1928.rows[0].state == 3 || D_001B1928.rows[1].state == 3)
        func_0029B698(150);
    for (index = 0; index < 2; index++) {
        row = &D_001B1928.rows[index];
        switch (row->state) {
        case 1:
            if (row->age >= 13)
                row->state = 2;
            break;
        case 3:
            row->timer++;
            delta = (int)((float)D_001B1928.pending * 0.0714285746f);
            D_001B1928.shown += delta;
            row->value -= delta;
            if (D_001B1928.falling ? row->value > 0 : row->value < 0)
                row->value = 0;
            if (row->timer >= 13) {
                if (D_001B1928.shown != D_001B1928.base + D_001B1928.pending)
                    D_001B1928.shown = D_001B1928.base + D_001B1928.pending;
                D_001B1928.pending = 0;
                D_001B1928.active = -1;
                row->state = 0;
                D_001B1928.falling = 0;
            }
            break;
        }
    }
}


INCLUDE_ASM("asm/pal/game", func_PAL_0028B038);
