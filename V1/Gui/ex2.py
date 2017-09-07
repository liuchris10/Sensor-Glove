k=1
title = "Sensor " + str(k) + ": (Pa)"
print(title)
num_sensors = 3
sensors_pressure = [[0 for x in range(1)] for y in range(num_sensors)]
print(sensors_pressure)
# for n in range(1, num_sensors):

for n in range(0, num_sensors):
    temp1 = n+1
    print(temp1)
    temp2 = (temp1 * 0.00034) + 4  # Converting Raw Values to Capacitance
    temp3 = (temp2 - 24) * 2.2  # Converting Capacitance to Pressure
    sensors_pressure[n].append(temp3)  # Storing values in Larger Data Array
print(sensors_pressure)

endbit = b'\n'
if endbit == b'\n':
    print(endbit)