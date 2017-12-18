#!/usr/bin/python
import math
import matplotlib.pyplot as pyplot
import numpy
from random import *

t_max = 3
fp = 200
tp = 1.0 / fp
tb = 0.2
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

def bin_signal():
    signal = []
    times = []
    n = int(math.floor(t_max/tb))
    bits = [randint(0, 1) for b in range(1, n + 1)]
    reps = int(tb / tp)    # musi byc podzielne!
    for bit in bits:
        signal[:] += [bit] * reps
    for t in numpy.arange(0, t_max, tp):
        times.append(t)
    return signal, times

def ask(signal, times):
    modulated = []
    f = 10  # f powinna byc wielokrotnoscia 1/Tb (tu: 10)
    for i in range(0, len(times)):
        if signal[i] == 0:
            modulated.append(0)
        else:
            modulated.append(math.sin(2 * math.pi * f * times[i]))
    return modulated

def fsk(signal, times):
    modulated = []
    n = 1
    f1 = (n+1)/tb
    f2 = (n+2)/tb
    for i in range(0, len(times)):
        if signal[i] == 0:
            modulated.append(math.sin(2 * math.pi * f1 * times[i]))
        else:
            modulated.append(math.sin(2 * math.pi * f2 * times[i]))
    return modulated

def psk(signal, times):
    modulated = []
    f = 10
    for i in range(0, len(times)):
        if signal[i] == 0:
            modulated.append(math.sin(2 * math.pi * f * times[i]))
        else:
            modulated.append(math.sin(2 * math.pi * f * times[i] + math.pi))
    return modulated

def main():
    signal, times = bin_signal()
    ask_sig = ask(signal, times)
    fsk_sig = fsk(signal, times)
    psk_sig = psk(signal, times)
    pyplot.subplot(411)
    pyplot.step(times, signal, where='pre')
    pyplot.ylim(-0.5, 1.5)
    pyplot.subplot(412)
    pyplot.plot(times, ask_sig)
    pyplot.subplot(413)
    pyplot.plot(times, fsk_sig)
    pyplot.subplot(414)
    pyplot.plot(times, psk_sig)
    pyplot.show()
    #magnitude(times, modulated)

if __name__ == "__main__":
    main()