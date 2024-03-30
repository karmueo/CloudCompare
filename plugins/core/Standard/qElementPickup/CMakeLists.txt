# CloudCompare example for standard plugins

# REPLACE ALL 'qElementPickup' OCCURENCES BY YOUR PLUGIN NAME
# AND ADAPT THE CODE BELOW TO YOUR OWN NEEDS!

# Add an option to CMake to control whether we build this plugin or not
option( PLUGIN_STANDARD_ELEMENTPICKUP "Check to install qElementPickup plugin" OFF )

if ( PLUGIN_STANDARD_ELEMENTPICKUP )
	project( QELEMENTPICKUP_PLUGIN )

	find_package( PCL REQUIRED )

	AddPlugin( NAME ${PROJECT_NAME} )

	add_subdirectory( include )
	add_subdirectory( src )
	
	# set dependencies to necessary libraries
	# target_link_libraries( ${PROJECT_NAME} LIB1 )
	# 添加静态库的包含目录
	target_include_directories( ${PROJECT_NAME}
			PUBLIC
			${PCL_INCLUDE_DIRS}
			${CMAKE_CURRENT_SOURCE_DIR}/../qPCL/PclUtils/utils
	)

	# 链接静态库
	target_link_libraries(${PROJECT_NAME}
			${CMAKE_BINARY_DIR}/plugins/core/Standard/qPCL/PclUtils/QPCL_PLUGIN_UTILS_LIBd.lib
			${PCL_LIBRARIES}
	)
endif()
