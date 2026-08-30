// int find(int x){
//     if (fa[x]==x) return x;
//     return fa[x]=find(fa[x]);
// }
// bool connect(int x, int y){
//     int xx = find(x), yy = find(y);
//     if (xx == yy) return 0;
//     U.push_back(x); V.push_back(y);
//     G[x].push_back({y, cnt});
//     deg[x]++;
//     G[y].push_back({x, cnt++});
//     deg[y]++;
//     fa[xx] = yy;
//     cc--;
//     return 1;
// }