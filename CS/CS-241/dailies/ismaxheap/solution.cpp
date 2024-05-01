#include <cmath>

/*<note> 
Derivation of #leaf formula:
    To compute the number of leaf nodes in this tree, we need two quantitys, 
    \begin{enumerate}
        \item The number of unfilled nodes at depth $d$
        \item The number of leaf nodes at depth $d-1$
    \end{enumerate}
    \bigbreak \noindent 
    To find the number of unfilled nodes at depth $d$, we use
    \begin{align*}
        n - (2^{d} -1) = n-2^{d} + 1
    .\end{align*}
    The quantity $2^{d}-1$ returns the number of nodes at depth $d-1$, Hence, subtracting $n$ from this quantity gives the number of leaf nodes at depth $d$
    \bigbreak \noindent 
    To find the number of leaf nodes at depth $d-1$, we use
    \begin{align*}
        \floor{
            \frac{2^{d+1}-n-1}{2}
        }
    .\end{align*}
    Where $d$ is the depth of the tree, and $n$ is the total number of nodes in the tree. The idea behind this formula is, we find the total number of possible nodes at depth $d$ ($2^{d}$), then subtract the number of leaf nodes at depth $d$ to get the number of nodes it will take to completly fill $d$, divding by 2 gives the number of leaf nodes at depth $d-1$ (flooring the result of course).
    \bigbreak \noindent 
    The summation of these results gives the total number of leaf nodes $L$. That is,
    \begin{align*}
        L = \floor{\frac{2^{d+1}-n-1}{2}} + (n-2^{d}+1)
    .\end{align*}

Finding depth $d$ is easy we just use logarithms to inverse the exponential property of bintrees

</note>*/

bool is_max_heap(int a[], int n) {

    int depth = log2(n);
    int leaf = (pow(2,(depth + 1)) - n -1) / 2 + (n - pow(2,depth) + 1);

    for (int i=0,j=1,k=2; i<(n-leaf); ++i, j=j+2, k=k+2) {
        if (a[i] < a[j] || a[i] < a[k]) {
            return false;
        }
    }

    return true;
}

