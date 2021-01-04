#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

char base64_dict[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

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

		for(int n = 0; n < 4; n++){

			temp = b >> (3-n)*6;
			temp &= 0x3f;

			if(doPadding && (toRead - n) < 0) dest[q] = '=';
			else dest[q] = base64_dict[temp];
			//printf("%c\n", dest[q]);
			q++;
		}
		p += 3;
	}

	dest[q] = '\0';


}
void base64_decode(byte* dest, char* src, int srcLen);