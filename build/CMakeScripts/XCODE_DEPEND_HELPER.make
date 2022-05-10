# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.FloatGraph.Debug:
PostBuild.vml.Debug: /Users/vincirist/projects/FloatGraph/build/Debug/FloatGraph
PostBuild.imgui.Debug: /Users/vincirist/projects/FloatGraph/build/Debug/FloatGraph
PostBuild.glfw.Debug: /Users/vincirist/projects/FloatGraph/build/Debug/FloatGraph
PostBuild.glad.Debug: /Users/vincirist/projects/FloatGraph/build/Debug/FloatGraph
/Users/vincirist/projects/FloatGraph/build/Debug/FloatGraph:\
	/Users/vincirist/projects/FloatGraph/build/extern/vml/Debug/libvml.a\
	/Users/vincirist/projects/FloatGraph/build/extern/imgui/Debug/libimgui.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glfw/Debug/libglfw.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glad/Debug/libglad.a
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/Debug/FloatGraph


PostBuild.glad.Debug:
/Users/vincirist/projects/FloatGraph/build/extern/glad/Debug/libglad.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glad/Debug/libglad.a


PostBuild.glfw.Debug:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/Debug/libglfw.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glfw/Debug/libglfw.a


PostBuild.imgui.Debug:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/Debug/libimgui.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/imgui/Debug/libimgui.a


PostBuild.vml.Debug:
/Users/vincirist/projects/FloatGraph/build/extern/vml/Debug/libvml.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/vml/Debug/libvml.a


PostBuild.FloatGraph.Release:
PostBuild.vml.Release: /Users/vincirist/projects/FloatGraph/build/Release/FloatGraph
PostBuild.imgui.Release: /Users/vincirist/projects/FloatGraph/build/Release/FloatGraph
PostBuild.glfw.Release: /Users/vincirist/projects/FloatGraph/build/Release/FloatGraph
PostBuild.glad.Release: /Users/vincirist/projects/FloatGraph/build/Release/FloatGraph
/Users/vincirist/projects/FloatGraph/build/Release/FloatGraph:\
	/Users/vincirist/projects/FloatGraph/build/extern/vml/Release/libvml.a\
	/Users/vincirist/projects/FloatGraph/build/extern/imgui/Release/libimgui.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glfw/Release/libglfw.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glad/Release/libglad.a
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/Release/FloatGraph


PostBuild.glad.Release:
/Users/vincirist/projects/FloatGraph/build/extern/glad/Release/libglad.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glad/Release/libglad.a


PostBuild.glfw.Release:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/Release/libglfw.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glfw/Release/libglfw.a


PostBuild.imgui.Release:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/Release/libimgui.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/imgui/Release/libimgui.a


PostBuild.vml.Release:
/Users/vincirist/projects/FloatGraph/build/extern/vml/Release/libvml.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/vml/Release/libvml.a


PostBuild.FloatGraph.MinSizeRel:
PostBuild.vml.MinSizeRel: /Users/vincirist/projects/FloatGraph/build/MinSizeRel/FloatGraph
PostBuild.imgui.MinSizeRel: /Users/vincirist/projects/FloatGraph/build/MinSizeRel/FloatGraph
PostBuild.glfw.MinSizeRel: /Users/vincirist/projects/FloatGraph/build/MinSizeRel/FloatGraph
PostBuild.glad.MinSizeRel: /Users/vincirist/projects/FloatGraph/build/MinSizeRel/FloatGraph
/Users/vincirist/projects/FloatGraph/build/MinSizeRel/FloatGraph:\
	/Users/vincirist/projects/FloatGraph/build/extern/vml/MinSizeRel/libvml.a\
	/Users/vincirist/projects/FloatGraph/build/extern/imgui/MinSizeRel/libimgui.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glfw/MinSizeRel/libglfw.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glad/MinSizeRel/libglad.a
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/MinSizeRel/FloatGraph


PostBuild.glad.MinSizeRel:
/Users/vincirist/projects/FloatGraph/build/extern/glad/MinSizeRel/libglad.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glad/MinSizeRel/libglad.a


PostBuild.glfw.MinSizeRel:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/MinSizeRel/libglfw.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glfw/MinSizeRel/libglfw.a


PostBuild.imgui.MinSizeRel:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/MinSizeRel/libimgui.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/imgui/MinSizeRel/libimgui.a


PostBuild.vml.MinSizeRel:
/Users/vincirist/projects/FloatGraph/build/extern/vml/MinSizeRel/libvml.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/vml/MinSizeRel/libvml.a


PostBuild.FloatGraph.RelWithDebInfo:
PostBuild.vml.RelWithDebInfo: /Users/vincirist/projects/FloatGraph/build/RelWithDebInfo/FloatGraph
PostBuild.imgui.RelWithDebInfo: /Users/vincirist/projects/FloatGraph/build/RelWithDebInfo/FloatGraph
PostBuild.glfw.RelWithDebInfo: /Users/vincirist/projects/FloatGraph/build/RelWithDebInfo/FloatGraph
PostBuild.glad.RelWithDebInfo: /Users/vincirist/projects/FloatGraph/build/RelWithDebInfo/FloatGraph
/Users/vincirist/projects/FloatGraph/build/RelWithDebInfo/FloatGraph:\
	/Users/vincirist/projects/FloatGraph/build/extern/vml/RelWithDebInfo/libvml.a\
	/Users/vincirist/projects/FloatGraph/build/extern/imgui/RelWithDebInfo/libimgui.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glfw/RelWithDebInfo/libglfw.a\
	/Users/vincirist/projects/FloatGraph/build/extern/glad/RelWithDebInfo/libglad.a
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/RelWithDebInfo/FloatGraph


PostBuild.glad.RelWithDebInfo:
/Users/vincirist/projects/FloatGraph/build/extern/glad/RelWithDebInfo/libglad.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glad/RelWithDebInfo/libglad.a


PostBuild.glfw.RelWithDebInfo:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/RelWithDebInfo/libglfw.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/glfw/RelWithDebInfo/libglfw.a


PostBuild.imgui.RelWithDebInfo:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/RelWithDebInfo/libimgui.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/imgui/RelWithDebInfo/libimgui.a


PostBuild.vml.RelWithDebInfo:
/Users/vincirist/projects/FloatGraph/build/extern/vml/RelWithDebInfo/libvml.a:
	/bin/rm -f /Users/vincirist/projects/FloatGraph/build/extern/vml/RelWithDebInfo/libvml.a




# For each target create a dummy ruleso the target does not have to exist
/Users/vincirist/projects/FloatGraph/build/extern/glad/Debug/libglad.a:
/Users/vincirist/projects/FloatGraph/build/extern/glad/MinSizeRel/libglad.a:
/Users/vincirist/projects/FloatGraph/build/extern/glad/RelWithDebInfo/libglad.a:
/Users/vincirist/projects/FloatGraph/build/extern/glad/Release/libglad.a:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/Debug/libglfw.a:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/MinSizeRel/libglfw.a:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/RelWithDebInfo/libglfw.a:
/Users/vincirist/projects/FloatGraph/build/extern/glfw/Release/libglfw.a:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/Debug/libimgui.a:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/MinSizeRel/libimgui.a:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/RelWithDebInfo/libimgui.a:
/Users/vincirist/projects/FloatGraph/build/extern/imgui/Release/libimgui.a:
/Users/vincirist/projects/FloatGraph/build/extern/vml/Debug/libvml.a:
/Users/vincirist/projects/FloatGraph/build/extern/vml/MinSizeRel/libvml.a:
/Users/vincirist/projects/FloatGraph/build/extern/vml/RelWithDebInfo/libvml.a:
/Users/vincirist/projects/FloatGraph/build/extern/vml/Release/libvml.a:
