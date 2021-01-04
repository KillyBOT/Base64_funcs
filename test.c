#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int main(int argc, char** argv){

	char src[512] = "something something";
	char dest[512];

	base64_encode(dest, src, strlen(src));

	printf("%s\n", dest);

	return 0;
}