#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include "errors.h"
using namespace std;


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
    double d;
    int id_prev;
    Color color;

    Vertex(int id_v)
    {
        this->id_v = id_v;
    }
};


class Graph
{
private:

    vector<Vertex> vertexes;

    // ��������������� ������� ��� ������ � ������
    void initialize();
    vector<Vertex> search_in_width(Vertex& start_v);

    // ��������������� ������� ��� ��������� ��������
    void initialize_for_dijkstra(int from);
    void sort(queue<Vertex>& Q);
    vector<Vertex> nearest_v(int id_v);
    void deikstra(int from);
    void relax(Vertex& u, Vertex& v);
public:
    //�������� �����
    ~Graph();
    void delete_graph();

    //��������-����������-�������� ������
    bool has_vertex(int id_v) const;
    int find_vertex(int id_v) const;
    void add_vertex(int id_v);
    bool remove_vertex(int id_v);

    //��������-����������-�������� �����
    void add_edge(int id_from, int id_to, int weight);
    bool remove_edge(int id_from, int id_to);
    bool has_edge(int id_from, int id_to) const;

    // ������ �����
    void print() const;

    // ������� � ������� �����
    int order() const;
    int degree() const;

    // ����� � ������
    vector<Vertex> walk_in_width(int id_first);

    //���������� ���� ���������� ��������
    vector<Vertex> shortest_path(int id_from, int id_to);
};