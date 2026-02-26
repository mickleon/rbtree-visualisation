# Red-black tree visualisation

## What is this?

There is C++ class for red/black tree, that have method for **console output** for tree **without any specific libraries**. The program correctly outputs numbers **with any number of digits**.

## What is it for?

This is a training example of a red/black tree. This may be necessary for those who study C++ and dynamic structures such as trees.

## Run

```bash
g++ main.cpp rbtree.cpp -o main && ./main
```

## Available methods

The following functions are available for working with tree:

- `void RBTree::insert(int value)`: inserts node with value `value` to a tree and calls the fixup function.
- `void RBTree::erase(int value)`: erases the node with value `value` from tree and calls the fixup function.
- `Node* RBTree::find(int value)`: returns a pointer to a node in the tree with the value `value`.
- `Node* RBTree::max()`: returns a pointer to a node in the tree with the maximal value.
- `Node* RBTree::min()`: returns a pointer to a node in the tree with the minimal value.
- `ostream &operator<<(ostream &out, const RBTree &tr)`: outputs the tree to the ostream. If `RBTree::show_null_leaves` is `true` (`false` by default) it displays null leaves.
- `void RBTree::clear()`: erases all the nodes from the tree.

## Example of output

![Tree output](/img/tree_output.png)

With null leaves:

![Tree output with null leaves](/img/tree_output_null_leaves.png)
