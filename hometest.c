#include "libftprintf.h"

// ORDER
// Flags [#|0| |-|+]
// Width
// .Precision
// input-size modifier [F|N|h|l|L]
// conversion-type character [d|f|o|X|E|...]

/*
	Precision overrides 0
	- overrides 0
	+ overrides [space]
	+ and [space] not with o or x/X
	+ and [space] appears before 0-padding
	# only with o and x/X
	# 0x appears before 0-padding 
*/

//	-.0#+ 

int main()
{
	char * string;
	// printf("%zu ", ft_strlen(string = ft_strjoin("foo", "bar")));
	// free (string);
	printf("%.10s\n", "teste");
	/* printf("%#0+- 10x test! #0+- 10x\n", 10);
	printf("%0+- 10d test! no #\n", 10);
	printf("%+- 10d test! no #0\n", 10);
	printf("%0- 10d test! no #+\n", 10);
	printf("%0+ 10d test! no #-\n", 10);
	printf("%0+-10d test! no #S\n\n", 10);
	
	printf("%#0+ 10x test! no -\n", 10);
	printf("%0+ 10x test! no -#\n", 10);
	printf("%#+ 10x test! no -0\n", 10);
	printf("%#0 10x test! no -+\n", 10);
	printf("%#0+10x test! no -S\n\n", 10);
	
	printf("%0+ 10d test! no -#\n", 10);
	printf("%+ 10d test! no -#0\n", 10);
	printf("%0 10d test! no -#+\n", 10);
	printf("%0+10d test! no -#S\n", 10); */
}