`unordered_map`

avoid when:
- keys can be coordinate-compressed, or a vector works
- millions of entries and memory matters
- worst-case sensitive: O(n) at worst, O(1) average
- contest permits adversarial hacks

```cpp
unordered_map<int, int> hs;
hs.max_load_factor(0.7);
hs.reserve(200000);
```
max_load_factor = number of elements per bucket <= 1, notice this should come before reserve because reserve reserves 200000/0.7 buckets!

## Bit Operations

```cpp
#include <bit>
unsigned x = 40; // 101000
popcount(x); // 2
bit_width(x); // 3
bit_floor(x); // 32
bit_ceil(x); // 64
has_single_bit(x); // 0

x & -x, LSB
x & (x-1), remove LSB
x | (x+1), add lowest 0 bit
(x>>k) & 1

for (int s = mask; s; s = (s-1) & mask)
```

## Bitset

