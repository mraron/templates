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

    REQUIRE(MAXN==1000010);
    REQUIRE(ps.size()==78499);
}

TEST_CASE("pfactors tests") {
    sieve();

    REQUIRE(pfactors(10).size()==2);
    REQUIRE(pfactors(2).size()==1);
    
    auto factors=pfactors(12);
    sort(factors.begin(), factors.end());
    REQUIRE(factors==vector<pair<int,int>>({{2,2},{3,1}}));
}

TEST_CASE("divs tests") {
    sieve();
    vector<pair<int, vector<int>>> tests = {
      {1,{1}},  
      {2,{1,2}},
      {3,{1,3}},
      {4,{1,2,4}},
      {5,{1,5}},
      {6,{1,2,3,6}},
      {7,{1,7}},
      {8,{1,2,4,8}},
      {9,{1,3,9}},
      {10,{1,2,5,10}},
      {144,{1,2,3,4,6,8,9,12,16,18,24,36,48,72,144}},
    };

    for(auto test:tests) {
        auto got=divs(test.xx);
        sort(all(got));

        REQUIRE(got==test.yy);
    }
}