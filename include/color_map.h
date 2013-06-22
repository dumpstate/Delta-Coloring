#ifndef DELTACOLORING_COLOR_MAP
#define DELTACOLORING_COLOR_MAP

namespace dColoring {	
	const char* color_map[] = {
		"#3366FF", "#6633FF", "#CC33FF", "#FF33CC",
		"#33CCFF", "#FF3366", "#3D2D02", "#A23D21",
		"#B88A00", "#F5B800", "#FF6633", "#9DBCFB",
		"#33FF66", "#CCFF33", "#9DEBFB", "#9DFBAD"
	};

	static const int color_map_size =
		sizeof(color_map) / sizeof(const char*);
}

#endif //DELTACOLORING_COLOR_MAP
