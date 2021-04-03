/*HEADER:
 * Houda Haidar
 * 21/02/2021
 * Ex: solve multi D sys using GSL library.
 * compile: gcc -lgsl multi.c -o multi -lm
 * run: ./multi
 */
#include<stdio.h>
#include<stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

#define MAX_ITERATIONS 1000

int my_function(const gsl_vector* x, void* p, gsl_vector* f);

int main(void)
{
	/*variables*/
	int size = 2, i = 0, status = 0;
	double epsrel = 10e-6, epabs = 0., value1 = 0, value2 = 0;
	double x_init[2] = {0.2, 1.};
	const gsl_multiroot_fsolver_type *solver_type;
	const gsl_vector* x ;
	const gsl_vector* dx ;
	gsl_multiroot_fsolver* my_solver;
	gsl_multiroot_function my_system ; /*definition  of  your  system  of  equations*/

	/*INSRUCTIONS*/


	/* MULTI D SYSTEM FUNCTION*/
	/*storing it*/
	my_system.f = &my_function ;
	my_system.n = 2 ; 
	my_system.params = NULL ;

	/*initial guess*/
	gsl_vector* initial_guess;
	initial_guess = gsl_vector_alloc(2); /*2 is dimension of sys*/
	/*set the components of the vector*/
	gsl_vector_set(initial_guess,0,x_init[0]);
	gsl_vector_set(initial_guess,1,x_init[1]);

	

	/*allocate newton method and set it to solve the func*/
	solver_type = gsl_multiroot_fsolver_dnewton;
	my_solver = gsl_multiroot_fsolver_alloc(solver_type,size);
	gsl_multiroot_fsolver_set(my_solver,&my_system,initial_guess);
	

	/*printf("%lf\n", my_solver);*/
	printf("using %s method\n", gsl_multiroot_fsolver_name(my_solver));
	printf("iter , root   :\n");		

	/*LOOP - iteration :: */
	status = GSL_CONTINUE;
	 for ( i = 1; i < MAX_ITERATIONS && status == GSL_CONTINUE ; i++)
	 {
		/*performs one step iteration of the solver :: breaks if result is not successful*/
		status = gsl_multiroot_fsolver_iterate(my_solver);
		if (status != GSL_SUCCESS)
			break;

		/*obtain best root from solver*/
		dx = x;
		x = gsl_multiroot_fsolver_root(my_solver);
		/*get vals from x*/
		value1 = gsl_vector_get(x,0);
		value2 = gsl_vector_get(x,1);
		dx =gsl_multiroot_fsolver_dx(my_solver);
		/*check estimate of sol:: within epsrel =  10e-6 (also ive put epabs = 0 bc i didnt know what to put*/
		status = gsl_multiroot_test_delta( dx, x,epabs, epsrel);
		if (status == GSL_SUCCESS)
			printf("root sucessfully converged\n");

        	
		/*display root*/
		printf("%d %lf %lf \n", i, value1, value2);

	 }

	




	/*free memory*/
	gsl_multiroot_fsolver_free(my_solver);

	return status;
}






int my_function(const gsl_vector* x, void* p, gsl_vector* f)
{
   /* Function of which we want to find a root.
   We don't use argument p here, but GSL needs the function signature to include it.
   *first argument = input vector to your function,
   *he second argumentis = pointer to additional information that might be necessary to compute your function
   *the  third  argument  = return  the  result  ofyour functionF(a vector as well).
   */
   double x1 = gsl_vector_get(x,0);
   double x2 = gsl_vector_get(x,1);

   gsl_vector_set(f, 0, pow(x1 - 1.2,2) + pow(x2 + 0.5,2) - 1. );
   gsl_vector_set(f, 1, 10.*pow(x1 - 2.2,2) + pow(x2 - 0.9,2) - 4. );

   return GSL_SUCCESS ; /*constant defined by GSL containing a code for a successful exit*/
}

