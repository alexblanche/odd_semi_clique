# Odd semi-cliques

## Context

A path-decomposition is a partition of the edges of an undirected graph into simple paths. In 1968, Tibor Gallai conjectured that any connected graph with n vertices had a path-decomposition into ceiling(n/2) paths. This conjecture is still open as of today.
For more info, my PhD thesis on the subject: https://www.labri.fr/perso/ablanche/data/Manuscript.pdf

An odd semi-clique is a complete graph K_{2k+1} from which at most k-1 edges have been removed. This class of dense graphs is known to require at least ceiling(n/2) paths, while a better bound of floor(n/2) has been proven for many different classes. It has been conjectured (Bonamy, Perrett, 2016) that any connected graph that is not an odd semi-clique has a path-decomposition into floor(n/2) paths.

## My method

While lots of sparse graph classes have been proven to satisfy Gallai's bound (and the stronger floor(n/2) bound), not much is known for dense graphs. In order to tackle the class of odd semi-cliques, I imagined the following method for finding a decomposition into ceil(n/2) paths. Here n = 2k+1, we refer to paths as colors, the (at most k-1) edges removed from the complete graph are called anti-edges, and they form the anti-graph.

1. Start by coloring the complete graph K_{2k} with the "zig-zagging" coloring due to Walecki (1883) (see page 30 of my thesis). This coloring can be formalized algebraically as follows: the vertices of the graph are labeled 0,1,...,2k-1, the colors are 0,1,...,k-1, and the color i is the set of edges {uv\in E(G), s.t. floor((u+v)/2) = i (mod k)}.

Remark: the Walecki coloring is the only one I know that achieves a Gallai-decomposition of the complete graph.

2. Place the anti-graph (of at most k-1 anti-edges) in the colored K_{2k} such that the anti-edges have different colors.
This corresponds to labeling the vertices of the anti-graph injectively in such a way that the labeling f(uv) = floor((u+v)/2) (mod k) distinguishes all the anti-edges. I call graphs having this property "soft-mean", by analogy to "mean graphs" who have a similar definition.

3. Find a "gray path" that uses exactly one edge from each unused color (this path does not have to be vertex-disjoint from the anti-graph).

4. Add one vertex that is adjacent with all the vertices from the K_{2k}, and color its incident edges so as to turn all the paths into cycles.

This way, the anti-edges "cut" some colors and turn their cycles into paths, and the gray path cuts the remaining colors. Exactly k+1 = ceiling(n/2) colors are used.

## Experiment

Since I could not prove that all graphs are soft-mean, and before attempting to brute-force all graphs up to a certain size to build confidence, I tried to brute-force the small complete graphs, as I figured that these were the cases most likely to fail.

### Files

The following repository contains two files:
- binomials.c contains functions to compute the binomial coefficients and enumerate the choices of k elements among n.
- mean_graph.c contains functions to search for a soft-mean labeling in a complete graph, check that it is a correct labeling, and print it.

### Conclusion

K_n is soft-mean for n = 2,...,7, and mean_graph.c computes a labeling in each case.
However, K_8 does not seem to have a solution (among ~2 billion possibilities), according to my program. To recap, this means that K8 cannot be embedded into K59 (k-1 = 8*7/2 = 28 so k = 29, n = 2k+1 = 59) in such a way that its edges have different colors in the Walecki coloring.
Therefore, I decided to abandon this strategy.
