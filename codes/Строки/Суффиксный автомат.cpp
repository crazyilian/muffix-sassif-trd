struct Node {
    int go[26];
    int suf;
    int len;
};
Node verts[MAXN];
int cnt_v = 1;
int max_v = 0;

void add(char c) {
    c -= 'a';
    int nv = cnt_v++;
    verts[max_v].go[c] = nv;
    verts[nv].len = verts[max_v].len + 1;
    int v = max_v;
    while (v != 0) {
        if (verts[verts[v].suf].go[c] == 0) {
            v = verts[v].suf;
            verts[v].go[c] = nv;
            verts[nv].len = max(verts[nv].len, verts[v].len + 1);
            continue;
        }
        int vv = verts[v].suf, uu = verts[vv].go[c];
        if (verts[vv].len + 1 == verts[uu].len) {
            verts[nv].suf = uu;
            break;
        }
        int v2 = cnt_v++;
        for (int c2 = 0; c2 < 26; c2++) {
            verts[v2].go[c2] = verts[uu].go[c2];
        }
        int to = verts[vv].go[c];
        do {
            if (verts[vv].go[c] == to) {
                verts[vv].go[c] = v2;
                verts[v2].len = max(verts[v2].len, verts[vv].len + 1);
            } else {
                break;
            }
            vv = verts[vv].suf;
        } while (vv != 0);
        if (verts[vv].go[c] == to) {
            verts[vv].go[c] = v2;
            verts[v2].len = max(verts[v2].len, verts[vv].len + 1);
        }
        verts[v2].suf = verts[uu].suf;
        verts[uu].suf = verts[nv].suf = v2;
        break;
    }
    max_v = nv;
}


