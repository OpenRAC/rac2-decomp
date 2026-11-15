/* func_PAL_0028C7C8, the PAL copy of func_0028BE00: the same C, where the timeout becomes 150 and the frame record is scaled to 50 Hz. */
#include "common.h"

typedef struct { char pad[0x14]; int name; char pad18[0x70]; unsigned short valid; char pad8a[4]; unsigned short ammo; char pad90[0x50]; } Info;
typedef struct { char pad[0x148]; float x, y; char pad150[0x70]; int held, pressed, pad1c8, inhibit, pad1d0, pad1d4, repeat; } Controller;
typedef struct { char pad[0xf0]; unsigned short uses; char padf2[2]; unsigned int maxFrame, levels; } Stats;
typedef struct { char pad[0x1248]; int selected; char pad124c[0x107c]; int pending; } Hero;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; } Slot;
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

extern int g_notice_owner;
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_001A8CFC;
extern int D_001A8D30 __attribute__((sda));
extern int g_radial_menu_page_index __attribute__((sda));
extern int D_001A8D90[] __attribute__((sda));
extern int g_radial_slot_count;
extern Slot **g_radial_menu_pages;
extern float D_001A8E10;
extern int D_001B1900;
extern int D_001B18FC;
extern int D_001B1598, D_001B18F8;
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
extern Info g_weapon_table[];
extern Controller g_pad_state;
extern char D_0018C316[];
extern char D_001A8E18[];
extern Stats g_progress_statistics;
extern Hero g_hero_state;
extern unsigned int D_001A7390;
extern int g_current_map_index;
extern short D_001A63AC NOT_SDA;
extern int menu_is_state_seven(void), hud_is_open_done(void);
extern void hud_request_open(void), menu_set_state_word_three(void);
extern void func_PAL_0034ED50(void *, int);
extern int FastDecTimer(void *);
extern float square_root(float), mat_fast_helper_a(float, float), IntToFloat(int), fast_subtract_rotations(float, float), FastDiffRots(float, float), math_fast_float_g(float);
extern int FloatToInt(float);
extern void STUB_printf(void *), load_request_disc_read_break(void), snd_play_from_global_bank(int, int, int);
extern int load_is_class_cached(int);
extern void LoadClassIntoFreeCacheSlot(int), menu_advance_state_in_mode_seven(void), hud_clear_flag_b(void), hud_clear_flag_a(void);
extern int hud_close_element_by_key(int);

static inline Info *InfoOf(int id)
{
    return &g_weapon_table[g_item_slot_to_record[id]];
}

void func_PAL_0028C7C8(Selector *p)
{
    float x, y, mag, ang, a, f, r;
    int old, n, s, k, id;
    int active;
    unsigned char *c, *e;

    if (g_notice_owner) return;
    active = 0;
    if (!D_001A7BB0[3] || menu_is_state_seven() || !D_001A7BB0[3]) {
        active = 1;
        if (!D_001A7BB0[3]) {
            hud_request_open();
            if (!hud_is_open_done()) active = 0;
        }
    }
    e = p->fade;
    if (active && D_001A8CFC) {
        func_PAL_0034ED50((char *)D_001A8CFC + 0x376C8, menu_is_state_seven() ? D_001A8D30 : 2);
        menu_set_state_word_three();
    }
    p->timeout = 150;
    p->timer = 24;
    if (FastDecTimer(D_0018C316) && !D_001A7BB0[3]) g_pad_state.inhibit = 2;
    x = g_pad_state.x;
    y = g_pad_state.y;
    mag = square_root(x * x + y * y);
    if (mag != 0.0f) {
        x /= mag;
        y /= mag;
    }
    ang = mat_fast_helper_a(x, y);
    if ((p->state >> 24) == 0) {
        if ((g_pad_state.pressed & 0xF000) || mag < 0.5f || --p->state == -1) {
            p->selected = -1;
            p->state = 0x10000FF;
        }
    }
    n = 0;
    old = p->selected;
    if ((p->state >> 24) == 1 && (g_pad_state.held & 0x10) && active) {
        if (mag > 0.9f) {
            a = ang + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)g_radial_slot_count;
            f = a * 0.15915494f * (float)g_radial_slot_count;
            r = (float)old * 6.2831855f / IntToFloat(g_radial_slot_count) - 3.1415927f;
            if (old == -1 || FastDiffRots(r, fast_subtract_rotations(ang, 1.5707964f)) > 0.5890487f) {
                s = (int)f % g_radial_slot_count;
                if ((s ^ 1) & 1) {
                    float fr = f - (float)FloatToInt(f);
                    if (fr > 0.8f) s++;
                    else if (fr < 0.2f) s--;
                    s = (s + g_radial_slot_count) % g_radial_slot_count;
                }
                p->selected = s;
                n = -1;
                D_001A8E10 = math_fast_float_g(a - ((float)s * 0.78539824f + 0.39269912f));
                if (D_001A8E10 > 0.0f) n = 1;
            }
        } else if (g_pad_state.repeat == 0 && (g_pad_state.pressed & 0xF000)) {
            int w;
            w = old;
            if (g_pad_state.pressed & 0x1000) {
                int t;
                if (w == -1) t = D_001A8D90[4];
                else t = g_radial_menu_pages[g_radial_menu_page_index][w].f10;
                w = t;
            }
            if (g_pad_state.pressed & 0x4000) {
                int t;
                if (w == -1) t = D_001A8D90[5];
                else t = g_radial_menu_pages[g_radial_menu_page_index][w].f14;
                w = t;
            }
            if (g_pad_state.pressed & 0x8000) {
                int t;
                if (w == -1) t = D_001A8D90[2];
                else t = g_radial_menu_pages[g_radial_menu_page_index][w].f8;
                w = t;
            }
            if (g_pad_state.pressed & 0x2000) {
                int t;
                if (w == -1) t = D_001A8D90[3];
                else t = g_radial_menu_pages[g_radial_menu_page_index][w].fC;
                w = t;
            }
            p->selected = w;
        }
        {
            Slot *t = g_radial_menu_pages[g_radial_menu_page_index];
            int cur = p->selected;
            if (t[cur].f0 == 0 && n != 0) {
                k = (cur + n) % g_radial_slot_count;
                if (t[k].f0 != 0) p->selected = k;
            }
        }
    }
    c = p->fade;
    if (p->selected != old) {
        STUB_printf(D_001A8E18);
        load_request_disc_read_break();
        c[1] = 0;
        snd_play_from_global_bank(3, 0, 0);
    } else if (c[1] < 8) c[1]++;
    if (p->selected >= 0 && !load_is_class_cached(InfoOf(g_radial_menu_pages[g_radial_menu_page_index][p->selected].f18)->name)) {
        LoadClassIntoFreeCacheSlot(InfoOf(g_radial_menu_pages[g_radial_menu_page_index][p->selected].f18)->name);
    } else {
        if (!(g_pad_state.held & 0x10) && !D_001A63AC) {
            if (c[0]) c[0]--;
            if (c[0] == 0 && p->selected >= 0 && (id = g_radial_menu_pages[g_radial_menu_page_index][p->selected].f18) != 0) {
                Info *rr;
                if (g_hero_state.selected != id && g_progress_statistics.uses < 0xFFFF) g_progress_statistics.uses++;
                if (g_progress_statistics.maxFrame < ((s32)(D_001A7390) * 5 + 2) / 6) g_progress_statistics.maxFrame = ((s32)(D_001A7390) * 5 + 2) / 6;
                g_progress_statistics.levels = g_progress_statistics.levels | (1 << g_current_map_index) | 0x80000000;
                g_hero_state.pending = id;
                rr = InfoOf(id);
                if (rr->valid && rr->ammo < g_item_ammo_counts[id]) g_item_ammo_counts[id] = rr->ammo;
            }
            if (D_001A7BB0[3]) menu_advance_state_in_mode_seven();
            else {
                hud_clear_flag_b();
                hud_clear_flag_a();
            }
        } else if (c[0] < 8) c[0]++;
    }
    if (e[0] == 0) {
        {
            int state = p->state;
            D_001B1900 = p->selected;
            D_001B18FC = state;
        }
        hud_close_element_by_key(p->handle);
        p->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
