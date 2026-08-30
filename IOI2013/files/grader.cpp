#include "artclass.h"

static int DIM[2];
static int R[500][500];
static int G[500][500];
static int B[500][500];

int main() {
    assert(scanf("%d",&DIM[1]) == 1);
    assert(scanf("%d",&DIM[0]) == 1);
    for (int i = 0; i < DIM[0]; i++)
        for (int j = 0; j < DIM[1]; j++)
            assert(scanf("%d %d %d",&R[i][j], &G[i][j], &B[i][j]) == 3);
    printf("%d\n", style(DIM[0], DIM[1], R, G, B));
    return 0;
}
