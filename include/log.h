#ifndef DELTACOLORING_LOG
#define DELTACOLORING_LOG

#include <cstdio>

#ifdef DEBUG
	#define LOG1(a) \
						std::cerr << __func__ << "(" << __LINE__ << \
							") -> " << a << std::endl
	#define LOG2(a, b) \
						std::cerr << __func__ << "(" << __LINE__ << \
							") -> " << a << " " << b << std::endl
  #define LOG3(a, b, c) \
						std::cerr << __func__ << "(" << __LINE__ << \
							") -> " << a << " " << b << " " << c << std::endl
	#define LOG4(a, b, c, d) \
						std::cerr << __func__ << "(" << __LINE__ << \
							") -> " << a << " " << b << " " << c << " " << d << std::endl
	#define LOG5(a, b, c, d, e) \
						std::cerr << __func__ << "(" << __LINE__ << \
							") -> " << a << " " << b << " " << c << " " << \
							d << " " << e << std::endl
	#define LOG6(a, b, c, d, e, f) \
						std::cerr << __func__ << "(" << __LINE__ << \
							") -> " << a << " " << b << " " << c << " " << \
							d << " " << e << " " << f << std::endl
#else
	#define LOG1(...)
	#define LOG2(...)
	#define LOG3(...)
	#define LOG4(...)
	#define LOG5(...)
	#define LOG6(...)
#endif

#endif //DELTACOLORING_LOG