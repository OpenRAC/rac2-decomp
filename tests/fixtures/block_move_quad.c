/* Block moves by alignment (tests/test_block_move_quad.py). */

typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad q[9]; } Packet;                  /* 0x90 bytes, 16-byte aligned */
typedef struct { Quad q[4]; } Short;                   /* 0x40 bytes, 16-byte aligned */
typedef struct { long long d[18]; } Words;             /* 0x90 bytes, 8-byte aligned */

extern Packet packet_dst;
extern Short short_dst;
extern Words words_dst;

void copy_packet(Packet *src)
{
    packet_dst = *src;
}

void copy_short(Short *src)
{
    short_dst = *src;
}

void copy_words(Words *src)
{
    words_dst = *src;
}
