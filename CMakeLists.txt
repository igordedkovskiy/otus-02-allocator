cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(CustomAllocator VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME} main.cpp)
add_library(CustomAllocator_lib CustomAllocator.cpp CustomAllocator.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(CustomAllocator_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(CustomAllocator_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    CustomAllocator_lib
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(CustomAllocator_lib PRIVATE
        /W4
    )
    #if(WITH_GTEST)
    #    target_compile_options(test_CustomAllocator PRIVATE
    #        /W4
    #    )
    #endif()
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra -pedantic -Werror
    )
    target_compile_options(CustomAllocator_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    #if(WITH_GTEST)
    #    target_compile_options(test_CustomAllocator PRIVATE
    #        -Wall -Wextra -pedantic -Werror
    #    )
    #endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT divmy@yandex.ru)
include(CPack)
