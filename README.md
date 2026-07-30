# Localizer

![License](https://img.shields.io/github/license/Official-3796B/Localizer)
![Repo Size](https://img.shields.io/github/repo-size/Official-3796B/Localizer)
![Last Commit](https://img.shields.io/github/last-commit/Official-3796B/Localizer)
![Issues](https://img.shields.io/github/issues/Official-3796B/Localizer)
![VEX](https://img.shields.io/badge/Platform-VEX%20V5-red)
![PROS](https://img.shields.io/badge/Built%20With-PROS-blue)

Thats pretty cool. Just saw the top thingies on someone else github, search it up and boom now we have it. 

# Description
Distance Sensor based localization. Works with PROS. 

# Disclaimer
No clue if it works, dont hold me to this. Coded this without a bot. 

# Download
1. Head to the release tab and download the latest release.
2. Drop the .cpp in your project's /src folder the and .h in your /include folder.
3. That's it!

# Initialization
1. At the top of each .cpp file accessing the localizer class, add '#include "localizer.h"' (with the double quotes)
2. Object prototype: Localization(std::vector<DistanceThingies> DistanceSensors, struct DistanceThingiesContinued DistanceConfig, struct FieldSize FieldSize, pros::Imu* imu);

3. To create an object, call the class name, followed by an object name.
4. Then define your distance sensors: {{distance_sensor, offset_x, offset_y, heading}...}
5. Then define your global distance sensor config: {min_confidence, max_distance}
6. Then the field boundaries: {min_x, max_x, min_y, max_y} (this should almost always be -72, 72, -72, 72)
7. Then finally, attach your imu: {imu}

**Example**:


# Roadmap
- [x] Initial Logic
- [x] File Management
- [x] Sensor Fusion
- [ ] Testing
- [ ] Better Instructions
- [ ] Full Release
- [ ] Anything Else?
