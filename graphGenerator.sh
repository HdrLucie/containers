#!/bin/zsh

# Generate a graph tmp.svg with dot every second, check if the generated graph is the same as the previous one (graph.svg) and if not, replace graph2.svg with graph.svg and graph.svg with tmp.svg
# a .dot file is deemed different from another if the number of lines is different
rm -f graph.dot tmp.svg graph.svg graph2.svg
# wait for graph.dot to be created
while [ ! -f graph.dot ]; do 
	sleep 1
done
touch graph.svg
V=0
while true
do
	dot -Tsvg graph.dot -o tmp.svg
	if [[ $(wc -l tmp.svg | awk '{print $1}') -ne $(wc -l graph.svg | awk '{print $1}') ]]
	then
		V=$((V+1))
		cp tmp.svg $V.svg
		echo $V
		cp graph.svg graph2.svg
		cp tmp.svg graph.svg
		# xdg-open graph.svg
		# xdg-open graph2.svg
	fi
done
