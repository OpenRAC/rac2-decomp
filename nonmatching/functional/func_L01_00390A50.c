/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * func_L01_00390A50: exact in 6 of 6 places, all releases, but only with a non-empty do { } while (0) around the forced arm, not landed: that wrapper stays disallowed pending the maintainers' open question (docs/MATCHING-BLOCKERS.md). Without it: 528/528 bytes, 0/6 places, 25 instructions differ, all flag/settings s3/s4 swaps. local-alloc doubles flag's live length (first set is a constant), so flag needs 16 weighted refs, has 14; find retail's own source of those 2 refs.
 */
void func_L01_00390A50(char *object)
{
    SpatialTriggerSettings *settings;
    ClosestPointQuad point;
    int flag = 0;
    int i;
    int j;
    int k;
    int *mobys;
    int forced;
    char *path;

    settings = *(SpatialTriggerSettings **)(object + 0x68);
    *(unsigned char *)(object + 0x30) = 0xFF;
    if (settings->switches[2])
        qcopy(&point, D_L01_001B94C0);
    else
        qcopy(&point, D_00189EA0);
    forced = *(unsigned char *)(object + 0x95);
    if (forced == 0) {
        if (settings->radius > 0.0f && func_002E3618(object + 0x10, &point) < settings->radius)
            flag = 1;
        if (!flag) {
            if (settings->path != -1) {
                path = D_L01_001FE180[settings->path];
                flag = func_311B48((char *)&point, path + 0x10, *(int *)path) != 0;
            }
        }
        if (!flag) {
            for (i = 0; ; i++) {
                if (i >= 6)
                    goto done;
                if (settings->volumes[i] == -1)
                    continue;
                if (func_3163C8((char *)&point, (void *)settings->volumes[i]))
                    break;
            }
            goto set;
        }
    } else do {
        if (forced == 1) {
set:
            flag = 1;
        } else {
            flag = 0;
        }
    } while (0);
done:
    if ((flag && !*(unsigned char *)(object + 0xBC)) ||
        (!flag && *(unsigned char *)(object + 0xBC)) ||
        !*(unsigned char *)(object + 0x20)) {
        if (flag)
            *(unsigned char *)(object + 0xBC) = 1;
        else
            *(unsigned char *)(object + 0xBC) = 0;
        *(unsigned char *)(object + 0x20) = *(unsigned char *)(object + 0xBC) + 1;
        mobys = settings->mobys;
        for (j = 0; j < 12; j++) {
            if (settings->lists[j] != -1)
                func_L01_003909E0((int)object, (int)settings, settings->lists[j], flag);
        }
        for (k = 0; k < 11; k++) {
            if (mobys[k] != -1)
                func_003907B8(mobys[k], (int)settings, flag);
        }
    }
}
