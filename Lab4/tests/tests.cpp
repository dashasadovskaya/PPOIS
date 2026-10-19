#include <UnitTest++/UnitTest++.h>
#include <vector>
#include <string>
#include "Sorting.h"
#include "Graph.h"

TEST(LibrarySortEmpty) {
    int a[] = {};
    librarySort(a, 0);   
}

TEST(LibrarySortOne) {
    int a[] = {5};
    librarySort(a, 1);
    CHECK_EQUAL(5, a[0]);
}

TEST(LibrarySortInt) {
    int a[] = {5, 3, 8, 1, 9, 2, 7};
    librarySort(a, 7);
    CHECK_EQUAL(1, a[0]);
    CHECK_EQUAL(2, a[1]);
    CHECK_EQUAL(3, a[2]);
    CHECK_EQUAL(5, a[3]);
    CHECK_EQUAL(7, a[4]);
    CHECK_EQUAL(8, a[5]);
    CHECK_EQUAL(9, a[6]);
}

TEST(LibrarySortAlreadySorted) {
    int a[] = {1, 2, 3, 4, 5};
    librarySort(a, 5);
    CHECK_EQUAL(1, a[0]);
    CHECK_EQUAL(5, a[4]);
}

TEST(LibrarySortReverse) {
    int a[] = {5, 4, 3, 2, 1};
    librarySort(a, 5);
    CHECK_EQUAL(1, a[0]);
    CHECK_EQUAL(5, a[4]);
}

TEST(LibrarySortDuplicates) {
    int a[] = {3, 1, 3, 1, 3, 1};
    librarySort(a, 6);
    CHECK_EQUAL(1, a[0]);
    CHECK_EQUAL(1, a[1]);
    CHECK_EQUAL(1, a[2]);
    CHECK_EQUAL(3, a[3]);
}

TEST(LibrarySortVector) {
    std::vector<int> v = {5, 3, 8, 1};
    librarySort(v);
    CHECK_EQUAL(1, v[0]);
    CHECK_EQUAL(3, v[1]);
    CHECK_EQUAL(5, v[2]);
    CHECK_EQUAL(8, v[3]);
}

TEST(LibrarySortNullThrows) {
    int* p = nullptr;
    CHECK_THROW(librarySort(p, 5), SortException);
}

TEST(SpreadSortEmpty) {
    int a[] = {};
    spreadSort(a, 0);
}

TEST(SpreadSortOne) {
    int a[] = {42};
    spreadSort(a, 1);
    CHECK_EQUAL(42, a[0]);
}

TEST(SpreadSortInt) {
    int a[] = {5, 3, 8, 1, 9, 2, 7};
    spreadSort(a, 7);
    CHECK_EQUAL(1, a[0]);
    CHECK_EQUAL(9, a[6]);
}

TEST(SpreadSortAllEqual) {
    int a[] = {3, 3, 3, 3};
    spreadSort(a, 4);
    CHECK_EQUAL(3, a[0]);
}

TEST(SpreadSortVector) {
    std::vector<int> v = {10, 5, 20, 15, 1};
    spreadSort(v);
    CHECK_EQUAL(1, v[0]);
    CHECK_EQUAL(20, v[4]);
}

TEST(SpreadSortNullThrows) {
    int* p = nullptr;
    CHECK_THROW(spreadSort(p, 5), SortException);
}

TEST(SpreadSortZeroBucketsThrows) {
    int a[] = {1, 2, 3};
    CHECK_THROW(spreadSort(a, 3, 0), SortException);
}

TEST(GraphEmpty) {
    Graph<int> g;
    CHECK(g.empty());
    CHECK_EQUAL(0u, g.vertexCount());
    CHECK_EQUAL(0u, g.edgeCount());
}

TEST(GraphAddVertex) {
    Graph<int> g;
    auto v = g.addVertex(42);
    CHECK(g.hasVertex(v));
    CHECK_EQUAL(1u, g.vertexCount());
    CHECK_EQUAL(42, g.vertexData(v));
}

TEST(GraphHasVertexFalse) {
    Graph<int> g;
    CHECK(!g.hasVertex(999));
}

TEST(GraphRemoveVertex) {
    Graph<int> g;
    auto v = g.addVertex(42);
    g.removeVertex(v);
    CHECK(!g.hasVertex(v));
    CHECK_EQUAL(0u, g.vertexCount());
}

TEST(GraphRemoveVertexNotFoundThrows) {
    Graph<int> g;
    CHECK_THROW(g.removeVertex(999), VertexNotFoundException);
}

TEST(GraphClear) {
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.clear();
    CHECK(g.empty());
}

TEST(GraphAddEdge) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    g.addEdge(v1, v2);
    CHECK(g.hasEdge(v1, v2));
    CHECK(g.hasEdge(v2, v1));   // неориентированный
    CHECK_EQUAL(1u, g.edgeCount());
}

TEST(GraphHasEdgeFalse) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    CHECK(!g.hasEdge(v1, v2));
}

TEST(GraphAddEdgeVertexNotFoundThrows) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    CHECK_THROW(g.addEdge(v1, 999), VertexNotFoundException);
}

TEST(GraphAddDuplicateEdgeThrows) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    g.addEdge(v1, v2);
    CHECK_THROW(g.addEdge(v1, v2), DuplicateException);
}

TEST(GraphRemoveEdge) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    g.addEdge(v1, v2);
    g.removeEdge(v1, v2);
    CHECK(!g.hasEdge(v1, v2));
    CHECK_EQUAL(0u, g.edgeCount());
}

TEST(GraphRemoveEdgeNotFoundThrows) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    CHECK_THROW(g.removeEdge(v1, v2), EdgeNotFoundException);
}

TEST(GraphDegree) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto v3 = g.addVertex(3);
    g.addEdge(v1, v2);
    g.addEdge(v1, v3);
    CHECK_EQUAL(2u, g.degree(v1));
    CHECK_EQUAL(1u, g.degree(v2));
    CHECK_EQUAL(1u, g.degree(v3));
}

TEST(GraphDegreeNotFoundThrows) {
    Graph<int> g;
    CHECK_THROW(g.degree(999), VertexNotFoundException);
}

TEST(GraphVertexIterator) {
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    int count = 0;
    for (auto it = g.begin(); it != g.end(); ++it) ++count;
    CHECK_EQUAL(3, count);
}

TEST(GraphVertexIteratorValues) {
    Graph<int> g;
    g.addVertex(10);
    g.addVertex(20);
    std::vector<int> vals;
    for (auto it = g.begin(); it != g.end(); ++it) vals.push_back(*it);
    CHECK_EQUAL(2u, vals.size());
    CHECK_EQUAL(10, vals[0]);
    CHECK_EQUAL(20, vals[1]);
}

TEST(GraphEdgeIterator) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto v3 = g.addVertex(3);
    g.addEdge(v1, v2);
    g.addEdge(v2, v3);
    int count = 0;
    for (auto it = g.edgeBegin(); it != g.edgeEnd(); ++it) ++count;
    CHECK_EQUAL(2, count);
}

TEST(GraphRemoveVertexCascadesEdges) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    g.addEdge(v1, v2);
    g.removeVertex(v1);
    CHECK_EQUAL(0u, g.edgeCount());
    CHECK(!g.hasVertex(v1));
}

TEST(GraphEqualityEmpty) {
    Graph<int> g1, g2;
    CHECK(g1 == g2);
}

int main() {
    return UnitTest::RunAllTests();
}