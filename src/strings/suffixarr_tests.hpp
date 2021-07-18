#include "../catch.hpp"
#include "../template.hpp"

#include "suffixarr.hpp"

TEST_CASE("suffix_array construction") {
    suffixarr::suffix_array sa("asd");
    REQUIRE(sa.sarr==vector<int>({3,0,2,1}));

    suffixarr::suffix_array sa2("abcbcba");
    REQUIRE(sa2.sarr==vector<int>({7,6,0,5,3,1,4,2}));

    suffixarr::suffix_array sa3("mississippi");
    REQUIRE(sa3.sarr==vector<int>({11,10,7,4,1,0,9,8,6,3,5,2}));
}