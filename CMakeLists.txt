cmake_minimum_required(VERSION 3.2)
if ($ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

add_executable(ip_filter main.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(ip_filter PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")

set(CPACK_PACKAGE_CONTACT neige.mvk@gmail.com)

include(CPack)