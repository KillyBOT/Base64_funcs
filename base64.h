#ifndef BASE64_H
#define BASE64_H

typedef unsigned char byte;

void base64_encode(char* dest, byte* src, size_t srcLen);
void base64_decode(byte* dest, char* src, int srcLen);

#endif