#include "../../catch.hpp"
#include "../../template.hpp"

#include "../zalgo.hpp"

TEST_CASE("Z calculation") {
    string s;
    vector<int> res;

    s="aabababa";
    res=zalgo::zalgo(s);
    REQUIRE(res==vector<int>({0,1,0,1,0,1,0,1}));

    s="abababa";
    res=zalgo::zalgo(s);
    REQUIRE(res==vector<int>({0,0,5,0,3,0,1}));
}