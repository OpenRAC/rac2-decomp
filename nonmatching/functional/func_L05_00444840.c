/* functional: high. From the near-miss draft (complete C, scheduling differs); same reads, writes and calls in retail's order; the level copy of func_002761F8 (05:002F6C50) is what retail calls. */
#include "common.h"
extern void func_L05_00444D60(void *, int *, int *, int);
extern int func_002AB1F0(u8 *);
extern int func_00282C30(int);
extern float func_00283CE0(int);
extern float func_00282E48(void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern u8 *D_L05_001FB5E0[];
typedef struct { int object_class, screen_range; float world_range; } TargetRule;
extern TargetRule D_L05_002B87F0[];
extern float D_L05_001B1B1C_gp SDATA(D_L05_001B1B1C);
extern float D_L05_001B1B18_gp SDATA(D_L05_001B1B18);
extern int D_001A79F0 NOT_SDA;
extern float D_L05_001B96C0[];
extern int D_L05_001B2048 NOT_SDA;

static __inline__ int target_class(u8 *object)
{
    if (object && *(u8 **)(object + 0x24))
        return *(s16 *)(*(u8 **)(object + 0x24) + 0x46);
    return 0;
}

/* Grid outputs are four separate32-bit words. The rule table has real12-byte
 * rows terminated by class-1; neither rule nor object-list extent is invented.
 * The parameter accessor returns a32-bit target address, matching its C def. */
u8 *func_L05_00444840(void *position, u8 **excluded, u8 *current)
{
    int source_x, source_y, target_x, target_y;
    int i, kind, range;
    float dx, dy, distance;
    u8 **cursor, *object, *parameters;
    TargetRule *rule;
    func_L05_00444D60(position, &source_x, &source_y, 0);
    cursor = D_L05_001FB5E0;
    while ((object = *cursor) != 0) {
        if (!object[0x31])
            goto next;
        parameters = (u8 *)func_002AB1F0(object);
        if (!parameters || *(float *)parameters <= 0.0f)
            goto next;
        kind = target_class(object);
        if (kind != 5 && kind != 15)
            goto next;
        if (excluded) {
            for (i = 0; excluded[i] && excluded[i] != object; i++) {}
            if (excluded[i])
                goto next;
        }
        func_L05_00444D60(object + 0x10, &target_x, &target_y, 0);
        dx = func_00283CE0(func_00282C30(target_x - source_x));
        dy = func_00283CE0(func_00282C30(target_y - source_y));
        range = 40;
        for (rule = D_L05_002B87F0; rule->object_class != -1; rule++) {
            if (rule->object_class == *(s16 *)(object + 0xAA)) {
                range = rule->screen_range;
                break;
            }
        }
        if (!(dx < D_L05_001B1B1C_gp + (float)range) || !(dy < D_L05_001B1B1C_gp + (float)range))
            goto next;
        distance = D_L05_001B1B18_gp;
        for (rule = D_L05_002B87F0; rule->object_class != -1; rule++) {
            if (rule->object_class == *(s16 *)(object + 0xAA)) {
                distance = rule->world_range;
                break;
            }
        }
        if (D_001A79F0 != 20 && distance < func_00282E48(D_L05_001B96C0, object + 0x10))
            goto next;
        if (current && current == object && D_L05_001B2048 % 3 != 0)
            return object;
        if (!func_002761F8(D_L05_001B96C0, object + 0x10, 16, object, 0))
            return object;
next:
        cursor++;
    }
    return 0;
}
