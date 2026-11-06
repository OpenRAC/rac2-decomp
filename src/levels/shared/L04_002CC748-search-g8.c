/* The -G8 sibling of L04_002CC748.c for the target search: the moby list count is read through
   $gp as well as through its absolute address. */
#include "common.h"
#define WBYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p,o) (*(short *)((char *)(p)+(o)))
typedef struct {
    float pos[4], velocity[4], previous[4], next[4];
    char *moby;
    int result;
} SearchOutput;
typedef struct {
    char pad[0x2290];
    char *moby;
    int state;
    int lastState;
    int mode;
} SearchHero;
extern SearchHero D_00189E20;
extern short D_L04_001B2630[] MACRO_ADDR __attribute__((sda));
extern char *D_L04_001B24DC;
extern int func_002ACBC8(void *, int);
extern int func_002A8AF0(void *, void *, int);
extern float func_00282E80(void *, void *);

/* Picks the hero, or the closest listed moby of class 0xCB or 0x76C in state 3 that lies within
   distance and passes the area (or region) tests, and fills out with its position and motion.
   Returns 0 for the hero, 1 for a moby and 2 when neither qualifies. */
int func_L04_003429F8(char *source, SearchOutput *out, int *areas, int count, void *region,
                      int regionCount, float distance)
{
    char *best = D_00189E20.moby;
    int result = 0;
    char *velocity, *previous, *next;
    int i, j, valid;
    char *m;
    float d;

    if (D_00189E20.mode == 24 || D_00189E20.state == 0x6F) {
        best = 0;
        result = 2;
        velocity = (char *)out->velocity;
        previous = (char *)out->previous;
        next = (char *)out->next;
    } else if (count > 0) {
        int i, limit;

        i = 0;
        limit = count - 1;
        do {
            velocity = (char *)out->velocity;
            previous = (char *)out->previous;
            next = (char *)out->next;
        } while (0);
        for (; i < limit; i++) {
            if (func_002ACBC8((char *)&D_00189E20 + 0x80, areas[i])) {
                best = 0;
                result = 2;
                break;
            }
        }
    } else {
        velocity = (char *)out->velocity;
        previous = (char *)out->previous;
        next = (char *)out->next;
        if (region && regionCount > 0
            && !func_002A8AF0((char *)&D_00189E20 + 0x80, region, regionCount)) {
            best = 0;
            result = 2;
        }
    }
    for (j = 1; j <= D_L04_001B2630[0]; j++) {
        m = D_L04_001B24DC + (D_L04_001B2630[j] << 8);
        if (m && (WSHORT(m, 0xAA) == 0xCB || WSHORT(m, 0xAA) == 0x76C) && WBYTE(m, 0x20) != 0xFE
            && WBYTE(m, 0x20) != 0xFD && WBYTE(m, 0x20) == 3) {
            valid = 1;
            d = func_00282E80(source + 0x10, m + 0x10);
            if (distance <= d) {
                valid = 0;
            } else if (count > 0) {
                for (i = 0; i < count - 1; i++) {
                    if (func_002ACBC8(m + 0x10, areas[i])) {
                        valid = 0;
                        break;
                    }
                }
            } else if (region && regionCount > 0 && !func_002A8AF0(m + 0x10, region, regionCount)) {
                valid = 0;
            }
            if (valid) {
                result = 1;
                best = m;
                distance = d;
            }
        }
    }
    if (best) {
        out->moby = best;
        qcopy(out, best + 0x10);
        qcopy(velocity, best + 0xF0);
        if (best == D_00189E20.moby) {
            qcopy(previous, (char *)&D_00189E20 + 0xD0);
            qcopy(next, (char *)&D_00189E20 + 0xE0);
        } else {
            qcopy(next, out);
            out->next[2] += 0.6f;
            qcopy(previous, next);
        }
    } else {
        out->moby = 0;
        qzero(out);
        qzero(velocity);
        qzero(next);
        qzero(previous);
    }
    out->result = result;
    return result;
}
