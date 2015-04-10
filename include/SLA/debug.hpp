#ifndef DEBUG_MACRO_INCLUDE
#define DEBUG_MACRO_INCLUDE

#ifdef _DEBUG
#define DEBUG(x) do { std::cerr << __PRETTY_FUNCTION__ << ": " <<  x << "\n"; } while (0)
#else
#  define DEBUG(x) do {} while (0)
#endif

#define ERROR(x) std::cerr << __PRETTY_FUNCTION__ << " ERROR: " <<  x << std::endl; exit(1);
#endif //DEBUG_MARCO_INCLUDE
