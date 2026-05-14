#include <vsgImGui/SendEventsToImGui.h>
#include <vsgImGui/imgui.h>
#include <vsgImGui/implot.h>

#include <imgui.h>
#include <implot.h>

int main()
{
    ImGui::CreateContext();
    ImPlot::CreateContext();

    auto handler = vsgImGui::SendEventsToImGui::create();
    const bool ok = static_cast<bool>(handler);

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return ok ? 0 : 1;
}
