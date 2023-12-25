import matplotlib.pyplot as plt
import numpy as np

data_file_name = "data.txt"


if __name__ == "__main__":
    x_points = np.array([])
    lev_points = np.array([])
    damerau_matrix_points = np.array([])
    damerau_rec_points = np.array([])
    damerau_hash_points = np.array([])
    f = open(data_file_name, "r")
    count = 0
    while True:
        line = f.readline()
        if not line:
            break
        line = line.replace(',', '')
        data = line.split()
        x_points = np.append(x_points, np.array([float(data[0])]))
        lev_points = np.append(lev_points, np.array([float(data[1]) / 1e6]))
        damerau_matrix_points = np.append(damerau_matrix_points, np.array([float(data[2]) / 1e6]))
        if data[3] != '-':
            damerau_rec_points = np.append(damerau_rec_points, np.array([float(data[3]) / 1e6]))
        else:
            damerau_rec_points = np.append(damerau_rec_points, np.array([float(damerau_rec_points[-1])]))
        damerau_hash_points = np.append(damerau_hash_points, np.array([float(data[4]) / 1e6]))
        count += 1
        # if (count > 8):
        #     break

    f.close()

    plt.plot(x_points, lev_points, label = "Нерекурсивный алгоритм Левенштейна")
    plt.plot(x_points, damerau_matrix_points, label = "Нерекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна")
    # plt.plot(x_points, damerau_rec_points, label = "Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна")
    # plt.plot(x_points, damerau_hash_points, label = "Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна с кэшем")
    # plt.yscale("log")
    plt.xlabel("Длина в символах")
    plt.ylabel("Время в мс")
    plt.legend()
    plt.show()
