# HashTree
## Abstract
#### “The only thing that grows faster than computer performance is expectation.” – Bjarne Stroustrup.

#### In computer science, new data structures are often adopted rapidly because they promise performance improvements. One of the most widely used is the Hash Map, which excels in average-case efficiency. Its fundamental operations—find, insert, and remove—can all be performed in $O(1)$ time on average, with space complexity $O(n)$. However, its performance suffers in the worst case, degrading to $O(n)$ due to hash collisions.

#### Traditional collision resolution strategies such as open addressing (probing) or separate chaining with linked lists do little to mitigate this issue. Linked lists, in particular, are inefficient for repeated lookups. This raises an important question: what if we could preserve the $O(1)$ average-case behavior of hash maps, but guarantee a better worst-case bound?

#### The idea is to replace the linked list traditionally used in separate chaining with a balanced binary search tree, specifically an AVL tree. This ensures that in the rare event of a collision, the operations degrade only to $O(\log n)$ instead of $O(n)$. In effect, this hybrid approach combines the strengths of hash maps and AVL trees, achieving $O(1)$ average performance with $O(\log n)$ guaranteed in the worst case.

## Related Work: 
#### Java’s HashMap standard library implements collision resolution using linked lists, which were later optimized by replacing them with Red-Black Trees to improve worst-case performance. While Red-Black Trees offer balanced insertion and lookup, they are not strictly height-balanced. In contrast, our design integrates an AVL tree as the collision resolution structure. Since AVL trees maintain stricter balancing than Red-Black Trees, this ensures a tighter bound on tree height and guarantees $O(\log n)$ performance in the worst case for find, insert, and remove operations, while preserving $O(1)$ average-case performance from hashing.

## Data Structure Design:
#### The data structure hashes element objects into an array of buckets. In the event of a collision (when the mapped element contains the same index of an already existing element represented as the bucket head pointer), each bucket maintains the strict balancing properties of an AVL tree. 

![](Design.png)

#### The find, insert, and remove operations begin with hashing, yielding $O(1)$ average-case access to the appropriate bucket. When collisions occur, the structure leverages the AVL tree within that bucket, ensuring a strict $O(\log n)$ worst-case bound for subsequent operations. This guarantee arises from the unique balancing mechanism of AVL trees: each node maintains a balance factor, and whenever the factor exceeds $1$ or $-1$, a rotation is performed to restore balance. As a result, the tree’s height is constrained to $O(\log n)$, in contrast to the potential $O(n)$ height of an unbalanced binary search tree. Below are the 4 cases of rotations required for balancing: 

![](Rotation4.png)

## Complexity Analysis: 
#### Lemma 1 (Average Case) : Under uniform hashing bounded by a constant load factor $\alpha$, the HashTree data structure has an expected $O(1)$ time complexity on find, insert, and remove operations.

$proof:$ Let $\alpha$ be the load factor calculated by $n/m$ where $n$ is the number of elements and $m$ is the number of buckets. This is bounded by a given constant $\alpha$ < $0.75$ = $O(1)$ necessary for resizing.
1. By uniform hashing, the expected number of elements in any bucket is $E[k]$ = $\alpha$ = $O(1)$, where $k$ is the number of elements in the bucket.
2. Each operation first calculates the hash and index of the bucket in $O(1)$.
3. Each bucket contains a balanced tree, so for an operation within a bucket containing $k$ elements, it cost $O(\log k + 1)$ time. Since $\log(k + 1)$ ≤ $k$, then we have $E[log(k + 1)$] ≤ $E[k]$ = $\alpha$ = $O(1)$. Therefore, the expected cost of operating within a bucket is $O(1)$ time.
   
We can now combine points 2 and 3 to get an overall expected $O(1)$ time complexity for the find, insert, and remove operations.

#### Lemma 2 (Worst Case) : The HashTree data structure guarantees a worst case time complexity of $O(\log n)$ for the find, insert, and remove operations.

$proof:$ In the worst case of maximum collisions, the bucket contains the structure of a balanced tree of height $h$. Suppose $N(h)$ is the minimum number of nodes, then we get the recurrence $N(h)$ = 1 + $N(h - 1)$ + $N(h - 2)$, growing asymptotically like the Fibonacci sequence. Thus we get $N(h)$ ≥ $Fib_{h + 2}$ where $Fib_{h + 2}$ grows as Θ($\phi^{h}$), thats is $\phi$ being the golden ratio $(1 + (5)^{1/2}) / 2$. This means to get the height of the balanced tree, we must do the logarithmic calculation to get $h$ = $O(\log k)$ where $k$ is the number of nodes/elements in the bucket.

Since $k$ ≤ $n$ where $n$ is the total number of nodes in the entire data structure, then we have $O(\log k)$ ⊆ $O(\log n)$ and in the maximum collision worst case, we have that $k$ = $n$, thus $O(\log k)$ = $O(\log n)$

#### Remark: These complexities are guaranteed on regular use operations. If the load factor exceeds $0.75$, resizing of the buckets array will cost a $O(n)$ pause for migrating the elements of the current array into the new resized array since we still get $O(\log n)$ on the find, insert, and remove operations. The space complexity of the HashTree data stucture is $O(n)$ where $n$ is the number of elements. More memory pointers are used than the standard hash map with seperate chaining (linked list) collision resolulion strategy.

## Benchmarks:
#### When running benchmark tests (using a helper file generated by AI), I compared the performance of my HashTree data structure against the standard C++ baseline unordered_map. The benchmarks measured the performance of the find, insert, and remove operations over 100,000 iterations, covering both average-case and worst-case scenarios. The results were as follows:

```
=== Benchmark: Average Case (unique keys) ===
unordered_map -> find: 4 ms, insert: 44 ms, remove: 17 ms
HashTree -> find: 1 ms, insert: 21 ms, remove: 4 ms

=== Benchmark: Worst Case (all collide) ===
unordered_map -> find: 4 ms, insert: 14 ms, remove: 3 ms
HashTree -> find: 1 ms, insert: 9 ms, remove: 1 ms
```

## Implementation:
#### The HashTree data structure was implemented to efficiently handle mappings between meteorite masses and their corresponding names or locations. Each entry uses the meteorite’s mass (in kilograms) as the key, with the meteorite’s name as the associated value. This design allows for fast lookups, insertions, and deletions while maintaining predictable performance even in the presence of collisions. It enables fast queries on mass-based keys, allowing astronomers to quickly identify and compare meteorites of interest near constant times even in large datasets.

```
// testing find method
This should be Aarhus: Aarhus
This should be San Diego: San Diego
This should be Acapulco: Acapulco
// testing remove method
This should be true: 1
This should be true: 1
This should be false: 0
// testing size method
This should be size 1: 1
```
## Resources:
#### Paper on AVL Trees: https://github.com/eduardolopez858/HashTree/blob/main/PaperAVL.pdf
#### Paper on HashMaps: https://github.com/eduardolopez858/HashTree/blob/main/PaperHash.pdf
#### Script for HashTree class: https://github.com/eduardolopez858/HashTree/blob/main/HashTree.h
#### Script for HashTree methods implementation: https://github.com/eduardolopez858/HashTree/blob/main/HashTree.cpp
#### Script for main method (simple meteorite implementation): https://github.com/eduardolopez858/HashTree/blob/main/main.cpp
#### Script for benchmarking: https://github.com/eduardolopez858/HashTree/blob/main/benchmark.cpp
#### Standard Template Library: https://www.geeksforgeeks.org/cpp/the-c-standard-template-library-stl/

