#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include "include/utils.hpp"

// Linear transform to find the orthogonal vector of the edge
Vector2 calculate_normalised_projection_axis(const Vector2 &current_point, const Vector2 &next_point) {
    const double axis_x = -(next_point.y - current_point.y);
    const double axis_y =   next_point.x - current_point.x;
    const double magnitude = hypot(axis_x, axis_y);

    Vector2 axis_normalised;
    axis_normalised.x = axis_x / magnitude;
    axis_normalised.y = axis_y / magnitude;

    return axis_normalised;
}

// Project the vertices of each polygon onto a axis
void compute_projections(const std::vector<Vector2> &bounds_a, const std::vector<Vector2> &bounds_b, const Vector2 &axis_normalised, std::vector<double> &projections_a, std::vector<double> &projections_b) {
    projections_a.clear();
    projections_b.clear();

    for (size_t i = 0; i < bounds_a.size(); i++) {
        const double projection_a = dot(axis_normalised, bounds_a[i]);
        const double projection_b = dot(axis_normalised, bounds_b[i]);
        projections_a.push_back(projection_a);
        projections_b.push_back(projection_b);
    }
}

// Check if the projections of two polygons overlap
bool is_overlapping(const std::vector<double> &projections_a, const std::vector<double> &projections_b) {
    const double max_projection_a = *std::max_element(projections_a.begin(), projections_a.end());
    const double min_projection_a = *std::min_element(projections_a.begin(), projections_a.end());
    const double max_projection_b = *std::max_element(projections_b.begin(), projections_b.end());
    const double min_projection_b = *std::min_element(projections_b.begin(), projections_b.end());

    // True if projection overlaps but does not necessarily mean the polygons are intersecting yet
    return !(max_projection_a < min_projection_b || max_projection_b < min_projection_a);
}

// Check if two convex polygons intersect
bool separating_axis_intersect(const std::vector<Vector2> &bounds_a, const std::vector<Vector2> &bounds_b) {
    std::vector<double> projections_a;
    std::vector<double> projections_b;
    projections_a.reserve(bounds_a.size());
    projections_b.reserve(bounds_b.size());

    for (size_t i = 0; i < bounds_a.size(); i++) {
        const Vector2 current_point = bounds_a[i];
        const Vector2 next_point = bounds_a[(i + 1) % bounds_a.size()];
        const Vector2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections(bounds_a, bounds_b, axis_normalised, projections_a, projections_b);
        
        if (!is_overlapping(projections_a, projections_b)) return false;
    }

    for (size_t i = 0; i < bounds_b.size(); i++) {
        const Vector2 current_point = bounds_b[i];
        const Vector2 next_point = bounds_b[(i + 1) % bounds_b.size()];
        const Vector2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections(bounds_a, bounds_b, axis_normalised, projections_a, projections_b);

        if (!is_overlapping(projections_a, projections_b)) return false;
    }

    // Intersects if all projections overlap
    return true;
}
