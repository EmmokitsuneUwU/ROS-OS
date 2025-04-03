#include "Math.hpp"

int intToChar(int ch)
{
	return 48 + ch;
}

int intCharToInt(char ch)
{
	return ch - 48;
}

int digitCount(int num)
{
	int count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return count;
}

void intToArray(int n, int *a, int *s) {
    int i = 0;
    
    if (n < 0) {
        n = -n;
    }
    
    while (n > 0) {
        a[i] = n % 10;
        n /= 10;
        i++;
    }
    
    *s = i;

    for (int j = 0; j < i / 2; j++) {
        int temp = a[j];
        a[j] = a[i - j - 1];
        a[i - j - 1] = temp;
    }
}