#include "graph.h"
#include <iostream>
#include <cmath>


int main() {
    // TODO(student): write many organized and effective tests
    {
        std::cout << "make an empty digraph" << std::endl;
        Graph G;

        std::cout << "add vertices" << std::endl;
        for (size_t n = 1; n <= 7; n++) {
            G.add_vertex(n);
        }

        std::cout << "add directed edges" << std::endl;
        G.add_edge(1,2,5);  // 1 ->{5} 2; (edge from 1 to 2 with weight 5)
        G.add_edge(1,3,3);
        G.add_edge(2,3,2);
        G.add_edge(2,5,3);
        G.add_edge(2,7,1);
        G.add_edge(3,4,7);
        G.add_edge(3,5,7);
        G.add_edge(4,1,2);
        G.add_edge(4,6,6);
        G.add_edge(5,4,2);
        G.add_edge(5,6,1);
        G.add_edge(7,5,1);

        std::cout << "G has " << G.vertex_count() << " vertices" << std::endl;
        std::cout << "G has " << G.edge_count() << " edges" << std::endl;

        std::cout << "compute shortest path from 2" <<std::endl;
        G.dijkstra(2);

        std::cout << "print shortest paths" <<std::endl;
        for (size_t n = 1; n <= 7; n++) {
            std::cout << "shortest path from 2 to " << n << std::endl;
            std::cout << "  ";
            G.print_shortest_path(n);
        }
    }

    {
        // Anon's mystery exception
        std::cout << "re-add edge after vertex replacement" << std::endl;
        Graph G;
        G.add_vertex(1);
        G.add_vertex(2);
        G.add_edge(1,2);
        // remove this for a segfault
        G.add_vertex(3);
        G.remove_vertex(1);
        G.add_vertex(1);
        G.add_edge(1,2);
    }

    {
        std::cout << "copy assignment for IO test" << std::endl;
        Graph IO;
        IO.add_vertex(1);
        IO.add_vertex(2);
        IO.add_edge(1,2,2);
        IO.add_vertex(4);
        IO.add_edge(1,4,1);
        IO.add_edge(2,4,3);
        IO.add_vertex(5);
        IO.add_edge(2,5,10);
        IO.add_vertex(3);
        IO.add_edge(3,1,4);
        IO.add_vertex(6);
        IO.add_edge(3,6,5);
        IO.add_edge(4,3,2);
        IO.add_edge(4,5,2);
        IO.add_edge(4,6,8);
        IO.add_vertex(7);
        IO.add_edge(4,7,4);
        IO.add_edge(5,7,6);
        IO.add_edge(7,6,1);

        Graph G;
        G = IO;

        G.dijkstra(1);
        for (size_t n = 1; n <= 7; n++) {
            G.print_shortest_path(n);
            std::cout << G.distance(n) << std::endl;
            // EXPECT_NE(G.distance(n), INFINITY);
        }
    }

    {
        std::cout << "a small source/sink" << std::endl;
        Graph G;
        G.add_vertex(0);
        G.dijkstra(1);
        std::cout << "doest G.distance(0) == INFINITY? " << std::boolalpha << (G.distance(0) == INFINITY) << std::endl;
        // EXPECT_EQ(G.distance(0), INFINITY);

        G.add_vertex(1);
        G.add_edge(0, 1, 0.1);
        G.dijkstra(1);
        std::cout << "doest G.distance(0) == INFINITY? " << std::boolalpha << (G.distance(0) == INFINITY) << std::endl;
        // EXPECT_EQ(G.distance(0), INFINITY);
        std::cout << "doest G.distance(1) == 0 " << std::boolalpha << (G.distance(1) == 0) << std::endl;
        // EXPECT_EQ(G.distance(1), 0);

        G.add_vertex(2);
        G.add_edge(0, 2, 0.2);
        G.add_edge(1, 2, 1.2);
        // std::cout << "The cost of (1,2): " << std::boolalpha << (G.cost(1,2) == 1.2) << std::endl;
        G.dijkstra(1);
        std::cout << "doest G.distance(0) == INFINITY? " << std::boolalpha << (G.distance(0) == INFINITY) << std::endl;
        // EXPECT_EQ(G.distance(0), INFINITY);
        std::cout << "doest G.distance(1) == 0 " << std::boolalpha << (G.distance(1) == 0) << std::endl;
        // EXPECT_EQ(G.distance(1), 0);
        std::cout << "doest G.distance(2) == 1.2 " << std::boolalpha << (G.distance(2) == 1.2) << std::endl;
        // EXPECT_EQ(G.distance(2), 1.2);
    }

    {
        std::cout << "just in time order of vertices and edges" << std::endl;
        Graph G;
        G.add_vertex(1);
        G.add_vertex(2);
        G.add_edge(1, 2, 2);
        G.add_vertex(4);
        G.add_edge(1, 4, 1);
        G.add_edge(2, 4, 3);
        G.add_vertex(5);
        G.add_edge(2, 5, 10);
        G.add_vertex(3);
        G.add_edge(3, 1, 4);
        G.add_vertex(6);
        G.add_edge(3, 6, 5);
        G.add_edge(4, 3, 2);
        G.add_edge(4, 5, 2);
        G.add_edge(4, 6, 8);
        G.add_vertex(7);
        G.add_edge(4, 7, 4);
        G.add_edge(5, 7, 6);
        G.add_edge(7, 6, 1);
        std::cout << "doest G.cost(1,2) == 2 " << std::boolalpha << (G.cost(1,2) == 2) << std::endl;
        // EXPECT_EQ(G.cost(1, 2), 2);
        std::cout << "doest G.cost(1,4) == 1 " << std::boolalpha << (G.cost(1,4) == 1) << std::endl;
        // EXPECT_EQ(G.cost(1, 4), 1);
        std::cout << "doest G.cost(2,4) == 3 " << std::boolalpha << (G.cost(2,4) == 3) << std::endl;
        // EXPECT_EQ(G.cost(2, 4), 3);
        std::cout << "doest G.cost(2,5) == 10 " << std::boolalpha << (G.cost(2,5) == 10) << std::endl;
        // EXPECT_EQ(G.cost(2, 5), 10);
        std::cout << "doest G.cost(3,1) == 4 " << std::boolalpha << (G.cost(3,1) == 4) << std::endl;
        // EXPECT_EQ(G.cost(3, 1), 4);
        std::cout << "doest G.cost(3,6) == 5 " << std::boolalpha << (G.cost(3,6) == 5) << std::endl;
        // EXPECT_EQ(G.cost(3, 6), 5);
        std::cout << "doest G.cost(4,3) == 2 " << std::boolalpha << (G.cost(4,3) == 2) << std::endl;
        // EXPECT_EQ(G.cost(4, 3), 2);
        std::cout << "doest G.cost(4,5) == 2 " << std::boolalpha << (G.cost(4,5) == 2) << std::endl;
        // EXPECT_EQ(G.cost(4, 5), 2);
        std::cout << "doest G.cost(4,6) == 8 " << std::boolalpha << (G.cost(4,6) == 8) << std::endl;
        // EXPECT_EQ(G.cost(4, 6), 8);
        std::cout << "doest G.cost(4,7) == 4 " << std::boolalpha << (G.cost(4,7) == 4) << std::endl;
        // EXPECT_EQ(G.cost(4, 7), 4);
        std::cout << "doest G.cost(5,7) == 6 " << std::boolalpha << (G.cost(5,7) == 6) << std::endl;
        // EXPECT_EQ(G.cost(5, 7), 6);
        std::cout << "doest G.cost(7,6) == 1 " << std::boolalpha << (G.cost(7,6) == 1) << std::endl;
        // EXPECT_EQ(G.cost(7, 6), 1);
    }

    {
        std::cout << "non-integer edge weight" << std::endl;
        Graph G;
        G.add_vertex(1);
        G.add_vertex(2);
        G.add_edge(1,2,1.618);
        std::cout << "Is EXPECT_LE(std::abs(G.cost(1,2) - 1.618), 1e-6) true? " << std::boolalpha << (std::abs(G.cost(1,2) - 1.618) <= 1e-6) << std::endl;
        // EXPECT_LE(std::abs(G.cost(1,2) - 1.618), 1e-6);  
    }

    {
        std::cout << "deep copy constructor" << std::endl;
        Graph G;
        const size_t N = 10;
        for (size_t i = 0; i < N; i++) {
        G.add_vertex(i);
        }
        for (size_t src = 0; src < N; src++) {
        for (size_t dest = 0; dest < N; dest++) {
            if (src == dest) {
            continue;
            }
            G.add_edge(src,dest);
        }
        }

        {
        Graph copy = G;
        for (size_t i = 0; i < N; i++) {
            std::cout << "EXPECT_TRUE(copy.contains_vertex(i)) true? " << std::boolalpha << (copy.contains_vertex(i)) << std::endl;
            // EXPECT_TRUE(copy.contains_vertex(i));
        }
        for (size_t src = 0; src < N; src++) {
            for (size_t dest = 0; dest < N; dest++) {
            if (src == dest) {
                std::cout << "EXPECT_FALSE(copy.contains_edge(src, dest)) false? " << std::boolalpha << (copy.contains_edge(src, dest)) << std::endl;
                // EXPECT_FALSE(copy.contains_edge(src, dest));
            } else {
                std::cout << "EXPECT_TRUE(copy.contains_edge(src, dest)) true? " << std::boolalpha << (copy.contains_edge(src, dest)) << std::endl;
                // EXPECT_TRUE(copy.contains_edge(src, dest));
            }
            }
        }
        copy.remove_vertex(0);
        copy.remove_vertex(N/2);
        copy.remove_vertex(N-1);
        std::cout << "EXPECT_FALSE(copy.contains_vertex(0)) false? " << std::boolalpha << (copy.contains_vertex(0)) << std::endl;
        // EXPECT_FALSE(copy.contains_vertex(0));
        std::cout << "EXPECT_FALSE(copy.contains_vertex(N/2)) false? " << std::boolalpha << (copy.contains_vertex(N/2)) << std::endl;
        // EXPECT_FALSE(copy.contains_vertex(N/2));
        std::cout << "EXPECT_FALSE(copy.contains_vertex(N-1)) false? " << std::boolalpha << (copy.contains_vertex(N-1)) << std::endl;
        // EXPECT_FALSE(copy.contains_vertex(N-1));
        std::cout << "EXPECT_TRUE(G.contains_vertex(0)) true? " << std::boolalpha << (G.contains_vertex(0)) << std::endl;
        // EXPECT_TRUE(G.contains_vertex(0));
        std::cout << "EXPECT_TRUE(G.contains_vertex(N/2)) true? " << std::boolalpha << (G.contains_vertex(N/2)) << std::endl;
        // EXPECT_TRUE(G.contains_vertex(N/2));
        std::cout << "EXPECT_TRUE(G.contains_vertex(N-1)) true? " << std::boolalpha << (G.contains_vertex(N-1)) << std::endl;
        // EXPECT_TRUE(G.contains_vertex(N-1));

        for (size_t i = 0; i < N; i++) {
            std::cout << "EXPECT_FALSE(copy.contains_edge(0,i)) false? " << std::boolalpha << (copy.contains_edge(0,i)) << std::endl;
            // // EXPECT_FALSE(copy.contains_edge(0,i));
            std::cout << "EXPECT_FALSE(copy.contains_edge(i,0)) false? " << std::boolalpha << (copy.contains_edge(i,0)) << " " << i << std::endl;
            // // EXPECT_FALSE(copy.contains_edge(i,0));
            std::cout << "EXPECT_FALSE(copy.contains_edge(N/2,i)) false? " << std::boolalpha << (copy.contains_edge(N/2,i)) << std::endl;
            // EXPECT_FALSE(copy.contains_edge(N/2,i));
            std::cout << "EXPECT_FALSE(copy.contains_edge(i,N/2)) false? " << std::boolalpha << (copy.contains_edge(i,N/2)) << std::endl;
            // EXPECT_FALSE(copy.contains_edge(i,N/2));
            std::cout << "EXPECT_FALSE(copy.contains_edge(N-1,i)) false? " << std::boolalpha << (copy.contains_edge(N-1,i)) << std::endl;
            // EXPECT_FALSE(copy.contains_edge(N-1,i));
            std::cout << "copy.contains_edge(i,N-1) false? " << std::boolalpha << (copy.contains_edge(i,N-1)) << std::endl;
            // EXPECT_FALSE(copy.contains_edge(i,N-1));
            
            if (i != 0) {
            std::cout << "EXPECT_TRUE(G.contains_edge(0,i)) true? " << std::boolalpha << (G.contains_edge(0,i)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(0,i));
            std::cout << "EXPECT_TRUE(G.contains_edge(i,0)) true? " << std::boolalpha << (G.contains_edge(i,0)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(i,0));
            }
            if (i != N/2) {
            std::cout << "EXPECT_TRUE(G.contains_edge(N/2,i)) true? " << std::boolalpha << (G.contains_edge(N/2,i)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(N/2,i));
            std::cout << "EXPECT_TRUE(G.contains_edge(i,N/2)) true? " << std::boolalpha << (G.contains_edge(i,N/2)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(i,N/2));
            }
            if (i != N-1) {
            std::cout << "EXPECT_TRUE(G.contains_edge(N-1,i)) true? " << std::boolalpha << (G.contains_edge(N-1,i)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(N-1,i));
            std::cout << "EXPECT_TRUE(G.contains_edge(i,N-1)) true? " << std::boolalpha << (G.contains_edge(i,N-1)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(i,N-1));
            }
        }
        std::cout << "EXPECT_TRUE(G.contains_vertex(0)) true? " << std::boolalpha << (G.contains_vertex(0)) << std::endl;
        // EXPECT_TRUE(G.contains_vertex(0));
        std::cout << "EXPECT_TRUE(G.contains_vertex(N/2)) true? " << std::boolalpha << (G.contains_vertex(N/2)) << std::endl;
        // EXPECT_TRUE(G.contains_vertex(N/2));
        std::cout << "EXPECT_TRUE(G.contains_vertex(N-1)) true? " << std::boolalpha << (G.contains_vertex(N-1)) << std::endl;
        // EXPECT_TRUE(G.contains_vertex(N-1));

        for (size_t i = 0; i < N; i++) {
            if (i != 0) {
            std::cout << "EXPECT_TRUE(G.contains_edge(0,i)) true? " << std::boolalpha << (G.contains_edge(0,i)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(0,i));
            std::cout << "EXPECT_TRUE(G.contains_edge(i,0)) true? " << std::boolalpha << (G.contains_edge(i,0)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(i,0));
            }
            if (i != N/2) {
            std::cout << "EXPECT_TRUE(G.contains_edge(N/2,i)) true? " << std::boolalpha << (G.contains_edge(N/2,i)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(N/2,i));
            std::cout << "EXPECT_TRUE(G.contains_edge(i,N/2)) true? " << std::boolalpha << (G.contains_edge(i,N/2)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(i,N/2));
            }
            if (i != N-1) {
            std::cout << "EXPECT_TRUE(G.contains_edge(N-1,i)) true? " << std::boolalpha << (G.contains_edge(N-1,i)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(N-1,i));
            std::cout << "EXPECT_TRUE(G.contains_edge(i,N-1)) true? " << std::boolalpha << (G.contains_edge(i,N-1)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(i,N-1));
            }
        }
        }
    }

    {
        std::cout << "remove vertex: bigger graph" << std::endl;
        Graph G;
        const size_t N = 10;
        for (size_t i = 0; i < N; i++) {
        G.add_vertex(i);
        }
        for (size_t src = 0; src < N; src++) {
        for (size_t dest = 0; dest < N; dest++) {
            if (src == dest) {
            continue;
            }
            G.add_edge(src,dest);
        }
        }

        G.remove_vertex(0);
        G.remove_vertex(N/2);
        G.remove_vertex(N-1);
        std::cout << "EXPECT_FALSE(G.contains_vertex(0)) false? " << std::boolalpha << (G.contains_vertex(0)) << std::endl;
        // EXPECT_FALSE(G.contains_vertex(0));
        std::cout << "EXPECT_FALSE(G.contains_vertex(N/2)) false? " << std::boolalpha << (G.contains_vertex(N/2)) << std::endl;
        // EXPECT_FALSE(G.contains_vertex(N/2));
        std::cout << "EXPECT_FALSE(G.contains_vertex(N-1)) false? " << std::boolalpha << (G.contains_vertex(N-1)) << std::endl;
        // EXPECT_FALSE(G.contains_vertex(N-1));

        for (size_t src = 0; src < N; src++) {
        for (size_t dest = 0; dest < N; dest++) {
            if (src == dest) {
            continue;
            }
            if (src == 0 || src == N/2 || src == N-1 || dest == 0|| dest == N/2 || dest == N-1) {
            std::cout << "EXPECT_FALSE(G.contains_edge(src,dest)) false? " << std::boolalpha << (G.contains_edge(src,dest)) << std::endl;
            // EXPECT_FALSE(G.contains_edge(src,dest));
            } else {
            std::cout << "EXPECT_TRUE(G.contains_edge(src,dest)) true? " << std::boolalpha << (G.contains_edge(src,dest)) << std::endl;
            // EXPECT_TRUE(G.contains_edge(src,dest));
            }
        }
        }
    }

    {
        std::cout << "example of local scoped stringstream I/O test" << std::endl;
        Graph G;
        {
        std::stringstream ss;
        G.print_shortest_path(1, ss);
        std::cout << std::boolalpha << (ss.str() == "<no path>\n") << std::endl;
        // EXPECT_EQ(ss.str(), "<no path>\n");
        }
    }



    return 0;
}
