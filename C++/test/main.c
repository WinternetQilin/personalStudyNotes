#include<stdio.h>
int a[4][4];
int sum = 0,sum1=0;
int mat1()
{
int j = 0;
int i1 = 3, j1 = 3;
int i2=0,j2=0;
for (int i = 0; i <= i1; i++)
{
	a[i][j] = i++;
	if (a[i][j] != 0)
	{
		i++;
		i1--;
	}
	for (j = 0; (i == i1) && (j <= j1); j++)
	{
		a[i][j] = i+j;
		if (a[i][j] != 0)
		{
			j++;
			j1--;
		}
		for (i2 = i1; (i2 >= 0)&&(j==j1); i2--)
		{
			a[i2][j] = i + j+sum;
			sum++;
			if (a[i2][j] != 0)
			{
				i2++;
				i1--;
			}
			for (j2 = j1; (j2 >= 0) && (i == i2); j2--)
			{
				a[i2][j2] = i + j + sum + sum1;
				if (a[i2][j2] != 0)
				{
					j2++;
					j1--;
				}
			}
		}

	}
}
return 0;
}
int main()
{
	mat1();
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <=3; j++)
		{
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}