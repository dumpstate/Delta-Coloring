#ifndef DELTACOLORING_TYPES
#define DELTACOLORING_TYPES

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <string>

using std::string;
using boost::property;
using boost::vertex_name_t;
using boost::vertex_color_t;
using boost::adjacency_list;
using boost::vecS;
using boost::listS;
using boost::undirectedS;
using boost::directedS;
using boost::edge_property_tag;
using boost::edge_weight_t;
using boost::no_property;
using boost::graph_traits;

namespace dColoring{	
	struct edge_component_t {
		enum {
			num = 555
		};
		typedef edge_property_tag kind;
	} edge_component;

	typedef property<vertex_name_t, string,
		property<vertex_color_t, int> > vertex_p;

	typedef property<edge_component_t, std::size_t>
		edge_p;	

	typedef adjacency_list<vecS, vecS, undirectedS,
		vertex_p, edge_p> Graph;

	typedef adjacency_list<vecS, vecS, undirectedS,
		no_property, property<edge_weight_t, int> > GraphW;
}

#endif //DELTACOLORING_TYPES
