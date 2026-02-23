#ifndef TREE_H
#define TREE_H
#include <vector>

struct Node {
    int inf;
    Node *left, *right;
    Node *parent;
    char color;

    Node(int value);
};

class RBTree {
public:
    RBTree();

    ~RBTree();

    void insert(int value);
    void erase(int value);
    Node *find(int value) const;
    Node *max() const;
    Node *min() const;
    void print(bool show_null_leaves = false) const;
    void clear();

private:
    Node *root;
    static Node *NIL;
    void right_rotate(Node *p);
    void left_rotate(Node *p);
    void insert_fixup(Node *node);
    void erase_node(Node *node);
    void erase_fixup(Node *node);
    Node *find(Node *node, int value) const;
    Node *max(Node *node) const;
    Node *min(Node *node) const;
    void clear(Node *node);
    int height(Node *node) const;
    int height() const;
    void make_array(
        std::vector<std::vector<Node *>> &array, Node *node, bool show_null_leaves = false,
        int depth = 0, int count = 1
    ) const;
    static void print_node(Node *node, int width);
};
#endif
