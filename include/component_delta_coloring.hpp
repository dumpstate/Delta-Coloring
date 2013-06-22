#ifndef DELTACOLORING_COMPONENT_DELTA_COLORING
#define DELTACOLORING_COMPONENT_DELTA_COLORING

#include "types.h"
#include "uwv_tuple.hpp"
#include "uwv_not_found_exception.hpp"
#include "distances_to_w.hpp"
#include "greedy_coloring.hpp"

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <climits>

#include <boost/graph/graph_traits.hpp>
#include <boost/foreach.hpp>

using std::cerr;
using std::endl;
using std::pair;
using std::vector;
using std::make_pair;
using std::sort;

using boost::property_traits;
using boost::graph_traits;
using boost::identity_property_map;
using boost::num_vertices;

namespace dColoring {
	/**
	 * 'graph' must not be biconnected.
	 */
	struct vertex_distance_comparator {
		template<typename T>
		bool operator()(const T& a, const T& b) {
			return a.second > b.second;
		}
	};

	template<class VertexListGraph, class Order, class ColorMap>
	typename property_traits<ColorMap>::value_type
	component_delta_coloring(const VertexListGraph& graph, Order order, ColorMap color) {
		typedef graph_traits<VertexListGraph> Graph;
		typedef typename Graph::vertex_descriptor	Vertex;
		typedef typename property_traits<ColorMap>::value_type size_type;

		// 0
		cerr << "num_vertices: " << num_vertices(graph) << endl;
		if(num_vertices(graph) <= 3) {
			#ifdef DEBUG
			cerr << "component_delta_coloring - component smaller than 3" << std::endl;
			#endif
			return greedy_coloring(graph, color);
		}

		// 1.a
		Vertex* uwv = get_uwv_tuple(graph);

		// 1.b
		vector<int> d(num_vertices(graph));
		distances_to_w(graph, uwv, d);

		vector<pair<Vertex, int> > distances;

		#ifdef DEBUG
		cerr << "[1 b.] Distances to W:" << endl;
		#endif
		BOOST_FOREACH(Vertex vi, vertices(graph)) {
			if(vi == uwv[FIRST]) d[vi] = INT_MAX;
			else if(vi == uwv[THIRD]) d[vi] = INT_MAX - 1;
			distances.push_back(make_pair(vi, d[vi]));
			#ifdef DEBUG
			cerr << "\tdistance(" << vi << ") = " << d[vi] << endl;
			#endif
		}

		// 1.c
		sort(distances.begin(), distances.end(), vertex_distance_comparator());

		#ifdef DEBUG
		cerr << "[1 c.] Coloring order:" << endl;
		for(typename vector<pair<Vertex, int> >::iterator it = distances.begin();
			it != distances.end(); ++it) {
			cerr << "\tdistance(" << (*it).first << ") = " << (*it).second << endl;
		}
		#endif

		// 1.d
		size_type colors = greedy_coloring(graph, order, color, distances);

		#ifdef DEBUG
		cerr << "[1 d.] Colors used: " << colors << endl;
		BOOST_FOREACH(Vertex v, vertices(graph)) {
			cerr << "\tVertex [" << v << "], color: " << get(color, v) <<
				", distance: " << d[v] << endl; 
		}
		#endif

		delete[] uwv;

		return colors;
	}

	/**
	 * I assume that the 'graph' argument is not a biconnected graph,
	 * i.e., there are no articulation vertices in the graph.
	 */
	template<class VertexListGraph, class ColorMap>
	typename property_traits<ColorMap>::value_type
	component_delta_coloring(const VertexListGraph& graph, ColorMap color) {
		typedef typename graph_traits<VertexListGraph>::vertex_descriptor Vertex;
		typedef typename graph_traits<VertexListGraph>::vertex_iterator Iterator;
	
		pair<Iterator, Iterator> v = vertices(graph);
		vector<Vertex> order(v.first, v.second);

		return 
			component_delta_coloring(
				graph,
				make_iterator_property_map(
					order.begin(),
					identity_property_map(),
					graph_traits<VertexListGraph>::null_vertex()),
				color);
	}
}

#endif //DELTACOLORING_COMPONENT_DELTA_COLORING