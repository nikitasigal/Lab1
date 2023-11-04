# Parallel Programming
## Lab 1
#### Usage
```shell
./run.sh -gv -t 80 -b 100 -s 30 -i ./data/input.txt -o ./data/output.csv
```
where:
- `-g` tell the script to generate new input data
- `-v` tell the script to visualize the output
- `-t 80` is the number of threads (defaults to `4`)
- `-b 100` is the number of bodies (defaults to `64`)
- `-s 30` is the number of seconds to simulate, assuming 20 iterations per second of simulation (defaults to `15`)
- `-i ./data/input.txt` is the input file (defaults to `./data/input.txt`)
- `-o ./data/output.csv` is the output file (defaults to `./data/output.csv`)