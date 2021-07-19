#include "../../catch.hpp"
#include "../../template.hpp"

#include "../fastpow.hpp"

TEST_CASE("fastpow basic") {
    REQUIRE(fastpow(2,10)==1024);
    REQUIRE(fastpow<ll>(2,1e9+7-2,1e9+7)==500000004);
    REQUIRE(fastpow(3,3)==27);
}