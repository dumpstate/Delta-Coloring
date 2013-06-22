//#define DEBUG

#include "../include/log.h"
#include "../include/types.h"
#include "../include/ParameterParser.hpp"
#include "../include/ColoringMode.hpp"
#include "../include/component_delta_coloring.hpp"
#include "../include/write_graph_to_dot.hpp"
#include "../include/delta_g.hpp"
#include "../include/get_component.hpp"
#include "../include/merge_components.hpp"

#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/graphviz.hpp>

#include <map>

using namespace std;
using namespace dColoring;

int main(int argc, char* argv[]){
	using namespace boost;

	typedef graph_traits<Graph>::vertex_descriptor vertex_t;

	ParameterParser pp(argc, argv);

	Graph graph(0);
	dynamic_properties dp;

	property_map<Graph, vertex_color_t>::type color =
		get(vertex_color, graph);
	dp.property("fillcolor", color);

	if(!read_graphviz(pp.getInput(), graph, dp, "fillcolor")) {
		return EXIT_FAILURE;
	}

	property_map<Graph, edge_component_t>::type component
		= get(edge_component, graph);
	size_t num_comps = biconnected_components(graph, component);		

	std::map<vertex_t, vertex_t>* old_to_new =
		new std::map<vertex_t, vertex_t>[num_comps]; 

	vector<Graph> components(num_comps);
	vector<property_map<Graph, vertex_color_t>::type> colors(num_comps);
	for(int i = 0; i < num_comps; i++) {
		LOG1("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		LOG4("i:", i, ", num_comps:", num_comps);
		components[i] = get_component(graph, component, i, old_to_new[i]);
		colors[i] = get(vertex_color, components[i]);
		component_delta_coloring(components[i], colors[i]);
	}

	int num_col = merge_components(graph, color, num_comps,
		components, colors, old_to_new);
	int max_degree = delta_g(graph);

	//write graph to file
	write_graph_to_dot(graph, color, component, pp.getOutput(), 
		num_col, num_comps, max_degree);

	delete[] old_to_new;

	return EXIT_SUCCESS;
}