# Odd semi-cliques

## Context

A *path-decomposition* is a partition of the edges of an undirected graph into simple paths. In 1968, Tibor Gallai conjectured that any connected graph with $n$ vertices had a path-decomposition into $\left\lceil n / 2\right\rceil$ paths. This conjecture is still open as of today.  
For more info, my PhD thesis on the subject: https://www.labri.fr/perso/ablanche/data/Manuscript.pdf

An *odd semi-clique* is a complete graph $K_{2k+1}$ from which at most $k-1$ edges have been removed. This class of dense graphs is known to require at least $\left\lceil n / 2\right\rceil$ paths, while a better bound of $\left\lfloor n / 2\right\rfloor$ has been proven for many classes. It has been conjectured (Bonamy, Perrett, 2016) that any connected graph that is not an odd semi-clique has a path-decomposition into $\left\lfloor n / 2\right\rfloor$ paths.

## My method

While lots of sparse graph classes have been proven to satisfy Gallai's bound (and the stronger $\left\lfloor n / 2\right\rfloor$ bound), not much is known for dense graphs. In order to tackle the class of odd semi-cliques, I imagined the following method for finding a decomposition into $\left\lceil n / 2\right\rceil$ paths. Here $n = 2k+1$, we refer to paths as colors, the (at most $k-1$) edges removed from the complete graph are called *anti-edges*, and they form the *anti-graph*.

1. Start by coloring the complete graph $K_{2k}$ with the "zig-zagging" coloring due to Walecki (1883) (see page 30 of my thesis). This coloring can be formalized algebraically as follows: the vertices of the graph are labeled $0, 1, \dots, 2k-1$, the colors are $0, 1, \dots, k-1$, and the color $i$ is the set of edges $\{uv \in E(G),\ \text{s.t.}\ \left\lfloor (u + v) / 2\right\rfloor = i (\mod k)\}$.

**Remark**: the Walecki coloring is the only one I know that achieves a Gallai-decomposition of the complete graph.

2. Place the anti-graph (of at most $k-1$ anti-edges) in the colored $K_{2k}$ such that the anti-edges have different colors.  
This corresponds to labeling the vertices of the anti-graph injectively in such a way that the labeling $f(uv) = \left\lfloor (u + v) / 2\right\rfloor (\mod k)$ distinguishes all the anti-edges. I call graphs having this property *soft-mean*, by analogy to *mean graphs* which have a similar definition.

3. Find a *gray path* that uses exactly one edge from each unused color (this path does not have to be vertex-disjoint from the anti-graph).

4. Add one vertex that is adjacent with all the vertices from the $K_{2k}$, and color its incident edges so as to turn all the paths into cycles.

This way, the anti-edges "cut" some colors and turn their cycles into paths, and the gray path cuts the remaining colors. Exactly $k+1 = \left\lceil n / 2\right\rceil$ colors are used.

## Experiment

Since I could not prove that all graphs are soft-mean, and before attempting to brute-force all graphs up to a certain size to build confidence, I tried to brute-force the small complete graphs, as I figured that these were the cases most likely to fail.  
The parameter ``N`` is defined in the file ``include/parameters.h``.

### Conclusion

$K_n$ is soft-mean for $n = 2, \dots, 7$, and we compute a labeling in each case.  
However, $K_8$ does not seem to have a solution (among ~2 billion possibilities), according to my program. To recap, this means that $K_8$ cannot be embedded into $K_{59}$ ($k - 1 = (8 \times 7)/2 = 28$ so $k = 29$, $n = 2k+1 = 59$) in such a way that its edges have different colors in the Walecki coloring.  
Therefore, I decided to abandon this strategy.
