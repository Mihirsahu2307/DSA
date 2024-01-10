const int N = 3e5 + 5;
int seg[4 * N], lazy[4 * N], a[N];
 
void push(int si, int l, int r) {
    if (lazy[si]) {
        seg[si] += lazy[si];
        if (l < r) {
            lazy[2 * si + 1] += lazy[si];
            lazy[2 * si + 2] += lazy[si];
        }
        lazy[si] = 0;
    }
}

void build(int l, int r, int i) {
    if(l == r) {
        seg[i] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(l, mid, 2*i + 1);
    build(mid + 1, r, 2*i + 2);
    seg[i] = max(seg[2*i + 1], seg[2*i + 2]);
}
 
void update(int ql, int qr, int val, int l, int r, int si) {
    push(si, l, r);
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        lazy[si] = val;
        push(si, l, r);
        return;
    }
 
    int m = (l + r) >> 1;
    update(ql, qr, val, l, m, 2 * si + 1);
    update(ql, qr, val, m + 1, r, 2 * si + 2);
    seg[si] = max(seg[2 * si + 1], seg[2 * si + 2]);
}
 
int query(int ql, int qr, int l, int r, int si) {
    push(si, l, r);
    if (ql > r || qr < l) return 0ll;
    if (ql <= l && r <= qr) return seg[si];
 
    int m = (l + r) >> 1;
    return max(query(ql, qr, l, m, 2 * si + 1), query(ql, qr, m + 1, r, 2 * si + 2));
}
