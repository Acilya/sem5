#!/usr/bin/python
import math
import csv
import matplotlib.pyplot as pyplot
import numpy

t_max = 2
fp = 200
SUBSTRACT = 0
ADD = 1
MULTIPLICATE = 2
REAL = 0
IMAGINARY = 1

def drawPlot(x, y, xlabel, ylabel, title):
    pyplot.plot(x, y)
    pyplot.xlabel(xlabel)
    pyplot.ylabel(ylabel)
    pyplot.grid(True)
    title = title + ".png"
    pyplot.savefig(title)

def saveAsCsv(x, y):
    with open('signals.csv', 'wb') as csv_file:
        writer = csv.writer(csv_file)
        for point in x, y:
            writer.writerow(point)

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
    #drawPlot(times, points, "time (s)", "simple_tone", "signal")
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
    #drawPlot(times, sin_sum, "time (s)", "signal", "signal")
    return times, sin_sum

def dft(spectrumElement, samples):
    k = []
    n = len(samples)
    for i in range(0, n):
        temp = []
        temp.append(samples[i] * math.cos(2 * math.pi * spectrumElement * i / n))
        temp.append(samples[i] * math.sin(2 * math.pi * spectrumElement * i / n) * (-1))
        if not k:
            k = temp
        else:
            k[REAL] = k[REAL] + temp[REAL]
            k[IMAGINARY] = k[IMAGINARY] + temp[IMAGINARY]
    #print "%.2f" % k[REAL], "+", "%.2f" % k[IMAGINARY], "* j"
    return k

def mag(times, samples):
    global fp
    x = []
    for i in range(0, len(times)):
        x.append(samples[i])
    dft_v = []
    for i in range(0, len(x)):
        dft_v.append(dft(i, x))
    xmag = []
    f = []
    n = float(len(x))
    for i in numpy.arange(0.0, n/2, 1.0):
        xmag.append(math.sqrt((dft_v[int(i)][REAL])**2 + (dft_v[int(i)][IMAGINARY])**2))
        f.append(i * fp / n)
    drawPlot(f, xmag, "frequency", "amplitude", "magnitude")

def main():
    #xs, ys = simple_tone(1, 23, 0)
    xs, ys = operations(1, 2, 60, 23, 0, 0, ADD)
    #x = [2, 3, -4, -1]
    #dft(2, x)
    mag(xs, ys)

if __name__ == "__main__":
    main()
