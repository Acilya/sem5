#!/usr/bin/python
import math
import csv
import matplotlib.pyplot as pyplot
import numpy
from random import *

t_max = 3
fp = 100
tb = 0.1
REAL = 0
IMAGINARY = 1

def drawPlot(x, y, xlabel, ylabel, title):
    pyplot.plot(x, y)
    pyplot.xlabel(xlabel)
    pyplot.ylabel(ylabel)
    pyplot.grid(True)
    title = title + ".png"
    pyplot.savefig(title)
    pyplot.show()

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
    return k

def magnitude(times, samples):
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

def bin_signal(n):
    signal = [randint(0, 1) for b in range(1, n + 1)]
    return signal

def ask():
    tp = 1.0 / fp
    f = 10  # f powinna byc wielokrotnoscia 1/Tb (tu: 10)
    times = []
    signal = []
    modulated = []
    bits = bin_signal(int(math.floor(t_max/tb)))
    reps = int(tb / tp)    # musi byc podzielne!
    for bit in bits:
        signal[:] += [bit] * reps
    for t in numpy.arange(0, t_max, tp):
        times.append(t)
    for i in range(0, len(times)):
        if signal[i] == 0:
            modulated.append(0)
        else:
            modulated.append(math.sin(2*math.pi*f*times[i]))
    pyplot.subplot(211)
    pyplot.step(times, signal, where='pre')
    pyplot.ylim(-0.5, 1.5)
    pyplot.subplot(212)
    pyplot.plot(times, modulated)
    pyplot.show()
    magnitude(times, modulated)

#def fsk(signal):

#def psk(signal):

def main():
    ask()

if __name__ == "__main__":
    main()