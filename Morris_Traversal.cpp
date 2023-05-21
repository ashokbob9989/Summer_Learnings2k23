#include<bits/stdc++.h>
using namespace  std;

/*T(n)=O(n)  and S(n)=O(1)->indeed better then normal/inorder trversal*/
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
        BST(){}

        TreeNode* insert(TreeNode* root, int x)
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
                    if(x < ptr->val)ptr=ptr->left;
                    else ptr=ptr->right;
                }
                if(x < par->val) par->left=temp;
                else par->right=temp;
            }

            return root;
        }

        void InOrderRec(TreeNode* root)
        {
            if(root!=NULL)
            {
                InOrderTrav(root->left);
                cout << root->val << " ";
                InOrderTrav(root->right);
            }
        }
        void InOrderTrav(TreeNode *root) { InOrderRec(root); }


        vector<int> MorristravInorder(TreeNode* root)
        {
            vector<int> sol;
            TreeNode *curr = root;
            
            while(curr!=NULL)
            {
                if(curr->left==NULL)
                {
                    sol.push_back(curr->val);
                    curr = curr->right;
                }
                else
                {
                    TreeNode *prev = curr->left;
                    while(prev->right!=NULL && prev->right!=curr)
                    { prev=prev->right;}

                    if(prev->right==NULL)
                    {
                        prev->right = curr;
                        curr = curr->left;
                    }
                    else
                    {
                        prev->right = NULL;
                        sol.push_back(curr->val);
                        curr = curr->right;
                    }
                }
            }

            return sol;
        }

        vector<int> MorristravPreOrder(TreeNode* root)
        {
            vector<int> sol;
            TreeNode *curr = root;

            while(curr!=NULL)
            {
                if(curr->left==NULL)
                {
                    sol.push_back(curr->val);
                    curr = curr->right;
                }
                else
                {
                    TreeNode *prev = curr->left;
                    while(prev->right!=NULL && prev->right!=curr)
                    {prev=prev->right;}

                    if(prev->right==NULL)
                    {
                        prev->right = curr;
                        sol.push_back(curr->val);
                        curr = curr->left;
                    }
                    else
                    {
                        prev->right = NULL;
                        curr = curr->right;
                    }
                }
            }
            return sol;
        }

};

int main()
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

        vector<int> morrisinorder = bst.MorristravInorder(root);
        for(auto &it : morrisinorder) cout<<it<<" ";
        cout<<endl;

        vector<int> morrisPreOrder = bst.MorristravPreOrder(root);
        for(auto &it : morrisPreOrder) cout<<it<<" ";
        cout<<endl;

        return 0;

}