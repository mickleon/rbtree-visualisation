#ifndef TREE_H
#define TREE_H
#include <ostream>
#include <vector>

using std::ostream, std::vector;

struct Node {
    int inf;
    Node *left, *right;
    Node *parent;
    char color;

    Node(const int value);
};

class RBTree {
public:
    bool show_null_leaves;
    RBTree();

    ~RBTree();

    void insert(const int value);
    void erase(const int value);
    Node *find(const int value) const;
    int max() const;
    int min() const;
    void clear();

    friend ostream &operator<<(ostream &ostream, const RBTree &tr);

private:
    Node *root;
    static const Node *NIL;

    void right_rotate(Node *p);
    void left_rotate(Node *p);
    void insert_fixup(Node *node);
    void erase_node(Node *node);
    void erase_fixup(Node *node);
    Node *find(Node *node, const int value) const;
    Node *max(Node *node) const;
    Node *min(Node *node) const;
    void clear(Node *node);
    int height(const Node *node) const;
    int height() const;
    void make_array(
        vector<vector<const Node *>> &array, const Node *node, const int depth = 0,
        const int count = 1
    ) const;

    friend ostream &operator<<(ostream &ostream, const Node *node);
};
#endif
