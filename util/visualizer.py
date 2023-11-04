from celluloid import Camera
import matplotlib.pyplot as plt
import numpy as np
import sys

fig = plt.figure(figsize=(10, 10))
plt.axis((-100, 100, -100, 100))
camera = Camera(fig)

OUTPUT_FILE = sys.argv[-1]

with open(OUTPUT_FILE) as f:
    lines = f.readlines()
    masses = [float(x) for x in lines[0].split(",")[1:]]

    for line in lines[1:]:
        values = [float(x) for x in line.split(",")[1:]]
        plt.scatter(values[::2], values[1::2], c=masses, cmap='plasma')
        camera.snap()

animation = camera.animate()
animation.save("./data/animation.mp4", fps=20)
