import numpy as np
import matplotlib.pyplot as plt
from matplotlib import gridspec

def grad(per):
    if per <= 0.25:
        return (0, 4 * per, 1)
    if per <= 0.5:
        return (0, 1, 1 - 4 * (per - 0.25))
    if per <= 0.75:
        return (4 * (per - 0.5), 1, 0)
    if per <= 1:
        return (1, 1 - 4 * (per - 0.75), 0)
    return (1, 0, 0)

data = np.loadtxt("data.dat")

x = data[:, 0]
y = data[:, 1]
t = data[:, 2]

tmin = t.min()
#t = t - tmin
tmax = t.max()
if tmax == 0.0:
	tmax = 1.0

t /= tmax

colors = np.array([grad(i) for i in t])

fig = plt.figure()

fig.set_figheight(4)
 
# set width of each subplot as 8
fig.set_figwidth(8)

spec = gridspec.GridSpec(ncols=2, nrows=2,
                         width_ratios=[2, 1], wspace=0.5,
                         hspace=0.5, height_ratios=[1, 2])
#fig, axs = plt.subplots(1, 2)
#axs[0].scatter(x, y, color=colors)

#axs[1].grid()
axs0 = plt.subplot2grid(shape=(1, 4), loc=(0, 0), colspan=3)
axs1 = plt.subplot2grid(shape=(1, 7), loc=(0, 6), colspan=3)
axs1.get_xaxis ().set_visible ( False )
axs0.scatter(x, y, color=colors)
for dot in np.linspace(tmin, tmax, 200):
	axs1.scatter(0, dot, color=grad(dot / tmax))


plt.show()
