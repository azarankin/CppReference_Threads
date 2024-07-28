# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_BUILD_TYPE debug)
add_definitions(-DUNICODE -D_UNICODE)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CppReference_Threads")

add_executable (01_Unique_Lock "01_unique_lock.cpp")
add_executable (02_Condition_Variable "02_condition_variable.cpp")
add_executable (03_Semiphore "03_semiphore.cpp")
add_executable (03_01_Ping "03_01_ping.cpp")
add_executable (03_02_Pong "03_02_pong.cpp")

#set_property(TARGET 03_Semiphore PROPERTY CXX_STANDARD 20)


#target_link_libraries(WideStringExample
#    PRIVATE
#        # Add any required libraries here, if necessary
#)




# Include sub-projects.
#add_subdirectory ("a01_Unique_Lock")
#add_subdirectory ("a02_Condition_Varialbe")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")
#add_subdirectory ("")

