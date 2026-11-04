/* func_PAL_L11_004791F0, the PAL copy of func_L11_00472E10: the same C, where func_L00_002B9D60
   becomes func_PAL_L00_002B9CD8. */

typedef unsigned char u8;
typedef unsigned short u16;
extern u8 D_001A7B2B;
extern int D_001A79F0;
extern u8 D_0019B4A8[];
typedef struct { u8 prefix[0x464]; u8 flags[1]; } LevelFlags;
extern LevelFlags D_L11_0021F8B0;
extern u8 D_00189EA0[];
extern u8 D_00188660[];
extern u8 *D_L11_001B359C __attribute__((sda));
extern int func_002ACD38(void *);
extern void func_L00_003672F8(void);
extern void func_PAL_L00_002B9CD8(float *, float *, int, int);
extern float func_00282E80(void *, void *);
extern int func_L00_0035F5A0(int, int, int);
extern void func_002E59F8(int);
extern int func_002B38B8(u8 *);
extern void func_0029F338(void *);

void func_PAL_L11_004791F0(u8 *object) {
    float position[4];
    float rotation[4];
    int *state = *(int **)(object + 0x68);
    int count, slot;
    u8 *record;
    u8 *counter;
    if (object[0x20] == 0) {
        if (D_001A7B2B) {
            u16 id = *(u16 *)(object + 0xB2);
            int bits;
            if (D_L11_0021F8B0.flags[(short)id] == 0) {
                bits = D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400];
                if (*(u16 *)(object + 0xB2) & 1) bits = (bits >> 4) & 7;
                else bits &= 7;
                if (bits == 0 && func_002ACD38(object + 0x10)) {
                    func_L00_003672F8();
                    position[0] = 363.18f;
                    position[1] = 680.68f;
                    position[2] = 155.73f;
                    rotation[2] = 2.3561947f;
                    rotation[0] = 0;
                    rotation[1] = 0;
                    func_PAL_L00_002B9CD8(position, rotation, 0, 1);
                }
            }
        }
        object[0x20] = 1;
    }
    if (func_00282E80(object + 0x10, D_00189EA0) < 32.0f) {
        if (D_001A79F0 == 11) {
            record = D_00188660 + state[8] * 0x70;
            if (*(int *)(record + 0x88) != *(int *)(D_00189EA0 + 0x2210) || record[0x74] == 0)
                state[8] = func_L00_0035F5A0(27, 6, *(int *)(D_00189EA0 + 0x2210));
        }
    } else {
        slot = state[8];
        if (slot != -1) {
            record = D_00188660 + slot * 0x70;
            if (*(int *)(record + 0x88) == *(int *)(D_00189EA0 + 0x2210) && record[0x74]) func_002E59F8(slot);
        }
        state[8] = -1;
    }
    if (!func_002B38B8(object)) {
        u16 id = *(u16 *)(object + 0xB2);
        int bits;
        if (!D_L11_0021F8B0.flags[(short)id]) {
            bits = D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400];
            if ((*(u16 *)(object + 0xB2) & 1)
                ? ((bits >> 4) & 7) != 0
                : (bits & 7) != 0) goto cleanup;
            return;
        }
    }
cleanup:
    for (count = 0; count < 8; count++) {
        if (state[count] != -1) func_0029F338(D_L11_001B359C + state[count] * 0x100);
    }
    {
        int counter_id = *(u16 *)(object + 0xB2);
        if (counter_id & 1) {
            counter = &D_0019B4A8[((short)counter_id >> 1) + D_001A79F0 * 0x400];
            if (((*counter >> 4) & 7) != 7) *counter += 16;
        } else {
            counter = &D_0019B4A8[((short)counter_id >> 1) + D_001A79F0 * 0x400];
            if ((*counter & 7) != 7) ++*counter;
        }
    }
    {
        int final_slot = state[8];
        if (final_slot != -1) {
            record = D_00188660 + final_slot * 0x70;
            if (*(int *)(record + 0x88) == *(int *)(D_00189EA0 + 0x2210) && record[0x74]) func_002E59F8(final_slot);
        }
        state[8] = -1;
        func_0029F338(object);
    }
}
