#ifndef NEAREST_CENTRAL_H
#define NEAREST_CENTRAL_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <utility>

// Encuentra la central más cercana a un punto dado (x, y)
std::pair<int, int> findNearestCentral(int x, int y, const std::vector<std::pair<int, int>>& centrals) {
    if (centrals.empty()) {
        throw std::invalid_argument("La lista de centrales no puede estar vacía.");
    }

    // Inicializa la central más cercana con el primer elemento de la lista
    std::pair<int, int> nearest = centrals[0];
    double minDist = std::hypot(nearest.first - x, nearest.second - y);

    // Itera por cada central para calcular la distancia euclidiana
    for (const auto& central : centrals) {
        double dist = std::hypot(central.first - x, central.second - y);

        if (dist < minDist) {
            minDist = dist;   // Actualiza la distancia mínima
            nearest = central; // Actualiza la central más cercana
        }
    }

    return nearest; // Retorna la central más cercana como un std::pair
}

#endif // NEAREST_CENTRAL_H
