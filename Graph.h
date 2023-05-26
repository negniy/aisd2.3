#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>
using namespace std;


class Graph
{
private:
    struct Edge
    {
        Edge* next;
        int id_to;
        double weight;
        Edge(int id_to, double weight) : id_to(id_to), weight(weight) {}
    };

    enum Color
    {
        white = 0,
        gray = 1,
        black = 2
    };

    struct  Vertex
    {
        int id_v;
        vector<Edge> edges;

        Vertex(int id_v)
        {
            this->id_v = id_v;
            
        }
    };

    vector<Vertex> vertexes;
public:

    ~Graph();
    void delete_graph();
    
    //проверка-добавление-удаление вершин
    bool has_vertex(int id_v) const;
    int find_vertex(int id_v) const;
    void add_vertex(int id_v);
    bool remove_vertex(int id_v);

    //проверка-добавление-удаление ребер
    void add_edge(int from, int to, int weight);
    bool remove_edge(int ftom, int to);
    bool has_edge(int from, int to) const; 

    void print() const;

    int order() const; 
    int degree() const; 


    
    vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    
    vector<Vertex>  walk(const Vertex& start_vertex)const;
};

