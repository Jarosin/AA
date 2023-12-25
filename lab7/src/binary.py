class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class Tree(object):
    def __init__(self):
        self.root = None
        self.total = 0

    def Insert(self, key):
        self.root = self.recInsert(self.root, key)

    def recInsert(self, node, key):
        if node is None:
            return Node(key)

        temp = node
        while (True):
            if temp.key > key:
                if temp.left is None:
                    temp.left = Node(key)
                    return node
                temp = temp.left
            else:
                if temp.right is None:
                    temp.right = Node(key)
                    return node
                temp = temp.right

    def Search(self, key):
        self.total = 0
        res = self.recSearch(self.root, key)
        return res

    def SearchCount(self, key):
        self.total = 0
        res = self.recSearch(self.root, key)
        return self.total


    def recSearch(self, root, key):
        node = root
        while(True):
            self.total += 1
            if node is None or node.key == key:
                return node

            if node.key > key:
                node = node.left
            else:
                node = node.right

    def PreOrder(self):
        self.recPreOrder(self.root)

    def recPreOrder(self, root):
        if not root:
            return

        print("{0} ".format(root.key), end="")
        self.recPreOrder(root.left)
        self.recPreOrder(root.right)
