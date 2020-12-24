FIND_PACKAGE(UNITY REQUIRED) #VOID_LIB_PATH
add_executable(tests main.cpp)
configure_void_library(win32 true)
target_include_directories(tests PRIVATE ${UNITY_LIB_PATH} ${VOID_LIB_PATH})
add_unity_library(tests)
target_link_libraries(tests PRIVATE void-win32 project_options project_warnings)
target_link_libraries(tests PRIVATE unity)

SET(DOXY_INPUT ${PROJECT_SOURCE_DIR}/src)
ADD_DOCUMENTATION(doc doc/Doxyfile)