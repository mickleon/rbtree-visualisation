#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "rbtree.h"

using std::vector, std::cout, std::setw;

Node::Node(int value): inf(value), left(nullptr), right(nullptr), parent(nullptr), color('r') {}

RBTree::RBTree(): root(nullptr) {}

// "nullptr" node that used for `print(show_null_leaves = true)`
Node *RBTree::NIL = new Node(0);

RBTree::~RBTree() {
    clear(this->root);
}

// Rotates the tree to the left around the node `p`
void RBTree::left_rotate(Node *p) {
    if (p == nullptr || p->right == nullptr) {
        return;
    }

    Node *c = p->right;
    p->right = c->left;
    if (c->left != nullptr) {
        c->left->parent = p;
    }

    c->parent = p->parent;
    if (c->parent == nullptr) {
        this->root = c;
    } else if (p == p->parent->left) {
        p->parent->left = c;
    } else {
        p->parent->right = c;
    }

    c->left = p;
    p->parent = c;
}

// Rotates the tree to the right around the node `p`
void RBTree::right_rotate(Node *p) {
    if (p == nullptr || p->left == nullptr) {
        return;
    }

    Node *c = p->left;
    p->left = c->right;
    if (c->right != nullptr) {
        c->right->parent = p;
    }

    c->parent = p->parent;
    if (c->parent == nullptr) {
        this->root = c;
    } else if (p == p->parent->right) {
        p->parent->right = c;
    } else {
        p->parent->left = c;
    }

    c->right = p;
    p->parent = c;
}

// Inserts node with value `value` to a tree and calls the fixup function
void RBTree::insert(int value) {
    Node *temp = this->root;
    while (temp != nullptr) {
        if (value < temp->inf && temp->left != nullptr) {
            temp = temp->left;
        } else if (value > temp->inf && temp->right != nullptr) {
            temp = temp->right;
        } else if (value != temp->inf) {
            break;
        } else {
            return;
        }
    }

    Node *node = new Node(value);
    if (temp == nullptr) {
        this->root = node;
    } else {
        node->parent = temp;
        if (value < temp->inf) {
            temp->left = node;
        } else {
            temp->right = node;
        }
    }
    this->insert_fixup(node);
}

// Auxullary function for `insert`, it does a fixup of a tree
void RBTree::insert_fixup(Node *node) {
    while (node->parent != nullptr && node->parent->color == 'r') {
        Node *g = node->parent->parent;
        if (node->parent == g->left) {
            Node *u = g->right;
            if (u != nullptr && u->color == 'r') { // Uncle is red
                node->parent->color = 'b';
                u->color = 'b';
                g->color = 'r';
                node = g;
            } else {                               // Uncle is black
                if (node == node->parent->right) { // Node is left child
                    node = node->parent;
                    this->left_rotate(node);
                    g = node->parent->parent;
                }
                // Node is right child
                node->parent->color = 'b';
                g->color = 'r';
                this->right_rotate(g);
                break;
            }
        } else { // Symmetricall case
            Node *u = g->left;
            if (u != nullptr && u->color == 'r') { // Uncle is red
                node->parent->color = 'b';
                u->color = 'b';
                g->color = 'r';
                node = g;
            } else {                              // Uncle is black
                if (node == node->parent->left) { // Node is left child
                    node = node->parent;
                    this->right_rotate(node);
                    g = node->parent->parent;
                }
                // Node is right child
                node->parent->color = 'b';
                g->color = 'r';
                this->left_rotate(g);
                break;
            }
        }
    }
    this->root->color = 'b';
}

// Erases the node with value `value` from tree and calls the fixup function
void RBTree::erase(int value) {
    Node *node = this->find(value);
    if (node != nullptr) {
        this->erase_node(node);
    }
}

// Erases the node `node` from tree and calls the fixup function
void RBTree::erase_node(Node *node) {
    if (node->left != nullptr || node->right != nullptr) { // If `node` has children ...
        Node *temp;
        if (node->left == nullptr) {
            temp = node->right;
        } else if (node->right == nullptr) {
            temp = node->left;
        } else {
            temp = this->min(node->right);
        }
        node->inf = temp->inf;
        node = temp; // ... redefine `node` as his childless descendant
    }

    if (node->parent == nullptr) { // Root
        this->root = nullptr;
    } else {
        if (node->color == 'b') {
            this->erase_fixup(node);
        }
        if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
    }
    delete node;
}

// Auxullary function for `erase`, it does a fixup of a tree
void RBTree::erase_fixup(Node *node) {
    while (node->parent != nullptr && node->color == 'b') {
        if (node == node->parent->left) {
            Node *s = node->parent->right;
            if (s != nullptr && s->color == 'r') { // Sibling is red
                s->color = 'b';
                node->parent->color = 'r';
                this->left_rotate(node->parent);
                s = node->parent->right;
            }
            if ((s->left == nullptr || s->left->color == 'b') &&
                (s->right == nullptr ||
                 s->right->color == 'b')) { // Sibling and his children is black
                s->color = 'r';
                node = node->parent;
            } else { // Sibling is black, his left child is red, right is black
                if ((s->right == nullptr || s->right->color == 'b')) {
                    if (s->left != nullptr) {
                        s->left->color = 'b';
                    }
                    s->color = 'r';
                    this->right_rotate(s);
                    s = node->parent->right;
                }
                // Sibling is black, his right child is red
                s->color = node->parent->color;
                node->parent->color = 'b';
                if (s->right != nullptr) {
                    s->right->color = 'b';
                }
                this->left_rotate(node->parent);
                node = this->root;
            }
        } else { // Symmetrical case
            Node *s = node->parent->left;
            if (s != nullptr && s->color == 'r') { // Sibling is red
                s->color = 'b';
                node->parent->color = 'r';
                this->right_rotate(node->parent);
                s = node->parent->left;
            }
            if ((s->left == nullptr || s->left->color == 'b') &&
                (s->right == nullptr ||
                 s->right->color == 'b')) { // Sibling and his children is black
                s->color = 'r';
                node = node->parent;
            } else { // Sibling is black, his right child is red, left is black
                if ((s->left == nullptr || s->left->color == 'b')) {
                    if (s->right != nullptr) {
                        s->right->color = 'b';
                    }
                    s->color = 'r';
                    this->left_rotate(s);
                    s = node->parent->left;
                    node->parent = node->parent;
                }
                // Sibling is black, his left child is red
                s->color = node->parent->color;
                node->parent->color = 'b';
                if (s->left != nullptr) {
                    s->left->color = 'b';
                }
                this->right_rotate(node->parent);
                node = this->root;
            }
        }
    }
    node->color = 'b';
}

// Returns a pointer to a node in the subtree `node` with the value `value`
Node *RBTree::find(Node *node, int value) const {
    if (node == nullptr || node->inf == value) {
        return node;
    }

    if (value < node->inf) {
        return this->find(node->left, value);
    }
    return this->find(node->right, value);
}

// Overload of previous function, where `node` is a tree root `this->root`
Node *RBTree::find(int value) const {
    return this->find(this->root, value);
}

// Returns a pointer to a node in the subtree `node` with the maximal value
Node *RBTree::max(Node *node) const {
    if (node == nullptr) {
        return nullptr;
    }

    Node *y = node;
    while (y->right != nullptr) {
        y = y->right;
    }
    return y;
}

// Overload of previous function, where `node` is a tree root `this->root`
Node *RBTree::max() const {
    return this->max(this->root);
}

// Returns a pointer to a node in the subtree `node` with the minimal value
Node *RBTree::min(Node *node) const {
    if (node == nullptr) {
        return nullptr;
    }
    Node *y = node;
    while (y->left != nullptr) {
        y = y->left;
    }
    return y;
}

// Overload of previous function, where `node` is a tree root `this->root`
Node *RBTree::min() const {
    return this->min(this->root);
}

int RBTree::height(Node *node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(this->height(node->left), this->height(node->right));
}

// Overload of previous function, where `node` is a tree root `this->root`
int RBTree::height() const {
    return this->height(this->root);
}

// Traversal with depth calculation and node offset from the left edge of the
// level
void RBTree::make_array(
    vector<vector<Node *>> &array, Node *node, bool show_null_leaves, int depth, int count
) const {
    array[depth][count - (1 << depth)] = node;

    if (node->left != nullptr) {
        this->make_array(array, node->left, show_null_leaves, depth + 1, count * 2);
    } else if (show_null_leaves) {
        array[depth + 1][count * 2 - (1 << (depth + 1))] = RBTree::NIL;
    }

    if (node->right != nullptr) {
        this->make_array(array, node->right, show_null_leaves, depth + 1, count * 2 + 1);
    } else if (show_null_leaves) {
        array[depth + 1][count * 2 + 1 - (1 << (depth + 1))] = RBTree::NIL;
    }
}

// The number of characters to output the number
int digit_count(int x) {
    if (x > 0) {
        return log10(x) + 1;
    } else if (x < 0) {
        return log10(abs(x)) + 2;
    } else {
        return 1;
    }
}

// Auxulary function for the `print`, it outputs one node `node` with width `width` and color. If
// `node == RBTree::NIL`, it outputs `n`
void RBTree::print_node(Node *node, int width = 0) {
    if (node == nullptr) {
        if (width > 0) {
            cout << setw(width) << ' ';
        }
    } else if (node == RBTree::NIL) {
        cout << setw(width) << 'n';
    } else if (node->color == 'r') {
        cout << "\033[31m" << setw(width) << node->inf << "\033[0m";
    } else {
        cout << setw(width) << node->inf;
    }
}

// Function for tree output
void RBTree::print(bool show_null_leaves) const {
    if (this->root == nullptr) {
        std::cout << "NULL TREE\n";
        return;
    }

    // Maximum number of digit of node in tree
    int d = std::max(digit_count(this->max()->inf), digit_count(this->min()->inf));
    int width, offset = 1;

    vector<vector<Node *>> array;
    array.assign(show_null_leaves ? (this->height() + 1) : this->height(), {});
    for (vector<Node *> &level : array) {
        level.assign(offset, nullptr);
        offset <<= 1;
    }
    this->make_array(array, this->root, show_null_leaves);

    // TODO: don't use offset in loop
    for (vector<Node *> &level : array) {
        offset >>= 1;
        width = (d + 1) * offset / 2;
        for (auto node : level) {
            RBTree::print_node(node, width);
            width = (d + 1) * offset;
        }
        cout << '\n';
    }
}

// Erases all the nodes from the subtree `node`
void RBTree::clear(Node *node) {
    if (node != nullptr) {
        this->clear(node->left);
        this->clear(node->right);
        delete node;
    }
}

// Overload of previous function, where `node` is a tree root `this->root`
void RBTree::clear() {
    return this->clear(this->root);
}
