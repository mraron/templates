#include "../catch.hpp"
#include "../template.hpp"

#include "suffixarr.hpp"

TEST_CASE("suffix_array construction") {
    suffix_array sa("asd");
    REQUIRE(sa.sarr==vector<int>({3,0,2,1}));

    suffix_array sa2("abcbcba");
    REQUIRE(sa2.sarr==vector<int>({7,6,0,5,3,1,4,2}));

    suffix_array sa3("mississippi");
    REQUIRE(sa3.sarr==vector<int>({11,10,7,4,1,0,9,8,6,3,5,2}));
}

TEST_CASE("suffix_array lcp") {
    auto calc_lcp = [&](string s, vector<int> sarr) -> vector<int> {
        vector<int> lcp(sz(sarr));
        lcp[0]=0;
        for(int i=1;i+1<sz(sarr);++i) {
            while(max(sarr[i], sarr[i+1])+lcp[i]<sz(s) && s[sarr[i]+lcp[i]]==s[sarr[i+1]+lcp[i]]) lcp[i]++;
        }

        return lcp;
    };

    vector<string> tests={"asd", "abcbcba", "mississippi", "ababaa"};
    for(string s:tests) {
        suffix_array sa(s);
        sa.calc_lcp();
        
        REQUIRE(sa.lcp==calc_lcp(s, sa.sarr));
    }
}