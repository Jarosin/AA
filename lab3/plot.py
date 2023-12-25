import matplotlib.pyplot as plt
import numpy as np

data_file_name = "docs/csv/best.csv"


if __name__ == "__main__":
    x_points = np.array([])
    insert_points = np.array([])
    heap_points = np.array([])
    bitonic_points = np.array([])

    f = open(data_file_name, "r")
    line = f.readline()
    count = 0
    while True:
        line = f.readline()
        if not line:
            break
        line = line.replace(',', ' ')
        data = line.split()
        x_point = float(data[0])
        x_points = np.append(x_points, np.array([x_point]))
        insert_points = np.append(insert_points, np.array([float(data[1])]))
        heap_points = np.append(heap_points, np.array([float(data[2])]))
        bitonic_points = np.append(bitonic_points, np.array([float(data[3])]))

        # insert_points = np.append(insert_points, np.array([float(data[1]) / (10 ** 3)]))
        # heap_points = np.append(heap_points, np.array([float(data[2]) / (10 ** 3)]))
        # bitonic_points = np.append(bitonic_points, np.array([float(data[3]) / (10 ** 3)]))

        count += 1

    f.close()

    plt.title("Время выполнения сортировки в зависимости от длины массива")
    plt.plot(x_points, insert_points, label = "Сортировка вставками")
    plt.plot(x_points, heap_points, label = "Пирамидальная сортировка")
    plt.plot(x_points, bitonic_points, label = "Битонная сортировка")

    plt.yscale("log")
    plt.xlabel("Длина массива")
    # plt.ylabel("Время в секундах")
    plt.ylabel("Время в мс")

    plt.legend()
    plt.show()
