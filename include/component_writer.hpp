#ifndef DELTACOLORING_COMPONENTWRITER
#define DELTACOLORING_COMPONENTWRITER

#include <iostream>

namespace dColoring {
	template<class TComponentMap>
	class component_writer {
	public:
		component_writer(const TComponentMap& map)
			: mMap(map) { }
		template<class Edge>
		void operator()(std::ostream& out, const Edge& e) const {
			LOG2("component_writer", e);
			out << "[label=\"" << get(mMap, e) << "\"]";
		};
	private:
		TComponentMap mMap;
	};
}

#endif //DELTACOLORING_COMPONENTWRITER
