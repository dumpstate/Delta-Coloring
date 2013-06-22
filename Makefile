all: main

main: src/ParameterParser.cpp src/single_component_graph_coloring.cpp
	g++ -o deltaColoring 	\
		src/ParameterParser.cpp 					\
		src/single_component_graph_coloring.cpp -lboost_graph

.PHONY: main
