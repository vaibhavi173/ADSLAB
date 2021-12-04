#include<bits/stdc++.h>
using namespace std;
 

class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
};

//Function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
//Function to find height of tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
//Function to allocate new node
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return(node);
}
 
//Right rotate operation
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    
    x->right = y;
    y->left = T2;
 
    
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
   
    return x;
}
 
//Left rotate operation
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
   
    y->left = x;
    x->right = T2;
 
    
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    return y;
}
 
// Balance factor
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}
 //INSERT OPERATION
Node* insert(Node* node, int key)
{
  
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;
 
   /*updating height*/
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
   int balance = getBalance(node);
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    
    return node;
}
 
//To find inorder successor
Node * minValueNode(Node* node)
{
    Node* current = node;
 
    
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
//RECURSIVE DELETION FUNCTION
Node* deleteNode(Node* root, int key)
{
     
    
    if (root == NULL)
        return root;
 
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
 
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
 
    
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; 
            free(temp);
        }
        else
        {
            //find inorder successor for node with two child
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }
 
    // only one node
    if (root == NULL)
    return root;
 
    //  Update height
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    int balance = getBalance(root);
    //IF NODE IS UNBALANCED
    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

Node* search(Node* root, int key)
{
 
    if (root == NULL || root->key == key)
       return root;
    if (root->key < key)
       return search(root->right, key);
 
    return search(root->left, key);
}

//preorder traversal
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}


//INTERACTIVE DRIVER CODE
int main()
{ 
  int n;
  int k;
  Node* root = NULL;
  Node* temp = NULL;
  cout<<"1:createtree 2:deletetree 3:searchtree 4:displaytree"<<endl;
  cout<<"Enter your choice : ";
  cin>>n;
  while(1)
  {
  
  switch(n)
  {
    case 1:cout<<"Enter the key : ";
           cin>>k;
           root=insert(root,k);
           break;
    
    case 2:cout<<"Enter the key :: ";
           cin>>k;
           root = deleteNode(root, k);
           break;
    
    case 3:cout<<"Enter the key :: ";
           cin>>k;
           temp =search(root,k);
          if(temp==NULL)
          {
          cout<<"\nElement not found in the tree\n";
          }
          else
          {
          cout<<"\nElement is found in the tree \n";
           search(root,k);
           break;
          }
    
    case 4: cout<<"\nPreorder traversal of the the tree:";
            preOrder(root);
            cout<<endl;
            break;

  }
  cout<<"Enter your choice : ";
  cin>>n;
  }
 
}
