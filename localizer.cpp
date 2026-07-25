#include "localizer.h"

using namespace std;

float MM_IN = 25.4;

vector<int> hard_angles = {0, 90, 180, 270}; // hard angles are basically perpedicular lines and allow the bot to grab the shortest disrtance to a wall and then the coordinates. 

float Localization::normalize_angle(float angle) { // just realized some people will put negatives or ill get a negative, idk i havent tested. 
        if (angle < 0) {
            while (angle < 0) {
                angle += 360;
            }
            return angle;
        }
        else if (angle >= 360) {
            while (angle >= 360) {
                angle -= 360;
            }
            return angle;
        }
        else {
            return angle;
        }
}

float Localization::angle_distance(float angle1, float angle2) { // sometimes when something is more than 180 degrees away, we just counting the wrong way
    float difference = abs(angle1 - angle2);
    if (difference > 180) {
        difference = 360 - difference;
    }
    return abs(difference);
}


float Localization::to_radians(float value) { // c++ math in radians, so i need to convert. 
    return value * (M_PI / 180);
}

float Localization::coordinate_maker(float value, bool isX) { // negatives are left and down, positives are right and up
    value /= MM_IN;
    if (value < 0) {
        if (isX) {
            return field_size.minX + abs(value);
        }
        else {
            return field_size.minY + abs(value);
        }
    }
    else {
        if (isX) {
            return field_size.maxX - abs(value);
        }
        else {
            return field_size.maxY - abs(value);
        }
    }
}

hard_angle_clamp Localization::hard_angle_clamper(float TrueHeading) {
    hard_angle_clamp returnThis;
    returnThis.closest_angle = -1;
    returnThis.min_deviation = 360;
    for (int j = 0; j < hard_angles.size(); j++) {
        if (angle_distance(TrueHeading, hard_angles[j]) < returnThis.min_deviation) {
            returnThis.min_deviation = angle_distance(TrueHeading, hard_angles[j]);
            returnThis.closest_angle = hard_angles[j];
        }
    }
    return returnThis;
}

offset Localization::offset_calculator(float offsetX, float offsetY, float headingdeg) { //looked online, these are standard forumales, apparently i never learned them, but wikipedia got me https://en.wikipedia.org/wiki/Rotation_matrix
    // I need to flip because i dont go counterclockwise, but clockwise. 
    float rads = to_radians(normalize_angle(headingdeg));
    offset returnme;
    returnme.x = offsetX * cos(rads) + offsetY * sin(rads);
    returnme.y = offsetX * -sin(rads) + offsetY * cos(rads);
    return returnme;
}

void Localization::init_sensors() { // just normalize them
    for (int i = 0; i < DistanceSensors.size(); i++) {
        DistanceSensors[i].headingDeg = normalize_angle(DistanceSensors[i].headingDeg);
    }
}

void Localization::compute_raw() {
    float average_x = 0;
    float average_y = 0;
    int x_count = 0;
    int y_count = 0;
    for (int i = 0; i < DistanceSensors.size(); i++) {
        float confidence = DistanceSensors[i].sensor->get_confidence();
        float distance = DistanceSensors[i].sensor->get_distance() / MM_IN;
        if (confidence < DistanceConfig.minConfidence) {continue;}
        if (confidence == PROS_ERR || distance == PROS_ERR) {continue;}
        if (distance <= 0) {continue;} 
        if (distance > DistanceConfig.MaxDistance) {continue;}
        float TrueHeading =  normalize_angle(imu->get_rotation() + DistanceSensors[i].headingDeg);
        hard_angle_clamp IDKNAME = hard_angle_clamper(TrueHeading);
        IDKNAME.min_deviation = abs(IDKNAME.min_deviation); // might remove later, idk. 

        offset calculatedoffset = offset_calculator(DistanceSensors[i].offsetX, DistanceSensors[i].offsetY, imu->get_rotation());

        if (IDKNAME.closest_angle == 90) {
            average_x += coordinate_maker(cos(to_radians(IDKNAME.min_deviation)) * DistanceSensors[i].sensor->get_distance(), true) - calculatedoffset.x;
            x_count++;
        }
        else if (IDKNAME.closest_angle == 270) {
            average_x += coordinate_maker(-cos(to_radians(IDKNAME.min_deviation)) * DistanceSensors[i].sensor->get_distance(), true) - calculatedoffset.x;
            x_count++;
        }
        else if (IDKNAME.closest_angle == 180) {
            average_y += coordinate_maker(-cos(to_radians(IDKNAME.min_deviation)) * DistanceSensors[i].sensor->get_distance(), false) - calculatedoffset.y;
            y_count++;
        }
        else if (IDKNAME.closest_angle == 0) {
            average_y += coordinate_maker(cos(to_radians(IDKNAME.min_deviation)) * DistanceSensors[i].sensor->get_distance(), false) - calculatedoffset.y;
            y_count++;
        }
        
        
    }
    if (x_count > 0) {
        CurrentPose.x = average_x / x_count;
    }
    if (y_count > 0) {
        CurrentPose.y = average_y / y_count;
    }
    CurrentPose.headingDeg = normalize_angle(imu->get_rotation());
}


void Localization::set_starting_pose() { // okay now I want to set staring pose, and I can do this by checking where the sensor is facing, and if it is along a axis
    float average_x = 0;
    float average_y = 0;
    int x_count = 0;
    int y_count = 0;
    for (int i = 0; i < DistanceSensors.size(); i++) {
        float confidence = DistanceSensors[i].sensor->get_confidence();
        float distance = DistanceSensors[i].sensor->get_distance() / MM_IN;
        if (confidence < DistanceConfig.minConfidence) {continue;}
        if (confidence == PROS_ERR || distance == PROS_ERR) {continue;}
        if (distance <= 0) {continue;} 
        if (distance > DistanceConfig.MaxDistance) {continue;}
        float TrueHeading =  normalize_angle(imu->get_rotation() + DistanceSensors[i].headingDeg);
        hard_angle_clamp IDKNAME = hard_angle_clamper(TrueHeading);
        offset calculatedoffset = offset_calculator(DistanceSensors[i].offsetX, DistanceSensors[i].offsetY, imu->get_rotation());

        if (IDKNAME.closest_angle == 90) {
            average_x += coordinate_maker(DistanceSensors[i].sensor->get_distance(), true) - calculatedoffset.x;
            x_count++;
        }
        else if (IDKNAME.closest_angle == 270) {
            average_x += coordinate_maker(-DistanceSensors[i].sensor->get_distance(), true) - calculatedoffset.x;
            x_count++;
        }
        else if (IDKNAME.closest_angle == 180) {
            average_y += coordinate_maker(-DistanceSensors[i].sensor->get_distance(), false) - calculatedoffset.y;
            y_count++;
        }
        else if (IDKNAME.closest_angle == 0) {
            average_y += coordinate_maker(DistanceSensors[i].sensor->get_distance(), false) - calculatedoffset.y;
            y_count++;
        }
    }
    if (x_count > 0) {
        CurrentPose.x = average_x / x_count;
    }
    if (y_count > 0) {
        CurrentPose.y = average_y / y_count;
    }
    StartingPose.headingDeg = 0; // this is hardcoded for now, but I will make it dynamic later
}

Pose Localization::compute_relative() {
    compute_raw();
    RelativePose.x = CurrentPose.x - StartingPose.x;
    RelativePose.y = CurrentPose.y - StartingPose.y;
    RelativePose.headingDeg = normalize_angle(CurrentPose.headingDeg - StartingPose.headingDeg);
    return RelativePose;
}


Localization::Localization(vector<DistanceThingies> DistanceSensors, struct DistanceThingiesContinued DistanceConfig, struct FieldSize FieldSize, pros::Imu* imu) {
    this->DistanceSensors = DistanceSensors; //just learned what this-> does, and imma spam this now
    this->field_size = FieldSize;
    this->imu = imu;
    this-> DistanceConfig = DistanceConfig;
    init_sensors();
}

