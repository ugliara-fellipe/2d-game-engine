#ifndef TRACE_H
#define TRACE_H

#include <string.h>

#define __FILE_NAME__                                                          \
  (strrchr(__FILE__, '/')                                                      \
       ? strrchr(__FILE__, '/') + 1                                            \
       : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))

#define trace(output, type, format, ...)                                       \
  fprintf(output, "%s:%d: " type format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)

#define trace_error(format, ...) trace(stderr, "error: ", format, ##__VA_ARGS__)

#define trace_crash(format, ...) trace(stderr, "crash: ", format, ##__VA_ARGS__)

#endif
