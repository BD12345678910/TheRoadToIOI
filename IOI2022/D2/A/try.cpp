
ll P = 1;

precompute size: the number of choices in each subtree


dfs():
for (int v : G[x]){
	P += (sz[x]-sz[v]);
	dfs(v);
	P -= (sz[x]-sz[v]);
}