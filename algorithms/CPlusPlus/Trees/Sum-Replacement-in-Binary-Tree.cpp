
/*
    Problem:
    Replace the value of each node with the
    sum of all subtree nodes and itself.

NOTE: All leaf nodes value will remain unchanged as there is no
      left subtree or right subtree.


Example:   
    
                    1
                   /  \ 
                  2     3
                 / \   / \
                4   5  6  7    
        
    Expected Output:
    Step 1 - Leaf nodes will remain unchanged as per NOTE.
    Step 2 - Node with value has 2 childs 4 and 5 so the final value would be:
            Left child + right child+ itself
        
                    1
                   /  \ 
                  11    3
                 / \   / \
                4   5  6  7    
        
    Step 3 - Siimilarly repeat for node 3

                     1
                   /  \ 
                  11   16
                 / \   / \
                4   5  6  7   

    Step 4 - Final Step

                    28
                   /  \ 
                  11    16
                 / \   / \
                4   5  6  7    
    
    Therefore Preorder before Sum replace: 1 2 4 5 3 6 7 
    Preorder after Dum replace: 28 11 4 5 16 6 7

*/

/*----------------------------

      
Recursive Solution
Time Complexity: O(n)
---------------------------*/

#include <iostream>
#include <queue>
using namespace std;

// Basic Structure of a tree
struct Node
{
    int data;
    struct Node *left, *right;
};

/* function to create a new node of tree and returns pointer */
struct Node *CreateNode(int data)
{
    struct Node *temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
};

/*function to insert element in binary tree */
Node *insert(Node *root, int data)
{
    // If the tree is empty, assign new node address to root
    if (root == NULL)
    {
        root = CreateNode(data);
        return root;
    }

    /* Else, do level order traversal until we find an empty place, i.e. either left child or right child of some
     node is pointing to NULL. */

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);
        else
        {
            temp->left = CreateNode(data);
            return root;
        }

        if (temp->right != NULL)
            q.push(temp->right);
        else
        {
            temp->right = CreateNode(data);
            return root;
        }
    }
    return root;
}

//Function of sum replace
void sumReplace(Node *&root)
{
    //Base Case
    if (root == NULL)
        return;

    sumReplace(root->left);
    sumReplace(root->right);

    if (root->left != NULL)
    {
        root->data += root->left->data;
    }

    if (root->right != NULL)
    {
        root->data += root->right->data;
    }
}

//Preorder Traversal
void Preorder(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    Preorder(root->left);
    Preorder(root->right);
}

// Driver code
int main()
{
    Node *root = NULL;
    int n, num;
    cout << "Enter the Number of nodes";
    cin >> n;
    cout << "Enter the value of the nodes";
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        root = insert(root, num);
    }
    cout << "Preorder before Sum replace:";
    Preorder(root);
    sumReplace(root);
    cout << endl;
    cout << "Preorder after Sum Replace:";
    Preorder(root);

    return 0;
}