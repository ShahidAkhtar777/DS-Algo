/*
Given the root of a binary tree and an integer targetSum,
return true if the tree has a root-to-leaf path such that adding
up all the values along the path equals targetSum.
*/

// Time O(N) SpaceO(N)

//C++ Implementation
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==NULL)
            return false;

        bool leftPossible = hasPathSum(root->left, targetSum - root->val);
        bool rightPossible = hasPathSum(root->right, targetSum - root->val);

        if(targetSum==root->val and !root->left and !root->right)
            return true;

        return leftPossible | rightPossible;
    }
};

// Python Implementation
class Solution:
    # Time Complexity O(N) Space Complexity O(N)
    def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:
        if root is None:
            return False

        if not root.left and not root.right:
            return targetSum == root.val

        targetSum -= root.val
        return self.hasPathSum(root.left, targetSum) or self.hasPathSum(root.right, targetSum)