#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>
using namespace std;

struct  Vertex
{
    int id_v;
    vector<Edge> edges;
    double mark;
    int id_prev;

    Vertex(int id_v)
    {
        this->id_v = id_v;
    }
};

struct Edge
{
    Edge* next;
    int id_to;
    double weight;
    Edge(int id_to, double weight) : id_to(id_to), weight(weight) {}
};

class Graph
{
private:
    
    enum Color
    {
        white = 0,
        gray = 1,
        black = 2
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
    void add_edge(int id_from, int id_to, int weight);
    bool remove_edge(int id_ftom, int id_to);
    bool has_edge(int id_from, int id_to) const;

    void print() const;

    int order() const; 
    int degree() const;
    queue<Vertex> update_queue(queue<Vertex> Q);

    void relax(Vertex& u, Vertex& v);


    vector<Edge> shortest_path(int id_from, int id_to);
    
    vector<Vertex>  walk(const Vertex& start_vertex)const;
};

