/*
	���� ������
	> < >= <= == !=
*/

#include <stdio.h>

int main()
{
	int num1 = 0;
	int num2 = 0;
	int nResult = 0;

	nResult = num1 > 3;
	printf("��� %d\n", nResult);

	nResult = ++num1 + 2 >= 3;
	printf("��� %d\n", nResult);

	nResult = ( 6 <= num1++ * 2 );
	printf("��� %d\n", nResult);

	// == ( ���� ? )
	nResult = (num1 == 3);
	printf("��� %d\n", nResult);

	num1 += num2++ + 1;

	// != ( ���� �ʳ� ? )
	nResult = (num1 != 3);
	printf("��� %d\n", nResult);


	return 0;
}