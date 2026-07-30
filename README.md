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
1. At the top of each .cpp file accessing the localizer class, add <img width="172" height="19" alt="Screenshot 2026-07-31 at 12 14 57 AM" src="https://github.com/user-attachments/assets/8463a79c-acfb-4657-8a5d-4be5385070c8" />

2. Object prototype: <img width="1114" height="17" alt="Screenshot 2026-07-31 at 12 20 05 AM" src="https://github.com/user-attachments/assets/f7077d08-1708-4fe2-93a1-e91ae5f81971" />


3. To create an object, call the class name, followed by an object name.
4. Then define your distance sensors: {{distance_sensor, offset_x, offset_y, heading}...}
5. Then define your global distance sensor config: {min_confidence, max_distance}
6. Then the field boundaries: {min_x, max_x, min_y, max_y}
7. Then finally, attach your imu: {imu}

**Example**:

<img width="795" height="80" alt="Screenshot 2026-07-31 at 12 14 41 AM" src="https://github.com/user-attachments/assets/c27f2afd-07d3-4505-b001-29cf2b7d5552" />

# Usage
1. Prior to the first movement in your auto, call<img width="222" height="21" alt="Screenshot 2026-07-31 at 12 53 48 AM" src="https://github.com/user-attachments/assets/2d2168ba-cf23-4d6e-aa7f-cb912ab1c5e6" />
2. Then call <img width="153" height="21" alt="Screenshot 2026-07-31 at 12 59 44 AM" src="https://github.com/user-attachments/assets/3aada4c4-5f59-458b-9147-28d8a034932f" /> if you have an unreliable Odom-based pose, or if you do, input it: <img width="416" height="26" alt="Screenshot 2026-07-31 at 12 59 59 AM" src="https://github.com/user-attachments/assets/6e91819c-7c5c-485f-b74d-fbca48738881" />
3. These functions return a pose (x, y, theta), so make sure to assign it to a chassis pose.
4. That's it!






# Roadmap
- [x] Initial Logic
- [x] File Management
- [x] Sensor Fusion
- [ ] Testing
- [ ] Better Instructions
- [ ] Full Release
- [ ] Anything Else?
