/* func_00335960 - 360 bytes.  Worker attempt, 27 October 2026 (draft below).

   Close: first 22 insns match. Mine 316 B vs 360 B. Differences:
   - retail copies list ptr to $t0 (daddu t0,a2) and loads mode (lw 0x14(t0))
   AFTER the loop; mine loads mode early into $t0.
   - retail loop is fully rotated: header peeled (beqz a3; lw next; beql; c.le
   key,time), body, then i++/sltu/next/key re-test, a2=v1 in delay slot of
   back branch. Mine does `b` into the middle (shared tail), 44 B shorter.
   Tried: for-loop with break, while with split ifs, while(i<count && b->next
   && b->key<=time). All give the same jump-into-middle shape. mode test as
   `<0` then `<2` vs combined: retail is bltz + slti (separate). */

typedef struct KeyNode {
    struct KeyNode *next;
    int pad4;
    float key;
    float value[4];
} KeyNode;

typedef struct KeyList {
    int pad0[3];
    KeyNode *first;
    unsigned int count;
    int mode;
} KeyList;

typedef struct KeyOwner {
    int pad0[2];
    KeyList *list;
} KeyOwner;

void func_00335960(KeyOwner *owner, float *out, float time)
{
    KeyList *list = owner->list;
    KeyNode *a;
    KeyNode *b;
    unsigned int i;
    float t, w;

    if (list->count == 0)
        return;
    if (list->count == 1) {
        out[0] = owner->list->first->value[0];
        out[1] = owner->list->first->value[1];
        out[2] = owner->list->first->value[2];
        out[3] = owner->list->first->value[3];
        return;
    }
    a = b = list->first;
    i = 0;
    while (i < list->count && b->next != 0 && b->key <= time) {
        a = b;
        b = b->next;
        i++;
    }
    t = (time - a->key) / (b->key - a->key);
    if (list->mode < 0)
        return;
    if (list->mode < 2) {
        w = 1.0f - t;
        out[0] = w * a->value[0] + t * b->value[0];
        out[1] = w * a->value[1] + t * b->value[1];
        out[2] = w * a->value[2] + t * b->value[2];
        out[3] = w * a->value[3] + t * b->value[3];
    }
}
