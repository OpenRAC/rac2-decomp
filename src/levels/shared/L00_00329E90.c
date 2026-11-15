#include "common.h"

/* The two slots the level's resident records live in, and the counter that
   says which of them is the current one. */
typedef struct Slot_00329E90 {
    void (*callback)(struct Slot_00329E90 *);
    int id;
    char pad[0xA430 - 8];
} Slot_00329E90;

extern Slot_00329E90 D_L00_00268E20[];
extern int D_L00_001A902C[] __attribute__((sda));

/* Finds or frees one of the two slots for this entity and returns its number; tells the caller if the slot was already its own. */
int AcquireEntitySlot(char *entity, void (*callback)(Slot_00329E90 *), int *out) {
    int tries, g, id, last;
    Slot_00329E90 *rec;

    for (tries = 0; tries < 2; tries++) {
        g = D_L00_001A902C[0];
        id = D_L00_00268E20[g].id;
        if (id == -1 || id == *(short *)(entity + 0xAA)) {
            *out = id != -1;
            D_L00_00268E20[g].id = *(short *)(entity + 0xAA);
            D_L00_00268E20[g].callback = callback;
            D_L00_001A902C[0] = (D_L00_001A902C[0] + 1) % 2;
            return g;
        }
        D_L00_001A902C[0] = (g + 1) % 2;
    }
    rec = &D_L00_00268E20[D_L00_001A902C[0]];
    if (rec->callback != 0)
        rec->callback(rec);
    last = D_L00_001A902C[0];
    *out = 0;
    D_L00_00268E20[last].id = *(short *)(entity + 0xAA);
    D_L00_00268E20[last].callback = callback;
    D_L00_001A902C[0] = (D_L00_001A902C[0] + 1) % 2;
    return last;
}
