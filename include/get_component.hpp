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
				std::cerr << "\tpair: " << e;
				Vertex oldSource = source(e, graph);
				Vertex oldTarget = target(e, graph);
				Vertex newSource, newTarget;
				
				if(local_names.count(oldSource) > 0) {
					std::cerr << "\tlocal_names(oldSource)";
					newSource = local_names[oldSource];
				} else {
					std::cerr << "\t!local_names(oldSource)";
					newSource = add_vertex(comp);
					std::cerr << "\t writing to local_names " << newSource;
					local_names[oldSource] = newSource;
					std::cerr << "\t writing to names ";
					names[newSource] = oldSource;
				}
				std::cerr << "lll";
				if(local_names.count(oldTarget) > 0) {
					std::cerr << "\tlocal_names(oldTarget)";
					newTarget = local_names[oldTarget];
				} else {
					std::cerr << "\t!local_names(oldTarget)";
					newTarget = add_vertex(comp);
					local_names[oldTarget] = newTarget;
					names[newTarget] = oldTarget;
				}
				std::cerr << " add_edge" << std::endl;
				add_edge(newSource, newTarget, comp);
			}
		}

		#ifdef DEBUG
		std::cerr << "Component: " << curr << 
			" size: " << num_vertices(comp) << std::endl;
		BOOST_FOREACH(Edge e, edges(comp)) {
			std::cerr << "\tEdge: " << e << std::endl;
		}
		#endif

		return comp;
	}
}

#endif //DELTACOLORING_GET_COMPONENT