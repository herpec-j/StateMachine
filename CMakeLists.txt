cmake_minimum_required(VERSION 2.6)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

project(StateMachine)

if (MSVC)

else()
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if (COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif (COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else ()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif ()
endif ()

set(StateMachine_HDRS
	${PROJECT_SOURCE_DIR}/StateMachine/Includes/StateMachine/StateMachine.hpp
	${PROJECT_SOURCE_DIR}/StateMachine/Includes/StateMachine/State.hpp)

source_group(Includes FILES ${StateMachine_HDRS})

set(StateMachine_Private_HDRS
	${PROJECT_SOURCE_DIR}/StateMachine/Includes/StateMachine/Private/Singleton.hpp)

source_group(Includes\\Private FILES ${StateMachine_Private_HDRS})

set(HDRS
	${StateMachine_HDRS}
	${StateMachine_Private_HDRS})
	
set(SRCS
	${PROJECT_SOURCE_DIR}/StateMachine/Sources/Test.cpp)

source_group(Sources FILES ${SRCS})

include_directories("$(PROJECT_SOURCE_DIR)/StateMachine/Includes")

add_executable(StateMachineTest ${SRCS} ${HDRS})

enable_testing()

add_test(StateMachineUnitTests StateMachineTest)

set_tests_properties(StateMachineUnitTests
	PROPERTIES PASS_REGULAR_EXPRESSION "Success!")