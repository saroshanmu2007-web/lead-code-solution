class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) { 
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n, 0), heavy(n, -1);
        vector<int> sz(n, 1), head(n), pos(n);
        vector<int> order = {0};

        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            int u = order[i], best = 0;
            for (int v : adj[u]) {
                if (parent[v] == u) {
                    sz[u] += sz[v];
                    if (sz[v] > best) {
                        best = sz[v];
                        heavy[u] = v;
                    }
                }
            }
        }

        int timer = 0;
        vector<pair<int, int>> st = {{0, 0}};

        while (!st.empty()) {
            auto [u, h] = st.back();
            st.pop_back();

            for (int v = u; v != -1; v = heavy[v]) {
                head[v] = h;
                pos[v] = timer++;

                for (int w : adj[v]) {
                    if (parent[w] == v && w != heavy[v])
                        st.push_back({w, w});
                }
            }
        }

        int size = 1;
        while (size < n) size <<= 1;

        vector<int> seg(2 * size, 0);

        for (int i = 0; i < n; i++)
            seg[size + pos[i]] = 1 << (s[i] - 'a');

        for (int i = size - 1; i > 0; i--)
            seg[i] = seg[i * 2] ^ seg[i * 2 + 1];

        auto update = [&](int p, int val) {
            p += size;
            seg[p] = val;
            for (p >>= 1; p; p >>= 1)
                seg[p] = seg[p * 2] ^ seg[p * 2 + 1];
        };

        auto rangeQuery = [&](int l, int r) {
            int res = 0;
            for (l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res ^= seg[l++];
                if (r & 1) res ^= seg[--r];
            }
            return res;
        };

        auto pathQuery = [&](int u, int v) {
            int mask = 0;

            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]])
                    swap(u, v);

                mask ^= rangeQuery(pos[head[u]], pos[u]);
                u = parent[head[u]];
            }

            if (depth[u] > depth[v]) swap(u, v);
            mask ^= rangeQuery(pos[u], pos[v]);

            return mask;
        };

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                s[u] = c;
                update(pos[u], 1 << (c - 'a'));
            } else {
                ss >> v;
                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};