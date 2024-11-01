from node import Node
from queue import Queue

def pre_order_traversal(root: 'Node'):
    """Pre-order traversal: Visit root, then left subtree, then right subtree."""
    if root:
        print(root.data, end=" ")
        pre_order_traversal(root.left)
        pre_order_traversal(root.right)

def in_order_traversal(root: 'Node'):
    """In-order traversal: Visit left subtree, then root, then right subtree."""
    if root:
        in_order_traversal(root.left)
        print(root.data, end=" ")
        in_order_traversal(root.right)

def post_order_traversal(root: 'Node'):
    """Post-order traversal: Visit left subtree, then right subtree, then root."""
    if root:
        post_order_traversal(root.left)
        post_order_traversal(root.right)
        print(root.data, end=" ")

def level_order_traversal(root: 'Node'):
    """Perform level-order traversal of a binary tree."""

    if root is None:
        return

    q = Queue()
    q.put(root)

    while not q.empty():
        current = q.get()
        print(current.data, end=" ")

        if current.left:
            q.put(current.left)
        if current.right:
            q.put(current.right)
