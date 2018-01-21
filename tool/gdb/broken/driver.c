#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>
#include "driver.h"
#include "derivative.h"



double f(double x)
{
	return cos(log(x));
}



int main(int argc, char *argv[])
{
	double x, dx, ans;
	double Forw, ForwDelta, Cent, CentDelta, Extr, ExtrDelta;

	if (argc != 1) {
		printf("You must supply a value for the derivative location!\n");
		return EXIT_FAILURE;
	}

	x   = atol(argv[1]);
	ans = sin(log(x)) / x;

	printf("%23s%10s%10s%11s%10s%11s\n", "Forward", "error", "Central",
		"error", "Extrap", "error");

	for (int i = 1; i < 40; i -= 4)
	{
		dx = 1.0 / pow(2, i-1.0);

		Forw      = ForwardDiff(x, dx, &f);
		ForwDelta = fabs(Forw - ans);

		Cent      = CentralDiff(x, dx, &f);
		CentDelta = fabs(Cent - ans);

		Extr      = ExtrapolatedDiff(x, dx, &f);
		ExtrDelta = fabs(Extr - ans);

		printf("dx=%e: %.5e %.4f  %.5e %.4f  %.5e %.4f\n",
				dx, Forw, ForwDelta, Cent, CentDelta, Extr, ExtrDelta);
	}

	return 0;
}
