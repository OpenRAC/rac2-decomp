#include "include_asm.h"
#include "names.h"

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
extern CounterState g_bolt_counter_state __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern int g_player_bolts[] __attribute__((sda));
extern int func_US2_0029C570(void);
extern void func_0029CBA8(int);
extern void hud_reset_bolt_counter_display(void);
extern void level_forward_value(int);

/* Moves the shown bolt count (D_001A79F8 is the real one) to the real count: a change opens a
 * transition row, 60 frames without a further change commit it, and the pending amount is then
 * applied over 15 frames. */
void func_US2_0028AD38(void)
{
    CounterRow *row;
    int index;
    int falling;
    int previous;
    int delta;

    if (func_US2_0029C570())
        return;
    func_0029CBA8((int)&g_bolt_counter_state.shown);
    if (g_current_game_mode[0] == 5 && g_player_bolts[0] < g_bolt_counter_state.shown) {
        hud_reset_bolt_counter_display();
    } else {
        falling = g_bolt_counter_state.falling;
        if (!falling && g_bolt_counter_state.active == -1 && g_player_bolts[0] < g_bolt_counter_state.shown) {
            index = g_bolt_counter_state.rows[0].state != 0;
            row = &g_bolt_counter_state.rows[index];
            falling = 1;
            row->state = falling;
            row->timer = 0;
            row->age = 0;
            row->value = g_bolt_counter_state.shown - g_player_bolts[0];
            g_bolt_counter_state.active = index;
            g_bolt_counter_state.falling = falling;
        } else if (!falling && g_bolt_counter_state.active == -1 && g_bolt_counter_state.shown + g_bolt_counter_state.pending < g_player_bolts[0]) {
            index = g_bolt_counter_state.rows[0].state != 0;
            row = &g_bolt_counter_state.rows[index];
            row->state = 1;
            row->timer = 0;
            row->age = 0;
            row->value = 0;
            g_bolt_counter_state.active = index;
            g_bolt_counter_state.falling = 0;
        }
    }
    index = g_bolt_counter_state.active;
    if (index != -1) {
        row = &g_bolt_counter_state.rows[index];
        if (row->state != 3) {
            previous = row->value;
            if (previous >= 0) {
                row->value = g_player_bolts[0] - g_bolt_counter_state.shown + g_bolt_counter_state.pending;
                if (row->value != previous)
                    row->timer = 0;
            }
            row->timer++;
            row->age++;
            if (row->timer > 60) {
                g_bolt_counter_state.pending = row->value;
                g_bolt_counter_state.base = g_bolt_counter_state.shown;
                row->timer = -1;
                row->state = 3;
            }
        }
    }
    if (index != -1 || g_bolt_counter_state.rows[0].state == 3 || g_bolt_counter_state.rows[1].state == 3)
        level_forward_value(180);
    for (index = 0; index < 2; index++) {
        row = &g_bolt_counter_state.rows[index];
        switch (row->state) {
        case 1:
            if (row->age >= 15)
                row->state = 2;
            break;
        case 3:
            row->timer++;
            delta = (int)((float)g_bolt_counter_state.pending * 0.0714285746f);
            g_bolt_counter_state.shown += delta;
            row->value -= delta;
            if (g_bolt_counter_state.falling ? row->value > 0 : row->value < 0)
                row->value = 0;
            if (row->timer >= 15) {
                if (g_bolt_counter_state.shown != g_bolt_counter_state.base + g_bolt_counter_state.pending)
                    g_bolt_counter_state.shown = g_bolt_counter_state.base + g_bolt_counter_state.pending;
                g_bolt_counter_state.pending = 0;
                g_bolt_counter_state.active = -1;
                row->state = 0;
                g_bolt_counter_state.falling = 0;
            }
            break;
        }
    }
}

