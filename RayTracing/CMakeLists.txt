cmake_minimum_required(VERSION 3.10)

project(RayTracing)


# Build zlib
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/zlib/)
# Build libpng
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/libpng/)


# Specify our source files
add_executable(RayTracing
	src/main.cpp
	
	src/Hittable/Hittable.cpp
	src/Hittable/Sphere.cpp

	src/HittableList/HittableList.cpp

	src/Ray3/Ray3.cpp

	src/Vec3/Vec3.cpp
)

# Include our own headers
target_include_directories(RayTracing PUBLIC ${CMAKE_SOURCE_DIR}/src/)
# Include third-party headers
target_include_directories(RayTracing PUBLIC ${CMAKE_SOURCE_DIR}/libs/zlib/)
target_include_directories(RayTracing PUBLIC ${CMAKE_SOURCE_DIR}/libs/libpng/)

# Link against libpng
target_link_libraries(RayTracing ${CMAKE_SOURCE_DIR}/libs/libpng/libpng)
target_link_libraries(RayTracing ${CMAKE_SOURCE_DIR}/libs/zlib/zlib)
