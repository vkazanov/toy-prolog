#ifndef UTIL_H
#define UTIL_H

void fail(const char* error);

void quit();

void trim(char* str);

void remove_comments(char* buf);

void strip_whitespace(char* buf);

#endif //UTIL_H
