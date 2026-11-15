#include "common.h"
#include "structs.h"
#include <stdarg.h>

extern int r1_func_0011D960(void);

           /* DI */
extern void r1_func_0011D9A8(void);

       /* sceSifSetReg */
extern void sif_rpc_finish_request(char *);

/*
 * sifrpc's _request_end: the completion handler for a request block. Two
 * command ids do extra work before the common teardown: 0x8000000A (RPC
 * call) runs the client's end callback, 0x80000009 (RPC bind) copies the
 * server, buff and cbuff back into it. Then, whatever the id was,
 * iSignalSema the client's semaphore if it has one, free its packet
 * (func_0011D1E8) and clear the pointer. Exact under both compilers.
 *
 * Two levers (build-sn/try/func_0011D238/RESULT.md):
 *  - Retail's dispatch is gcc's case-node decision tree rooted at
 *    0x8000000A, which a two-case switch never builds (at two nodes it
 *    stays a chain). The switch has a third case above 0x8000000A that
 *    shares the default's body: with one shared label the node stays in
 *    the case list, the three-node tree roots at the median, and the
 *    now-redundant test is deleted. Any value above 0x8000000A works;
 *    0x8000000C is ps2sdk's SIF_CMD_RPC_RDATA, a guess.
 *  - `o` is loaded inside each arm and reloaded only after the callback.
 *    (Re-read once after the switch it is also exact under 2.9-ee, whose
 *    -fstrict-aliasing drops the reload after the 0x80000009 stores, but
 *    2.95.3 keeps that reload.)
 */
extern int r1_func_00118CA0(int);

extern void sif_rpc_handle_read_data(void *, void *);

extern void sif_rpc_handle_bind(void *, void *);

typedef struct {
    int packet;
    int requestId;
    int semaphoreId;
    char pad_C[0x4];
    int unk10;
    char pad_14[0x10];
    int server;
} BindClient;

typedef struct {
    char pad_0[0x14];
    int packetAddress;
    int requestId;
    int client;
    int serviceId;
} BindPacket;

extern char r1_D_00156900[];

extern int r1_func_00118C70(void *);

   /* CreateSema */
extern void r1_func_00118C80(int);

     /* DeleteSema */
extern int r1_func_00118CB0(int);

typedef signed int s32_1B4C8;

extern s32_1B4C8 r1_func_00118C70();

extern s32_1B4C8 r1_func_00118CB0();

extern s32_1B4C8 sceSifSendCmd();

extern s32 r1_func_00118CB0(s32);

extern int sceSifBindRpc(void *, int, int);

extern void sif_rpc_handle_call(void *, void *);

extern void r1_func_00119678(int thread_id);

/* rac1-decomp src/core/00119D88.c: func_0011AFE8 */
/* Claim the first free 0x40-byte slot in the table {next_id, base,
   count} at arg0, with interrupts held off across the search. A claimed
   slot records its index and state in +0x10, points +0x14 at itself and
   takes the next id; id 0 is skipped, so after handing out 1 the
   counter jumps straight to 2. Returns the slot, or 0 if the table is
   full.

   Two shapes mattered. `i` must be assigned AFTER the r1_func_0011D960
   call: initialised in its declaration it is live across the call, so
   it lands in a third callee-saved register and drags in a save/restore
   pair, where retail keeps it in $v1.

   And the id fan-in has to be written as an explicit if/ELSE with a
   separate assignment in each arm. Retail rematerialises `addiu $v1,$0,1`
   in the taken arm even though $v1 already holds that value, and no
   form that computes the value once -- including writing the redundant
   `id = 1;` after the store -- survives: the compiler folds it away and
   the function comes out 4 bytes short. Giving the two arms their own
   assignments to `id` keeps both definitions alive. */
/* Finds a free packet slot in the RPC packet table and hands it out with a fresh id. Returns 0 if the table is full. */
void *sif_rpc_alloc_packet(void *tablePtr) {
    char *table = (char *)tablePtr;
    int slotCount;
    char *slot;
    int i;
    int slotId;
    int nextCount;

    r1_func_0011D960();
    slotCount = *(int *)(table + 0x8);
    i = 0;
    slot = *(char **)(table + 0x4);
    while (i < slotCount) {
        if ((*(int *)(slot + 0x10) & 1) == 0) {
            *(int *)(slot + 0x10) = (i << 16) | 5;
            nextCount = *(int *)table + 1;
            *(int *)table = nextCount;
            if (nextCount == 1) {
                *(int *)table = nextCount + 1;
                slotId = 1;
            } else {
                slotId = nextCount;
            }
            *(char **)(slot + 0x14) = slot;
            *(int *)(slot + 0x18) = slotId;
            r1_func_0011D9A8();
            return slot;
        }
        i++;
        slot += 0x40;
    }
    r1_func_0011D9A8();
    return 0;
}

/* rac1-decomp src/core/00119D88.c: func_0011B090 */
/* Gives a packet slot back by clearing its id and its in-use flag. */
void sif_rpc_free_packet(void *slotPtr) {
    char *slot = (char *)slotPtr;
    unsigned int flags = *(unsigned int *)(slot + 0x10);
    *(int *)(slot + 0x18) = 0;
    *(unsigned int *)(slot + 0x10) = flags & 0xFFFFFFFEu;
}

/* rac1-decomp src/core/00119D88.c: func_0011B0B0 */
/*
 * REVERTED at 20/48 (same size). Semantics are certain:
 *
 *   int rem = *(int *)(arg0 + 0x24) % *(int *)(arg0 + 0x18);
 *   *(int *)(arg0 + 0x24) = rem + 1;
 *   return *(int *)(arg0 + 0x14) + (rem << 6);
 *
 * A wrapping counter: takes the modulo of field 0x24 by field 0x18,
 * writes back rem+1, and returns field 0x14 + rem*64 (a 64-byte-stride
 * table index). Every instruction matches retail including the div trap
 * guard; the residual is the allocator picking the opposite registers
 * for the divisor and the mfhi result ($2/$3 swapped versus retail),
 * which then reorders the tail so the store lands in the jr delay slot
 * where retail puts the addu. Tried: hoisting the base load into a
 * local, and naming rem+1 as a separate local -- neither changed the
 * allocation. Same open scratch-register question as r1_func_001160D8.
 */
/* Hand out the next 0x40-byte slot of the ring {.., +0x14 base, +0x18
   count, .., +0x24 next}: take next modulo count, advance next past it,
   return the slot. The slot address has to be formed BEFORE the store of
   the new index: that is what gives retail's allocation (remainder in $v0,
   divisor in $v1) and its tail, `addiu` before `sll` and the `addu` in the
   jr delay slot. Storing first and indexing in the return is 20/48. */
/* The slot address is computed into a local before next = i + 1 is
   stored. */
/* Hands out the next response packet from a ring of packets, wrapping around at the end. */
void *sif_rpc_get_next_response_packet(void *ringPtr) {
    char *ring = (char *)ringPtr;
    int index = *(int *)(ring + 0x24) % *(int *)(ring + 0x18);
    char *slot = *(char **)(ring + 0x14) + index * 0x40;
    *(int *)(ring + 0x24) = index + 1;
    return slot;
}

/* rac1-decomp src/core/00119D88.c: func_0011B0E0 */
/* Finishes an RPC request: runs any end callback, wakes the waiting thread and frees the packet. */
void sif_rpc_finish_request(char *request) {
    char *client;
    int semaId;

    switch (*(unsigned int *)(request + 0x20)) {
    case 0x8000000A:
        client = *(char **)(request + 0x1C);
        if (*(int *)(client + 0x1C) != 0) {
            (*(void (**)(int))(client + 0x1C))(*(int *)(client + 0x20));
            client = *(char **)(request + 0x1C);
        }
        break;
    case 0x80000009:
        client = *(char **)(request + 0x1C);
        *(int *)(client + 0x24) = *(int *)(request + 0x24);
        *(int *)(client + 0x14) = *(int *)(request + 0x28);
        *(int *)(client + 0x18) = *(int *)(request + 0x2C);
        break;
    case 0x8000000C:
    default:
        client = *(char **)(request + 0x1C);
        break;
    }
    semaId = *(int *)(client + 0x8);
    if (semaId >= 0) {
        r1_func_00118CA0(semaId);
    }
    sif_rpc_free_packet(*(void **)client);
    *(int *)client = 0;
}

/* rac1-decomp src/core/00119D88.c: func_0011B198 */
/* _request_rdata (libkernl.a:sifrpc.o): the sifcmd system handler for
   SIF_CMD_RPC_RDATA (0x8000000c). Grabs a free response packet
   (func_0011D208 = _rpc_get_fpacket), copies the requester's pkt_addr
   and recvbuf pointer (rdata's words 5 and 7) into the response, tags
   the response SIF_CMD_RPC_RDATA (word 8), then forwards the
   requester's src/dest/size (words 8/9/10) to the IOP as
   isceSifSendCmd(SIF_CMD_RPC_END, ...) (func_0011CD60). Void: the
   trailing call is a tail jump. Both copied fields have to be read into
   their own locals before either store: that is what puts pkt_addr in
   $a1 and recvbuf in $a0, matching retail (any other shape -- inline
   reads, one field hoisted, or reversed declaration order -- swaps that
   allocation or reloads recvbuf late). */
/* Answers a data request from the IOP by building a reply packet and sending it back. */
void sif_rpc_handle_read_data(void *rdata, void *data) {
    int *request = (int *)rdata;
    int *response = (int *)sif_rpc_get_next_response_packet(data);
    int pkt_addr = request[5];
    int recvbuf = request[7];

    response[5] = pkt_addr;
    response[7] = recvbuf;
    response[8] = 0x8000000C;
    isceSifSendCmd(0x80000008, (int)response, 0x40, request[8], request[9], request[10]);
}

/* rac1-decomp src/core/00119D88.c: func_0011B1F8 */
/* Searches the list of servers for the one with the given id. Returns 0 if none is found. */
void *sif_rpc_find_server_by_id(int key, void *dataTable) {
    void *queue = *(void **)((char *)dataTable + 0x28);
    while (queue != 0) {
        void *serverData = *(void **)((char *)queue + 8);
        while (serverData != 0) {
            if (*(int *)serverData == key) {
                return serverData;
            }
            serverData = *(void **)((char *)serverData + 0x38);
        }
        queue = *(void **)((char *)queue + 0x14);
    }
    return 0;
}

/* rac1-decomp src/core/00119D88.c: func_0011B248 */
/* _request_bind (libkernl.a:sifrpc.o): the sifcmd system handler for
   SIF_CMD_RPC_BIND (0x80000009). Grabs a free response packet
   (func_0011D208 = _rpc_get_fpacket), copies the requester's pkt_addr
   and cd (bind's words 5 and 7) into it, tags it SIF_CMD_RPC_BIND,
   looks up the requested service id (bind's word 8, search_svdata =
   func_0011D350) and fills in the server/buf/cbuf fields (words 9-11)
   from it if found, zeroing them otherwise, then forwards to the IOP as
   isceSifSendCmd(SIF_CMD_RPC_END, ...) (func_0011CD60). Matches
   ps2sdk's _request_bind field-for-field (sifrpc.c).

   Two shapes mattered: pkt_addr and cd need their own locals declared
   in that order (pkt_addr first) even though cd is stored first --
   reversed, the two loads swap registers (func_0011D2F0's lever again);
   and the not-found case has to be the `if` arm, sd-found the `else`
   (retail branches on `sd == 0` being false, i.e. `bnel`; writing the
   found case first inverts the branch, as in func_0011D590). */
/* Answers a bind request from the IOP by looking up the server and sending its details back. */
void sif_rpc_handle_bind(void *bind, void *data) {
    int *request = (int *)bind;
    int *response = (int *)sif_rpc_get_next_response_packet(data);
    int pkt_addr = request[5];
    int cd = request[7];
    int *serverData;

    response[7] = cd;
    response[5] = pkt_addr;
    response[8] = 0x80000009;
    serverData = (int *)sif_rpc_find_server_by_id(request[8], data);
    if (serverData == 0) {
        response[9] = 0;
        response[10] = 0;
        response[11] = 0;
    } else {
        response[9] = (int)serverData;
        response[10] = serverData[2];
        response[11] = serverData[5];
    }
    isceSifSendCmd(0x80000008, (int)response, 0x40, 0, 0, 0);
}

/* rac1-decomp src/core/00119D88.c: func_0011B2F8 */
      /* WaitSema */

/* sceSifBindRpc. Adapted from Lombyte (GPL-3.0) for PAL. */
/* Connects a client to a server on the IOP and waits until the server answers. */
int sceSifBindRpc(void *clientArg, int serviceId, int mode) {
    BindClient *client = clientArg;
    int sema_param[6];
    int semaId;
    BindPacket *packet;

    client->unk10 = 0;
    client->server = 0;
    packet = (BindPacket *)sif_rpc_alloc_packet(r1_D_00156900);
    if (packet == 0) {
        return -1;
    }
    client->requestId = packet->requestId;
    client->packet = (int)packet;
    packet->serviceId = serviceId;
    packet->packetAddress = (int)packet;
    packet->client = (int)client;
    if (mode & 1) {
        goto block_7;
    }
    sema_param[1] = 1;
    sema_param[2] = 0;
    semaId = r1_func_00118C70(sema_param);
    client->semaphoreId = semaId;
    if (semaId >= 0) {
        goto block_4;
    }
    sif_rpc_free_packet(packet);
    return -3;
block_4:
    if (sceSifSendCmd(0x80000009, (int)packet, 0x40, 0, 0, 0) != 0) {
        goto block_6;
    }
    sif_rpc_free_packet(packet);
    r1_func_00118C80(client->semaphoreId);
    return -2;
block_6:
    r1_func_00118CB0(client->semaphoreId);
    r1_func_00118C80(client->semaphoreId);
    return 0;
block_7:
    client->semaphoreId = -1;
    if (sceSifSendCmd(0x80000009, (int)packet, 0x40, 0, 0, 0) != 0) {
        return 0;
    }
    sif_rpc_free_packet(packet);
    return -2;
}

/* rac1-decomp src/core/00119D88.c: func_0011B438 */
/* _request_call (libkernl.a:sifrpc.o): the sifcmd system handler for
   SIF_CMD_RPC_CALL (0x8000000a). Queues the request's server object
   (request->sd, word 13) onto its data queue's (sd->base, word 16)
   linked list of pending calls -- append to the current end if the
   queue is non-empty (base->start, word 3), else start a new list --
   then copies the request's fields into the server object (pkt_addr,
   client/cd, rpc_number, size/send_size, recvbuf, rsize/recv_size,
   rmode, rid/rec_id), and finally wakes the queue's worker thread
   (iWakeupThread, r1_func_00119678) unless it is already running or has
   none. Matches ps2sdk's _request_call field-for-field (sifrpc.c).

   Three shapes mattered: the empty-queue arm has to come first (retail
   tests and branches on it, not on the append case); and the first two
   copied fields (pkt_addr, client) need their own locals, both declared
   right there (not hoisted to the top, which pulls their loads into the
   queue-splice code) and both declared before either store -- the same
   allocator lever as func_0011D2F0 -- or the pair's load/store order
   swaps or its two registers trade places. */
/* Adds an incoming call request to its server queue and wakes the server thread. */
void sif_rpc_handle_call(void *request, void *data) {
    int *req = (int *)request;
    int *sd = (int *)req[13];
    int *base = (int *)sd[16];

    if (base[3] == 0) {
        base[3] = (int)sd;
    } else {
        int *end = (int *)base[4];
        end[15] = (int)sd;
    }
    base[4] = (int)sd;
    {
        int pkt_addr = req[5];
        int client = req[7];
        sd[8] = pkt_addr;
        sd[7] = client;
    }
    sd[9] = req[8];
    sd[3] = req[9];
    sd[10] = req[10];
    sd[11] = req[11];
    sd[12] = req[12];
    sd[13] = req[4];

    if (base[0] < 0 || base[1] != 0) return;
    r1_func_00119678(base[0]);
}

extern void r1_func_0011AD70(void *addr, s32 size);
extern char r1_D_00156900[];
extern int r1_func_00118C70(void *);   /* CreateSema */
extern void r1_func_00118C80(int);     /* DeleteSema */
extern int r1_func_00118CB0(int);      /* WaitSema */
typedef unsigned char u8_1B4C8;
struct SifRpcClient_1B4C8
{
  volatile s32_1B4C8 packet;
  volatile s32_1B4C8 request_id;
    s32_1B4C8 semaphore_id;
    u8_1B4C8 pad_C[0x8];
    s32_1B4C8 server_buffer;
    u8_1B4C8 pad_18[0x4];
    s32_1B4C8 end_callback;
  volatile s32_1B4C8 end_argument;
    s32_1B4C8 server;
};
struct SifRpcPacket_1B4C8 {
    u8_1B4C8 pad_0[0x14];
    s32_1B4C8 packet_address;
    s32_1B4C8 request_id;
    s32_1B4C8 client;
    s32_1B4C8 rpc_number;
    s32_1B4C8 send_size;
    s32_1B4C8 receive_address;
    s32_1B4C8 receive_size;
    s32_1B4C8 completion_mode;
    s32_1B4C8 server;
};
extern u8_1B4C8 r1_D_00156900_1B4C8[] __asm__("r1_D_00156900");
extern s32_1B4C8 r1_func_00118C70();
extern s32_1B4C8 r1_func_00118C80_1B4C8() __asm__("r1_func_00118C80");
extern s32_1B4C8 r1_func_00118CB0();
extern s32_1B4C8 r1_func_0011AFE8_1B4C8() __asm__("r1_func_0011AFE8");
extern s32_1B4C8 r1_func_0011B090_1B4C8() __asm__("r1_func_0011B090");
extern s32_1B4C8 r1_func_0011ABC8();
extern s32_1B4C8 r1_func_0011AD70_1B4C8() __asm__("r1_func_0011AD70");


/* rac1-decomp src/core/00119D88.c: func_0011D620 */
/* Sends a call to a server on the IOP, and waits for the answer unless asked not to. */
s32_1B4C8 sceSifCallRpc(struct SifRpcClient_1B4C8 *client, s32_1B4C8 rpc_number, s32_1B4C8 mode, s32_1B4C8 send_buf, s32_1B4C8 send_size,
                          s32_1B4C8 recv_buf, s32_1B4C8 recv_size, s32_1B4C8 end_func, s32_1B4C8 end_data) {
    s32_1B4C8 semaphore_parameters[6];
    struct SifRpcPacket_1B4C8 *packet;
    s32_1B4C8 semaphore_id;
    s32_1B4C8 skip_cache_writeback;
    s32_1B4C8 request_id;
    s32_1B4C8 allocation_failure_result;
    packet = (struct SifRpcPacket_1B4C8 *)r1_func_0011AFE8_1B4C8(r1_D_00156900_1B4C8);
    allocation_failure_result = -1;
    if (packet == 0) {
        return allocation_failure_result;
    }
    request_id = packet->request_id;
    skip_cache_writeback = mode & 2;
    client->end_argument = end_data;
    client->packet = (s32_1B4C8)packet;
    client->request_id = request_id;
    client->end_callback = end_func;
    packet->rpc_number = rpc_number;
    packet->send_size = send_size;
    packet->receive_address = recv_buf;
    packet->receive_size = recv_size;
    packet->packet_address = (s32_1B4C8)packet;
    packet->server = client->server;
    packet->client = (s32_1B4C8)client;
    if (!skip_cache_writeback) {
        if (send_buf == recv_buf) {
            r1_func_0011AD70_1B4C8(send_buf, (send_size >= recv_size) ? (send_size) : (recv_size));
        } else {
            if (send_size > 0) {
                r1_func_0011AD70_1B4C8(send_buf, send_size);
            }
            if (recv_size > 0) {
                r1_func_0011AD70_1B4C8(recv_buf, recv_size);
            }
        }
    }
    if (mode & 1) {
        if (end_func == 0) {
            packet->completion_mode = 0;
        } else {
            packet->completion_mode = 1;
        }
        client->semaphore_id = -1;
        if (r1_func_0011ABC8(0x8000000A, packet, 0x40, send_buf, client->server_buffer, send_size) != 0) {
            return 0;
        } else {
            r1_func_0011B090_1B4C8(packet);
            return -2;
        }
    } else {
        semaphore_parameters[1] = 1;
        semaphore_parameters[2] = 0;
        semaphore_id = r1_func_00118C70(semaphore_parameters);
        client->semaphore_id = semaphore_id;
        if (semaphore_id < 0) {
            r1_func_0011B090_1B4C8(packet);
            return -3;
        }
        packet->completion_mode = 1;
        if (r1_func_0011ABC8(0x8000000A, packet, 0x40, send_buf, client->server_buffer, send_size) == 0) {
            r1_func_00118C80_1B4C8(client->semaphore_id);
            r1_func_0011B090_1B4C8(packet);
            return -2;
        }
        r1_func_00118CB0(client->semaphore_id);
        r1_func_00118C80_1B4C8(client->semaphore_id);
        return 0;
    }
}

/* rac1-decomp src/core/00119D88.c: func_0011B6B8 */
/*
 * REVERTED: size mismatch, 56 bytes against retail's 60. Semantics are
 * certain:
 *
 *   char *p = *(char **)arg0;
 *   if (p == 0) return 0;
 *   if (*(int *)(arg0 + 4) != *(int *)(p + 0x18)) return 0;
 *   if (*(int *)(p + 0x10) & 1) return 1;
 *   return 0;
 *
 * Retail keeps TWO exit blocks -- a shared `return 0` and a separate
 * `return 1`, each with its own `jr` -- which is 15 instructions. This
 * compiler merges them into a single exit and sets $v0 in the branch
 * delay slots, 14 instructions. Tried both the && chain and explicit
 * early returns; both merge. The exit structure is not expressible from
 * C here.
 */
/* Is the handle {slot, id} at arg0 still live: the slot is set, its id at
   +0x18 still matches the handle's, and its in-use bit (+0x10 bit 0) is
   set. Written as one inverted guard that returns 0, then `return 1`:
   that keeps retail's two exits (shared `return 0` block the tests fall
   into, a separate `return 1`), and gcc leaves all three branch slots to
   the assembler, which fills them with nops as retail has them. The &&
   form returning 1 merges the exits; early returns give bnel. */
/* One test for the three failure cases, then return 1. */
/* Checks that an RPC handle still points to a packet that is in use. */
int sif_rpc_is_handle_valid(void *handlePtr) {
    char *handle = (char *)handlePtr;
    char *slot = *(char **)handle;

    if (slot == 0 || *(int *)(handle + 4) != *(int *)(slot + 0x18) ||
        !(*(int *)(slot + 0x10) & 1)) {
        return 0;
    }
    return 1;
}

