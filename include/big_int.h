#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <gmpxx.h>
#include <chrono>

using big_int = mpz_class;

char* big_int_to_cstr(const big_int& i);

struct rand_state : public gmp_randclass {
    rand_state();
    big_int get(const big_int& max);
};

#endif