from avl import *
from binary import *

def generate_n(tree, n):
    for i in range(n):
        tree.Insert(i)

def measure():
    experiments = [129, 257, 513, 1025, 2049]

    print("Количество элементов, худший случай AVL, лучший случай AVL, худший случай BST, лучший случай BST")
    for n in experiments:
        avlTree = AVLTree()
        tree = Tree()

        generate_n(avlTree, n)
        generate_n(tree, n)

        print(n, avlTree.SearchCount(n + 1), avlTree.SearchCount(avlTree.root.key), tree.SearchCount(n + 1), tree.SearchCount(tree.root.key), sep = ',')
