#!/usr/bin/python
import math
import matplotlib.pyplot as pyplot
import numpy

t_max = 1
SUBSTRACT = 0
ADD = 1
MULTIPLICATE = 2

def simple_tone(a, f, phi):
    points = []
    w = 2 * math.pi * f
    global t_max
    times = []
    t = 1.0/100.0
    for time in numpy.arange(0, t_max, t):
        times.append(time)
        point_val = a * math.sin(w * time + phi)
        points.append(point_val)
    return times, points

def operations(a1, a2, f1, f2, phi1, phi2, op_type):
    w1 = 2 * math.pi * f1
    w2 = 2 * math.pi * f2
    if w1 > w2:
        t = 1.0/(2.0*w1)
    else:
        t = 1.0/(2.0*w2)
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
            k[0] = k[0] + temp[0]
            k[1] = k[1] + temp[1]
    return k

def mag(samples):
    dfts = []
    for i in range(0, len(samples)):
        dfts.append(dft(i, samples))
    xmag = []
    n = len(dfts)
    for i in range(0, n):
        xmag.append(math.sqrt((dfts[i][0])**2 + (dfts[i][1])**2))
    pyplot.plot(range(0, len(samples)), xmag)
    pyplot.xlabel('samples')
    pyplot.ylabel('A')
    pyplot.grid(True)
    pyplot.savefig("magn.png")

def main():
    #xs, ys = simple_tone(1, 2, 0)
    xs, ys = operations(1, 1, 2, 10, 0, 0, ADD)
    '''with open('signals.csv', 'wb') as csv_file:
        writer = csv.writer(csv_file)
        for point in xs, ys:
            writer.writerow(point)'''
    '''pyplot.plot(xs, ys)
    pyplot.xlabel('time (s)')
    pyplot.ylabel('signal')
    pyplot.grid(True)
    pyplot.savefig("signal.png")'''
    mag(ys)

if __name__ == "__main__":
    main()
