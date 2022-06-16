#include <iostream>
#include "B.cpp"
#include "AVL.cpp"
#include "BPlus.cpp"

using namespace std;

int main() {
    AVL* avl = new AVL();
    Node* raiz = NULL;
    B* b = new B();

    int i, n, t;
    cout << "enter the number of elements to be inserted\n";
    cin >> n;

    BPTree *bptree = new BPTree(n);

    for (i = 0; i < n; i++) {
        cout << "enter the element\n";
        cin >> t;
        b->insert(t);
        bptree->insert(t);
        raiz = avl->insertarNodo(raiz, t);
    }

    cout << "AVL tree\n";
    avl->pintarArbol(raiz, "", true);

    cout << "traversal of constructed B tree\n";
    b->traverse(b->r);

    cout << "BPlus Tree\n";
    bptree->printNode(bptree->root);

}