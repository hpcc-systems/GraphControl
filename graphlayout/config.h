#ifdef WIN32
#include <../../windows/config.h>
#else
#include <../../config.h>
#endif
#undef ENABLE_LTDL
#undef HAVE_EXPAT
#undef HAVE_EXPAT_H
#undef HAVE_LIBZ
#undef HAVE_GTS
#undef HAVE_VALUES_H
#define YY_NO_UNISTD_H