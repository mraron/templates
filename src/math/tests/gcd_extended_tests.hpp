#include "../../catch.hpp"
#include "../../template.hpp"

#include "../gcd_extended.hpp"

TEST_CASE("gcd_extended tests") {
    vector<pair<ll,ll>> tests={{2,3},{123,23},{50,100},{13*6, 13*9},{100,1000}};
    for(auto i:tests) {
        ll cx, cy;
        ll g=extended_gcd(i.xx, i.yy, &cx, &cy);
        REQUIRE(cx*i.xx+cy*i.yy==g);
        REQUIRE(__gcd(i.xx,i.yy)==g);
    }
}