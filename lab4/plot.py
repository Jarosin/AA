import matplotlib.pyplot as plt
import numpy as np

data_file_name = "docs/csv/results.csv"


if __name__ == "__main__":
    x_points = np.array([])
    substr_points = np.array([])

    f = open(data_file_name, "r")
    line = f.readline()
    count = 0
    while True:
        line = f.readline()
        if not line:
            break
        line = line.replace(',', ' ')
        data = line.split()
        x_point = int(data[0])
        x_points = np.append(x_points, np.array([x_point]))
        substr_points = np.append(substr_points, np.array([float(data[1])]))

        count += 1

    f.close()

    plt.title("Время выполнения реализации алгоритма в зависимости от количества потоков")
    plt.plot(x_points, substr_points, label = "Алгоритм поиска подстроки")

    plt.xlabel("Количество дополнительных потоков")
    plt.ylabel("Время в мс")

    plt.legend()
    plt.show()
