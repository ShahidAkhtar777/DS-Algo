"""
Given the root of a binary tree, imagine yourself
standing on the right side of it, return the values
of the nodes you can see ordered from top to bottom.
"""

from typing import Optional, List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    @staticmethod
    def right_side_view(root: Optional[TreeNode]) -> List[int]:
        def dfs(node: Optional[TreeNode], level: int):
            if not node:
                return

            if level == len(right_view):
                right_view.append(node.val)

            dfs(node.right, level + 1)
            dfs(node.left, level + 1)

        right_view = []
        dfs(root, 0)
        return right_view
