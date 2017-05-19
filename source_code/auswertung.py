import matplotlib.pyplot as pyplot
import pandas as pandas


dataset = pandas.read_csv("cmake-build-debug/coords.txt", sep=";", header=0, encoding="utf8")

fig = pyplot.figure();
ax = fig.add_subplot(1,1,1)
ax.hist(dataset['Radius'], bins=5)
ax.set_ylabel('Anzahl Moleküle mit Radius')
ax.set_title('Radius')
pyplot.show()