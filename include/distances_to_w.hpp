#ifndef DELTACOLORING_DISTANCES_TO_W
#define DELTACOLORING_DISTANCES_TO_W

#include "types.h"

#include <vector>

#include <boost/foreach.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using std::vector;

using boost::num_vertices;
using boost::edge_weight_t;
using boost::edge_weight;
using boost::predecessor_map;

namespace dColoring {
	template<class VertexListGraph, class Vertex, class Distances>
	void distances_to_w(const VertexListGraph& graph, Vertex* uwv, Distances& d) {
		typedef graph_traits<GraphW>::vertex_descriptor VertexW;
		typedef graph_traits<GraphW>::edge_descriptor EdgeW;
		typedef typename graph_traits<VertexListGraph>::edge_descriptor Edge;

		const int num_nodes = num_vertices(graph);
		GraphW graph_temp(num_nodes);

		property_map <GraphW, edge_weight_t>::type weightmap = 
  		get(edge_weight, graph_temp);

  	BOOST_FOREACH(Edge e, edges(graph)) {
			VertexW s = source(e, graph), t = target(e, graph);
			if(s == uwv[FIRST] || s == uwv[THIRD] || 
				t == uwv[FIRST] || t == uwv[THIRD])
				continue;
			EdgeW e_temp; bool inserted;
			tie(e_temp, inserted) = add_edge(s, t, graph_temp);
			weightmap[e_temp] = 1;
		}

		vector<VertexW> p(num_vertices(graph));

		dijkstra_shortest_paths(graph_temp, vertex(uwv[SECOND], graph_temp),
			predecessor_map(&p[0]).distance_map(&d[0]));
	}
}

#endif //DELTACOLORING_DISTANCES_TO_W