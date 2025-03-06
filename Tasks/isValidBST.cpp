#include <iostream>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
        bool isValidBST(TreeNode *node) {
            return this->isValidBST(node, nullptr, nullptr);
        }
    private:
        bool isValidBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
            if (root == nullptr) {
                return true;
            } else if ((minNode != nullptr && root->val <= minNode->val) || 
            (maxNode != nullptr && root->val >= maxNode->val)) {
                return false;
            } else {
                return this->isValidBST(root->left, minNode, root) && 
                this->isValidBST(root->right, root, maxNode);
            }
        }
};


int main() {
    Solution s;
    TreeNode n1(5);
    TreeNode n2(4);
    TreeNode n3(6);
    TreeNode n4(3);
    TreeNode n5(7);
    n1.left = &n2;
    n1.right = &n3;
    n3.left = &n4;
    n3.right = &n5;
    std::cout << s.isValidBST(&n1) << std::endl;
    return 0;
}