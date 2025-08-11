# CMakeList.txt : CMake project for IdleSnub, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HDR_FILES headers/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IdleSnub PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)


target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE pdh
  PRIVATE advapi32
  PRIVATE psapi
)

# TODO: Add tests and install targets if needed.
