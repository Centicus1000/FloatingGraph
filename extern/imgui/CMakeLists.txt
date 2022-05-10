set(IMGUI_HEADER_FILES
	imgui.h
	imconfig.h
	imgui_internal.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	# implot
	implot.h
	implot_internal.h
)

set(IMGUI_SOURCE_FILES
	imgui.cpp
	imgui_draw.cpp
	imgui_widgets.cpp
	imgui_tables.cpp
	imgui_demo.cpp
	# implot
	implot.cpp
	implot_items.cpp
	implot_demo.cpp
)


add_library(imgui STATIC ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
target_include_directories(imgui PUBLIC ..)

# toggles real dir view
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
