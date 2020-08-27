
- After cloning the project, create build dir and cd to it
- Fire cmake in build dir only. o/w it will little up the project directory

$ cmake .. -DCMAKE_BUILD_TYPE=Debug
$ make 
$ make coverage


Refs/Credits:
https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html
http://mathnathan.com/2010/07/getting-started-with-cmake/
https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
https://stackoverflow.com/questions/37957583/how-to-use-gcov-with-cmake
https://jhbell.com/using-cmake-and-gcov
https://stackoverflow.com/questions/6891447/cmake-variable-scope-add-subdirectory


