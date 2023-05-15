cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(Radon
  VERSION 0.0.0.1
  LANGUAGES C CXX  )

set(CMAKE_CXX_STANDARD 23)
set(SMTG_CREATE_PLUGIN_LINK OFF)

set(vst3sdk_SOURCE_DIR C:/dev/vst/VST3_SDK/src)
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(Radon
  src/version.h
  src/cids.h
  src/processor.h
  src/processor.cpp
  src/controller.h
  src/controller.cpp
  src/entry.cpp  )

#- VSTGUI Wanted ----
# if(SMTG_ADD_VSTGUI)
#     target_sources(Radon
#         PRIVATE
#             resource/editor.uidesc
#     )
#     target_link_libraries(Radon
#         PRIVATE
#             vstgui_support
#     )
#     smtg_add_vst3_resource(Radon "resource/editor.uidesc")
# endif()
# -------------------

smtg_add_vst3_snapshot(Radon resource/snapshot.png)
smtg_add_vst3_snapshot(Radon resource/snapshot_2.0x.png)

target_link_libraries(Radon
    PRIVATE
        sdk
)

if(SMTG_MAC)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)
    smtg_set_bundle(Radon
		BUNDLE_IDENTIFIER com.tnznt.Radon
		INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS
    )
    smtg_set_debug_executable(Radon
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(Radon PRIVATE
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Radon)

        smtg_set_debug_executable(Radon
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif()