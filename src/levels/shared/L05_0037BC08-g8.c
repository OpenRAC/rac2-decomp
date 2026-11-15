#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

/* The list of ids each object holds, and the table of live objects the ids index. */
extern unsigned short *D_L05_001FB220[];

/* The table of live objects, in the address the game keeps it at. */
extern int D_L05_001B251C;

/* The game's counters, of which the third counts the objects in flight. */
extern int D_L05_00221D10[];

extern char *moby_get_motion_data(char *);
extern void follower_set_state(char *, int);
extern void vec_clear_128(int);

extern int moby_is_in_use(char *);
extern int moby_get_link_value(char *);
extern void moby_clear_links(char *);

/* Walks the list of ids the object holds, and frees every id whose object is still free and
   belongs to the same group. */
void group_free_members_and_self(char *obj)
{
    unsigned short *p;
    int *child;
    int *parent;
    int off;
    short t;

    if (D_L05_001FB220[*(unsigned char *)(obj + 0x21)] == 0)
        return;
    parent = (int *)moby_get_motion_data(obj);
    p = D_L05_001FB220[*(unsigned char *)(obj + 0x21)];
    do {
        off = (*p & 0x7FFF) << 8;
        child = (int *)moby_get_motion_data((char *)(D_L05_001B251C + off));
        if (moby_is_in_use((char *)(D_L05_001B251C + off)) != 0
            && moby_get_link_value((char *)(D_L05_001B251C + off)) == 0
            && child[7] == parent[7]) {
            moby_clear_links((char *)(D_L05_001B251C + off));
            follower_set_state((char *)(D_L05_001B251C + off), 1);
        }
        t = *(short *)p;
        p++;
    } while (t >= 0);
    moby_clear_links(obj);
    follower_set_state(obj, 1);
    D_L05_00221D10[2]--;
}

/* Finds the object the list of ids names, and hands the object its place: the two objects
   swap their first two words, and the found one is emptied while the other is filled in. */
void group_swap_with_free_member(char *obj)
{
    unsigned short *p;
    int *child;
    int *parent;
    int *found;
    int addr;
    int off;
    short t;

    addr = 0;
    if (D_L05_001FB220[*(unsigned char *)(obj + 0x21)] == 0)
        return;
    parent = (int *)moby_get_motion_data(obj);
    p = D_L05_001FB220[*(unsigned char *)(obj + 0x21)];
    do {
        off = (*p & 0x7FFF) << 8;
        child = (int *)moby_get_motion_data((char *)(D_L05_001B251C + off));
        if (moby_is_in_use((char *)(D_L05_001B251C + off)) != 0
            && moby_get_link_value((char *)(D_L05_001B251C + off)) == 0
            && child[7] == parent[7]
            && child[8] == 1) {
            addr = D_L05_001B251C + off;
            break;
        }
        t = *(short *)p;
        p++;
    } while (t >= 0);
    found = (int *)moby_get_motion_data((char *)addr);
    *(TI128 *)parent = *(TI128 *)found;
    vec_clear_128((int)found);
    found[8] = 0;
    parent[8] = 1;
    found[4] = 0;
    parent[4] = addr;
    found[5] = 1;
    parent[5] = 0;
    found[6] = parent[6];
    parent[6] = -1;
    follower_set_state((char *)addr, 1);
}
