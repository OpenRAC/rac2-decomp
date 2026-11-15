#include "names.h"
/* Applies trigger and timer commands to the object, its parent and its two linked parts. */
#include "common.h"
extern int coll_point_inside_region(void *, int);
extern int trooper_legs_count_with_value(void *, int);
extern int FastDecTimer(void *);
extern void STUB_printf(const char *, ...);
extern int moby_fuse_linked_objects(void *, void *, void *, char **, int);
extern char g_hero_position[];
extern char D_L09_001B10E0[];
extern int D_L09_001B2388[] __attribute__((sda));
typedef struct ActivationState ActivationState;
typedef struct ActivationClass {
    char pad00[0x10];
    int update;
} ActivationClass;
typedef struct ActivationObject {
    char pad00[0x20];
    u8 status;
    char pad21[3];
    ActivationClass *type;
    char pad28[8];
    u8 group, enabled;
    char pad32[2];
    u16 flags;
    char pad36[0x32];
    ActivationState *state;
    char pad6C[0x29];
    u8 command;
    char pad96[2];
    int update;
    char pad9C[0xE];
    short class_code;
    char padAC[6];
    short id;
} ActivationObject;
struct ActivationState {
    char pad00[0x2F0];
    ActivationObject *parts[2];
    ActivationObject *parent;
    char pad2FC[4];
    short timer;
    u8 flags;
    char pad303[0x11];
    int trigger;
    char pad318[4];
    s8 command;
    u8 disabled, group, mode;
    char pad320[0x100];
    int threshold_arg;
    char pad424[8];
    int threshold;
};
/* Turns the enemy and its linked parts on or off when a trigger or timer says so. */
int enemy_process_activation(ActivationObject *obj)
{
    ActivationState *s = obj->state;
    if (s->group && obj->group == 255) obj->group = s->group;
    if (s->trigger != -1 && !obj->command) {
        if (!coll_point_inside_region(g_hero_position, s->trigger)) {
            if (!s->disabled) s->command = -2;
            else if (s->command == -2) s->command = 0;
        } else if ((!s->mode || ((s->flags^1) & 1)) && !s->command) s->command = 1;
    }
    if (s->flags & 2) {
        if (trooper_legs_count_with_value(obj, s->threshold_arg) < s->threshold) { s->command = 0; return 1; }
        if (FastDecTimer(&s->timer)) s->command = 1;
        else s->command = 0;
    }
    if (s->command < 0) {
        if (!s->disabled) {
            ActivationObject *p;
            int i;
            obj->enabled = 0;
            obj->flags |= 1;
            obj->update = 0;
            p = s->parent;
            if (p && p->class_code == MOBY_CLASS_MEGACORP_TROOPER_TORSO && p->status != 0xFE && p->status != 0xFD) {
                p->flags |= 1;
                s->parent->enabled = 0;
                s->parent->update = 0;
            }
            for (i = 0; i < 2; ++i) {
                ActivationObject *part = s->parts[i];
                if (part && part->class_code == 0xD66 /* moby class 3430 */ && part->status != 0xFE && part->status != 0xFD) {
                    part->flags |= 1;
                    s->parts[i]->enabled = 0;
                }
            }
        }
        s->disabled = 1;
        if (s->command == -2) s->command = 0;
        return 1;
    } else if (s->command > 0) {
        if (s->disabled) {
            ActivationObject *p;
            int i;
            s->disabled = 0;
            s->command = 0;
            STUB_printf(D_L09_001B10E0, D_L09_001B2388[0], obj->id, 0);
            obj->flags &= ~1;
            obj->enabled = 1;
            obj->update = obj->type->update;
            obj->flags |= 0x1000;
            p = s->parent;
            if (p && p->class_code == MOBY_CLASS_MEGACORP_TROOPER_TORSO && p->status != 0xFE && p->status != 0xFD) {
                p->flags &= ~1;
                s->parent->enabled = 1;
                s->parent->update = s->parent->type->update;
                s->parent->flags |= 0x1000;
            }
            for (i = 0; i < 2; ++i) {
                ActivationObject *part = s->parts[i];
                if (part && part->class_code == 0xD66 /* moby class 3430 */ && part->status != 0xFE && part->status != 0xFD) {
                    part->flags &= ~1;
                    s->parts[i]->enabled = 1;
                }
            }
            moby_fuse_linked_objects(obj, (char *)obj + 0x10, (char *)obj + 0xF0, (char **)s->parts, 3);
        }
    } else if (s->disabled) {
        if (s->command == -2) s->command = 0;
        return 1;
    }
    if (s->command == -2) s->command = 0;
    return 0;
}
