/* 6 November 2026: 964/964 bytes, 0/28 USA v1.01 placements, game
 * -O2 -G8 -ffunction-sections in src/game/002F5220.c. First difference +0xC4.
 * The two confirm alternatives must be a positive OR, each with its pressed,
 * held and mode tests. This reproduces the repeated held-bit test, state-base
 * copy and mode reload that the previous 948-byte nested guard lost. A separate
 * activation pointer and the same F93State alias on refusal also recover the
 * retail activation/refusal tails without inventing accesses.
 * Remaining: the two animation selections swap the registers holding 3 and 1;
 * the item-kind/index/record region uses v0/a0/a1 where retail uses v1/a1/a0.
 * Measured new trials: one-pass groups at the guard (944/952), animation
 * initialization/read/store (968), and item-id/kind reads (968); explicit
 * selected/offset/id locals and narrower pointer lifetimes leave 964 bytes
 * with the same allocation differences. Putting the animation expression
 * wholly inside the animated branch gives 972 bytes. No exact credit.
 * Historical constraints, 3 November: a fully inlined guard helper shrank
 * the body to 928 bytes; declaring animation wholly within its conditional
 * recovered its registers but moved the constant out of the delay slot.
 * Required surrounding declarations remain those of 002F5220.c: F73Record
 * D_00239BA0, D_00139568, D_00138180, D_001A79F8, D_0021F240 and
 * int func_002E5CF8(int, int, void *). Full linked builds are left to the lead.
 */
extern int D_001B2240, D_001B223C;
extern int D_001B2244 __attribute__((sda));
extern int D_00139688[];
extern void func_0028B6C8(int, unsigned int);
extern int func_002F6510(void);
extern void func_002F9198(void);


typedef struct { int id, kind; int fields[4]; } ShopRow_93;
typedef struct {
    char pad0[0x28]; char *moby; char pad2C[0x24];
    volatile int mode; char pad54[0x18]; int scroll;
    char pad70[8]; int handle; char pad7C[4]; int selected;
    int busy; int animated; char pad8C[4]; int animation;
    char pad94[0xAC]; ShopRow_93 rows[64]; int count;
} ShopInput_93;
extern ShopInput_93 F93State __asm__("D_0021F240");
typedef struct { char pad[0x1C4]; int buttons; } Input_93;
void func_002F93B0(void)
{
    ShopInput_93 *state = &F93State;
    int cost;
    int *item;
    char *record;
    if (state->busy) return;
    {
        Input_93 *input = (Input_93 *)D_00138180;
        if ((input->buttons & 0x2000) ||
                (D_001B2240 >= 16 && D_001B2240 % 10 == 1)) {
            if (state->scroll < 57) {
                int moved = 0;
                if (state->selected < state->count - 1) {
                    ++state->selected;
                    moved = 1;
                }
                if (moved) {
                    {
                        int animation = 3;
                        if (state->animated) {
                            if (state->mode != 2) animation = 1;
                            state->animation = animation;
                        }
                    }
                    state->scroll += 56;
                    func_002E5CF8(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            func_0028B6C8(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)D_00138180;
        ShopInput_93 *state;
        if ((input->buttons & 0x8000) ||
                (D_001B223C >= 16 && D_001B223C % 10 == 1)) {
            state = &F93State;
            if (state->scroll >= -56) {
                int moved = 0;
                if (state->selected > 0) {
                    --state->selected;
                    moved = 1;
                }
                if (moved) {
                    {
                        int animation = 3;
                        if (state->animated) {
                            if (state->mode != 2) animation = 1;
                            state->animation = animation;
                        }
                    }
                    state->scroll -= 56;
                    func_002E5CF8(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            func_0028B6C8(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)D_00138180;
        ShopInput_93 *state;
        if (((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode != 3) ||
            ((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode == 3 &&
             *(int *)((char *)&F93State + 0x144 + F93State.selected * 12) != 0)) {
                state = &F93State;
                if (state->mode == 0) {
                    int stride = sizeof(ShopRow_93);
                    int *kinds = &state->rows[0].kind;
                    item = (int *)((char *)kinds + state->selected * stride);
                    if (*item == 0) {
                        cost = func_002F6510();
                        if ((*(int *)&D_001A79F8) >= cost) goto activate;
                    }
                    item = (int *)((char *)kinds + state->selected * stride);
                    if (*item != 1) goto rejected;
                    record = (char *)D_00239BA0 + D_00139568[state->rows[state->selected].id] * 224;
                    if (D_00139688[state->rows[state->selected].id] >= *(unsigned short *)(record + 0x8E)) goto rejected;
                    if ((*(int *)&D_001A79F8) < *(unsigned short *)(record + 0x88)) goto rejected;
                }
activate:
                {
                    ShopInput_93 *active = &F93State;
                    if (active->animated) active->animation = 1;
                    active->busy = 1;
                    func_002E5CF8(0, 17, active->moby);
                    goto finish;
                }
rejected:
                func_002E5CF8(2, 17, F93State.moby);
        }
    }
finish:
    if (((Input_93 *)D_00138180)->buttons & 0x10) func_002F9198();
}
