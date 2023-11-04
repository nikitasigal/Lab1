import random
import sys

BODIES, SECONDS, INPUT_FILE = sys.argv[1:]
BODIES = int(BODIES)
SECONDS = int(SECONDS)

with open(INPUT_FILE, "w") as f:
    f.write(f"{BODIES} {20 * SECONDS}\n")
    for _ in range(BODIES):
        f.write(f"{random.uniform(1e9, 1e12)}\n")
        f.write(f"{random.uniform(-75, 75)} {random.uniform(-75, 75)}\n")
        f.write(f"{random.uniform(-2, 2)} {random.uniform(-2, 2)}\n")
