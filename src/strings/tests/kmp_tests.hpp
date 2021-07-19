#include "../../catch.hpp"
#include "../../template.hpp"

#include "../kmp.hpp"

TEST_CASE("LPS calculation") {
    string pat="";
    REQUIRE(kmp::lps(pat).size()==0);

    auto naive = [&](string& pat) -> vector<int> {
        vector<int> res(sz(pat));
        for(int j=1;j<sz(pat);++j) {
            for(int k=1;k<=j;++k) {
                bool ok=true;
                int a=0, b=j-k+1;
                while(a<k) {
                    ok&=pat[a]==pat[b];
                    a++;b++;
                }
                
                if(ok) res[j]=k;
            }
        }

        return res;
    };

    pat="abaasdcsd";
    REQUIRE(kmp::lps(pat)==naive(pat));

    pat="abc";
    REQUIRE(kmp::lps(pat)==naive(pat));
    
    pat="abcabc";
    REQUIRE(kmp::lps(pat)==naive(pat));

    pat="aaaaaa";
    REQUIRE(kmp::lps(pat)==naive(pat));

    pat="abacabaabcccabaababababac";
    REQUIRE(kmp::lps(pat)==naive(pat));
}