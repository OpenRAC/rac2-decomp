

typedef int s32;

typedef unsigned char u8;

/* Third lot: nine further bodies shared with RAC1 and measured identical in
   RAC2's boot. Each was located by exact byte search, compiled with the
   qualified RAC2 profile, and compared byte for byte before entering the
   catalogue. The bodies carry no data or call reference; all operands are
   parameters, so nothing needed re-anchoring. */

/* Stores a value from a received command into the client's result table. */
s32 func_0011C880(s32 *command, s32 *clientData) {
    s32 *dst;
    s32 index;
    s32 value;

    index = *(s32 *)((u8 *)command + 0x10);
    dst = *(s32 **)((u8 *)clientData + 0x1C);
    value = *(s32 *)((u8 *)command + 0x14);
    dst[index] = value;
}

/* Copies a value from a received command into the client data and returns it. */
s32 func_0011C8A0(s32 *command, s32 *clientData) {
    s32 value;

    value = *(s32 *)((u8 *)command + 0x10);
    *(s32 *)((u8 *)clientData + 0x8) = value;
    return value;
}
