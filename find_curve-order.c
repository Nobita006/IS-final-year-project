#include<stdio.h>
#include"gmp.h"

int no_of_points=0;
int check_prime(mpz_t m)
{
	mpz_t modprime;
	mpz_init(modprime);
	if(mpz_probab_prime_p(m,50)<1)
	 	mpz_nextprime(m,m);
	do
	{
		mpz_mod_ui(modprime,m,4);
		if(mpz_cmp_ui(modprime,3)==0)	
			return 1;
        	else
			mpz_nextprime(m,m);
	}while(1);


}
void find_points(mpz_t a,mpz_t b,mpz_t p)
{
	int ret=0; 
	mpz_t x,xx,y,temp1,temp2,temp3;
	mpz_init(x); mpz_init(xx); mpz_init(y);mpz_init(temp1);mpz_init(temp2);mpz_init(temp3);

    	for(mpz_set_ui(x,0);mpz_cmp(x,p)!=0;mpz_add_ui(x,x,1))
	{
        	mpz_pow_ui(temp1,x,3);
		mpz_mul(temp2,x,a);
        	mpz_add(temp3,temp2,b);
        	mpz_add(xx,temp3,temp1);
        	mpz_mod(xx,xx,p);
		if(mpz_cmp_ui(xx,0)==0)
		{
			mpz_set(y,xx);
			fflush(stdout);
			no_of_points++;
		}
        	ret=mpz_legendre(xx,p);
        	if(ret==1)
        	{
                	mpz_add_ui(temp1,p,1);
			mpz_set_ui(temp2,4);
			mpz_fdiv_q(temp1,temp1,temp2);
			mpz_powm(y,xx,temp1,p);
			no_of_points++;
			mpz_sub(y,p,y);
			fflush(stdout);
			no_of_points++;

          	}
	}
	no_of_points++; // Including the point at infinity.

     /*  Clear all variables  */
	mpz_clear(temp1); mpz_clear(temp2); mpz_clear(temp3);mpz_clear(x); mpz_clear(y); mpz_clear(xx);

}

int main(int argc,char *argv[])
{
	int fl=0;
 	mpz_t m,a,b;
 	mpz_init(m); mpz_init(a); mpz_init(b);
 	mpz_set_str(a,argv[1],10);
 	mpz_set_str(b,argv[2],10);
	mpz_set_str(m,argv[3],10);
	fl=check_prime(m);
        if(fl==1)
	gmp_printf("Prime field is :%Zd\n", m);
 	find_points(a,b,m);
	printf("\nThe Order of the Curve is: %d\n", no_of_points);
 	mpz_clear(m);mpz_clear(a),mpz_clear(b);
 	return 0;
}
