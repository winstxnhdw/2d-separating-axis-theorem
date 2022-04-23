#pragma once

typedef struct {
    double x;
    double y;
} Vector2;

// Returns the dot products of two vectors
constexpr double dot(const Vector2 &A, const Vector2 &B) {
    return A.x*B.x + A.y*B.y;
}
