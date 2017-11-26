#!/usr/bin/python
import math
import csv
import matplotlib.pyplot as pyplot
import numpy

t_max = 5
fp = 100
SUBSTRACT = 0
ADD = 1
MULTIPLICATE = 2

def simple_tone(a, f, phi):
    points = []
    w = 2 * math.pi * f
    global t_max, fp
    times = []
    t = 1.0/fp
    for time in numpy.arange(0, t_max, t):
        times.append(time)
        point_val = a * math.sin(w * time + phi)
        points.append(point_val)
    return times, points

def operations(a1, a2, f1, f2, phi1, phi2, op_type):
    w1 = 2 * math.pi * f1
    w2 = 2 * math.pi * f2
    global t_max, fp
    t = 1.0/fp
    times = []
    sin_sum = []
    for time in numpy.arange(0, t_max, t):
        times.append(time)
        if ADD == op_type:
            point_val = a1 * math.sin(w1 * time + phi1) + a2 * math.sin(w2 * time + phi2)
        elif SUBSTRACT == op_type:
            point_val = a1 * math.sin(w1 * time + phi1) - a2 * math.sin(w2 * time + phi2)
        elif MULTIPLICATE == op_type:
            point_val = a1 * math.sin(w1 * time + phi1) * a2 * math.sin(w2 * time + phi2)
        sin_sum.append(point_val)
    return times, sin_sum

def main():
    xs, ys = simple_tone(1, 1, 1)
    #xs, ys = operations(1, 2, 1, 2, 1, 2, SUBSTRACT)
    '''with open('signals.csv', 'wb') as csv_file:
        writer = csv.writer(csv_file)
        for point in xs, ys:
            writer.writerow(point)'''
    pyplot.plot(xs, ys)
    pyplot.xlabel('time (s)')
    pyplot.ylabel('signal')
    pyplot.grid(True)
    pyplot.savefig("signal.png")

if __name__ == "__main__":
    main()
