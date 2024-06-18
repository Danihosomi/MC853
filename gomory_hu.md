# Gomory Hu Tree


## Definition



## Algorithm with Gusfield's Simplification


### Implementation


```{.cpp file=gomoryhu}
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
```

## Applications


## Practice Problems
