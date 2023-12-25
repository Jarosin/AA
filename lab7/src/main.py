from avl import *
from binary import *
from utils import *

MESSAGE = "Меню\n\
1. Сбалансированное дерево поиска \n\
2. Несбалансированное дерево поиска \n\
3. Вывести текущее дерево \n\
4. Добавить элементы в дерево \n\
5. Найти элемент в дереве \n\
6. Провести замеры количества сравнений \n\
0. Выход \n\
Выбор: "

if __name__ == '__main__':
    option = -1
    tree = None
    while (option != 0):
        try:
            option = int(input(MESSAGE))
        except:
            option = -1
        if (option == 1):
            tree = AVLTree()
        elif (option == 2):
            tree = Tree()
        elif (option == 3):
            tree.PreOrder()
        elif (option == 4):
            print("Введите числа через пробел: ")
            try:
                numbers = list(map(int, input().split()))
                for number in numbers:
                    tree.Insert(number)
            except:
                print("Ошибка при вводе")

        elif (option == 5):
            try:
                key = int(input("Введите искомый элемент: "))
                found = tree.Search(key)
                if found is None:
                    print("Число не было найдено")
                else:
                    print("Число было найдено")
            except:
                print("Ошибка при вводе")

        elif (option == 6):
            measure()

        elif (option == 0):
            print("Завершение выполнения")
        else:
            print("Повторите ввод")
