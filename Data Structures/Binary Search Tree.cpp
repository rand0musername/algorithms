// RandomUsername (Nikola Jovanovic)
// Binary Search Tree
// init: O(1)
// insert: O(logN) if balanced ( O(N) worst case )
// remove: O(logN) if balanced ( O(N) worst case )
// find: O(logN) if balanced ( O(N) worst case )
// inorder/preorder/postorder: O(N)
// N - BST size

#include <bits/stdc++.h>
#define DBG false
#define debug(x) if(DBG) printf("(ln %d) %s = %d\n", __LINE__, #x, x);
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2
#define INF 1000000000
#define MAXN 100005
#define MAXLOGN 20

using namespace std;

// Node structure
struct node
{
    int key;
    node* left;
    node* right;
    node* parent;
    node()
    {
        left = right = parent = NULL;
        key = 0;
    }
};

// Binary Search Tree
struct BST
{
    node* root;
    int sz;

    BST()
    {
        root = NULL;
        sz = 0;
    }

    bool isEmpty()
    {
        return (root == NULL);
    }

    int size()
    {
        return sz;
    }

    void insert(int x)
    {
        if(isEmpty())
        {
            root = new node();
            root -> key = x;
            sz++;
            return;
        }
        node* curr = root;
        while(curr != NULL)
        {
            if(x > curr -> key )
            {

                if(curr -> right == NULL)
                {
                    sz++;
                    node* nw = new node();
                    nw -> key = x;
                    curr -> right = nw;
                    nw -> parent = curr;
                    return;
                }
                else curr = curr -> right;
            }
            else if(x < curr -> key )
            {

                if(curr -> left == NULL)
                {
                    sz++;
                    node* nw = new node();
                    nw -> key = x;
                    curr -> left = nw;
                    nw -> parent = curr;
                    return;
                }
                else curr = curr -> left;
            }
            else return;

        }
    }

    node* find(int x)
    {
        if(isEmpty())
        {
           return NULL;
        }
        node* curr = root;
        while(curr != NULL)
        {
            if(x > curr -> key )
                curr = curr -> right;
            else if(x < curr -> key )
                curr = curr -> left;
            else return curr;
        }
        return NULL;
    }

    void remove(int x)
    {
        node* curr = find(x);
        if(curr == NULL) return;
        sz--;

        node* parent = curr -> parent;
        if(curr == root && size() == 0)
        {
            root = NULL;
        }
        else if(curr -> left == NULL && curr -> right == NULL)
        {
            if(parent > curr)
                parent -> left = NULL;
            else
                parent -> right = NULL;
        }
        else if(curr -> left == NULL)
        {
            curr -> key = curr -> right -> key;
            curr -> right = NULL;
        }
        else if(curr -> right == NULL)
        {
            curr -> key = curr -> left -> key;
            curr -> left = NULL;
        }
        else
        {
            // both children exist, find predecessor
            node* pred = curr -> left;
            node* predParent = curr;
            while(pred -> right != NULL)
            {
                predParent = pred;
                pred = pred -> right;
            }
            // swap
            curr -> key = pred -> key;
            predParent -> right = pred -> left;
            delete pred;
        }
    }

    // tree traversals

    void inOrder(node* curr)
    {
        if(curr == NULL) return;
        inOrder(curr -> left);
        printf("%d ", curr -> key);
        inOrder(curr -> right);
    }

    void postOrder(node* curr)
    {
        if(curr == NULL) return;
        postOrder(curr -> left);
        postOrder(curr -> right);
        printf("%d ", curr -> key);
    }

    void preOrder(node* curr)
    {
        if(curr == NULL) return;
        printf("%d ", curr -> key);
        preOrder(curr -> left);
        preOrder(curr -> right);
    }
};

// Testing
int main()
{
    BST bst;
    //Commands: sz isempty insert_x remove_x find_x
    // pre post pin
    char kom[10];
    int x;
    while(1)
    {
        scanf("%s", kom);
        if(kom[0] == 's')
        {
            printf("Size: %d\n", bst.size());
        }
        else if(kom[0] == 'i' && kom[1] == 's')
        {
            if(bst.isEmpty())
                printf("Empty\n");
            else
                printf("Not empty\n");
        }
        else if(kom[0] == 'i' && kom[1] == 'n')
        {
            scanf("%d", &x);
            bst.insert(x);
            printf("Inserted %d\n", x);
        }
        else if(kom[0] == 'r')
        {
            scanf("%d", &x);
            bst.remove(x);
            printf("Removed %d\n", x);
        }
        else if(kom[0] == 'f')
        {
            scanf("%d", &x);
            node* res = bst.find(x);
            if(res == NULL)
                printf("%d doesn't exist.\n", x);
            else
                printf("%d exists.\n", x);
        }
        else if(kom[0] == 'p')
        {
            if(kom[1] == 'r')
                bst.preOrder(bst.root), printf("\n");
            else if(kom[1] == 'i')
                bst.inOrder(bst.root), printf("\n");
            else if(kom[1] == 'o')
                bst.postOrder(bst.root), printf("\n");
        }
    }
    return 0;
}
