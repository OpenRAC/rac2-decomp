/* functional: medium. Written from the assembly: the 16-byte quadword copies are plain 4-float copies, the packet and direction buffers are local arrays; the packet's size past byte 28 is a guess (func_002A8C00 fills it). */

extern char D_L00_00256BC0[];                   /* 48 entries of 208 bytes */

extern char *func_002AB1F0(void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *dst, void *table, float scale);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);
extern void func_00282D08(void *out, void *from, void *to, float t);
extern int func_00282948(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *packet, char *owner, int flags, void *direction, float amount);
extern void func_002A8E20(void *target, void *packet);
extern void func_L00_00412928(char *pos, int count, int mode);

static void copy16_00411B30(void *dst, void *src)
{
    ((int *)dst)[0] = ((int *)src)[0];
    ((int *)dst)[1] = ((int *)src)[1];
    ((int *)dst)[2] = ((int *)src)[2];
    ((int *)dst)[3] = ((int *)src)[3];
}

/* Steps every entry that belongs to `owner`: takes the current position (+32) and rotation (+48)
   from their targets, blending towards the target's transform when it has a body, eases the six
   angles (+96..+104, +132..+140) towards their goals, builds the two angle triples from sin and
   cos, mixes the rotation by the timers at +184/+188, and when the timer runs out spawns a
   packet at the target. The entry is released when its second timer (+168) runs out. */
void func_L00_00411B30(void *self)
{
    char *owner = (char *)self;
    int i;

    for (i = 0; i < 48; i++) {
        char *e = D_L00_00256BC0 + i * 208;
        char *s2, *s1, *t, *body;
        float scale;
        float tmp[4];
        float dir[4];
        int pkt[12];
        float f20;

        if (*(char **)(e + 172) != owner) {
            continue;
        }
        s2 = e + 32;
        copy16_00411B30(s2, e + 64);

        t = *(char **)(e + 180);
        if (t != 0) {
            body = func_002AB1F0(t);
            if (body != 0) {
                func_002AFFD8(t + 16, tmp, 1);
                func_00282D30(tmp, tmp, *(float *)(body + 16));
                func_00282CC0(tmp, tmp, *(char **)(e + 180) + 16);
                func_00282CC0(s2, tmp, s2);
            } else {
                copy16_00411B30(s2, t + 16);
            }
        }

        scale = *(int *)(e + 184) != 0 ? 100.0f : 1.0f;
        *(float *)(e + 96) = func_00283B98(*(float *)(e + 96), *(float *)(e + 108) * scale);
        *(float *)(e + 100) = func_00283B98(*(float *)(e + 100), *(float *)(e + 112) * scale);
        *(float *)(e + 104) = func_00283B98(*(float *)(e + 104), *(float *)(e + 116) * scale);
        *(float *)(e + 132) = func_00283B98(*(float *)(e + 132), *(float *)(e + 144) * scale);
        *(float *)(e + 136) = func_00283B98(*(float *)(e + 136), *(float *)(e + 148) * scale);
        *(float *)(e + 140) = func_00283B98(*(float *)(e + 140), *(float *)(e + 152) * scale);

        *(float *)(e + 0) = func_00283180(*(float *)(e + 96)) * *(float *)(e + 120);
        *(float *)(e + 4) = func_00283198(*(float *)(e + 100)) * *(float *)(e + 124);
        *(float *)(e + 8) = -func_00283198(*(float *)(e + 104)) * *(float *)(e + 128);
        *(float *)(e + 16) = func_00283180(*(float *)(e + 132)) * *(float *)(e + 156);
        *(float *)(e + 20) = func_00283198(*(float *)(e + 136)) * *(float *)(e + 160);
        *(float *)(e + 24) = -func_00283198(*(float *)(e + 140)) * *(float *)(e + 164);

        s2 = e + 48;
        copy16_00411B30(s2, e + 80);
        s1 = e + 32;
        t = *(char **)(e + 176);
        if (t != 0) {
            body = func_002AB1F0(t);
            if (body != 0) {
                func_002AFFD8(t + 16, tmp, 1);
                func_00282D30(tmp, tmp, *(float *)(body + 16));
                func_00282CC0(tmp, tmp, *(char **)(e + 176) + 16);
                func_00282CC0(s2, tmp, s2);
            } else {
                copy16_00411B30(s2, t + 16);
            }
        }

        f20 = func_00283CE0(*(int *)(e + 184));
        f20 = f20 / func_00283CE0(*(int *)(e + 188));
        func_00282D08(s2, s1, s2, 1.0f - f20);

        if (func_00282948(e + 184) == 0) {
            continue;
        }
        if (*(int *)(*(char **)(e + 176) + 152) != 0 && *(int *)(e + 192) == 0 && *(int *)(e + 196) != 0) {
            func_00282CF0(dir, s2, s1);
            func_00282F20(dir, dir, 0.033333335f);
            *(int *)(owner + 184) = *(int *)(*(char **)(e + 204) + 32);
            func_002A8C00(pkt, owner, 0x210000, dir, *(float *)(e + 200));
            ((char *)pkt)[24] = 5;
            ((char *)pkt)[25] = 3;
            *(unsigned short *)((char *)pkt + 26) = *(unsigned short *)(owner + 170);
            func_002A8E20(*(char **)(e + 176), pkt);
            *(int *)(e + 192) = 1;
            func_L00_00412928(s2, 10, 1);
        }
        if (func_00282948(e + 168) != 0) {
            *(int *)(e + 172) = 0;
        }
    }
}
