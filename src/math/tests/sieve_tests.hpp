#include "../../catch.hpp"
#include "../../template.hpp"

#include "../sieve.hpp"

TEST_CASE("sieve tests") {
    sieve();
    
    REQUIRE(ps[0]==2);
    REQUIRE(ps[1]==3);
    REQUIRE(ps[2]==5);
    REQUIRE(ps[3]==7);
    REQUIRE(ps[4]==11);
    REQUIRE(ps[5]==13);
    REQUIRE(ps[6]==17);
    REQUIRE(ps[7]==19);
    REQUIRE(ps[8]==23);
    REQUIRE(ps[9]==29);
    REQUIRE(ps[10]==31);

    REQUIRE(MAXN==1000001);
    REQUIRE(ps.size()==78498);
}