#include <vsgImGui/SendEventsToImGui.h>
#include <vsgImGui/Texture.h>
#include <vsgImGui/imgui.h>
#include <vsgImGui/implot.h>

#include <imgui.h>
#include <implot.h>

#include <type_traits>

namespace
{
using ImageFunction = void (*)(ImTextureID, const ImVec2&, const ImVec2&, const ImVec2&, const ImVec4&, const ImVec4&);
ImageFunction volatile image_function = &ImGui::Image;
} // namespace

int main()
{
    static_assert(std::is_integral<ImTextureID>::value, "system imgui should provide the ImTextureID ABI");

    ImGui::CreateContext();
    ImPlot::CreateContext();

    auto handler = vsgImGui::SendEventsToImGui::create();
    const bool ok = static_cast<bool>(handler) && image_function != nullptr;

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return ok ? 0 : 1;
}
