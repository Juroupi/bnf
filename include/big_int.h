#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <gmpxx.h>
#include <ctime>

using big_int = mpz_class;

class rand_state : public gmp_randclass {

public:

    rand_state() : gmp_randclass(gmp_randinit_mt) {
        seed(time(nullptr));
    }

    inline big_int get(const big_int& max) {
        return get_z_range(max);
    }
};

#endif