#include <iostream>
#include "separating_axis.hpp"

std::vector<Vector2> calculate_bounds(const double x, const double y, const double yaw, const double centre_to_front, const double centre_to_rear, const double centre_to_side) {
    const double sin_yaw = sin(yaw);
    const double cos_yaw = cos(yaw);

    Vector2 front_right_point;
    front_right_point.x = x + centre_to_side * sin_yaw + centre_to_front * cos_yaw;
    front_right_point.y = y - centre_to_side * cos_yaw + centre_to_front * sin_yaw;

    Vector2 front_left_point;
    front_left_point.x = x - centre_to_side * sin_yaw + centre_to_front * cos_yaw;
    front_left_point.y = y + centre_to_side * cos_yaw + centre_to_front * sin_yaw;

    Vector2 rear_left_point;
    rear_left_point.x = x - centre_to_side * sin_yaw - centre_to_rear * cos_yaw;
    rear_left_point.y = y + centre_to_side * cos_yaw - centre_to_rear * sin_yaw;

    Vector2 rear_right_point;
    rear_right_point.x = x + centre_to_side * sin_yaw - centre_to_rear * cos_yaw;
    rear_right_point.y = y - centre_to_side * cos_yaw - centre_to_rear * sin_yaw;

    return {front_right_point, front_left_point, rear_left_point, rear_right_point};
}

int main() {
    const double x1 = 0.0;
    const double y1 = 0.0;
    const double yaw1 = 0.0;
    const double centre_to_front1 = 3.0;
    const double centre_to_rear1 = 3.0;
    const double centre_to_side1 = 1.0;

    const double x2 = 5.0;
    const double y2 = 3.0;
    const double yaw2 = 0.0;
    const double centre_to_front2 = 3.0;
    const double centre_to_rear2 = 3.0;
    const double centre_to_side2 = 1.0;

    const std::vector<Vector2> A = calculate_bounds(x1, y1, yaw1, centre_to_front1, centre_to_rear1, centre_to_side1);
    const std::vector<Vector2> B = calculate_bounds(x2, y2, yaw2, centre_to_front2, centre_to_rear2, centre_to_side2);
    
    std::cout << (separating_axis_intersect(A, B) == true ? "The polygons intersect." : "The polygons do not intersect.") << std::endl;
}
