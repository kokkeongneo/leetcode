/*
403. Frog Jump

A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.


If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

Note:

The number of stones is ≥ 2 and is < 1,100.
Each stone's position will be a non-negative integer < 231.
The first stone's position is always 0.



Example 1:
[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping 
1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.



Example 2:
[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as 
the gap between the 5th and 6th stone is too large.
*/

typedef struct {
    int *p;
    int n;
    int sz;
} steps_t;

int bs(int *stones, int start, int end, int u) {
    int mid, m;
    
    if (start > end) return -1;
    
    mid = start + (end - start) / 2;
    m = stones[mid];
    
    if (m == u) return mid;
    else if (m < u) return bs(stones, mid + 1, end, u);
    return bs(stones, start, mid - 1, u);
}
void add_step(int *stones, int sz, steps_t *units, int u, int s) {
    int i, j;
    steps_t *steps;
    
    if (s == 0) return;
    
    i = bs(stones, 0, sz - 1, u);
    
    if (i == -1) return;
    
    steps = &units[i];
    
    for (j = 0; j < steps->n; j ++) {
        if (steps->p[j] == s) return;
    }
    
    if (steps->sz == steps->n) {
        if (steps->sz == 0) steps->sz = 10;
        else steps->sz *= 2;
        steps->p = realloc(steps->p, steps->sz * sizeof(int));
        //assert(steps->p);
    }
    steps->p[steps->n ++] = s;
}

bool canCross(int* stones, int stonesSize) {
    steps_t units[1100] = { 0 }, *steps;
    int i, j, u, s;
    bool ans = false;
    
    if (stones[1] != 1) return false;
    
    add_step(stones, stonesSize, units, 1, 1);
    
    for (i = 1; i < stonesSize; i ++) {
        u = stones[i];
        steps = &units[i];
        for (j = 0; j < steps->n; j ++) {
            s = steps->p[j];
            add_step(stones, stonesSize, units, u + s - 1, s - 1);
            add_step(stones, stonesSize, units, u + s,     s);
            add_step(stones, stonesSize, units, u + s + 1, s + 1);
        }
    }
    
    if (units[stonesSize - 1].n > 0) ans = true;
    
    for (i = 0; i < 1100; i ++) {
        if (units[i].p) free(units[i].p);
    }
    
    return ans;
}


/*
Difficulty:Hard


*/
