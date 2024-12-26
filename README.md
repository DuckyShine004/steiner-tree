# steiner-tree
C++ implementation of Steiner trees based on a MST approximation. It is used to solve and optimise (combinatorial) graph problems given that the graph problem itself is NP-hard.

The time complexity of this algorithm is $O(E\cdot V^2)$. Refer to the references section for more information.

### Input Format
First line:
* Contains two space separated integers:
  * $E$: the number of edges minus one. It is the upper bound for vertex numbers in the range of $1\leq x\leq E$.
  * $V$: the number of terminal nodes.

Next $E - 1$ lines:
* Contains two space separated integers:
  * $u$: the node directly connects to $v$.
  * $v$: the node directly connects to $u$.
  * Forms an edge $uv$.

Last line:
* Contains $V$ space separated integers denoting the number of each terminal node.

> [!IMPORTANT]  
> Create an input file in the project directory `data/inputs/` under any name. Create an output file in the project directory `data/outputs/` under the same name.

### Compilation
To compile and run the code against some input, use the following command:
```sh
./compile.sh main <input-filename>
```

Where `input-filename` is the name of the input file.

### License

Distributed under the `MIT License`. See `LICENSE.txt` for more information.

### References
[1] Wu, B. Y., & Chao, K. M. (n.d.). Steiner minimal trees∗. Steiner Minimal Trees*. https://www.csie.ntu.edu.tw/~kmchao/tree10spr/Steiner.pdf 
