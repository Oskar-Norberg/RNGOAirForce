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
To compile the Build version of the game, generate a solution and build the "RNGOEngine_RuntimeBuild" The other are either from libraries or other engine units which will be pulled in as you compile the head. Same goes for the Editor (RNGOEngine_Editor) and Runtime (RNGOEngine_Core)

If the program crashes on startup, it's most likely due to your IDE's current working directory not being set to the same path as the executeable. This means the executeable doesn't know where to look for its assets. Either change your exeuction path/working directory to the same as the executeable, or simply launch it from the file-explorer.
