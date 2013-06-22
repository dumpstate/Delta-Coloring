#ifndef DELTACOLORING_UWV_TUPLE
#define DELTACOLORING_UWV_TUPLE

#include "is_graph_connected.hpp"
#include "uwv_not_found_exception.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/copy.hpp>
#include <iostream>

using boost::graph_traits;
using boost::tie;

namespace dColoring {
	static const int UWV_SIZE = 3;
	static const int FIRST = 0;
	static const int SECOND = 1;
	static const int THIRD = 2;
	
	template<class VertexListGraph, class Vertex>
	bool are_uwv_ok(const VertexListGraph& graph, Vertex uwv[]) {
		// Checking whether the FIRST and THIRD are not heighbors.
		typedef typename graph_traits<VertexListGraph>::adjacency_iterator AdjIterator;
		
		AdjIterator n_v, n_vend;
		for(tie(n_v, n_vend) = adjacent_vertices(uwv[FIRST], graph); n_v != n_vend; ++n_v) {
			if(uwv[THIRD] == *n_v)
				return false;
		}
		
		// Removing FIRST and THIRD, then checking whether graph remains connected.
		VertexListGraph temp_graph;
		copy_graph(graph, temp_graph);

		clear_vertex(uwv[FIRST], temp_graph);
		clear_vertex(uwv[THIRD], temp_graph);
		remove_vertex(uwv[FIRST], temp_graph);
		remove_vertex(uwv[THIRD], temp_graph);

		return is_graph_connected(temp_graph);
	}

	template<class VertexListGraph>
	typename graph_traits<VertexListGraph>::vertex_descriptor*
  get_uwv_tuple(const VertexListGraph& graph) {
		typedef typename graph_traits<VertexListGraph>::vertex_descriptor Vertex;
		typedef typename graph_traits<VertexListGraph>::vertex_iterator Iterator;
		typedef typename graph_traits<VertexListGraph>::adjacency_iterator AdjIterator;
		Vertex* uwv = new Vertex[UWV_SIZE];

		Iterator f_v, f_vend;
		AdjIterator s_v, s_vend, t_v, t_vend;
		bool done = false;
		for(tie(f_v, f_vend) = vertices(graph); f_v != f_vend; ++f_v) {
			uwv[FIRST] = *f_v;

			for(tie(s_v, s_vend) = adjacent_vertices(uwv[FIRST], graph); s_v != s_vend; ++s_v) {
				uwv[SECOND] = *s_v;
				if(uwv[SECOND] == uwv[FIRST]) continue;

				for(tie(t_v, t_vend) = adjacent_vertices(uwv[SECOND], graph); t_v != t_vend; ++t_v) {
					uwv[THIRD] = *t_v;
					if(uwv[THIRD] == uwv[FIRST] || uwv[THIRD] == uwv[SECOND]) continue;

					if(are_uwv_ok(graph, uwv))
						goto DONE;
				}
			}
		}

		throw uwv_not_found_exception();

	DONE:
		#ifdef DEBUG
		std::cerr << "[1 a.] UWV tuple: [" << 
			uwv[FIRST] << ", " <<
			uwv[SECOND] << ", " <<
			uwv[THIRD] << "]" << std::endl;
		#endif

		return uwv;
	}
}
#endif //DELTACOLORING_UWV_TUPLE