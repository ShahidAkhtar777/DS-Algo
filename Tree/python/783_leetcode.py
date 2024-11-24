"""
Minimum Distance Between BST Nodes

Given the root of a Binary Search Tree (BST), return the minimum difference between
the values of any two different nodes in the tree.
"""

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def min_diff_in_bst(self, root: Optional[TreeNode]) -> float:
        # Mutable variable to store state
        state = {"lastVal": None, "minDiff": float('inf')}

        def helper(node: Optional[TreeNode]):
            if not node:
                return

            helper(node.left)
            if state["lastVal"] is not None:
                state["minDiff"] = min(
                    state["minDiff"], abs(node.val - state["lastVal"])
                )

            state["lastVal"] = node.val
            helper(node.right)

        helper(root)
        return state["minDiff"]


def insert_into_bst(root: Optional[TreeNode], val: int) -> TreeNode:
    if not root:
        return TreeNode(val)

    if val < root.val:
        root.left = insert_into_bst(root.left, val)
    else:
        root.right = insert_into_bst(root.right, val)

    return root


values = [4, 2, 8, 6, 1, 12]
root = None
for value in values:
    root = insert_into_bst(root, value)

solution = Solution()
result = solution.min_diff_in_bst(root)
print(f"Minimum Diff between Nodes: {result}")
