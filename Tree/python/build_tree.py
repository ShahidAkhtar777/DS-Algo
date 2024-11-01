from node import Node


def build_tree(preorder_values):
    """Build a binary tree from a list of values in preorder."""
    if not preorder_values:
        return None

    values_iter = iter(preorder_values)

    def build_tree_helper():
        val = next(values_iter, None)
        if val is None or val == -1:
            return None

        node = Node(val)
        node.left = build_tree_helper()
        node.right = build_tree_helper()
        return node

    return build_tree_helper()
