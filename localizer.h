#pragma once // bascially makes compiler only compile this once

#include <vector>
#include "main.h"

struct FieldSize { // This john allows for simple storage of field parameter (sizes)
    float minX;
    float maxX;
    float minY;
    float maxY;
};

struct DistanceThingies { // This allows for ths storage of each distance sensor and its config
    pros::Distance* sensor;
    float offsetX;
    float offsetY;
    float headingDeg;
};

struct DistanceThingiesContinued { // This is an overall config of all distance sensnors a few tweak
    float minConfidence;
    float MaxDistance;
};

struct Pose { // This is a pose, (x, y, theta)
    float x;
    float y;
    float headingDeg;
};

struct offset { // This is done so I can do math without dummy distance sensor data. Also stroage of rotational offset data too
    float x;
    float y;
};

struct hard_angle_clamp { // I use clamps in two functions, so I made a function and gave it its own data type which returns the two usable variables. 
    float min_deviation;
    float closest_angle;
};



class Localization {
    private:
    std::vector<DistanceThingies> DistanceSensors;
    FieldSize field_size;
    Pose CurrentPose;
    Pose StartingPose;
    Pose RelativePose;
    pros::Imu* imu;
    DistanceThingiesContinued DistanceConfig;

    float normalize_angle(float angle); //prototype i think
    float angle_distance(float angle1, float angle2);
    float to_radians(float value);
    float coordinate_maker(float value, bool isX);
    hard_angle_clamp hard_angle_clamper(float TrueHeading);
    offset offset_calculator(float offsetX, float offsetY, float headingdeg);
    void init_sensors();
    void compute_raw();

    public:
        void set_starting_pose();
        Pose compute_relative();
        Localization(std::vector<DistanceThingies> DistanceSensors, struct DistanceThingiesContinued DistanceConfig, struct FieldSize FieldSize, pros::Imu* imu);
};

