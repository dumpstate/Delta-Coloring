#ifndef DELTACOLORING_GREEDY_COLORING
#define DELTACOLORING_GREEDY_COLORING

#include <vector>

#include <boost/graph/graph_traits.hpp>

#include <boost/foreach.hpp>

using std::vector;

using boost::property_traits;
using boost::num_vertices;

namespace dColoring {
	template<typename VertexListGraph, typename ColorMap>
	typename property_traits<ColorMap>::value_type
	greedy_coloring(const VertexListGraph& graph, const ColorMap& color) {
		typedef typename VertexListGraph::vertex_descriptor Vertex;
		typedef typename VertexListGraph::vertex_iterator Iterator;
		typedef typename VertexListGraph::adjacency_iterator AdjIterator;
		typedef typename property_traits<ColorMap>::value_type size_type;

		size_type colors = 0;
		const size_type num_v = num_vertices(graph);
		vector<size_type> mark(
			num_v, std::numeric_limits<size_type>::max BOOST_PREVENT_MACRO_SUBSTITUTION());

		Iterator v, vend;
		for(tie(v, vend) = vertices(graph); v != vend; ++v)
			put(color, *v, num_v - 1);

		int i = 0;
		BOOST_FOREACH(Vertex current, vertices(graph)){
			AdjIterator v, vend;
			for(tie(v, vend) = adjacent_vertices(current, graph); v != vend; ++v)
				mark[get(color, *v)] = i;

			size_type j = 0;

			while(j < colors && mark[j] == i)
				++j;

			if(j == colors)
				++colors;

			put(color, current, j);
			++i;
		}

		return colors;
	}

	template<typename VertexListGraph, typename Order, 
		typename ColorMap, typename Distances>
	typename property_traits<ColorMap>::value_type
	greedy_coloring(const VertexListGraph& graph, 
		const Order& order, const ColorMap& color, const Distances& distances) {
		typedef graph_traits<VertexListGraph> Graph;
		typedef typename Graph::vertex_descriptor	Vertex;
		typedef typename Graph::vertex_iterator	Iterator;
		typedef typename property_traits<ColorMap>::value_type size_type;

		size_type colors = 0;
		const size_type num_v = num_vertices(graph);

		vector<size_type> mark(
			num_v, std::numeric_limits<size_type>::max BOOST_PREVENT_MACRO_SUBSTITUTION());

		Iterator v, vend;
		for(tie(v, vend) = vertices(graph); v != vend; ++v)
			put(color, *v, num_v - 1);
		for(size_type i = 0; i < num_v; i++) {
			Vertex current = distances.at(i).first;

			typename Graph::adjacency_iterator v, vend;

			for(tie(v, vend) = adjacent_vertices(current, graph); v != vend; ++v)
				mark[get(color, *v)] = i;

			size_type j = 0;
		
			while(j < colors && mark[j] == i)
				++j;
			
			if(j == colors)
				++colors;

			put(color, current, j);
		}

		return colors;
	}
}

#endif //DELTACOLORING_GREEDY_COLORING