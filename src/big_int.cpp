#include "big_int.h"

rand_state::rand_state() : gmp_randclass(gmp_randinit_mt) {
    seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

big_int rand_state::get(const big_int& max) {
    return (max <= 0) ? big_int(0) : get_z_range(max);
}