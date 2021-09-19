#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <vector>
#include <cmath>

using std::vector;
using std::stack;
using std::unordered_map;
using std::priority_queue;

struct Vertex {
    size_t id;
    unordered_map<size_t, double> adj;
    bool known;
    double dist;
    Vertex* path;

    Vertex(): id(), adj(), known(false), dist(INFINITY), path(nullptr) {};
    Vertex(size_t x): id(x), adj(), known(false), dist(INFINITY), path(nullptr) {};
    ~Vertex() {};
    Vertex(const Vertex& v): id(v.id), adj(v.adj), known(v.known), dist(v.dist), path(v.path) {};
    Vertex& operator=(const Vertex& v) {
        if(this == &v) {
            return *this;
        }
        id = v.id;
        adj = v.adj;
        known = v.known;
        dist = v.dist;
        path = v.path;
        return *this;
    }
    // Vertex(size_t x,float ): id(x), adj(), known(false), dist(), path() {};

};

class Comparator {
    public:
    bool operator() (const Vertex* v1, const Vertex* v2) {
        return v1->dist > v2->dist;
    }
};

class Graph {
    // TODO(student): implement Graph
    public:
    unordered_map<size_t, Vertex> vertices;
    size_t dijkstraedNum;

    Graph(): vertices(), dijkstraedNum() {};
    Graph(const Graph& v): vertices(v.vertices), dijkstraedNum(v.dijkstraedNum) {};
    Graph& operator=(const Graph& v) {
        if(this == &v) {
            return *this;
        }
        vertices.clear();
        vertices = v.vertices;
        dijkstraedNum = v.dijkstraedNum;
        return *this;
    };
    ~Graph() {
        vertices.clear();
    };

    size_t vertex_count() const {
        return vertices.size();
    };
    size_t edge_count() const {
        size_t numEdges = 0;
        for(auto i : vertices) {
            numEdges += i.second.adj.size();
        }
        return numEdges;
    };

    bool contains_vertex(size_t id) const {
        if(vertices.find(id) == vertices.end()) {
            return false;
        }
        return true;
        // for(auto& i : vertices) {
        //     if(i.first == id) {
        //         return true;
        //     }
        // }
        // return false;
    };
    bool contains_edge(size_t src, size_t dest) const {
        if(contains_vertex(src) == false || contains_vertex(dest) == false || vertices.at(src).adj.find(dest) == vertices.at(src).adj.end()) {
            return false;
        }
        return true;
        // for(auto i : vertices) {
        //     for(auto j : i.second.adj) {
        //         if(i.first == src && j.first == dest) {
        //             return true;
        //         }
        //     }
        // }
        // return false;
    };
    double cost(size_t src, size_t dest) const{
        if(!contains_edge(src,dest)) {
            return INFINITY;
        }
        return vertices.at(src).adj.at(dest);
        // for(auto i : vertices) {
        //     for(auto j : i.second.adj) {
        //         if(i.first == src && j.first == dest) {
        //             return i.second.adj.at(dest);
        //         }
        //     }
        // }
        // return INFINITY;
    };

    bool add_vertex(size_t id) {
        if(contains_vertex(id)) {
            return false;
        }
        // for(auto i : vertices) {
        //     if(i.first == id) {
        //         return false;
        //     }
        // }
        std::pair<size_t,Vertex> myPair(id,Vertex(id));
        vertices.insert(myPair);
        // vertices[id] = Vertex(id);
        return true;
    };
    bool add_edge(size_t src, size_t dest, double weight = 1) {
        if(contains_edge(src,dest)) {
            return false;
        }
        vertices[src].adj[dest] = weight;
        return true;
    };
    bool remove_vertex(size_t id) {
        if(!contains_vertex(id)) {
            return false;
        }
        for(auto& i : vertices) {
            i.second.adj.erase(id);
        }
        vertices.erase(id);
        return true;
    };
    bool remove_edge(size_t src, size_t dest) {
        if(!contains_edge(src,dest)) {
            return false;
        }
        vertices[src].adj.erase(dest);
        return true;
    };

    void dijkstra(size_t source_id) {
        for(auto i : vertices) {
            i.second.dist = INFINITY;
            i.second.known = false;
        }


        if(!contains_vertex(source_id)) {
            return;
        }

        dijkstraedNum = source_id;
        priority_queue<Vertex*, vector<Vertex*>, Comparator> pq;
        vertices[source_id].dist = 0;

        Vertex* v = &vertices[source_id];
        pq.push(v);

        while(!pq.empty()) {
            v = pq.top();
            v->known = true;

            pq.pop();
            

            for(auto i : v->adj) {
                for(auto& w : vertices) {
                    if(i.first == w.first && w.second.known == false) {
                        double cvw = cost(v->id, w.first);
                        if(v->dist + cvw < w.second.dist) {
                            w.second.dist = v->dist + cvw;
                            w.second.path = v;
                            pq.push(&w.second);
                        }
                    }
                }
            }
        }
    };
    double distance(size_t id) {
        return vertices[id].dist;
    };

    void print_shortest_path(size_t dest_id, std::ostream& out = std::cout) {
        // check for nullptr and vertex not existing
        if((!contains_vertex(dest_id) || vertices[dest_id].path == nullptr) && dest_id != dijkstraedNum) {
            out << "<no path>\n";
            return;
        }
        stack<size_t> stk;
        Vertex* next = vertices[dest_id].path;
        while(next != nullptr) {
            stk.push(next->id);
            next = vertices[next->id].path;
        }
        size_t initSize = stk.size();
        for(size_t i = 0; i < initSize; i++) {
            out  << stk.top() << " --> ";
            stk.pop();
        }
        out << dest_id;
        out << " distance: " << distance(dest_id) << "\n";
    };

};

#endif  // GRAPH_H
