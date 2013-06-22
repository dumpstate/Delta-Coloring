#ifndef DELTACOLORING_MERGE_COMPONENTS
#define DELTACOLORING_MERGE_COMPONENTS

#include <set>
#include <cmath>

#include <boost/foreach.hpp>

namespace dColoring {
	template<typename Graph, typename Color>
	void increment_colors(Graph& graph, Color& color, int max) {
		typedef typename Graph::vertex_descriptor Vertex;

		LOG1("incrementing");

		BOOST_FOREACH(Vertex v, vertices(graph)) {
			color[v] = (color[v] + 1) % (max + 1);
		}
	}

	template<typename Color, typename Vertex, typename Graph, 
		typename CompColor, typename Names>
	void reassign_colors(Color& color, Vertex collisionVertex, 
		Graph& component, CompColor& compColor, Names& names, int maxColComponent) {
		LOG2("reassign ", collisionVertex);
		const int targetCol = color[names[collisionVertex]];
		LOG4("targetCol =", targetCol, ", maxColComponent =", maxColComponent);
		if(targetCol <= maxColComponent) {
			LOG1("\tGreater");
			while(targetCol != compColor[collisionVertex]) {
				increment_colors(component, compColor, maxColComponent);
			}
		} else {
			LOG1("\tNot greater");
			while(compColor[collisionVertex] != 0) {
				increment_colors(component, compColor, maxColComponent);
			}
			BOOST_FOREACH(Vertex v, vertices(component)) {
				LOG4("\tbefore: compCol[", v, "] =", compColor[v]);
				compColor[v] = abs(targetCol - compColor[v]);
				LOG4("\tafter: compCol[", v, "] =", compColor[v]);
			}
		}
	}

	template<typename Graph, typename Color, typename Components, 
		typename Colors, typename Names>
	int merge_components(Graph& graph, Color& color, int num_comps, 
			Components& components, Colors& colors, Names& names) {
		using namespace boost;
		typedef typename Graph::vertex_descriptor Vertex;

		std::set<Vertex> assigned;

		LOG2("merging num comps:", num_comps);

		int max_col = 0;
		for(int i = 0; i < num_comps; i++) {
			LOG2("Component:", i);
			Color compColor = colors[i];
			Graph component = components[i];

			int maxColComponent = 0;
			bool reassignColors = false;
			Vertex collisionVertex;
			BOOST_FOREACH(Vertex v, vertices(component)) {
				LOG6("\tVertex: ", v, ", old: ", names[i][v], ", color: ", compColor[v]);
				LOG2("\t\tcolorMap: ", color[names[i][v]]);

				int currColor = compColor[v];

				if(assigned.count(names[i][v]) > 0) {
					reassignColors = true;
					collisionVertex = v;
				}
				if(currColor > max_col)
					max_col = currColor;
				if(currColor > maxColComponent)
					maxColComponent = currColor;
			}

			if(reassignColors)
				reassign_colors(color, collisionVertex, 
					component, compColor, names[i], maxColComponent);

			BOOST_FOREACH(Vertex v, vertices(component)) {
				assigned.insert(names[i][v]);
				color[names[i][v]] = compColor[v];
				LOG4("Final color[", names[i][v], "] =", color[names[i][v]]);
			}
		}

		return max_col + 1;
	}
}

#endif //DELTACOLORING_MERGE_COMPONENTS