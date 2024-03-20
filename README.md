Made using Visual Studio 2022 as a Cmake project

This uses GTest for testing, and CMake for building.

I used vspkg to install GTest
you may need to change the CMakeLists.txt file to point to your vspkg install location
specifically this line:

```
include(d:/vcpkg/scripts/buildsystems/vcpkg.cmake)
```