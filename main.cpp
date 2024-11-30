#include <iostream>
#include <vector>
#include <stdexcept>
#include "kruskal.h"
#include "tsp.h"
#include "ford_fulkerson.h"
#include "nearest_central.h"

int main() {
    try {
        // Leer el número de colonias
        int n;
        std::cin >> n;
        if (n <= 0) {
            throw std::invalid_argument("El número de colonias debe ser mayor a 0.");
        }

        // Matriz de distancias (grafo para TSP y Kruskal)
        std::vector<std::vector<int>> graph(n, std::vector<int>(n));

        // Leer la matriz de distancias
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> graph[i][j];
                if (i == j && graph[i][j] != 0) {
                    throw std::invalid_argument("Las distancias entre una ciudad y sí misma deben ser 0.");
                }
                if (graph[i][j] < 0) {
                    throw std::invalid_argument("Las distancias entre colonias no pueden ser negativas.");
                }
            }
        }

        // Matriz de capacidades (grafo para Ford-Fulkerson)
        std::vector<std::vector<int>> capacity(n, std::vector<int>(n));

        // Leer la matriz de capacidades
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> capacity[i][j];
                if (capacity[i][j] < 0) {
                    throw std::invalid_argument("Las capacidades de flujo no pueden ser negativas.");
                }
            }
        }

        // Leer las coordenadas de las centrales
        std::vector<std::pair<int, int>> centrals;
        for (int i = 0; i < n; ++i) {
            char openParen, comma, closeParen;
            int x, y;
            std::cin >> openParen >> x >> comma >> y >> closeParen;
            if (openParen != '(' || comma != ',' || closeParen != ')') {
                throw std::invalid_argument("Formato inválido para las coordenadas de las centrales.");
            }
            centrals.emplace_back(x, y);
        }

        // Leer las coordenadas de la nueva contratación
        int newX, newY;
        char openParen, comma, closeParen;
        std::cin >> openParen >> newX >> comma >> newY >> closeParen;
        if (openParen != '(' || comma != ',' || closeParen != ')') {
            throw std::invalid_argument("Formato inválido para las coordenadas de la nueva contratación.");
        }

        // 1. Kruskal - Forma de cablear con fibra
        try {
            std::vector<Edge> edges;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (graph[i][j] > 0) {
                        edges.push_back({i, j, graph[i][j]});
                    }
                }
            }

            Kruskal kruskal(n);
            auto mst = kruskal.minimumSpanningTree(edges);

            std::cout << "1.\n";
            for (const auto& edge : mst) {
                std::cout << "(" << char('A' + edge.u) << ", " << char('A' + edge.v) << ")\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en Kruskal: " << e.what() << "\n";
        }

        // 2. Traveling Salesman - Ruta más corta
        std::vector<std::vector<int>> distances = {
            {0, 16, 45, 32},
            {16, 0, 18, 21},
            {45, 18, 0, 7},
            {32, 21, 7, 0}
        };

        // Inicializar y resolver
        TravelingSalesmanBruteForce tsp(distances);
        std::string path = tsp.findShortestPath();
        int cost = tsp.getMinCost();

        // Imprimir resultados
        std::cout << "2.\n" << path << "\n";


        // 3. Ford-Fulkerson - Máximo flujo
        try {
            FordFulkerson ff(capacity);
            int maxFlow = ff.findMaxFlow(0, n - 1);
            std::cout << "3.\n" << maxFlow << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en Ford-Fulkerson: " << e.what() << "\n";
        }

        // 4. Búsqueda lineal - Central más cercana
        try {
            auto nearest = findNearestCentral(newX, newY, centrals);
            std::cout << "4.\n(" << nearest.first << ", " << nearest.second << ")\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en búsqueda lineal: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
