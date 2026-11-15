#include "names.h"
extern unsigned short *D_L05_001FB220[];
extern unsigned char *D_L05_001B251C __attribute__((sda));
extern int moby_get_motion_data(unsigned char *);

/* Count initialized entries in the tagged list; the last entry has bit15 set. */
int list_count_ready_objects(unsigned char *object) {
    void *head = D_L05_001FB220[object[0x21]];
    unsigned short *entry;
    int count = 0;
    int next;
    unsigned char *state;
    if (head == 0) return 0;
    entry = (unsigned short *)head;
    do {
        state = (unsigned char *)moby_get_motion_data(D_L05_001B251C + ((*entry & 0x7FFF) << 8));
        if (state) {
            next = count + 1;
            count = *(int *)(state + 0x110) != 1 ? count : next;
        }
    } while ((short)*entry++ >= 0);
    return count;
}
