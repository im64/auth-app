cmake_minimum_required(VERSION 3.25.2)
project(auth-app)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    Email/EmailHandlerImpl.cpp
)

target_link_libraries(${PROJECT_NAME} quickmail)

