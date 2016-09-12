#define CATCH_CONFIG_MAIN
#include "000-external/catch.hpp"

#include "Graph.hh"
#include "GraphBuilder.hh"
#include "GraphTextIO.hh"

TEST_CASE( "Directed graph", "[DirectedGraph]" ) {
  DirectedGraph<> g = GraphBuilder<DirectedGraph<> >::clrs_22_4();

  SECTION("isDirected()") {
    REQUIRE(g.isDirected() == true);
  }

  SECTION("hasVertex()") {
    REQUIRE(g.hasVertex("u") == true);
    REQUIRE(g.hasVertex("v") == true);
    REQUIRE(g.hasVertex("w") == true);
    REQUIRE(g.hasVertex("x") == true);
    REQUIRE(g.hasVertex("y") == true);
    REQUIRE(g.hasVertex("z") == true);
    REQUIRE(g.hasVertex("a") == false);
    REQUIRE(g.hasVertex("b") == false);
  }

  SECTION("numVertices()") {
    REQUIRE(g.numVertices() == 6);
  }

  SECTION("getState() && getMutableState()") {
    REQUIRE(g.getState() == "");
    g.getMutableState() = "state 123";
    REQUIRE(g.getState() == "state 123");
  }

  SECTION("getVertexState() && getMutableVertexState()") {
    g.getMutableVertexState("u") = "u state 123";
    REQUIRE(g.getVertexState("u") == "u state 123");
    REQUIRE(g.getVertexState("v") == "");
  }

  SECTION("getEdgeState() && getMutableEdgeState()") {
    g.getMutableEdgeState("u", "v") = "u -> v state 123";
    REQUIRE(g.getEdgeState("u", "v") == "u -> v state 123");
    REQUIRE(g.getEdgeState("v", "y") == "");
  }

  SECTION("numEdges()") {
    REQUIRE(g.numEdges() == 8);
  }

  SECTION("hasEdge()") {
    REQUIRE(g.hasEdge("u", "v") == true);
    REQUIRE(g.hasEdge("v", "y") == true);
    REQUIRE(g.hasEdge("u", "x") == true);
    REQUIRE(g.hasEdge("x", "v") == true);
    REQUIRE(g.hasEdge("y", "x") == true);
    REQUIRE(g.hasEdge("w", "y") == true);
    REQUIRE(g.hasEdge("w", "z") == true);
    REQUIRE(g.hasEdge("z", "z") == true);

    REQUIRE(g.hasEdge("v", "u") == false);
    REQUIRE(g.hasEdge("v", "w") == false);
    REQUIRE(g.hasEdge("x", "y") == false);
  }

  SECTION("all vertex iterator") {
    std::set<std::string> expectedVertices = {
      "u", "v", "w", "x", "y", "z"
    };
    std::set<std::string> actualVertices(g.vertexBegin(), g.vertexEnd());
    REQUIRE(expectedVertices == actualVertices);
  }

  SECTION("neighbors vertex iterator of u") {
    std::set<std::string> expectedNeighbors = { "v", "x" };
    std::set<std::string> actualNeighbors(g.adjBegin("u"), g.adjEnd("u"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of v") {
    std::set<std::string> expectedNeighbors = { "y" };
    std::set<std::string> actualNeighbors(g.adjBegin("v"), g.adjEnd("v"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of w") {
    std::set<std::string> expectedNeighbors = { "y", "z" };
    std::set<std::string> actualNeighbors(g.adjBegin("w"), g.adjEnd("w"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of x") {
    std::set<std::string> expectedNeighbors = { "v" };
    std::set<std::string> actualNeighbors(g.adjBegin("x"), g.adjEnd("x"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of y") {
    std::set<std::string> expectedNeighbors = { "x" };
    std::set<std::string> actualNeighbors(g.adjBegin("y"), g.adjEnd("y"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of z") {
    std::set<std::string> expectedNeighbors = { "z" };
    std::set<std::string> actualNeighbors(g.adjBegin("z"), g.adjEnd("z"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }
}

TEST_CASE( "Undirected graph", "[UndirectedGraph]" ) {
  UndirectedGraph<> g = GraphBuilder<UndirectedGraph<> >::clrs_22_3();

  SECTION("isDirected()") {
    REQUIRE(g.isDirected() == false);
  }

  SECTION("hasVertex()") {
    REQUIRE(g.hasVertex("r") == true);
    REQUIRE(g.hasVertex("s") == true);
    REQUIRE(g.hasVertex("t") == true);
    REQUIRE(g.hasVertex("u") == true);
    REQUIRE(g.hasVertex("v") == true);
    REQUIRE(g.hasVertex("w") == true);
    REQUIRE(g.hasVertex("x") == true);
    REQUIRE(g.hasVertex("y") == true);

    REQUIRE(g.hasVertex("a") == false);
    REQUIRE(g.hasVertex("b") == false);
  }

  SECTION("numVertices()") {
    REQUIRE(g.numVertices() == 8);
  }

  SECTION("getVertexState() && getMutableVertexState()") {
    g.getMutableVertexState("u") = "u state 123";
    REQUIRE(g.getVertexState("u") == "u state 123");
    REQUIRE(g.getVertexState("v") == "");
  }

  SECTION("getState() && getMutableState()") {
    REQUIRE(g.getState() == "");
    g.getMutableState() = "state 123";
    REQUIRE(g.getState() == "state 123");
  }

  SECTION("getEdgeState() && getMutableEdgeState()") {
    g.getMutableEdgeState("u", "t") = "u - t state 123";
    REQUIRE(g.getEdgeState("u", "t") == "u - t state 123");
    REQUIRE(g.getEdgeState("x", "y") == "");
  }

  SECTION("numEdges()") {
    REQUIRE(g.numEdges() == 10);
  }

  SECTION("hasEdge()") {
    REQUIRE(g.hasEdge("r", "s") == true);
    REQUIRE(g.hasEdge("s", "r") == true);

    REQUIRE(g.hasEdge("r", "v") == true);
    REQUIRE(g.hasEdge("v", "r") == true);

    REQUIRE(g.hasEdge("s", "w") == true);
    REQUIRE(g.hasEdge("w", "s") == true);

    REQUIRE(g.hasEdge("w", "t") == true);
    REQUIRE(g.hasEdge("t", "w") == true);

    REQUIRE(g.hasEdge("t", "x") == true);
    REQUIRE(g.hasEdge("x", "t") == true);

    REQUIRE(g.hasEdge("x", "w") == true);
    REQUIRE(g.hasEdge("w", "x") == true);

    REQUIRE(g.hasEdge("t", "u") == true);
    REQUIRE(g.hasEdge("u", "t") == true);

    REQUIRE(g.hasEdge("t", "x") == true);
    REQUIRE(g.hasEdge("x", "t") == true);

    REQUIRE(g.hasEdge("x", "u") == true);
    REQUIRE(g.hasEdge("u", "x") == true);

    REQUIRE(g.hasEdge("y", "u") == true);
    REQUIRE(g.hasEdge("u", "y") == true);

    REQUIRE(g.hasEdge("y", "x") == true);
    REQUIRE(g.hasEdge("x", "y") == true);

    REQUIRE(g.hasEdge("v", "u") == false);
    REQUIRE(g.hasEdge("u", "v") == false);
    REQUIRE(g.hasEdge("r", "w") == false);
    REQUIRE(g.hasEdge("w", "r") == false);
  }

  SECTION("all vertex iterator") {
    std::set<std::string> expectedVertices = {
      "r", "s", "t", "u", "v", "w", "x", "y"
    };
    std::set<std::string> actualVertices(g.vertexBegin(), g.vertexEnd());
    REQUIRE(expectedVertices == actualVertices);
  }

  SECTION("neighbors vertex iterator of r") {
    std::set<std::string> expectedNeighbors = { "s", "v" };
    std::set<std::string> actualNeighbors(g.adjBegin("r"), g.adjEnd("r"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of s") {
    std::set<std::string> expectedNeighbors = { "r", "w" };
    std::set<std::string> actualNeighbors(g.adjBegin("s"), g.adjEnd("s"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of t") {
    std::set<std::string> expectedNeighbors = { "w", "x", "u" };
    std::set<std::string> actualNeighbors(g.adjBegin("t"), g.adjEnd("t"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of u") {
    std::set<std::string> expectedNeighbors = { "t", "x", "y" };
    std::set<std::string> actualNeighbors(g.adjBegin("u"), g.adjEnd("u"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of v") {
    std::set<std::string> expectedNeighbors = { "r" };
    std::set<std::string> actualNeighbors(g.adjBegin("v"), g.adjEnd("v"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of w") {
    std::set<std::string> expectedNeighbors = { "s", "t", "x" };
    std::set<std::string> actualNeighbors(g.adjBegin("w"), g.adjEnd("w"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of x") {
    std::set<std::string> expectedNeighbors = { "w", "t", "u", "y" };
    std::set<std::string> actualNeighbors(g.adjBegin("x"), g.adjEnd("x"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }

  SECTION("neighbors vertex iterator of y") {
    std::set<std::string> expectedNeighbors = { "x", "u" };
    std::set<std::string> actualNeighbors(g.adjBegin("y"), g.adjEnd("y"));
    REQUIRE(expectedNeighbors == actualNeighbors);
  }
}
