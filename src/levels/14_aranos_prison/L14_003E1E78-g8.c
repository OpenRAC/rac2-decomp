#include "common.h"

typedef struct {
    char pad00[0x5C];
    int flags;
    int proximity;
    int contact;
    int mobIndex;
    unsigned char *linked;
    int openTime;
    int activeTime;
    int closeTime;
    int timer;
    int requested;
    int color;
    int emitTimer;
} FieldState;

typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[3];
    char *model;
    char pad28[9];
    unsigned char active;
    char pad32[2];
    unsigned short flags;
    char pad36[0x32];
    FieldState *data;
    char pad6C[0xC];
    int color;
    char pad7C[0x1C];
    int animation;
} FieldMob;

extern void get_moby_color(void *, int *, int *, int *);
extern void set_moby_color(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(int *);
extern int FastTweenColor(int, int, float);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern int hero_is_current_selected_id(void *);
extern void moby_copy_pos_rot(void *, void *, void *);
extern void moby_pass_pos_rot_to_helper(void *, void *, void *);
extern void moby_rebuild_matrix_scaled(void *);
extern float moby_get_state_progress(void *);
extern void DrawFadingField(char *self);
extern void part_l14_spawn_flash(void *);

/* The level's entity array, read as a bare symbol (lui/lw) as in the level's other units. */
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
extern float g_hero_height_limit NOT_SDA;
extern FieldMob *g_field_mob_contact NOT_SDA;
extern int g_emitter_color_blue __attribute__((sda));
extern int g_emitter_color_green __attribute__((sda));
extern int g_emitter_color_red __attribute__((sda));
extern int g_emitter_emit_timer __attribute__((sda));

/* Widening after the three high-channel terms preserves the color grouping. */

/* A field that cycles off (1) -> rising (2) -> on (3) -> falling (4) -> off. Rising and
   falling run the same emitter, colour fade and draw (written out in both cases; the compiler
   cross-jumps the copies into one tail, as in retail); the on state can pass a request on to
   the linked entity when that is another field (class 0xAFE). */
/* Updates the moby of class 2814: an energy field that switches on and off. */
void UpdatePrisonEnergyField(FieldMob *self) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    int r, g, bl, c;
    FieldState *s = self->data;
    unsigned char *e;

    switch (self->state) {
    case 0:
        get_moby_color(self, &r, &g, &bl);
        s->color = (long long)(int)(0x80000000 + (bl << 16) + (g << 8)) + r;
        if (s->mobIndex != -1) {
            s->linked = D_L14_001B259C_base[0] + (s->mobIndex << 8);
        } else {
            s->linked = 0;
        }
        s->requested = 0;
        self->color = 0x80008000;
        self->flags |= 0x10;
        if (s->proximity) {
            moby_set_state(self, 3, -1);
        } else {
            moby_set_state(self, 1, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(self)) {
            self->flags |= 0x100;
            s->requested = 0;
            s->flags = 0;
            self->color = 0x80000080;
            s->emitTimer = g_emitter_emit_timer;
            s->timer = s->closeTime;
            s->requested = 0;
        }
        if (math_fast_float_d(&s->timer)) {
            moby_set_state(self, 1, -1);
        }
        if (math_fast_float_d(&s->emitTimer)) {
            part_l14_spawn_flash(self);
            s->emitTimer = g_emitter_emit_timer;
        }
        c = (long long)(int)(0xFF000000 | (g_emitter_color_red << 16) | (g_emitter_color_green << 8)) | g_emitter_color_blue;
        c = FastTweenColor(c, s->color, moby_get_state_progress(self));
        set_moby_color(self, c & 0xFF, (c >> 8) & 0xFF, (c >> 16) & 0xFF);
        moby_copy_pos_rot(self, a, b);
        moby_rebuild_matrix_scaled(self);
        moby_pass_pos_rot_to_helper(self, a, b);
        gfx_add_draw_callback_third(DrawFadingField, (char *)self);
        break;
    case 1:
        if (flag_set_first_pending(self)) {
            self->active = 0;
            self->animation = 0;
            self->flags |= 1;
        }
        if (s->requested || (s->proximity && self->position[2] > g_hero_height_limit)) {
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(self)) {
            self->active = 1;
            self->flags = (self->flags | 0x100) & 0xFFFE;
            self->animation = *(int *)(self->model + 0x10);
            s->emitTimer = g_emitter_emit_timer;
            s->timer = s->openTime;
        }
        if (math_fast_float_d(&s->timer)) {
            moby_set_state(self, 3, -1);
        }
        if (math_fast_float_d(&s->emitTimer)) {
            part_l14_spawn_flash(self);
            s->emitTimer = g_emitter_emit_timer;
        }
        c = (long long)(int)(0xFF000000 | (g_emitter_color_red << 16) | (g_emitter_color_green << 8)) | g_emitter_color_blue;
        c = FastTweenColor(c, s->color, moby_get_state_progress(self));
        set_moby_color(self, c & 0xFF, (c >> 8) & 0xFF, (c >> 16) & 0xFF);
        moby_copy_pos_rot(self, a, b);
        moby_rebuild_matrix_scaled(self);
        moby_pass_pos_rot_to_helper(self, a, b);
        gfx_add_draw_callback_third(DrawFadingField, (char *)self);
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            self->flags &= 0xFEFF;
            if (s->contact) {
                s->flags |= 0x20;
            } else {
                s->flags |= 1;
            }
            s->timer = s->activeTime;
            self->color = 0x80008000;
        }
        if ((hero_is_current_selected_id(self) && !s->contact) || (g_field_mob_contact == self && s->contact)) {
            e = s->linked;
            if (e != 0 && *(short *)(e + 0xAA) == 0xAFE /* moby class 2814 */) {
                *(int *)(*(char **)(e + 0x68) + 0x80) = 1;
            }
        }
        if (s->proximity && self->position[2] > g_hero_height_limit) {
            s->timer = s->activeTime;
        }
        if (math_fast_float_d(&s->timer)) {
            moby_set_state(self, 4, -1);
        }
        break;
    }
}

