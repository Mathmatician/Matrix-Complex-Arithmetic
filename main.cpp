#include <iostream>
#include <vector>
#include <thread>

#include "Matrix.h"
#include "Complex.h"


int main()
{
	
	MATRIX<COMPLEX> mtx1 = {
		{COMPLEX(1, -1), COMPLEX(2, 3)},
		{COMPLEX(5, -4), COMPLEX(-3, 8)},
	};

	MATRIX<COMPLEX> mtx2 = {
		{COMPLEX(1, -1), COMPLEX(2, 3)},
		{COMPLEX(5, -4), COMPLEX(-3, 8)},
	};

	MATRIX<COMPLEX> result = Multiply(mtx1, mtx2);
	
	Display(result);


	return 0;
}

