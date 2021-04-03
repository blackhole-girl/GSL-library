/*HEADER:
 * Houda Haidar
 * 21/02/2021
 * Ex: compute dot product btw two gsl vectors
 * comp : gcc -lgsl gsl_vector.c -o gsl_vector -lm
 * run: ./gsl_vector
 */
#include <gsl/gsl_vector.h>
#include<stdio.h>

double product(gsl_vector* my_vector1 , gsl_vector* my_vector2);
int main()
{
	/*variable*/
	int i = 0, size = 4, x = 1, y= 2;
	double dot = 0;
	gsl_vector* my_vector1 ;
	gsl_vector* my_vector2 ;

	/*instructions*/
	my_vector1 = gsl_vector_alloc(size) ;
	my_vector2 = gsl_vector_alloc(size) ;

	for ( i = 0; i < size ; i ++)
	{
		gsl_vector_set(my_vector1, i, x);
		gsl_vector_set(my_vector2, i, y);
	}
	
	printf("dot product is :\n");
	dot = product(my_vector1,my_vector2);
	printf("%lf\n", dot);

	return 0;

}


double product(gsl_vector* my_vector1 , gsl_vector* my_vector2)
{
	int i = 0, size = 4;
	double dot = 0, value1 = 0, value2 = 0;


	for ( i = 0; i<size; i++)
	{
		value1 = gsl_vector_get(my_vector1, i);
		value2 = gsl_vector_get(my_vector2, i);

		dot += value1 * value2;
	}

	return dot;

}
