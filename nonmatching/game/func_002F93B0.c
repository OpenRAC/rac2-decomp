/* Tier: Claude Opus 5.5 (xhigh), 3 November 2026. Game -O2 -G8 -ffunction-sections.
 * Best check: 948/964 bytes, 0/28 USA v1.01 places; 142 of 241 diff rows differ
 * (previous retained draft: 145). Change from the Sol-high draft: `moved` is now a
 * block-local in each movement section, which gives section 2 retail's $v1.
 * What differs:
 * (1) The animation temporaries are swapped (ours: $a0 = 3, $v1 = 1; retail:
 *     $v1 = 3, $a0 = 1). A block-local `animation` gets the retail registers but
 *     moves the `= 3` out of the beqz delay slot (956 bytes, beql).
 * (2) The purchase guard is 16 bytes short. Retail re-tests the held bit
 *     (bnez $a1), uses a copy of the state address ($a0 = $v0), reloads mode, and
 *     compares it with a fresh constant 3. All of this needs block B (the
 *     mode == 3 check) to be a separate cse block in both cse1 and cse2, with
 *     gcse PRE making the address copy. A static inline helper is fully cse'd
 *     (928 bytes). Mode stays volatile only to keep the reload.
 * Declarations: in 002F5220.c this needs the F73Record D_00239BA0 declaration from
 * func_002F73A8 (the body casts to char *), the file's D_00139568, D_00138180,
 * D_001A79F8 (MACRO_ADDR), D_0021F240 and int func_002E5CF8(int, int, void *).
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
        if (input->buttons & 0x40) {
            int held = D_001B2244 & 0x40;
            if (!held) {
                state = &F93State;
                if (state->mode == 3) {
                    if (held) goto finish;
                    if (state->mode != 3) goto finish;
                    if (*(int *)((char *)state + 0x144 + state->selected * 12) == 0) goto finish;
                }
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
                state = &F93State;
                if (state->animated) state->animation = 1;
                state->busy = 1;
                func_002E5CF8(0, 17, state->moby);
                goto finish;
rejected:
                func_002E5CF8(2, 17, *(char **)(((char *)&D_0021F240) + 0x28));
            }
        }
    }
finish:
    if (((Input_93 *)D_00138180)->buttons & 0x10) func_002F9198();
}
