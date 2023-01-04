#include "../../catch.hpp"
#include "../../template.hpp"

#include "../treap.hpp"

TEST_CASE("treap") {
    auto to_vec=[&](treap<int> t) {
        vector<int> ans;
        function<void(treap<int>::node*)> rec=[&](treap<int>::node* root) {
            if(root==nullptr) return ;
            rec(root->L);
            ans.pb(root->key);
            rec(root->R);
        };

        rec(t.root);
        return ans;
    };
    
    treap<int> t;
    t.insert(40);
    t.insert(10);
    t.insert(20);
    t.insert(30);
    
    REQUIRE(to_vec(t)==vector<int>({10, 20, 30, 40}));
    REQUIRE(t.erase(10));
    REQUIRE(to_vec(t)==vector<int>({20, 30, 40}));
    REQUIRE(t.erase(20));
    REQUIRE(to_vec(t)==vector<int>({30, 40}));
    REQUIRE_FALSE(t.erase(20));
    REQUIRE(t.erase(40));
    REQUIRE(to_vec(t)==vector<int>({30}));

}