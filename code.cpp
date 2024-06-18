struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};

	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n = 0) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 1) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
        int L = 30;
		do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
 
struct gomory_hu
{
	struct edg
	{
		int u, v, cap;
	};
 
    Dinic dinic;
 
	vector<edg> edgs;
 
	void add_edge(int u, int v, int cap)
	{
		edgs.push_back({u, v, cap});
	}
 
	vector<int> vis;
 
	void dfs(int a)
	{
		if (vis[a])
			return;
		vis[a] = 1;
		for (auto &e : dinic.adj[a])
			if (e.c - e.flow() > 0)
				dfs(e.to);
	}
 
	vector<pair<ll, int>> solve(int n) 
	{					   
		vector<pair<ll, int>> retv(n); // if i > 0, stores pair(cost, 
									   // parent).
		for (int i = 1; i < n; i++)
		{
            dinic = Dinic(n);
 
			for (auto &e : edgs)
				dinic.addEdge(e.u, e.v, e.cap);
    
			retv[i].first = dinic.calc(i, retv[i].second);
			
			vis.assign(n, 0);
			dfs(i);
 
			for (int j = i + 1; j < n; j++)
				if (retv[j].second == retv[i].second && vis[j])
					retv[j].second = i;
		}
 
		return retv;
	}
};
