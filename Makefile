all: main

main: src/ParameterParser.cpp src/graph_coloring.cpp
	g++ -o deltaColoring 	\
		src/ParameterParser.cpp 					\
		src/graph_coloring.cpp -Bstatic -lboost_graph

.PHONY: main
