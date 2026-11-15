#include "include_asm.h"
#include "common.h"

/* func_002BABE8 is in 002B7E28-g8.c.

   It reads the game-time word D_001B1688, whose retail access is the pair
   `lui $v0,%hi(D_001B1688)` / `lw $v0,%lo(D_001B1688)($v0)`: one register for the
   address and the loaded word.  A file built with -G8 (config/cflags.txt) makes the
   compiler emit a bare symbol reference, which the assembler expands into that
   pair; a -G0 unit emits `lui`/`lw` with two different registers instead.  The
   same file holds the clear of the fixed-address word at 0x10000000, which the
   retail reaches through its own `lui`/`sw` pair. */

extern int g_game_time;

/* The fixed-address word the particle update clears.  Its address is the same in
   every program, so it is named after the address; the incomplete array keeps it
   out of the small-data pool, which is what makes the compiler split the address
   into the retail's `lui`/`sw` pair. */
extern int D_10000000[];

extern void vec_decode_byte_color(char *dst, char *src);

extern void FastVecAdd(char *dst, char *a, char *b);

extern float IntToFloat(int a);

extern int FastTweenColor(int a, int b, float f);

extern int FastDecTimer(short *p);

extern void lerp_vector(float *out, char *a, char *b, float f);

extern void part_kill(void *p);

typedef struct {
    float v[4];
} Vec4_002BABE8;

/* Updates one animated effect each frame: moves it, and blends its color and size through its fade-in, hold and fade-out phases. */
void part_update_fading_effect(char *self)
{
    char *effect = self;
    char *anim = self + 0x20;
    Vec4_002BABE8 step, from_step, to_step;
    float progress;

    if (g_game_time & 1) {
        *(unsigned char *)(effect + 8) = *(unsigned char *)(effect + 8) + 1;
    }
    if (*(short *)(anim + 0x10) != 0) {
        D_10000000[0] = 0;
        vec_decode_byte_color((char *)&step, anim);
        FastVecAdd(effect + 0x10, effect + 0x10, (char *)&step);
        progress = IntToFloat(*(short *)(effect + 0xA)) / IntToFloat(*(short *)(anim + 0x10));
        *(int *)(effect + 4) = FastTweenColor(*(int *)(anim + 8) & 0xFFFFFF, *(int *)(anim + 8), 1.0f - progress);
        *(float *)(effect + 0xC) = (float)(*(short *)(anim + 0x16) * 1000);
        if (FastDecTimer((short *)(effect + 0xA)) != 0) {
            *(short *)(anim + 0x10) = 0;
            *(short *)(effect + 0xA) = *(unsigned short *)(anim + 0x12);
        }
    } else if (*(short *)(anim + 0x12) != 0) {
        vec_decode_byte_color((char *)&from_step, anim);
        vec_decode_byte_color((char *)&to_step, effect + 0x24);
        progress = IntToFloat(*(short *)(effect + 0xA)) / IntToFloat(*(short *)(anim + 0x12));
        lerp_vector((float *)&step, (char *)&to_step, (char *)&from_step, progress);
        FastVecAdd(effect + 0x10, effect + 0x10, (char *)&step);
        *(float *)(effect + 0xC) = ((float)(*(short *)(anim + 0x16) - *(short *)(anim + 0x18)) * progress
                               + (float)*(short *)(anim + 0x18)) * 1000.0f;
        *(int *)(effect + 4) = FastTweenColor(*(int *)(anim + 0xC), *(int *)(anim + 8), progress);
        if (FastDecTimer((short *)(effect + 0xA)) != 0) {
            *(short *)(anim + 0x12) = 0;
            *(short *)(effect + 0xA) = *(unsigned short *)(anim + 0x14);
        }
    } else {
        vec_decode_byte_color((char *)&step, effect + 0x24);
        FastVecAdd(effect + 0x10, effect + 0x10, (char *)&step);
        *(int *)(effect + 4) = FastTweenColor(*(int *)(anim + 0xC) & 0xFFFFFF, *(int *)(anim + 0xC),
                                         IntToFloat(*(short *)(effect + 0xA))
                                             / IntToFloat(*(short *)(anim + 0x14)));
        *(float *)(effect + 0xC) = (float)(*(short *)(anim + 0x18) * 1000);
        if (FastDecTimer((short *)(effect + 0xA)) != 0) {
            part_kill(effect);
        }
    }
}

/* One step of a dialogue script: a node array of 28-byte records, the current node
   index at +0x36 of the script state. */
typedef struct {
    int message;
    unsigned short sound;
    short next;
    short kind;
    short arg;
    short ifTrue;
    short ifFalse;
    unsigned short flags;
    char pad12[0xA];
} DialogNode_002B8108;

typedef struct {
    char pad0[4];
    short prev;
    char pad6[2];
    unsigned char skippable;
    char pad9[0x2D];
    short cur;
    int startTime;
    DialogNode_002B8108 *nodes;
} DialogState_002B8108;

typedef struct {
    char *s[6];
} Separators_002B8108;

typedef struct {
    char pad0[0x80];
    int cost;
    char pad84[0x10];
    unsigned short price;
    char pad96[0x4A];
} ClassRecord_002B8108;

/* The talking moby, its dialogue state and the message on screen: 002F5220-g8.c
   reads the moby and state fields of the same block.  Being one aggregate (not
   three scalars) is what keeps retail's stores ahead of the following node loads. */
typedef struct { int unk0; char *moby; void *data; int unkC; int message; } DialogTalk_002B8108;
extern DialogTalk_002B8108 D_001B178C MACRO_ADDR;
extern int D_001AA2B8 __attribute__((sda));
extern Separators_002B8108 D_001AA250;
extern char D_001AA278[];
extern char D_001AA288[];
extern int g_player_bolts;
extern short D_001A7A1A;
extern unsigned char D_001A7BB4;
extern unsigned char g_item_slot_to_record[];
extern ClassRecord_002B8108 g_weapon_table[];
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern unsigned char D_001A7B30[] MACRO_ADDR;

extern int request_begin_slot(int, int, int, int, int);
extern int save_count_items_above_baseline(void);
extern void hud_play_sound_effect(char *);
extern int hud_close_element_by_key(int);
extern char *GetLocalizedString(int);
extern char *strcpy(char *, const char *);
extern char *strstr(const char *, const char *);
extern int sprintf(char *, const char *, ...);

/* The class-record lookups are written index-first, i[D_00139568] and
   (j)[D_00239BA0]: retail adds each index to its base in that operand order
   (blocker 28), which is also what orders the loads in the switch cases. */
/* Runs one step of a dialogue script: shows the current line, checks its condition and moves on to the next line. */
void cutscene_run_dialogue_node(char *owner, DialogState_002B8108 *st, int enter)
{
    DialogNode_002B8108 *node = &st->nodes[st->cur];
    char text[0x100];
    Separators_002B8108 seps;
    char number[0x20];
    short kind;
    int cond;
    short next;

    if (st->nodes == 0) {
        return;
    }
    if (enter) {
        st->prev = st->cur;
        st->startTime = g_game_time;
        if (st->cur != node->next) {
            unsigned short flags = node->flags;
            st->cur = node->next;
            node = &st->nodes[st->cur];
            st->skippable = node->flags & 1;
            if (flags & 4) {
                unsigned short sound;
                D_001B178C.moby = owner;
                D_001B178C.data = st;
                sound = node->sound;
                if (sound & 0x4000) {
                    request_begin_slot(1, 1, 0, (short)(sound ^ 0x4000), 0);
                } else {
                    request_begin_slot(2, 1, (short)sound, 0, 0);
                }
            }
        }
    }
    if (st->cur == -1) {
        return;
    }
    D_001B178C.message = node->message;
    kind = node->kind;
    if (kind == 6) {
        seps = D_001AA250;
        strcpy((char *)0x70000000, GetLocalizedString(node->message));
        {
            char *p = strstr((char *)0x70000000, D_001AA288);
            if (p != 0) {
                p[1] = 's';
            }
        }
        {
            int price = (node->arg[g_item_slot_to_record])[g_weapon_table].price;
            sprintf(number, D_001AA278, price / 1000, seps.s[D_001A7BB4 % 6], price % 1000);
        }
        sprintf(text, (char *)0x70000000, number);
    } else {
        sprintf(text, GetLocalizedString(node->message));
    }
    if (D_001B178C.message != 0) {
        hud_play_sound_effect(text);
    } else if (D_001AA2B8 != -1) {
        hud_close_element_by_key(D_001AA2B8);
        D_001AA2B8 = -1;
    }
    if (node->kind == 0) {
        return;
    }
    switch (node->kind) {
    case 1:
        cond = g_player_bolts >= (node->arg[g_item_slot_to_record])[g_weapon_table].cost;
        break;
    case 2:
        cond = g_item_owned_flags[node->arg] != 0;
        break;
    case 3:
        cond = g_item_owned_flags[node->arg] != 0 && D_001A7B30[node->arg] == 0;
        break;
    case 5:
        cond = save_count_items_above_baseline() >= node->arg;
        break;
    case 6:
        cond = g_player_bolts >= (node->arg[g_item_slot_to_record])[g_weapon_table].price && save_count_items_above_baseline() >= 4;
        break;
    case 7:
        cond = D_001A7A1A >= node->arg;
        break;
    default:
        cond = 0;
        break;
    }
    if (cond) {
        next = node->ifTrue;
    } else {
        next = node->ifFalse;
    }
    if (next != st->cur) {
        st->cur = next;
        st->startTime = g_game_time;
        node = &st->nodes[next];
        st->skippable = node->flags & 1;
        cutscene_run_dialogue_node(owner, st, 0);
    }
}

/* func_002B85F8 (RAC1 pad.c: poll_pad_device_state): reads one pad's socket state,
   fetches its button and actuator profiles once the pad is connected, then each
   frame reads the buttons and sends the two vibration levels.  The store of the
   "pad 0 disconnected" flag is a bare -G8 symbol reference, which the assembler
   expands into retail's lui/sw pair through $at. */

extern int scePad2GetState(int socket);
extern int pad_read_button_mask(int socket, void *profile);
extern int func_00128F50(int socket, void *profile);
extern int func_00128A50(int socket, void *data);
extern int sceVibSetActParam(int socket, int profile_size, void *profile, int data_size, void *data);
extern void ClearPadInput(void *pad);
extern void pad_decode_reading(void *pad, void *data, int size);
extern int D_001A7428;

typedef struct {
    unsigned char pad0[0x180];
    unsigned char profile[4];
    unsigned char act[4];
    unsigned char vibration0;
    unsigned char vibration1;
    unsigned char pad18a[10];
    int socket;
    int profile_state;
    int device_state;
    int held, pressed, released, prev_held;
    int raw_held, raw_pressed, raw_released, prev_raw_held;
    unsigned char pad1c0[0x1C];
    int profile_mask;
    unsigned char pad1e0[0x168];
    int latched_held;
} PadPollState;

extern PadPollState g_pad_state;

/* Reads the state of one controller each frame, fetching its button and vibration profile when it connects, and sends the vibration levels. */
void poll_pad_device_state(void *pad_arg)
{
    PadPollState *p = pad_arg;
    unsigned char buf[64];
    short vibration;
    int status, n, i;

    p->held = 0;
    p->prev_held = p->latched_held;
    p->prev_raw_held = p->raw_held;
    p->raw_held = 0;
    status = scePad2GetState(p->socket);
    p->device_state = status;
    if (status == 1) {
        switch (p->profile_state) {
        case 0: {
            int n;

            n = pad_read_button_mask(p->socket, buf);
            if (*(unsigned int *)buf == 0xFFFFFFFF)
                p->profile_mask = 0x79;
            else
                p->profile_mask = 0;
            if (n < 5) {
                for (i = 0; i < n; i++)
                    p->profile[i] = buf[i];
                p->profile_state = 1;
            } else {
                p->profile_state = 2;
                n = 0;
            }
            for (i = n; i < 4; i++)
                p->profile[i] = buf[i];
            n = func_00128F50(p->socket, buf);
            if (n < 5) {
                for (i = 0; i < n; i++)
                    p->act[i] = buf[i];
            } else {
                n = 0;
            }
            for (i = n; i < 4; i++)
                p->act[i] = buf[i];
            ClearPadInput(p);
            break;
        }
        case 1:
            n = func_00128A50(p->socket, buf);
            vibration = 0;
            if (p->act[0] & 2)
                vibration = p->vibration1;
            if (p->act[0] & 1) {
                short shifted = vibration << 1;

                vibration = shifted | (p->vibration0 & 1);
            }
            sceVibSetActParam(p->socket, 1, p->act, 2, &vibration);
            pad_decode_reading(p, buf, n);
            break;
        case 2:
            ClearPadInput(p);
            break;
        }
    } else {
        ClearPadInput(p);
        p->profile_state = 0;
    }
    p->vibration0 = 0;
    p->vibration1 = 0;
    D_001A7428 = g_pad_state.device_state == 0;
}
