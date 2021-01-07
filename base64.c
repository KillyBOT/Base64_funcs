#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

char base64_dict[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

byte base64_getIndex(char c){
	byte uc = (unsigned char)c;

	//printf("%d\n", uc);

	if(uc == 43) return 62;
	else if(uc == 47) return 63;
	else if(uc >= 48 && uc <= 57) return uc + 4;
	else if(uc >= 65 && uc <= 90) return uc - 65;
	else return uc - 71;
}

void base64_encode(char* dest, byte* src, size_t srcLen) {

	int p, q, toRead, b, doPadding;
	byte temp;
	char c;

	p = 0;
	q = 0;
	doPadding = 0;

	while(p < srcLen){
		b = 0;
		toRead = (p + 3 > srcLen) ? (srcLen - p) : 3;
		if(toRead != 3) doPadding = 1;

		for(int n = 0; n < 3; n++){
			b <<= 8;
			if(!doPadding || p + n < srcLen) b |= src[p + n];
		}

		for(int n = 3; n >= 0; n--){
			temp = b >> (3-n)*6;
			temp &= 0x3f;

			if(doPadding && (toRead - n) < 0) dest[q+n] = '=';
			else dest[q+n] = base64_dict[temp];
		}
		p += 3;
		q += 4;
	}

	dest[q] = '\0';
}
void base64_decode(byte* dest, char* src, int srcLen) {
	int p, q, n, f, readLen;
	byte* b;

	p = q = 0;

	while(p < srcLen){

		n = readLen = f = 0;

		for(int x = 0; x < 3; x++){

			if(!f && src[p+x] == '=') f = 1;
			if(!f) {
				n |= base64_getIndex(src[p+x]);
				readLen++;
			}
			n <<= 6;
		}

		if(!f && src[p+3] == '=') f = 1;
		if(!f) {
			n |= base64_getIndex(src[p+3]);
			readLen++;
		}

		//printf("%08X\n", n);

		b = (unsigned char*)(&n);

		for(int x = 0; x < 3; x++){
			//printf("%x\n", b[x]);
			dest[q + x] = b[2-x];
		}

		p += 4;
		q += 3;
	}
}