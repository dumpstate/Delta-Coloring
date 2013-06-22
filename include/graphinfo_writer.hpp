#ifndef DELTACOLORING_GRAPHINFOWRITER
#define DELTACOLORING_GRAPHINFOWRITER

#include <iostream>

namespace dColoring {
	class graphinfo_writer {
	public:
		graphinfo_writer(int colors, int components, int delta_g)
			: mColors(colors), mComponents(components), mDeltaG(delta_g) { }
		void operator()(std::ostream& out) const {
			LOG1("graphinfo_writer");
			out << "node[shape=\"circle\",style=\"filled\"]\n";
			out << "col[label=\"Colors: " << mColors << "\",shape=\"box\"];\n";
			out << "com[label=\"Components: " << mComponents << "\",shape=\"box\"];\n";
			out << "del[label=\"Delta: " << mDeltaG << "\", shape=\"box\"];\n";
		}
	private:
		int mColors;
		int mComponents;
		int mDeltaG;
	};
}

#endif //DELTACOLORING_GRAPHINFOWRITER
