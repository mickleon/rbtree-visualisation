#include <iostream>

#include "rbtree.h"

int main() {
    using std::cin, std::cout;
    RBTree tr;
    cout << "Number of nodes: ";
    int n, x;
    cin >> n;
    if (n > 0) {
        cout << "Nodes: ";
        for (int i = 0; i < n; i++) {
            cin >> x;
            tr.insert(x);
        }
    }

    char c;
    while (true) {
        cout << tr;
        cout << "1. Insert\n2. Erase\n3. Quit\n> ";
        cin >> c;
        switch (c) {
        case '1': {
            cout << "Node to insert: ";
            cin >> x;
            tr.insert(x);
            break;
        }
        case '2': {
            cout << "Node to erase: ";
            cin >> x;
            tr.erase(x);
            break;
        }
        case '3': return 0;
        case 'q': return 0;
        case 'Q': return 0;
        default: break;
        }
    }
}

/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
