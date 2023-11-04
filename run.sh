generate_new_data=false
visualize_output=false
number_of_threads=4
number_of_bodies=64
number_of_seconds=15
input_file="./data/input.txt"
output_file="./data/output.csv"

while getopts 'gvt:b:s:i:o:' OPTION; do
	case "$OPTION" in
	g)
		generate_new_data=true
		;;
	v)
		visualize_output=true
		;;
	t)
		number_of_threads="$OPTARG"
		;;
	b)
		number_of_bodies="$OPTARG"
		;;
	s)
		number_of_seconds="$OPTARG"
		;;
	i)
		input_file="$OPTARG"
		;;
	o)
		output_file="$OPTARG"
		;;
	?)
		echo "Incorrect usage"
		exit 1
		;;
	esac
done

if [ "$generate_new_data" = true ] || [ "$visualize_input" = true ]; then
	echo "Checking requirements..."
	pip install -q -r ./util/requirements.txt
fi

if $generate_new_data; then
	echo "Generating input..."
	python ./util/generator.py "$number_of_bodies" "$number_of_seconds" "$input_file"
fi

echo "Running the simulation..."
./build/Lab1 "$input_file" "$output_file" "$number_of_threads"

if $visualize_output; then
	echo "Visualizing..."
	python ./util/visualizer.py "$output_file"
fi

echo "Done!"
