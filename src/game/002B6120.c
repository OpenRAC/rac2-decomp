#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_T16_FD6E0D08A
#define RAC2_T_T16_FD6E0D08A
typedef struct { float x; float y; int pad[2]; } T16_Fd6e0d08a;
#endif

extern void *func_L00_0032C638_1(void *, void *);

extern int path_set_follower_nodes(void *, void *, int, int);

extern float func_00283248_9(float, float);

extern int moby_step_controller(void *, void *, float);

extern float func_00282E80_4(void *, void *);

typedef unsigned char u8;

typedef int s32;

extern u8 g_music_state[];

typedef struct { u8 before[0x68]; s32 active; u8 gap[6]; short state; } CallState;

extern void snd_send_cmd46(s32);

typedef unsigned int u32;

extern void snd_clear_flag_and_update(void);

extern s32 snd_Pump(void);

typedef struct {
 u8 before[0x2c]; short clear2c; u8 gap1[14]; short mode,next; u8 gap2[4];
 u32 busy44; short value48; u8 gap3[2]; short step4c,step4e; u8 gap4[24];
 u32 busy68; u8 gap5[4]; short step70,step72; u8 gap6[24];
 u32 busy8c; u8 gap7[4]; short step94,step96;
} WaitState;

extern s32 func_00133310(void);

extern s32 snd_send_cmd36(s32);

/* Frozen Batch A A05-store-rotation-52; acknowledged claim 43a7518b17439f6bdc9390be9d4164b47eec4bed94a72d581fdec3b883b0a554. */
typedef unsigned char BatchA_A05_u8;

typedef int BatchA_A05_s32;

typedef short BatchA_A05_BatchAs16;

typedef struct { BatchA_A05_u8 b[0x50]; BatchA_A05_BatchAs16 f50; BatchA_A05_BatchAs16 f52; BatchA_A05_u8 c[0x20]; BatchA_A05_BatchAs16 f74; BatchA_A05_BatchAs16 f76; BatchA_A05_u8 d[0x20]; BatchA_A05_BatchAs16 f98; BatchA_A05_BatchAs16 f9a; } BatchA_A05_BatchA52;

extern BatchA_A05_BatchA52 BatchA_A05_BatchA_D001A63A8;

/* Frozen Batch A A11-sda-3store-28; acknowledged claim 9b61d4cdd097ce0a56790793fdd6c129d3f0d822e40e788cde17e6418bdea65f. */
typedef unsigned char BatchA_A11_u8;

typedef unsigned short BatchA_A11_u16;

extern BatchA_A11_u8 BatchA_A11_D_001A63A8[];

/* Set the value of each enabled resident channel in its observed update order. */
typedef struct ResidentChannel64 {
    short flags;
    short value;
    u8 fields4[0x20];
} ResidentChannel64;

typedef struct ResidentChannels64 {
    u8 fields0[0x50];
    ResidentChannel64 channels[3];
} ResidentChannels64;

typedef struct __attribute__((packed)) { u8 mode[4]; } CdMode;

extern CdMode D_001A63E8;

extern u8 D_001A7900[] __attribute__((sda));

extern s32 D_001A7430[] __attribute__((sda));

extern s32 D_001A7434 __attribute__((sda));

extern s32 CdStartRead(s32,s32,s32,CdMode *);

extern short func_002B7CE0_1(int);

extern int func_002B7B18_1(char *, int, int);

extern void FlushCache(s32);

extern s32 snd_get_cd_read_error(void);

typedef struct { int offset, size; } SoundEntry;

typedef struct { char pad[0x52fc]; int base; SoundEntry entries[1]; } SoundTable;

typedef struct {
    unsigned int handle;
    short track, volume, flags, state, fade, unknown, crossfade, unknown2;
    int poll_interval, sample_rate;
    char tail[8];
} StreamChannel;

typedef struct { u8 pad[0x44]; StreamChannel channel[3]; } StreamState;

extern int g_copy_setup_data[];

extern int func_00133350(int, int, int, int, int, int, int, int, int, int,
                         void (*)(int, long), unsigned long);

/* Computes the x/y difference between one 16-byte record of the second handle and the record after the first handle's base, dispatches through three helpers and walks a short counter field up or down by one when the last helper's float result stays under a stored threshold. */
int path_follow_nodes(char *object, char *nodes)
{
    char *follower;
    float heading;

    follower = (char *)func_L00_0032C638_1(object, nodes);
    if (follower == 0)
        return 0;
    if ((int)nodes != *(int *)(follower + 196))
        path_set_follower_nodes(object, nodes, -1, 0);
    heading = func_00283248_9(((T16_Fd6e0d08a *)(nodes + (*(short *)(follower + 200) << 4)))[1].x - ((T16_Fd6e0d08a *)object)[1].x,
                ((T16_Fd6e0d08a *)(nodes + (*(short *)(follower + 200) << 4)))[1].y - ((T16_Fd6e0d08a *)object)[1].y);
    moby_step_controller(object, &((T16_Fd6e0d08a *)nodes)[*(short *)(follower + 202) + 1], heading);
    if (func_00282E80_4(&((T16_Fd6e0d08a *)object)[1], &((T16_Fd6e0d08a *)nodes)[*(short *)(follower + 200) + 1])
        <= *(float *)(follower + 52)) {
        if (*(short *)(follower + 202) == *(short *)(follower + 200))
            return 1;
        if (*(short *)(follower + 202) < *(short *)(follower + 200))
            *(short *)(follower + 200) = (unsigned short)*(short *)(follower + 200) - 1;
        else
            *(short *)(follower + 200) = (unsigned short)*(short *)(follower + 200) + 1;
    }
    return 0;
}


extern char *moby_get_controller(void *);

/* Stores the list of path nodes, the last node index and a start value in an object's path follower. */
int path_set_follower_nodes(void *object, void *rawNodes, int count, int value)
{
    unsigned short *nodes = rawNodes;
    char *follower = moby_get_controller(object);
    if (follower == 0)
        return 0;
    *(unsigned short **)(follower + 0xC4) = nodes;
    if (count == -1)
        *(short *)(follower + 0xCA) = nodes[0] - 1;
    else
        *(short *)(follower + 0xCA) = count;
    *(short *)(follower + 0xC8) = value;
    return 1;
}

/* func_002B62A0 is matched in 002B6120-g8.c (-G8 small data). */


extern float *g_path_table[];
extern int point_in_path_xy(float *, float *, int);
extern int path_push_point_away(int, float *, float *, float);

/* Checks that an object is still over its assigned floor polygon, and flags it when it has left. */
int coll_check_object_inside_polygon(unsigned char *object)
{
    char *state = moby_get_controller(object);
    float output[4];
    float *position;
    float *polygon;
    if (state == 0 || *(int *)(state + 0x3C) == -1)
        return 0;
    polygon = g_path_table[*(int *)(state + 0x3C)];
    position = (float *)(object + 0x10);
    if (point_in_path_xy(position, polygon + 4, *(int *)polygon)) {
        if (!path_push_point_away(*(int *)(state + 0x3C), position, output, *(float *)state))
            return 1;
    }
    *(unsigned int *)(state + 0x9C) |= 1;
    return 0;
}


extern unsigned int g_dma_packet_cursor __attribute__((sda));
extern char *D_001A742C __attribute__((section(".sdata")));
extern char D_001BAD40[];
extern void text_draw_pulsing(void);
extern void DrawSubtitles(void);
extern char D_001A6AF0[];
extern int g_scene_playback_state[];
extern void iFlushCache(int);

/* Starts a DMA chain at packet: two ref tags sent through VIF DIRECT (9 quadwords from
   the screen context + 0xC0, 0x25 from D_001A6AF0), counts the frame at D_001B8840 + 0x34,
   lets one of two builders append, then ends the chain and hands it to func_0011AED0.
   The cursor is an integer address, so each word stored through it may alias it and it
   is read again before every store. The movie callers also supply a mode word;
   this implementation does not consume it. */
void BuildFrameDmaChain(void *packet, int unusedMode)
{
    g_dma_packet_cursor = (unsigned int)packet;
    *(unsigned int *)(g_dma_packet_cursor + 0x00) = 0x30000009;
    *(unsigned int *)(g_dma_packet_cursor + 0x04) = (unsigned int)(D_001A742C + 0xC0) & 0x0FFFFFFF;
    *(unsigned int *)(g_dma_packet_cursor + 0x08) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 0x0C) = 0x50000009;
    *(unsigned int *)(g_dma_packet_cursor + 0x10) = 0x30000025;
    *(unsigned int *)(g_dma_packet_cursor + 0x14) = (unsigned int)D_001A6AF0;
    *(unsigned int *)(g_dma_packet_cursor + 0x18) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 0x1C) = 0x50000025;
    g_dma_packet_cursor += 0x20;
    g_scene_playback_state[13]++;
    if (*(int *)D_001BAD40)
        text_draw_pulsing();
    else
        DrawSubtitles();
    *(unsigned int *)(g_dma_packet_cursor + 0x00) = 0x70000000;
    *(unsigned int *)(g_dma_packet_cursor + 0x04) = 0;
    g_dma_packet_cursor += 0x10;
    iFlushCache(0);
}



/* func_002B6658 is in 002B6120-g8.c (its list head is in small data). */

extern char D_001A7248[] __attribute__((sda));
extern int sceSifCallRpc(void *, int, int, int, int, int, int, int, int);
extern int snd_send_cmd2a_once(int, int, int, int);

/* Runs a short fixed sequence of three sound setup calls. */
void snd_run_setup_sequence(void) {
    sceSifCallRpc(D_001A7248, 3, 0, 0, 0, 0, 0, 0, 0);
    snd_send_cmd2a_once(7, 0xA000, 0, 1);
    sceSifCallRpc(D_001A7248, 3, 0, 0, 0, 0, 0, 0, 0);
}

/* Callback that stores a result value at the address it was given. */
void load_store_callback_result(int result, long resultAddr) {
    int *out = (int *)(int)resultAddr;

    if (out != 0) {
        *out = result;
    }
}

extern char g_sound_state[];

/* func_002B6788 is matched in 002B6788.c. */

extern void func_001325E8(int, void (*)(int, long), unsigned long);

/* Marks a sound bank status slot as pending and starts a load that writes its result into that slot. */
void snd_start_bank_load(int source, int index) {
    char *statusBase = g_sound_state;
    char *slot;
    unsigned long slotAddr;
    statusBase = statusBase + 0x17A0;
    slot = statusBase + index * 4;
    *(unsigned int *)slot = 0xFFFFFFFFu;
    slotAddr = (unsigned long)(unsigned int)slot;
    func_001325E8(source, load_store_callback_result, slotAddr);
}

/* func_002B6828 is matched in 002B6828.c. */

/* func_002B68C8 is built from 002B68C8.c. */

extern void load_on_disc_read_finished(s32);
extern void *func_001336D0(void (*)(s32));

/* Registers the disc read completion callback with the file system. */
void load_register_disc_read_callback(void) {
    func_001336D0(load_on_disc_read_finished);
}

/* func_002B6958 is built from 002B6120-sound-g8.c. */

/* Moves the music stream from state 3 to state 4 and tells the sound system, if a stream is active. */
s32 snd_resume_music_stream(void) {
    if (((CallState *)g_music_state)->active==0) return 0;
    if (((CallState *)g_music_state)->state!=3) return 0;
    snd_send_cmd46(((CallState *)g_music_state)->active); ((CallState *)g_music_state)->state=4;
    return 1;
}

extern void request_store_result_and_advance_alt(int, long);

/* If the primary stream channel is idle (handle 0) and table entry index is present, claim
   it (handle -1, state 1, track, mode, 10 / 48000, volume) and start entries index and
   index + 1 (offset plus the table base, long sums as in func_002B6F70) on it with flag 1. */
void snd_start_music_stream(int index, int mode, int volume)
{
    StreamState *s = (StreamState *)g_music_state;
    SoundTable *d;
    long first, second;
    int offset;

    if (s->channel[0].handle) return;
    d = (SoundTable *)g_copy_setup_data;
    offset = d->entries[index].offset;
    if (!offset) return;
    s->channel[0].handle = 0xffffffffU;
    s->channel[0].state = 1;
    s->channel[0].track = index;
    s->channel[0].flags = mode;
    s->channel[0].poll_interval = 10;
    s->channel[0].sample_rate = 48000;
    s->channel[0].volume = volume;
    s->channel[0].crossfade = 0;
    first = offset + d->base;
    second = d->entries[index + 1].offset + d->base;
    func_00133350(first, second, 0, 0, (short)volume, 0, 1, 0, 0, 1,
                  request_store_result_and_advance_alt, (unsigned int)&s->channel[0]);
}

extern void request_store_result_move_to_end(int, long);

/* As func_002B6D80 for a non-negative index, with flag 0, the callback func_002B7FB0 and the
   stores in the order retail's scheduling needs. */
void snd_start_music_stream_no_loop(int index, int mode, int volume)
{
    StreamState *s;
    SoundTable *d;
    long first, second;
    int offset;

    if (index < 0) return;
    s = (StreamState *)g_music_state;
    if (s->channel[0].handle) return;
    d = (SoundTable *)g_copy_setup_data;
    offset = d->entries[index].offset;
    if (!offset) return;
    s->channel[0].handle = 0xffffffffU;
    s->channel[0].state = 1;
    s->channel[0].poll_interval = 10;
    s->channel[0].sample_rate = 48000;
    s->channel[0].track = index;
    s->channel[0].flags = mode;
    s->channel[0].volume = volume;
    s->channel[0].crossfade = 0;
    first = offset + d->base;
    second = d->entries[index + 1].offset + d->base;
    func_00133350(first, second, 0, 0, (short)volume, 0, 1, 0, 0, 0,
                  request_store_result_move_to_end, (unsigned int)&s->channel[0]);
}

extern void request_resume_pending_result(int, long);

/* While the primary stream channel is playing (handle neither 0 nor -1) and not already in
   state 9, start entry index + 3 and index + 2 of the stream table (offset plus the table
   base) on it if entry index + 1 is present: state 9, volume, track and mode recorded, then
   the stream call with the current handle as its eighth argument and bit 0 of the mode as
   flag 4. The locations are long sums passed to int parameters (one truncdisi2 each, as in
   retail), and the statements keep the order retail's scheduling and allocation need. */
void snd_queue_music_transition_stream(int index, int mode, int volume)
{
    StreamState *s = (StreamState *)g_music_state;
    SoundTable *d;
    long first, second;
    unsigned int current;
    int stream_flags;
    unsigned long callback_data;

    if (s->channel[0].state == 9) return;
    current = s->channel[0].handle;
    if (current == 0 || current == 0xffffffffU) return;
    d = (SoundTable *)g_copy_setup_data;
    if (!d->entries[index + 1].offset) return;
    s->channel[0].state = 9;
    second = d->entries[index + 2].offset + d->base;
    s->channel[0].volume = volume;
    s->channel[0].track = index;
    s->channel[0].flags = mode;
    s->channel[0].poll_interval = 10;
    s->channel[0].crossfade = 0;
    first = d->entries[index + 3].offset + d->base;
    s->channel[0].sample_rate = 48000;
    stream_flags = (mode & 1) << 2;
    callback_data = (unsigned int)&s->channel[0];
    func_00133350(first, second, 0, 0, (short)volume, 0, 1, current, 0, stream_flags,
                  request_resume_pending_result, callback_data);
}

/* Waits for all music streams and sound jobs to finish, then clears the music state. */
void snd_wait_for_music_idle(void) {
    ((void (*)(void))snd_clear_flag_and_update)();
    while (((WaitState *)g_music_state)->busy44 == 0xffffffffU) snd_Pump();
    while (((WaitState *)g_music_state)->busy8c == 0xffffffffU) snd_Pump();
    while (((WaitState *)g_music_state)->busy68 == 0xffffffffU) snd_Pump();
    func_00133310();
    while (snd_Pump() != 0) {}
    snd_send_cmd36(1);
    ((WaitState *)g_music_state)->step4e = 0; ((WaitState *)g_music_state)->step4c = 0; ((WaitState *)g_music_state)->busy44 = 0;
    if (((WaitState *)g_music_state)->mode != -1) ((WaitState *)g_music_state)->value48 = ((WaitState *)g_music_state)->mode;
    ((WaitState *)g_music_state)->step72 = 0; ((WaitState *)g_music_state)->step70 = 0; ((WaitState *)g_music_state)->busy68 = 0;
    ((WaitState *)g_music_state)->step96 = 0; ((WaitState *)g_music_state)->step94 = 0; ((WaitState *)g_music_state)->busy8c = 0;
    ((WaitState *)g_music_state)->clear2c = 0; ((WaitState *)g_music_state)->mode = -1;
    ((WaitState *)g_music_state)->next = -1;
}

/* Resets the fade values of the music channels to their paused settings. */
void music_Pause(BatchA_A05_s32 resetSecond) {
    if (resetSecond != 0) { BatchA_A05_BatchA_D001A63A8.f76 = 0; BatchA_A05_BatchA_D001A63A8.f74 = -0x8000; }
    BatchA_A05_BatchA_D001A63A8.f9a = 0;
    BatchA_A05_BatchA_D001A63A8.f50 = -0x8000;
    BatchA_A05_BatchA_D001A63A8.f52 = 0;
    BatchA_A05_BatchA_D001A63A8.f98 = -0x8000;
}

/* Sets the fade values of the three music channels back to their normal setting. */
void music_Unpause(void) {
    BatchA_A11_u8 *state = BatchA_A11_D_001A63A8;
    *(BatchA_A11_u16 *)(state + 0x50) = 4;
    *(BatchA_A11_u16 *)(state + 0x98) = 4;
    *(BatchA_A11_u16 *)(state + 0x74) = 4;
}

/* Sets the value of each music channel that is switched on. */
void music_set_active_track_value(s32 newValue)
{
    ResidentChannels64 *state = (ResidentChannels64 *)g_music_state;
    if (state->channels[0].flags & 0x8000)
        state->channels[0].value = newValue;
    if (state->channels[2].flags & 0x8000)
        state->channels[2].value = newValue;
    if (state->channels[1].flags & 0x8000)
        state->channels[1].value = newValue;
}


/* func_002B7578 is matched in 002B7578.c (its own jump-table unit). */

extern char D_001AA1E8[];
extern void STUB_printf(void *);
extern int snd_run_handler_or_send_cmd37(void);
/* Asks the music system to stop the disc read that is in progress. */
void load_request_disc_read_break(void) {
    u8 *state = g_music_state;
    if (*(short *)(state + 4) != 0) {
        STUB_printf(D_001AA1E8);
        snd_run_handler_or_send_cmd37();
        state[6] = 1;
    }
}

extern u8 D_001AA1F8[];
extern void math_trap_always(void);

/* Starts reading disc sectors into memory when no read is running. Returns the number of bytes requested, or 0 if it could not start. */
int load_start_disc_read(int dest, int sector, int sectorCount)
{
    u8 *state = g_music_state;
    if (*(short *)(state + 4) == 0 && sectorCount != 0) {
        *(int *)(state + 0x18) = 0;
        *(int *)(state + 0x1c) = 0;
        if (CdStartRead(sector, sectorCount, dest, (CdMode *)(state + 0x40))) {
            *(int *)(state + 0x14) = dest;
            *(short *)(state + 4) = 1;
            *(int *)(state + 8) = sector;
            *(int *)(state + 0x10) = sectorCount;
            return sectorCount << 11;
        }
        STUB_printf(D_001AA1F8);
        math_trap_always();
    }
    return 0;
}

extern int load_start_disc_read(int, int, int);

typedef struct { u8 pad[0x18]; int first, second; } PairState;

/* Starts a disc read and, if it started, remembers the two extra values for the completion callback. */
int load_start_disc_read_with_callback(int dest, int sector, int sectorCount, int first, int second)
{
    int bytes = load_start_disc_read(dest, sector, sectorCount);
    if (bytes != 0) {
        PairState *state = (PairState *)g_music_state;
        state->first = first;
        state->second = second;
    }
    return bytes;
}

/* Reads disc sectors into memory and waits for the read to be handled. Always returns 1. */
s32 load_read_disc_sectors_blocking(s32 dest, s32 sector, s32 sectorCount) {
    CdMode mode = D_001A63E8;
    mode.mode[1] = D_001A7900[0];
    D_001A7430[0] = 0; D_001A7434 = 0;
    CdStartRead(sector,sectorCount,dest,&mode);
    snd_clear_flag_and_update(); snd_Pump();
    return 1;
}

/* Calls one callee with the argument 1, then a second callee with (first, second, third argument) keeping its result, calls the first callee again with 1, and returns the kept result. */
int load_read_disc_with_pause(char *dest, int sector, int sectorCount)
{
    int result;

    func_002B7CE0_1(1);
    result = func_002B7B18_1(dest, sector, sectorCount);
    func_002B7CE0_1(1);
    return result;
}


/* Callback run when a disc read step finishes: sets the music system idle and calls the stored completion callback. */
void load_on_disc_read_finished(s32 event) {
    if (event == 1) {
        if (snd_get_cd_read_error() != 0) { *(short *)(g_music_state+4) = 2; } else {
            void (*callback)(s32,s32);
            s32 data, flag;
            ((void (*)(s32))FlushCache)(0);
            flag = g_music_state[6] == 0;
            callback = *(void (**)(s32,s32))(g_music_state+0x18);
            *(short *)(g_music_state+4) = 0;
            g_music_state[6] = 0;
            if (callback) {
                data = *(s32 *)(g_music_state+0x1c);
                *(void (**)(s32,s32))(g_music_state+0x18) = 0;
                *(s32 *)(g_music_state+0x1c) = 0;
                callback(data,flag);
            }
        }
    }
}

void music_channel_ready_callback(int arg0, long arg1) {
    short *p = (short *)(int)arg1;

    if (p != 0 && arg0 != 0 && p[5] == 2) {
        p[5] = 3;
    }
}
