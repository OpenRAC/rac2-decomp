/* functional: high. Plain floats in place of VU0 code, in its order (joint matrix rows accumulated x, y, z then + row3*1; scale on all four lanes; moby matrix the same way); vitof12 is int/4096. The 128-bit copies keep their w lanes: a record's point keeps its own w times the scale. Retail keeps its $s registers in their upper halves instead of on the stack; that has no C meaning. As retail, the moby loop is a do-while (one moby even for a zero count) and the buffer test (past D_001EF2E0 + 8064) comes after func_002A3110 runs. */
extern int D_001B1B7C;
extern unsigned char D_001EF160[];
extern unsigned char D_001EF2E0[];
extern unsigned int D_001B1B90[];
extern void func_002A3110(void *, int, int);

/* r.xyz = m0*v.x + m1*v.y + m2*v.z + m3*1 (VU0 mula/madda/madda/madd order); r.w = v.w. */
static void xform_002DFD88(float *r, const float *m0, const float *m1, const float *m2, const float *m3, const float *v)
{
    float o[3];
    int j;

    for (j = 0; j < 3; j++) {
        float acc = m0[j] * v[0];
        acc = acc + m1[j] * v[1];
        acc = acc + m2[j] * v[2];
        o[j] = acc + m3[j] * 1.0f;
    }
    r[0] = o[0];
    r[1] = o[1];
    r[2] = o[2];
    r[3] = v[3];
}

static float bits_002DFD88(unsigned int u)
{
    union {
        unsigned int i;
        float f;
    } c;
    c.i = u;
    return c.f;
}

/* Build the moby light/attachment point list: for each of the D_001B1B7C entries at D_001EF160 (8 bytes: moby, u16 scale,
   u16 tag), run func_002A3110(moby, class byte 8, -1), then write to D_001EF2E0 a 48-byte header (count, tag, plane distance
   of moby+0xE0 row against its position + moby+0x70, moby+0x74; the row; a colour quadword from D_001B1B90[moby+0xBD] or
   (0,0,0,1) - row) and the class's point records transformed through the scratchpad joint matrices (0x70000000 + 64 j),
   scaled by moby+0x2C/1024 * scale/4096, and through the moby matrix: 32-byte single-joint records, 48-byte two-joint
   segments whose ends are pulled in by negative weights. Ends with a zero quadword. */
void func_002DFD88(void)
{
    int n = D_001B1B7C;
    unsigned char *e = D_001EF160;
    unsigned char *out = D_001EF2E0;
    unsigned char *lim = D_001EF2E0 + 8064;

    do {
        char *moby = *(char **)e;
        char *cls = *(char **)(moby + 0x24);
        unsigned int sc, tag;
        float scale;
        float *r0, *r1, *r2, *pos;
        unsigned char *rec;
        unsigned char *hdr;
        int count;
        int stop;
        int ci;
        unsigned int col[4];

        n--;
        func_002A3110(moby, *(unsigned char *)(cls + 8), -1);
        sc = *(unsigned short *)(e + 4);
        tag = *(unsigned short *)(e + 6);
        e += 8;
        scale = *(float *)(moby + 0x2C) * bits_002DFD88(0x3A800000);
        scale = scale * ((float)(int)sc * (1.0f / 4096.0f));
        rec = *(unsigned char **)(cls + 0x14) - *(unsigned char *)(cls + 0xF) * 16;
        r0 = (float *)(moby + 0xC0);
        r1 = (float *)(moby + 0xD0);
        r2 = (float *)(moby + 0xE0);
        pos = (float *)(moby + 0x10);
        if ((int)(out - lim) > 0) {
            break;
        }
        ci = *(signed char *)(moby + 0xBD);
        hdr = out;
        {
            float px = r2[0] * pos[0], py = r2[1] * pos[1], pz = r2[2] * pos[2];
            float acc = px + py;
            float d;
            unsigned int w116 = *(unsigned int *)(moby + 0x74);
            int j;

            acc = acc + 1.0f * pz;
            d = acc + 1.0f * *(float *)(moby + 0x70);
            for (j = 0; j < 4; j++) {
                ((unsigned int *)(out + 16))[j] = ((unsigned int *)r2)[j];
            }
            count = 0;
            if (ci * 16 < 0) {
                float *c = (float *)col;
                c[0] = 0.0f - r2[0];
                c[1] = 0.0f - r2[1];
                c[2] = 0.0f - r2[2];
                c[3] = 1.0f - r2[3];
            } else {
                for (j = 0; j < 4; j++) {
                    col[j] = D_001B1B90[ci * 4 + j];
                }
            }
            *(unsigned int *)(out + 4) = tag;
            *(float *)(out + 8) = d;
            *(unsigned int *)(out + 12) = w116;
            for (j = 0; j < 4; j++) {
                ((unsigned int *)(out + 32))[j] = col[j];
            }
            out += 48;
        }
        stop = 0;
        for (;;) {
            unsigned int kind;

            if (stop != 0) {
                break;
            }
            kind = rec[0];
            stop = rec[1];
            if (kind == 0) {
                float *m = (float *)(0x70000000 + *(int *)(rec + 4) * 64);
                unsigned int v0 = *(unsigned int *)(rec + 8);
                float p[4];
                int j;

                count++;
                xform_002DFD88(p, m, m + 4, m + 8, m + 12, (float *)(rec + 16));
                for (j = 0; j < 4; j++) {
                    p[j] = p[j] * scale;
                }
                xform_002DFD88(p, r0, r1, r2, pos, p);
                *(unsigned int *)(out + 0) = kind;
                *(unsigned int *)(out + 4) = v0;
                *(unsigned int *)(out + 8) = 0;
                *(unsigned int *)(out + 12) = 0;
                for (j = 0; j < 4; j++) {
                    ((float *)(out + 16))[j] = p[j];
                }
                out += 32;
                rec += 32;
            } else {
                float *ma = (float *)(0x70000000 + *(unsigned short *)(rec + 4) * 64);
                float *mb = (float *)(0x70000000 + *(unsigned short *)(rec + 6) * 64);
                float a[4], b[4];
                int wa, wb;
                int j;

                xform_002DFD88(a, ma, ma + 4, ma + 8, ma + 12, (float *)(rec + 16));
                xform_002DFD88(b, mb, mb + 4, mb + 8, mb + 12, (float *)(rec + 32));
                for (j = 0; j < 4; j++) {
                    a[j] = a[j] * scale;
                }
                for (j = 0; j < 4; j++) {
                    b[j] = b[j] * scale;
                }
                wa = *(int *)(rec + 8);
                wb = *(int *)(rec + 12);
                xform_002DFD88(a, r0, r1, r2, pos, a);
                xform_002DFD88(b, r0, r1, r2, pos, b);
                if (wa < 0) {
                    float t = (float)(int)(-wa << 4) * (1.0f / 4096.0f);
                    for (j = 0; j < 3; j++) {
                        float dd = a[j] - b[j];
                        dd = dd * t;
                        a[j] = a[j] + dd;
                    }
                    wa = 0;
                }
                if (wb < 0) {
                    float t = (float)(int)(-wb << 4) * (1.0f / 4096.0f);
                    for (j = 0; j < 3; j++) {
                        float dd = b[j] - a[j];
                        dd = dd * t;
                        b[j] = b[j] + dd;
                    }
                    wb = 0;
                }
                *(unsigned int *)(out + 0) = kind;
                *(unsigned int *)(out + 12) = 0;
                *(int *)(out + 4) = wa;
                *(int *)(out + 8) = wb;
                for (j = 0; j < 4; j++) {
                    ((float *)(out + 16))[j] = a[j];
                    ((float *)(out + 32))[j] = b[j];
                }
                out += 48;
                count++;
                rec += 48;
            }
        }
        *(int *)hdr = count;
    } while (n > 0);
    {
        int j;
        for (j = 0; j < 4; j++) {
            ((unsigned int *)out)[j] = 0;
        }
    }
}
