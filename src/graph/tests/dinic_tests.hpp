#include "../../catch.hpp"
#include "../../template.hpp"

#include "../dinic.hpp"

TEST_CASE("dinic basic flow") {
    Dinic mf(5);
    mf.add_edge(1,2,1);
    mf.add_edge(2,3,2);
    mf.add_edge(3,4,1);
    mf.add_edge(1,4,3);
    REQUIRE(mf.flow(1,4)==4);
}