all: main

main: src/ParameterParser.cpp src/graph_coloring.cpp
	g++ -static -o deltaColoring 	\
		src/ParameterParser.cpp 					\
		src/graph_coloring.cpp \
		-pthread -lstdc++ /usr/local/lib/libboost_graph.a /usr/local/lib/libboost_regex.a

.PHONY: main