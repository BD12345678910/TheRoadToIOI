// sometimes naive methods have good complexity...

// subtask 3:

// consider brutally updating the segment tree:
// maintain min and max over interval
// then when a half goes over or under after update,
// we go clamp it by force

// n log n per update??
// yes, but consider amortized: 
// define P = number of different neighbors.


// consider updating interval I, and it contains k of these different neighbors
// then, roughly, each of these k different neighbors costs an additional
// log n to update. roughly (k+1) log n per update
// however, in total, only 2Q different neighbors can ever be produced!
// this gives Q log N

// subtask 4:

// the sequence of moves is universal
// given this sequence, for each box, find the last time the box was empty or full
// this also leads to the final solution.