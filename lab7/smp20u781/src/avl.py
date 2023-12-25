class treeNode(object):
	def __init__(self, key):
		self.key = key
		self.left = None
		self.right = None
		self.height = 1

class AVLTree(object):
    def __init__(self):
        self.root = None
        self.total = 0

    def Insert(self, key):
        self.root = self.recInsert(self.root, key)

    def recInsert(self, root, key):
        if not root:
            return treeNode(key)
        elif key < root.key:
            root.left = self.recInsert(root.left, key)
        else:
            root.right = self.recInsert(root.right, key)

        root.height = 1 + max(self.getHeight(root.left),
                        self.getHeight(root.right))

        b = self.getBal(root)

        if b > 1 and key < root.left.key:
            return self.rightRotate(root)

        if b < -1 and key > root.right.key:
            return self.leftRotate(root)

        if b > 1 and key > root.left.key:
            root.left = self.leftRotate(root.left)
            return self.rightRotate(root)

        if b < -1 and key < root.right.key:
            root.right = self.rightRotate(root.right)
            return self.leftRotate(root)

        return root

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

    def leftRotate(self, z):

        y = z.right
        T2 = y.left

        y.left = z
        z.right = T2

        z.height = 1 + max(self.getHeight(z.left),
                        self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left),
                        self.getHeight(y.right))

        return y

    def rightRotate(self, z):

        y = z.left
        T3 = y.right

        y.right = z
        z.left = T3

        z.height = 1 + max(self.getHeight(z.left),
                        self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left),
                        self.getHeight(y.right))

        return y

    def getHeight(self, root):
        if not root:
            return 0

        return root.height

    def getBal(self, root):
        if not root:
            return 0

        return self.getHeight(root.left) - self.getHeight(root.right)

    def PreOrder(self):
        self.recPreOrder(self.root)

    def recPreOrder(self, root):
        if not root:
            return

        print("{0} ".format(root.key), end="")
        self.recPreOrder(root.left)
        self.recPreOrder(root.right)
