import matplotlib.pyplot as plt
from matplotlib.figure import Figure
n = 0
num_sensors = 3
sensors_pressure = [[0 for x in range(1)] for y in range(num_sensors)]
x = [0]
print(sensors_pressure)
# for n in range(1, num_sensors):
for n in range(0, num_sensors):
    for j in range(0, 50):
        if n == 0:
            x.append(j)
        temp1 = j + 1 + 50 * (n + 1)
        temp2 = (temp1 * 0.00034) + 4  # Converting Raw Values to Capacitance
        temp3 = (temp2 - 24) * 2.2  # Converting Capacitance to Pressure
        sensors_pressure[n].append(temp3)  # Storing values in Larger Data Array
sensors_pressure[1] = 51*[0]
plt.plot(x, sensors_pressure[1], color='blue')
plt.plot(x, sensors_pressure[2], color='red')
plt.show()
print(sensors_pressure[1])
print(sensors_pressure[2])