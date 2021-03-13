cmake_minimum_required(VERSION 3.5)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ENGINE

PROJECT(engine)
add_executable(${PROJECT_NAME} ./engine/main.cpp ./engine/tinyxlm2.cpp ./engine/tinyxml2.h ./engine/parser.cpp ./engine/parser.h ./engine/drawer.cpp ./engine/drawer.h ./src/point.cpp ./src/point.h ./src/shape.cpp ./src/shape.h)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	
	
	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib)
	
	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )	
	
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)

# GENERATOR

PROJECT(generator)
add_executable(${PROJECT_NAME} ./generator/main.cpp ./src/point.cpp ./src/point.h ./src/shape.cpp ./src/shape.h  ./generator/box.cpp ./generator/box.h generator/cone.cpp generator/cone.h generator/plane.cpp generator/plane.h generator/sphere.cpp generator/sphere.h)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
	message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")


	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
			${TOOLKITS_FOLDER}/glut/glut32.lib)

	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
	if(NOT GLUT_FOUND)
		message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)
