#include "Node.cpp"
#include <iostream>
#include <cstddef>

using namespace std;

class AVL
{
public:
    //int max(int a, int b);

    // Calcular altura
    int altura(Node* N) {
        if (N == NULL)
            return 0;
        return N->altura;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* newNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->izq = NULL;
        node->der = NULL;
        node->altura = 1;
        return (node);
    }

    // Rotar derecha
    Node* derRotar(Node* y) {
        Node* x = y->izq;
        Node* T2 = x->der;
        x->der = y;
        y->izq = T2;
        y->altura = max(altura(y->izq),
            altura(y->der)) + 1;
        x->altura = max(altura(x->izq),
            altura(x->der)) + 1;
        return x;
    }

    // RotarIzquierda izq
    Node* izqRotar(Node* x) {
        Node* y = x->der;
        Node* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        x->altura = max(altura(x->izq),
            altura(x->der)) +
            1;
        y->altura = max(altura(y->izq),
            altura(y->der)) +
            1;
        return y;
    }

    // Get the balance factor of each node
    int getFactorBalanceo(Node* N) {
        if (N == NULL)
            return 0;
        return altura(N->izq) -
            altura(N->der);
    }

    // Insertar Node
    Node* insertarNodo(Node* node, int key) {

        if (node == NULL) {
            return (newNode(key));
        }

        if (key < node->key)
        {
            node->izq = insertarNodo(node->izq, key);
        }
        else if (key > node->key)
        {
            node->der = insertarNodo(node->der, key);
        }
        else
        {
            return node;
        }


        // actualizar factor de balanceo y balancear el arbol
        node->altura = 1 + max(altura(node->izq), altura(node->der));

        int factorBalanceo = getFactorBalanceo(node);

        if (factorBalanceo > 1) {

            if (key < node->izq->key) {

                return derRotar(node);

            }
            else if (key > node->izq->key) {

                node->izq = izqRotar(node->izq);

                return derRotar(node);
            }
        }
        if (factorBalanceo < -1) {
            if (key > node->der->key) {

                return izqRotar(node);

            }
            else if (key < node->der->key) {

                node->der = derRotar(node->der);

                return izqRotar(node);
            }
        }
        return node;
    }


    void preOrden(Node* arbol)
    {
        if (arbol != NULL)
        {
            cout << arbol->key << " ";
            preOrden(arbol->izq);
            preOrden(arbol->der);
        }
    }

    void enOrden(Node* arbol)
    {
        if (arbol != NULL)
        {
            enOrden(arbol->izq);
            cout << arbol->key << " ";
            enOrden(arbol->der);
        }
    }

    void postOrden(Node* arbol)
    {
        if (arbol != NULL)
        {
            postOrden(arbol->izq);
            postOrden(arbol->der);
            cout << arbol->key << " ";
        }
    }

    void pintarArbol(Node* raiz, string indent, bool last) {
        if (raiz != nullptr) {
            cout << indent;
            if (last) {
                cout << "D----";
                indent += "   ";
            }
            else {
                cout << "I----";
                indent += "|  ";
            }
            cout << raiz->key << endl;
            pintarArbol(raiz->izq, indent, false);
            pintarArbol(raiz->der, indent, true);
        }
    }

};