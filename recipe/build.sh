#!/bin/bash

set -exo pipefail

# Remove vendored headers while building so sources use the external headers
# installed by the conda imgui and implot packages.
rm include/vsgImGui/imgui.h
rm include/vsgImGui/implot.h

cmake $SRC_DIR \
  ${CMAKE_ARGS} \
  -G Ninja \
  -B build \
  -DBUILD_SHARED_LIBS=ON \
  -DCMAKE_BUILD_TYPE=Release \
  -DVSG_IMGUI_USE_SYSTEM_IMGUI=ON \
  -DVSG_IMGUI_USE_SYSTEM_IMPLOT=ON

cmake --build build --parallel

# Install compatibility shims for downstreams that still include the historical
# vsgImGui paths while continuing to use the external conda headers.
cat > include/vsgImGui/imgui.h <<'EOF'
#pragma once
#include <imgui.h>
EOF
cat > include/vsgImGui/implot.h <<'EOF'
#pragma once
#include <implot.h>
EOF

cmake --install build --strip
