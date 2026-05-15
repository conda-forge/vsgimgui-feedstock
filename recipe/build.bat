@echo on

:: Remove vendored headers while building so sources use the external headers
:: installed by the conda imgui and implot packages.
del /q include\vsgImGui\imgui.h
del /q include\vsgImGui\implot.h
if errorlevel 1 exit 1

cmake %SRC_DIR% ^
  %CMAKE_ARGS% ^
  -B build ^
  -DBUILD_SHARED_LIBS=ON ^
  -DVSG_IMGUI_USE_SYSTEM_IMGUI=ON ^
  -DVSG_IMGUI_USE_SYSTEM_IMPLOT=ON
if errorlevel 1 exit 1

cmake --build build --parallel --config Release
if errorlevel 1 exit 1

:: Install compatibility shims for downstreams that still include the historical
:: vsgImGui paths while continuing to use the external conda headers.
(
  echo #pragma once
  echo #include ^<imgui.h^>
) > include\vsgImGui\imgui.h
(
  echo #pragma once
  echo #include ^<implot.h^>
) > include\vsgImGui\implot.h

cmake --install build --config Release
if errorlevel 1 exit 1
