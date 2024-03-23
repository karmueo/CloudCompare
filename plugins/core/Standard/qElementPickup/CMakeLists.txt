# CloudCompare example for standard plugins

# REPLACE ALL 'qElementPickup' OCCURENCES BY YOUR PLUGIN NAME
# AND ADAPT THE CODE BELOW TO YOUR OWN NEEDS!

# Add an option to CMake to control whether we build this plugin or not
option( PLUGIN_STANDARD_ELEMENTPICKUP "Check to install qElementPickup plugin" OFF )

if ( PLUGIN_STANDARD_ELEMENTPICKUP )
	project( QELEMENTPICKUP_PLUGIN )
	 
	AddPlugin( NAME ${PROJECT_NAME} )
		
	add_subdirectory( include )
	add_subdirectory( src )
	
	# set dependencies to necessary libraries
	# target_link_libraries( ${PROJECT_NAME} LIB1 )
endif()
