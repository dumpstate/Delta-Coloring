#ifndef DELTACOLORING_IS_GRAPH_CONNECTED
#define DELTACOLORING_IS_GRAPH_CONNECTED

#include "types.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/biconnected_components.hpp>
#include <iostream>

using boost::property_map;
using boost::default_dfs_visitor;

namespace dColoring {

	static int counter;

	class dfs_counter_visitor: public default_dfs_visitor {
	public:
		template<typename Vertex, typename Graph>
		void discover_vertex(Vertex u, const Graph & g) {
			++counter;
		}
	};

	template<class VertexListGraph>
	bool is_graph_connected(const VertexListGraph& graph) {
		counter = 0;
		dfs_counter_visitor vis;

		depth_first_search(graph, visitor(vis));
		
		return counter == num_vertices(graph);
	}
}

#endif //DELTACOLORING_IS_GRAPH_CONNECTED
