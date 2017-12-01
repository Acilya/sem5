#!/usr/bin/python
import math
import csv
import matplotlib.pyplot as pyplot
import numpy

t_max = 3
fp = 50
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
    #drawPlot(times, points, "time (s)", "simple_tone", "simple_signal")
    return times, points

def operations(a1, a2, a3, f1, f2, f3, phi1, phi2, phi3, op_type):
    w1 = 2 * math.pi * f1
    w2 = 2 * math.pi * f2
    w3 = 2 * math.pi * f3
    global t_max, fp
    t = 1.0/fp
    times = []
    sin_sum = []
    for time in numpy.arange(0, t_max, t):
        times.append(time)
        if ADD == op_type:
            point_val = a1 * math.sin(w1 * time + phi1) + a2 * math.sin(w2 * time + phi2) + a3 * math.sin(w3 * time + phi3)
        elif SUBSTRACT == op_type:
            point_val = a1 * math.sin(w1 * time + phi1) - a2 * math.sin(w2 * time + phi2) - a3 * math.sin(w3 * time + phi3)
        elif MULTIPLICATE == op_type:
            point_val = a1 * math.sin(w1 * time + phi1) * a2 * math.sin(w2 * time + phi2) * a3 * math.sin(w3 * time + phi3)
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

def magnitude(times, samples):
    global fp
    x = []
    for i in range(0, len(times)):
        windowFunc = 1 # 0.54-0.46*math.cos(2*math.pi*times[i]/len(times))
        x.append(samples[i] * windowFunc)
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

def amplitudeModulation():
    k = 0.2
    correctK = True
    signalTimes, signal = operations(1, 2, 1, 2, 3, 2, 0, 0, 0, ADD)
    carrierTimes, carrier = simple_tone(1, 20, 0)
    am = []
    for i in range(0, len(signal)):
        if abs(k*signal[i]) < 1:
            am.append(carrier[i] * (k * signal[i] + 1))   # carrier[i] = A * cos(2*pi*fn*t)
        else:
            print "Wrong k!"
            correctK = False
            break
    if correctK:
        drawPlot(carrierTimes, am, "time (s)", "signal", "AM")
        magnitude(carrierTimes, am)

def phaseModulation():
    k = 0.4
    correctK = True
    signalTimes, signal = operations(1, 2, 1, 2, 3, 2, 0, 0, 0, ADD)
    a = 1
    f = 20
    phi = 0
    carrierTimes, carrier = simple_tone(a, f, phi)
    pm = []
    for i in range(0, len(signal)):
        if k * max(map(abs, signal)) >= 1:
            pm.append(a * math.cos(2 * math.pi * f * carrierTimes[i] + k * signal[i]))
        else:
            print "Wrong k!"
            correctK = False
            break
    if correctK:
        drawPlot(carrierTimes, pm, "time (s)", "signal", "PM")

def main():
    #xs, ys = simple_tone(1, 1, 1)
    #xs, ys = operations(1, 2, 1, 2, 1, 2, ADD)
    #x = [2, 3, -4, -1]
    #dft(2, x)
    #magnitude(xs, ys)
    phaseModulation()

if __name__ == "__main__":
    main()
