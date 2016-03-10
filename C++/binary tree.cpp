//  binary tree
//  Created by John Madison on 8/28/15.
#include <iostream>
#include <random>
using namespace std;
random_device rd;
mt19937 gen(rd());

struct node
{
    int value;
    node* left;
    node* right;
};

node* tree = new node;

int numnodes(node* tree)
{
    if (tree == NULL) return 0;
    else return 1 + numnodes(tree->left) + numnodes(tree->right);
}

void preordertrav(node* root)
{
    if(root!=NULL)
    {
        cout << root->value << ' ';
        preordertrav(root->left);
        preordertrav(root->right);
    }
}

bool Emptytree(node *root)
{
    return root -> value <= -1;
}

void insert(node *root, int value)
{
    node *knew = new node;
    node *parent = new node;
    node *c = new node;
    if(!Emptytree(root))
    {
        knew = new node;
        knew -> value = value;
        knew -> left = NULL;
        knew -> right = NULL;
        parent = NULL;
        c = root;
        while(c!=NULL)
        {
            parent = c;
            if(gen()*clock()*rand()%10 >= 5) c = c -> left;
            else c = c -> right;
        }
        if(gen()*clock()*rand()%10 < 5) parent -> left = knew;
        else parent -> right = knew;
    }
    else root -> value = value;
}

void postordertrav(node *c)
{
    if(c!=NULL)
    {
        postordertrav(c->left);
        postordertrav(c->right);
        cout << c->value << " ";
    }
}

void inordertrav(node *c)
{
    if(c->left != NULL)
        inordertrav(c->left);
    cout << c->value << ' ';
    if(c->right != NULL)
        inordertrav(c->right);
}

//another inorder traversal


void inorder(node *root)
{
    if (root!=NULL)
    {
        inorder(root->left);
        cout << root->value << " " ;
        inorder(root->right);
    }
}



//get the max value of a tree.

int maxValueHelp(node* tree, int Max)
{
    if (tree == NULL)return Max;
    Max = Max > tree->value ? Max : tree->value;
    int leftMax  = maxValueHelp(tree->left,  Max);
    int rightMax = maxValueHelp(tree->right, Max);
    return leftMax > rightMax ? leftMax : rightMax;
}

int maxValue(node* tree)
{
    if (Emptytree(tree))
        throw "BT is empty";
    return maxValueHelp(tree, tree->value);
}

//another method to get a max value in a tree.

int max(int num1, int num2)
{
    if(num1 >= num2) return num1;
    else return num2;
}

int treeMax( node* root)
{
    if ((root -> left == NULL) && (root->right==NULL))
        return root->value;
    else if (root->left==NULL) return max(root->value, treeMax(root->right));
    else if (root->right ==NULL) return max(root->value, treeMax(root->left));
    else return max(root->value, max(treeMax(root->left),treeMax(root->right)));
}

int main()
{
    srand(clock());
    for(int i = 0; numnodes(tree)<10; i++) insert(tree, gen()*clock()*rand()%100);
    cout << numnodes(tree)<<" nodes in tree"<< endl;
    preordertrav(tree);
    cout << endl << "Max Value: " << maxValue(tree) << endl;
    cout << endl << "Max Value: " << treeMax(tree) << endl;
    inorder(tree);
    cout << endl;
    inordertrav(tree);
    cout<< endl << endl;
    return 0;
}


