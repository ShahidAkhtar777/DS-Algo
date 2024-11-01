from build_tree import build_tree
from traversals import (
    pre_order_traversal,
    post_order_traversal,
    in_order_traversal,
    level_order_traversal,
)


def main():
    # Example preorder traversal input (None or -1 represents no node)
    preorder_input = [1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1]

    root = build_tree(preorder_input)

    print("Preorder Traversal:")
    pre_order_traversal(root)  # Should print: 1 2 4 5 3 6
    print("\nPostorder Traversal:")
    post_order_traversal(root)  # Should print: 4 5 2 6 3 1
    print("\nInorder Traversal:")
    in_order_traversal(root)
    print("\nLevelorder Traversal:")
    level_order_traversal(root)  # Should print: 1 2 3 4 5 6


if __name__ == "__main__":
    main()
