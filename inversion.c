#include "inversion.h"

void BignumberCopy(BIGNUM* d, const BIGNUM* r)
{
	for (int i = 0; i < r->top; i++)
	{
		d->d[i] = r->d[i];
	}
	d->top = r->top;
}

void BignumberDivision(BIGNUM* q, BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{

}

void ExtendedEuclidean(BIGNUM* ai, const BIGNUM* P, const BIGNUM* a)
{
	BIGNUM u = { {0, }, 0, 0 };
	BIGNUM v = { {0, }, 0, 0 };
	BIGNUM x = { {0, }, 0, 0 };
	BIGNUM x1 = { {0, }, 0, 0 };
	BIGNUM x2 = { {0, }, 0, 0 };
	BIGNUM q = { {0, }, 0, 0 };
	BIGNUM r = { {0, }, 0, 0 };

	BIGNUM one = { {0, }, 0, 0 };
	one.d[0] = 1;
	one.top = 1;

	x1.d[0] = 1;
	x1.top = 1;

	x2.d[0] = 0;
	x1.top = 1;

	while (compare(&one, &u) != 0)
	{
		BignumberDivision(&q, &r, &v, &u);
		kara(&x1, &q, &x1);
		BignumberSub(&x, &x2, &x1);

		BignumberCopy(&v, &u);
		BignumberCopy(&u, &r);
		BignumberCopy(&x2, &x1);
		BignumberCopy(&x1, &x);
	}
	fastReduction(&ai, &x1, P);
}