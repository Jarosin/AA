import matplotlib.pyplot as plt
import numpy as np

data_file_name = "docs/csv/odd_time.csv"


if __name__ == "__main__":
    x_points = np.array([])
    damerau_matrix_points = np.array([])
    damerau_rec_points = np.array([])
    classic_points = np.array([])
    f = open(data_file_name, "r")
    line = f.readline()
    count = 0
    while True:
        line = f.readline()
        if not line:
            break
        line = line.replace(',', ' ')
        data = line.split()
        x_points = np.append(x_points, np.array([float(data[0])]))
        damerau_matrix_points = np.append(damerau_matrix_points, np.array([float(data[1])]))
        damerau_rec_points = np.append(damerau_rec_points, np.array([float(data[2])]))
        classic_points = np.append(classic_points, np.array([float(data[3])]))
        count += 1
        if (count > 8):
            break

    f.close()

    plt.plot(x_points, classic_points, label = "Классический алгоритм")
    plt.plot(x_points, damerau_matrix_points, label = "Алгоритм Винограда")
    plt.plot(x_points, damerau_rec_points, label = "Оптимизированный алгоритм Винограда")

    plt.xlabel("Размерность матрицы")
    plt.ylabel("Время в мс")
    plt.legend()
    plt.show()
