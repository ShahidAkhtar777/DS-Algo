from node import Node


def get_height(root: 'Node') -> int:
    if root is None:
        return 0

    left_ht = get_height(root.left)
    right_ht = get_height(root.right)

    return max(left_ht, right_ht) + 1


def get_count(root: 'Node') -> int:
    if root is None:
        return 0

    left_count = get_count(root.left)
    right_count = get_count(root.right)

    return left_count + right_count + 1


def get_sum(root: 'Node') -> int:
    if root is None:
        return 0

    left_sum = get_sum(root.left)
    right_sum = get_sum(root.right)

    return root.data + left_sum + right_sum


def tree_diameter(root: 'Node') -> int:
    def helper(root: 'Node') -> (int, int):
        if root is None:
            return 0, 0

        left_height, left_diameter = helper(root.left)
        right_height, right_diameter = helper(root.right)

        current_height = max(left_height, right_height) + 1
        dia_through_curr = left_height + right_height + 1

        current_diameter = max(left_diameter, right_diameter, dia_through_curr)

        return current_height, current_diameter

    _, diameter = helper(root)
    return diameter
