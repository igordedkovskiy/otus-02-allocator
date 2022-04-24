cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(CustomAllocator VERSION ${PROJECT_VESRION})

option(WITH_GTEST "Whether to build google test" ON)

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME} "main.cpp" "CustomAllocator.h")
#add_library(CustomAllocator_lib "CustomAllocator.h")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

#set_target_properties(CustomAllocator_lib PROPERTIES
#    CXX_STANDARD 17
#    CXX_STANDARD_REQUIRED ON
#)

#target_include_directories(CustomAllocator_lib
#    PRIVATE "${CMAKE_BINARY_DIR}"
#)

#target_link_libraries(${PROJECT_NAME} PRIVATE
#    CustomAllocator_lib
#)

if(WITH_GTEST)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest" "googletest")
    add_executable(test_allocator "test_allocator.cpp")

    target_include_directories(test_allocator PRIVATE
        ${GTEST_INCLUDE_DIRS}
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )

    set_target_properties(test_allocator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_allocator PRIVATE
        ${GTEST_BOTH_LIBRARIES}
        gtest
        gtest_main
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
#    target_compile_options(CustomAllocator_lib PRIVATE
#        /W4
#    )
    if(WITH_GTEST)
        target_compile_options(test_allocator PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        #-Wextra -pedantic -Werror
    )
#    target_compile_options(CustomAllocator_lib PRIVATE
#        -Wall -Wextra -pedantic -Werror
#    )
    if(WITH_GTEST)
        target_compile_options(test_allocator PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT divmy@yandex.ru)
include(CPack)

if(WITH_GTEST)
    include(CTest)
    enable_testing()
    add_test(test_allocator test_allocator)
endif()
