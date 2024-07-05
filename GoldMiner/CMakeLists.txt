# target

#INCLUDE_DIRECTORIES(
#	"${CMAKE_CURRENT_BINARY_DIR}"
#	"${CMAKE_CURRENT_SOURCE_DIR}"
#	"${PROJECT_SOURCE_DIR}/GoldMiner/src"
#	)
SET(SRC_LIST "src/main.cpp"
	# "src/model/Model.cpp"
	# "src/viewmodel/ViewModel.cpp"
	# "src/window/StatPage.cpp"
	)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_PCH_LIST "precomp.cpp")


add_executable(GoldMiner WIN32  ${SRC_LIST})

# ADD_EXECUTABLE(GoldMiner ${SRC_PCH_LIST} ${SRC_LIST})
# SET_PCH(GoldMiner "exe" "precomp.h" ${SRC_PCH_LIST} ${SRC_LIST})
SET_TARGET_PROPERTIES(GoldMiner PROPERTIES
	OUTPUT_NAME "GoldMiner"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET}")
target_link_libraries(GoldMiner Qt5::Widgets)

#end
