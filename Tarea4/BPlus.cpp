
#include <iostream>

using namespace std;

class TreeNode
{
public:
    bool isLeaf;
    int *keys;
    int count;
    TreeNode **child;
    TreeNode(int degree)
    {
        this->isLeaf = false;
        this->count = 0;
        this->keys = new int[degree];
        this->child = new TreeNode *[degree + 1];
        // Set initial child
        for (int i = 0; i <= degree; ++i)
        {
            this->child[i] = NULL;
        }
    }
    TreeNode()
    {
        this->count = 0;
    }
};
// Define tree structure
class BPTree
{
public: TreeNode *root;
    int degree;
    BPTree(int degree)
    {
        this->degree = degree;
        this->root = NULL;
    }
    TreeNode *findParent(TreeNode *cursor, TreeNode *child)
    {
        TreeNode *parent = NULL;
        if (cursor->isLeaf == true || (cursor->child[0])->isLeaf == true)
        {
            return NULL;
        }
        for (int i = 0; i < cursor->count + 1; i++)
        {
            if (cursor->child[i] == child)
            {
                parent = cursor;
                return parent;
            }
            else
            {
                parent = this->findParent(cursor->child[i], child);
                if (parent != NULL)
                {
                    return parent;
                }
            }
        }
        return parent;
    }
    void insertInternal(int x, TreeNode *cursor, TreeNode *child)
    {
        int i = 0;
        int j = 0;
        if (cursor->count < this->degree)
        {
            while (x > cursor->keys[i] && i < cursor->count)
            {
                i++;
            }
            for (j = cursor->count; j > i; j--)
            {
                cursor->keys[j] = cursor->keys[j - 1];
            }
            for (j = cursor->count + 1; j > i + 1; j--)
            {
                cursor->child[j] = cursor->child[j - 1];
            }
            cursor->keys[i] = x;
            cursor->count++;
            cursor->child[i + 1] = child;
        }
        else
        {
            TreeNode *newInternal = new TreeNode(this->degree);
            int *virtualKey = new int[this->degree + 1];
            TreeNode **virtualPtr = new TreeNode *[this->degree + 2];
            for (i = 0; i < this->degree; i++)
            {
                virtualKey[i] = cursor->keys[i];
            }
            for (i = 0; i < this->degree + 1; i++)
            {
                virtualPtr[i] = cursor->child[i];
            }
            i = 0;
            while (x > virtualKey[i] && i < this->degree)
            {
                i++;
            }
            for (j = this->degree + 1; j > i; j--)
            {
                virtualKey[j] = virtualKey[j - 1];
            }
            virtualKey[i] = x;
            for (j = this->degree + 2; j > i + 1; j--)
            {
                virtualPtr[j] = virtualPtr[j - 1];
            }
            virtualPtr[i + 1] = child;
            newInternal->isLeaf = false;
            cursor->count = (this->degree + 1) / 2;
            newInternal->count = this->degree - (this->degree + 1) / 2;
            for (i = 0, j = cursor->count + 1; i < newInternal->count;
                 i++, j++)
            {
                newInternal->keys[i] = virtualKey[j];
            }
            for (i = 0, j = cursor->count + 1; i < newInternal->count + 1;
                 i++, j++)
            {
                newInternal->child[i] = virtualPtr[j];
            }
            if (cursor == this->root)
            {
                this->root = new TreeNode(this->degree);
                this->root->keys[0] = cursor->keys[cursor->count];
                this->root->child[0] = cursor;
                this->root->child[1] = newInternal;
                this->root->isLeaf = false;
                this->root->count = 1;
            }
            else
            {
                this->insertInternal(cursor->keys[cursor->count],
                                     this->findParent(this->root, cursor),
                                     newInternal);
            }
        }
    }
    // Handles the request to add new node in B+ tree
    void insert(int x)
    {
        if (this->root == NULL)
        {
            // Add first node of tree
            this->root = new TreeNode(this->degree);
            this->root->isLeaf = true;
            this->root->count = 1;
            this->root->keys[0] = x;
        }
        else
        {
            // Loop controlling variables
            int i = 0;
            int j = 0;
            TreeNode *cursor = this->root;
            TreeNode *parent = NULL;
            // Executes the loop until when cursor node is not leaf node
            while (cursor->isLeaf == false)
            {
                // Get the current node
                parent = cursor;
                for (i = 0; i < cursor->count; i++)
                {
                    if (x < cursor->keys[i])
                    {
                        cursor = cursor->child[i];
                        break;
                    }
                    if (i == cursor->count - 1)
                    {
                        cursor = cursor->child[i + 1];
                        break;
                    }
                }
            }
            if (cursor->count < this->degree)
            {
                i = 0;
                while (x > cursor->keys[i] && i < cursor->count)
                {
                    i++;
                }
                for (j = cursor->count; j > i; j--)
                {
                    cursor->keys[j] = cursor->keys[j - 1];
                }
                cursor->keys[i] = x;
                cursor->count++;
                cursor->child[cursor->count] = cursor->child[cursor->count - 1];
                cursor->child[cursor->count - 1] = NULL;
            }
            else
            {
                TreeNode *newLeaf = new TreeNode(this->degree);
                int *virtualNode = new int[this->degree + 2];
                for (i = 0; i < this->degree; i++)
                {
                    virtualNode[i] = cursor->keys[i];
                }
                i = 0;
                while (x > virtualNode[i] && i < this->degree)
                {
                    i++;
                }
                for (j = this->degree + 1; j > i; j--)
                {
                    virtualNode[j] = virtualNode[j - 1];
                }
                virtualNode[i] = x;
                newLeaf->isLeaf = true;
                cursor->count = (this->degree + 1) / 2;
                newLeaf->count = this->degree + 1 - (this->degree + 1) / 2;
                cursor->child[cursor->count] = newLeaf;
                newLeaf->child[newLeaf->count] = cursor->child[this->degree];
                cursor->child[this->degree] = NULL;
                for (i = 0; i < cursor->count; i++)
                {
                    cursor->keys[i] = virtualNode[i];
                }
                for (i = 0, j = cursor->count; i < newLeaf->count; i++, j++)
                {
                    newLeaf->keys[i] = virtualNode[j];
                }
                if (cursor == this->root)
                {
                    TreeNode *newRoot = new TreeNode(this->degree);
                    newRoot->keys[0] = newLeaf->keys[0];
                    newRoot->child[0] = cursor;
                    newRoot->child[1] = newLeaf;
                    newRoot->isLeaf = false;
                    newRoot->count = 1;
                    this->root = newRoot;
                }
                else
                {
                    this->insertInternal(newLeaf->keys[0], parent, newLeaf);
                }
            }
        }
    }
    // Print the elements of B+ tree elements
    void printNode(TreeNode *node)
    {
        if (node == NULL)
        {
            return;
        }
        else
        {
            int i = 0;
            while (i < node->count)
            {
                if (node->isLeaf == false)
                {
                    // When node is not leaf
                    this->printNode(node->child[i]);
                }
                else
                {
                    // Print the left node value
                    cout << " -> " << node->keys[i];
                }
                i++;
            }
            if (node->isLeaf == false)
            {
                this->printNode(node->child[i]);
            }
        }
    }
};
