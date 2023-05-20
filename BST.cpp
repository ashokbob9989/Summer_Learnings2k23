#include<bits/stdc++.h>
using namespace std;

class TreeNode
{
    public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = NULL;
        right = NULL;
    }
};

class BST
{
    public:
    TreeNode* insert(TreeNode* root,int x)
    {
        TreeNode *temp = new TreeNode(x);
        if(root==NULL)root=temp;
        else 
        {
            TreeNode *ptr = root;
            TreeNode *par = root;
            while(ptr!=NULL)
            {
                par = ptr; /*this coz at last our ptr will point to NULL so we want just before the ptr's node*/
                if(x < ptr->val)ptr=ptr->left;
                else ptr=ptr->right;
            }

            if(x < par->val)par->left=temp;
            else par->right=temp;
        }
        return root;
    }

    void InOrderRec(TreeNode* root)
    {
        TreeNode *ptr = root;
        if(ptr!=NULL)
        {
            InOrderRec(ptr->left);
            cout << ptr->val << " ";
            InOrderRec(ptr->right);
        }
    }
    void InOrderTrav(TreeNode* root) { InOrderRec(root); }

    void PreOrderRec(TreeNode *root)
    {
        TreeNode *ptr = root;
        if (ptr != NULL)
        {
            cout << ptr->val << " ";
            InOrderRec(ptr->left);
            InOrderRec(ptr->right);
        }
    }
    void PreOrderTrav(TreeNode *root) { PreOrderRec(root); }

    void PostOrderRec(TreeNode *root)
    {
        TreeNode *ptr = root;
        if (ptr != NULL)
        {
            cout << ptr->val << " ";
            InOrderRec(ptr->left);
            InOrderRec(ptr->right);
        }
    }
    void PostOrderTrav(TreeNode *root) { PostOrderRec(root); }
};

class BSTIterator
{
    stack<TreeNode *> mys;
    bool reverse=true;

    public:
    BSTIterator(TreeNode *root, bool isreverse)
    {
        reverse = isreverse;
        pushall(root);
    }

    void pushall(TreeNode *ptr)
    {
        while (ptr != NULL)
        {
            mys.push(ptr);
            if (reverse == false)  ptr = ptr->left;
            else ptr = ptr->right;
        }
    }

    bool hasnext() { return !mys.empty(); }

    int next()
    {
        TreeNode *temp = mys.top();
        mys.pop();
        if (reverse == false) pushall(temp->right);
        else  pushall(temp->left);
        return temp->val; /*this is top value which we need right now*/
    }
};

class Solution
{
    public:
    bool t2sum(TreeNode *root, int k)
    {
        if (root == NULL) return false;
        BSTIterator l(root, false); /*this will give us inorder seq..that is in Increasing order*/
        BSTIterator r(root, true);  /*this gives in Decreasing order seq*/

        int i = l.next(); /*next greater element*/
        int j = r.next(); /*next smaller element*/

        while (i < j)
        {
            if (i + j == k)  return true;
            else if (i + j < k) i = l.next();
            else  j = r.next();
        }
        return false;
    }
};

int32_t main()
{
    BST bst;
    TreeNode *root = NULL;

    int n;
    cin >> n;
    while(n--)
    {
        int x;
        cin >> x;
        root=bst.insert(root,x);
    }

    // bst.InOrderTrav(root); /*lRr*/
    // cout << endl;

    // bst.PreOrderTrav(root); /*Rlr*/
    // cout << endl;

    // bst.PostOrderTrav(root); /*lrR*/
    // cout << endl;

    int sum;
    cin >> sum;
    Solution ss;
    cout<<ss.t2sum(root, sum)<<endl;

    return 0;
}
