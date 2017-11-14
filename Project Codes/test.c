#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a[50][32];
	for ( int i=0; i<3; i++ )
	{
		fgets(a[i], 32 , stdin);
	}
	for ( int i=0; i<3; i++ )
	{
		printf("%s\n", a[i]);
	}
	return 0;
}