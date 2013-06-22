#ifndef DELTACOLORING_GET_COMPONENT
#define DELTACOLORING_GET_COMPONENT

#include <iostream>
#include <map>

#include <boost/foreach.hpp>
#include <boost/graph/graph_traits.hpp>

using boost::source;
using boost::target;
using boost::add_vertex;
using boost::add_edge;

namespace dColoring {
	template<typename Graph, typename ComponentMap, typename NameDict>
	Graph get_component(Graph& graph, ComponentMap& componentMap,
		int curr, NameDict& names) {
		typedef typename Graph::edge_descriptor Edge;
		typedef typename Graph::vertex_descriptor Vertex;
		Graph comp(0);

		NameDict local_names;
		BOOST_FOREACH(Edge e, edges(graph)) {
			if(curr == get(componentMap, e)) {
				Vertex oldSource = source(e, graph);
				Vertex oldTarget = target(e, graph);
				Vertex newSource, newTarget;
				
				if(local_names.count(oldSource) > 0) {
					newSource = local_names[oldSource];
				} else {
					newSource = add_vertex(comp);
					local_names[oldSource] = newSource;
					names[newSource] = oldSource;
				}

				if(local_names.count(oldTarget) > 0) {
					newTarget = local_names[oldTarget];
				} else {
					newTarget = add_vertex(comp);
					local_names[oldTarget] = newTarget;
					names[newTarget] = oldTarget;
				}
				add_edge(newSource, newTarget, comp);
			}
		}

		#ifdef DEBUG
		LOG4("\tComponent:", curr, "size:", num_vertices(comp));
		BOOST_FOREACH(Edge e, edges(comp)) {
			LOG2("\t\tEdge:", e);
		}
		#endif

		return comp;
	}
}

#endif //DELTACOLORING_GET_COMPONENT