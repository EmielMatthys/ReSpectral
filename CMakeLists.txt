cmake_minimum_required(VERSION 3.0.0)
project(RESPECTRAL VERSION 0.1.0)

#add_subdirectory(spdlog-1.8.2)

add_library(RESPECTRAL SHARED
        RESPECTRAL.cpp
        Injector.cpp Injector.h
        Module.cpp Module.h ModuleManager.cpp ModuleManager.h
        vtablehook.h
        getvfunc.h
        hooks/Panel.h
        hexdump.h
        DrawTools.h
        TF2/CUserCmd.h
        netvars.h netvars.cpp NetVar.cpp NetVar.h ClientClass.h Chams.cpp hooks/IVModelRender.h)

#target_link_directories(RESPECTRAL PUBLIC spdlog-1.8.2/build)
#target_include_directories(RESPECTRAL PUBLIC spdlog-1.8.2/include)

target_include_directories(RESPECTRAL SYSTEM PRIVATE
        "sdk-headers/source-sdk-2013-headers/mp/src/common"
        "sdk-headers/source-sdk-2013-headers/mp/src/mathlib"
        "sdk-headers/source-sdk-2013-headers/mp/src/public"
        "sdk-headers/source-sdk-2013-headers/mp/src/public/tier0"
        "sdk-headers/source-sdk-2013-headers/mp/src/public/tier1"
        "sdk-headers/source-sdk-2013-headers/mp/src/tier1"
        "sdk-headers/source-sdk-2013-headers/mp/src"
        )
#target_link_libraries(RESPECTRAL -ldl spdlog)

set(CMAKE_CXX_FLAGS "-m32 -march=native -fexceptions -DNDEBUG")
target_compile_definitions(RESPECTRAL PRIVATE
        _GLIBCXX_USE_CXX11_ABI=0
        _POSIX=1
        FREETYPE_GL_USE_VAO=1
        RAD_TELEMETRY_DISABLED=1
        LINUX=1
        USE_SDL=1
        _LINUX=1
        POSIX=1
        GNUC=1
        NO_MALLOC_OVERRIDE=1
        )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
