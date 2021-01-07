#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int main(int argc, char** argv){

	//char testString[512] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char src[512] = "something something";
	char dest[512];

	char decoded[512];

	//for(int x = 0; x < 64; x++) printf("%d\n", base64_getIndex(testString[x]));

	base64_encode(dest, src, strlen(src));

	printf("%s\n", dest);

	base64_decode(decoded, dest, strlen(dest));

	printf("%s\n", decoded);

	return 0;
}