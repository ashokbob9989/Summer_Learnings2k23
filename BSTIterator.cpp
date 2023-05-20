#include<bits/stdtr1c++.h>
using namespace std;

class TreeNode
{
    public:
        int val;
        TreeNode* left;
        TreeNode* right;

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
    BST(){}
        TreeNode* insert(TreeNode* root,int x)
        {
                TreeNode *temp = new TreeNode(x);
                if(root==NULL) root=temp;
                else
                {
                    TreeNode *ptr = root;
                    TreeNode *par = root;
                    while(ptr!=NULL)
                    {
                        par = ptr;
                        if(x < ptr->val) ptr=ptr->left;
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
};

stack<TreeNode *> mys1;
class BSTIteratorforward
{
    public:
    BSTIteratorforward(){}
        BSTIteratorforward(TreeNode* root)
        {
            while(root!=NULL)
            {
                mys1.push(root);
                root = root->left;
            }
        }

        bool hasnext() { return !mys1.empty(); }

        int next()
        {
            TreeNode *temp = mys1.top();
            mys1.pop();
            int val = temp->val;

            if(temp->right!=NULL)
            {
                temp = temp->right;
                while(temp!=NULL)
                {
                    mys1.push(temp);
                    temp = temp->left;
                }
            }

            return val;
        }
};

stack<TreeNode *> mys2;
class BSTIteratorbackward
{
    public:
    BSTIteratorbackward(){}
        BSTIteratorbackward(TreeNode* root)
        {
            while(root!=NULL)
            {
                mys2.push(root);
                root = root->right;
            }
        }

        bool hasprev() { return !mys2.empty(); }

        int prev()
        {
            TreeNode *temp = mys2.top();
            mys2.pop();
            int val = temp->val;

            if(temp->left!=NULL)
            {
                temp = temp->left;
                while(temp!=NULL)
                {
                    mys2.push(temp);
                    temp = temp->right;
                }
            }

            return val;
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

        bst.InOrderTrav(root);
        cout << endl;

        BSTIteratorforward i(root);
        while(i.hasnext())cout<<i.next()<<" ";

        cout << endl;
        
        BSTIteratorbackward j(root);
        while(j.hasprev()) cout<<j.prev()<<" ";
}
