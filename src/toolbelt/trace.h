/*
MIT License

Copyright (c) 2022 Fellipe Augusto Ugliara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <string.h>

#define __FILE_NAME__                                                          \
  (strrchr(__FILE__, '/')                                                      \
       ? strrchr(__FILE__, '/') + 1                                            \
       : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))

#define trace(output, type, format, ...)                                       \
  fprintf(output, "%s:%d: " type format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)

#define trace_error(format, ...) trace(stderr, "error: ", format, ##__VA_ARGS__)

#define trace_crash(format, ...) trace(stderr, "crash: ", format, ##__VA_ARGS__)

#define trace_debug(format, ...) trace(stdout, "debug: ", format, ##__VA_ARGS__)

#endif
