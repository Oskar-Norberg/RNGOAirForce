# RNGOAirForce
A half-rushed spline-shooter built using the RNGOEngine. Due to not wanting to pollute the engine source-code with project specific code, this was split into a separate project. If you want to see the commit logs for the entire engine. see [its repo](https://github.com/Oskar-Norberg/RNGOEngine-Core).

### Features:
- Spline Components
- Spline Attachments
- Basic FPS-Style Camera
- Shooting ability
- Win, Gameover and playing states

# Build Instructions
## Prerequisites:
* CMake
* C++23 compatible toolchain.

This repo consists of three parts, "Runtime" which is the engine core (compiled as a static library), editor (compiled as an executable) and the build (compiled as an executable). *For a full-screen, optimized, shipping-build you want the Build folder and the cmake therein.

To generate a solution file, go into one of the subproject (runtime, editor, build) paths and use cmake -G "GENERATOR_NAME" replacing GENERATOR_NAME with your preferred generator. Example: cd Build && cmake -G "Visual Studio 17"


## Troubleshooting
If the program crashes on startup, your IDE or wherever you are launching the project from probably doesn't have the current working directory set to where the executable is. Either set your execution/working directory to the executable, or manually copy the CONTENTS (not the folder itself) to your working directory.
