/*
	관계 연산자
	> < >= <= == !=
*/

#include <stdio.h>

int main()
{
	int num1 = 0;
	int num2 = 0;
	int nResult = 0;

	nResult = num1 > 3;
	printf("결과 %d\n", nResult);

	nResult = ++num1 + 2 >= 3;
	printf("결과 %d\n", nResult);

	nResult = ( 6 <= num1++ * 2 );
	printf("결과 %d\n", nResult);

	// == ( 같나 ? )
	nResult = (num1 == 3);
	printf("결과 %d\n", nResult);

	num1 += num2++ + 1;

	// != ( 같지 않나 ? )
	nResult = (num1 != 3);
	printf("결과 %d\n", nResult);


	return 0;
}