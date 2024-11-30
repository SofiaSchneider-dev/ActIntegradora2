#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <vector>
#include <climits>
#include <queue>
#include <iostream>
#include <stdexcept>

class FordFulkerson {
public:
    // Constructor: inicializa la capacidad, el flujo y el tamaño de la red
    FordFulkerson(const std::vector<std::vector<int>>& capacity) 
        : n(capacity.size()), capacity(capacity), flow(n, std::vector<int>(n, 0)) {
        if (capacity.empty() || capacity.size() != capacity[0].size()) {
            throw std::invalid_argument("La matriz de capacidades debe ser cuadrada y no vacía.");
        }
    }

    // Encuentra el flujo máximo desde el nodo fuente al nodo sumidero
    int findMaxFlow(int source, int sink) {
        if (source < 0 || sink < 0 || source >= n || sink >= n) {
            throw std::out_of_range("Source o sink están fuera del rango válido.");
        }

        int maxFlow = 0;

        // Mientras haya un camino aumentante en el grafo residual
        while (bfs(source, sink)) {
            int pathFlow = INT_MAX;

            // Encuentra el flujo máximo del camino aumentante encontrado
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
            }

            // Actualiza las capacidades residuales y el flujo
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += pathFlow;
                flow[v][u] -= pathFlow;
            }

            maxFlow += pathFlow; // Incrementa el flujo máximo total
        }

        return maxFlow; // Retorna el flujo máximo calculado
    }

private:
    int n;                                        // Número de nodos en la red
    const std::vector<std::vector<int>> capacity; // Matriz de capacidades
    std::vector<std::vector<int>> flow;           // Matriz de flujo
    std::vector<int> parent;                      // Vector para reconstruir el camino aumentante

    // Implementación de BFS para encontrar un camino aumentante
    bool bfs(int source, int sink) {
        parent.assign(n, -1); // Resetea los padres
        std::queue<int> q;
        q.push(source);
        parent[source] = source; // Marca el nodo fuente como visitado

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Revisa los vecinos del nodo actual
            for (int v = 0; v < n; ++v) {
                // Si no está visitado y hay capacidad residual positiva
                if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                    parent[v] = u; // Guarda el nodo previo
                    if (v == sink) return true; // Si alcanza el sink, devuelve true
                    q.push(v);
                }
            }
        }

        return false; // No se encontró un camino aumentante
    }
};

#endif // FORD_FULKERSON_H
