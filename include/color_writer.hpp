#ifndef DELTACOLORING_COLORWRITER
#define DELTACOLORING_COLORWRITER

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "color_map.h"

namespace dColoring {
	template<class TColorMap>
	class color_writer {
	public:
		color_writer(const TColorMap& map, const ColoringMode& mode)
			: mMap(map), mMode(mode) {
			srand(time(NULL));
			mOffset = rand() % color_map_size;	
		}
		template<class Vertex>
		void operator()(std::ostream& out, const Vertex& v) const {
			LOG4("color_writer", v, ", offset:", mOffset);
			out << "[fillcolor=\"";
			switch(mMode) {
			case COLOR_WITH_NUMBERS:
				out << get(mMap, v);
				break;
			case COLOR_WITH_COLORS:
				out	<< color_map[(get(mMap, v) % color_map_size + mOffset) % color_map_size];
				break;
			}
			out << "\",label=\"" << v << "[" << get(mMap, v) << "]" << "\"]";
		}
	private:
		const ColoringMode mMode;
		TColorMap mMap;
		int mOffset;
	};
}

#endif //DELTACOLORING_COLORWRITER
