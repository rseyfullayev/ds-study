As we know from [AVL]. If the binary tree is unbalanced it can be extremely huge, which can lead to inefficiencies.

In order to decrease the number of heights in the tree we use multi-way trees ( e.g. a binary tree is 2-way tree.

Multiway trees have some requirements:

- Each node can have 0-m subtrees
- A node with k subtrees has exactly k-1 data entries. ( e.g. Imagine we have two entries. we gonna have 3 subtrees that follow following restrictions: First subtree: keys $< k_1$ Second Subtree: $k_1$ < keys < $k_2$ Third: keys $> k_2$.
- The keys are sorted in non-decreasing order ( the difference between data points of the next and the previous entry can be 0! but not negative that fact is important - M-way trees allow _duplicates_)
- each subtree of m-way tree is also m-way tree. ( I mean, obvious no? )

Each node consists of entries that lead to other nodes. Thus, we gonna have two structures. First one, an entry structure that consists of individual entries within the node and each one of them store the key data ( or some pointer to another structure where data is stored ) and of-course the pointer to the right subtree. Why it is right? Because the as we said before if we have k entries we will have k+1 pointers that point to other nodes. In practice, we usually assign first pointer in the node itself and the second ones to the _right_ of the data-itself.

```c
typedef struct Entry {
	int data; // or pointer to another struct
	struct Node* right;
} Entry;
```

The second structure belongs to the node itself that contains all entriees. Because node contains the entries, the Node will have a first pointer that we mentioned before and array of Entry pointers and the number of entries themselves.

```c
typedef struct Node {
	struct Node* firstPtr;
	int nEntries;
	Entry entries[M-1];
} Node;
```

Here, _M_ is maximum allowed number of entries for each node. Because firstPtr contains the first one we shall omit one of them; thus, _M-1_ is the length of the array.
