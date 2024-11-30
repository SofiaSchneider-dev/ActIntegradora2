#include <vector>
#include <limits>
#include <iostream>
#include <string>

class TravelingSalesmanBruteForce {
public:
    TravelingSalesmanBruteForce(const std::vector<std::vector<int>>& distances)
        : dist(distances), n(distances.size()), minCost(INT_MAX) {
        if (dist.empty() || dist.size() != dist[0].size()) {
            throw std::invalid_argument("La matriz de distancias debe ser cuadrada y no vacía.");
        }
    }

    // Encuentra la ruta de costo mínimo
    std::string findShortestPath() {
        std::vector<int> path;      // Ruta actual
        std::vector<bool> visited(n, false); // Ciudades visitadas

        path.push_back(0); // Empezamos en la ciudad 0 (A)
        visited[0] = true;

        backtrack(0, 0, 1, 0, path, visited);

        return buildPathString(optimalPath);
    }

    int getMinCost() const {
        return minCost;
    }

private:
    const std::vector<std::vector<int>>& dist; // Matriz de distancias
    const int n;                               // Número de ciudades
    int minCost;                               // Costo mínimo encontrado
    std::vector<int> optimalPath;              // Ruta óptima

    void backtrack(int node, int cost, int count, int currentCost, 
                   std::vector<int>& path, std::vector<bool>& visited) {
        if (count == n) {
            // Regresamos a la ciudad inicial
            int finalCost = currentCost + dist[node][0];
            if (finalCost < minCost) {
                minCost = finalCost;
                optimalPath = path;
            }
            return;
        }

        for (int next = 0; next < n; ++next) {
            if (!visited[next] && dist[node][next] > 0) {
                visited[next] = true;
                path.push_back(next);

                backtrack(next, cost, count + 1, currentCost + dist[node][next], path, visited);

                // Deshacer cambios (backtracking)
                visited[next] = false;
                path.pop_back();
            }
        }
    }

    std::string buildPathString(const std::vector<int>& path) const {
        std::string result;
        for (int city : path) {
            result += char('A' + city);
            result += " ";
        }
        result += 'A'; // Volver al inicio
        return result;
    }
};
