#ifndef TREE_H
#define TREE_H
#include <ostream>
#include <vector>

using std::ostream, std::vector;

class RBTree {
public:
    bool show_null_leaves;
    RBTree();

    ~RBTree();

    struct Node {
        enum Color { BLACK, RED };

        int inf;
        Node *left, *right;
        Node *parent;
        Color color;

        Node(const int value);
    };

    void insert(const int value);
    void erase(const int value);
    RBTree::Node *find(const int value) const;
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
    static Node *find(Node *node, const int value);
    static Node *max(Node *node);
    static Node *min(Node *node);
    static void clear(Node *node);
    static int height(const Node *node);
    void make_array(
        vector<vector<const Node *>> &array, const Node *node, const int depth = 0,
        const int count = 1
    ) const;

    friend ostream &operator<<(ostream &ostream, const Node *node);
};
#endif
