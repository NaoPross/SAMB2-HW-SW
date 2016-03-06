import os, sys, time
import argparse
import datetime
import serial
import matplotlib.pyplot as plt


""" PARSE ARGUMENTS """
parser = argparse.ArgumentParser()
parser.add_argument(
    "readtime",
    help="the amount of time before the program stops reading from the serial port",
    type=int
)

args = parser.parse_args()

""" READ SERIAL DATA """
# initialization
port = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)
sda_states_arr = []
scl_states_arr = []

# store the start time
t_start = datetime.datetime.now().timestamp()

while datetime.datetime.now().timestamp() - t_start < args.readtime:
    raw_data = port.read(7)

    if not str(raw_data).startswith("b"):
        port.read(1)
    else:
        data = str(raw_data)[2:].replace('\'', '').replace('\\r\\n', '').split('=')

        print(str(raw_data))
        print(data)

        if data[0] == "SDA":
            sda_states_arr.append(data[1])
        elif data[0] == "SCL":
            scl_states_arr.append(data[1])

print(sda_states_arr)
print(scl_states_arr)

""" PLOT FUNCTION """
def plot(blue, green):
    plt.plot(blue)
    plt.plot(green)
    plt.axis([0, len(scl_states_arr), 0, 2])
    plt.show() 

""" DEBUG FUNCTIONS """
def fw_data(arr, num):
    out = arr[num:]
    for i in range(num):
        out.append(-1)
    return out

def bw_data(arr, num):
    out = arr[::-1]
    for i in range(num):
        out.append(-1)
    out.reverse()
    return out

def sum_to_data(arr, num):
    out = []
    for item in arr:
        out.append(item + num)
    return out

def sub_to_data(arr, num):
    out = []
    for item in arr:
        out.append(item - num)
    return out

""" ACTUAL PLOTTING """
sda_states_arr = sum_to_data(sda_states_arr, 1)
scl_states_arr = sub_to_data(scl_states_arr, 1)

plot(tuple(sda_states_arr), tuple(scl_states_arr))