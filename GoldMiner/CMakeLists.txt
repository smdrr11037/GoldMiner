# target

#INCLUDE_DIRECTORIES(
#	"${CMAKE_CURRENT_BINARY_DIR}"
#	"${CMAKE_CURRENT_SOURCE_DIR}"
#	"${PROJECT_SOURCE_DIR}/GoldMiner/src"
#	)
SET(SRC_LIST "src/main.cpp"
	"src/model/Model.cpp"
	"src/viewmodel/ViewModel.cpp"
	# "src/window/StatPage.cpp"
	"src/app/app.cpp"
	"src/window/MainWindow.cpp"
	"src/window/CompletePage.cpp"
	"src/window/GameOver.cpp"
	"src/window/StartPage.cpp"
	"src/window/RunningPage.cpp"
	)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
add_executable(GoldMiner WIN32 ${SRC_LIST})

# ADD_EXECUTABLE(GoldMiner ${SRC_PCH_LIST} ${SRC_LIST})
# SET_PCH(GoldMiner "exe" "precomp.h" ${SRC_PCH_LIST} ${SRC_LIST})
SET_TARGET_PROPERTIES(GoldMiner PROPERTIES
	OUTPUT_NAME "GoldMiner"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET}")
target_link_libraries(GoldMiner Qt5::Widgets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/installation")

# 添加安装规则，将可执行文件和DLL文件复制到安装目录
install(TARGETS GoldMiner
        RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 查找Qt的bin目录
set(Qt5_BIN_DIR C:/Qt/5.15.2/msvc2019_64/bin)

# 安装Qt的DLL文件
install(FILES
    "${Qt5_BIN_DIR}/Qt5Core.dll"
    "${Qt5_BIN_DIR}/Qt5Gui.dll"
    "${Qt5_BIN_DIR}/Qt5Widgets.dll"
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 安装平台插件
install(DIRECTORY "${Qt5_BIN_DIR}/../plugins/platforms"
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 安装游戏素材图片
install(DIRECTORY "src/window/image"
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#end
