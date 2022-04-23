# 2d-separating-axis-theorem

This repository contains a simple C++ implementation of a 2D separating axis algorithm. The algorithm does not compute the [Minimum Translation Vector (MTV)](https://dyn4j.org/2010/01/sat/#sat-mtv) as it is not within my use case. For more information, read [here](https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169). For predictable performance, the comparing polygons must have an equal number of vertices.

```yaml
:param bounds_a:            (std::vector<x, y>) vertices of polygon A
:param bounds_b:            (std::vector<x, y>) vertices of polygon B

:return isIntersecting:     (bool) true if the two polygons are intersecting
```

## Test

```bash
g++ main.cpp
./a.out
```

## Example

The following snippet is an example used in actual production.

```c++
const double yaw = path.points[i].yaw;
const double x = path.points[i].x - ego_centre_to_front_axle*cos(yaw);
const double y = path.points[i].y - ego_centre_to_front_axle*sin(yaw);
const std::vector<Vector2> vehicle_bounds = Obstacles::calculate_bounds(x, y, yaw, ego_centre_to_front, ego_centre_to_rear, ego_centre_to_side);

for (size_t j = 0; j < static_obstacles_set.size(); j++) {
    const std::vector<Vector2> static_obstacle = {
        static_obstacles_set[j].points[0],
        static_obstacles_set[j].points[1],
        static_obstacles_set[j].points[2],
        static_obstacles_set[j].points[3]
    };

    const bool isIntersecting = separating_axis_intersect(vehicle_bounds, static_obstacle);

    if (intersects) {
        path.is_blocked = true;
        path.is_static_obstacle = true;
    }
}
```
