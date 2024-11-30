#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <algorithm>
#include <iostream>

// Representa una arista con nodos de inicio, fin y peso
struct Edge {
    int u, v, weight;

    // Sobrecarga del operador '<' para ordenar las aristas por peso
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Kruskal {
public:
    // Constructor que inicializa los conjuntos disjuntos
    Kruskal(int nodes) : parent(nodes), rank(nodes, 0) {
        for (int i = 0; i < nodes; ++i) {
            parent[i] = i; // Cada nodo comienza como su propio padre
        }
    }

    // Encuentra el representante del conjunto al que pertenece 'u' con compresión de caminos
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]); // Compresión de caminos
        }
        return parent[u];
    }

    // Une dos conjuntos disjuntos y retorna true si se unieron exitosamente
    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                ++rank[rootU];
            }
            return true;
        }
        return false;
    }

    // Genera el Árbol de Expansión Mínima (MST) utilizando el algoritmo de Kruskal
    std::vector<Edge> minimumSpanningTree(std::vector<Edge> edges) {
        // Ordena las aristas por peso
        std::sort(edges.begin(), edges.end());

        std::vector<Edge> mst; // Almacena las aristas del MST

        // Itera sobre las aristas y las agrega al MST si no forman ciclos
        for (const Edge& edge : edges) {
            if (unionSets(edge.u, edge.v)) {
                mst.push_back(edge); // Arista válida para el MST
            }
        }

        return mst; // Retorna el MST
    }

private:
    std::vector<int> parent; // Almacena el padre de cada nodo
    std::vector<int> rank;   // Almacena el rango de cada conjunto
};

#endif // KRUSKAL_H
