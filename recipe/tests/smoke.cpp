#include <vsgImGui/SendEventsToImGui.h>
#include <vsgImGui/Texture.h>
#include <vsgImGui/imgui.h>
#include <vsgImGui/implot.h>

#include <imgui.h>
#include <implot.h>

#include <type_traits>

namespace
{
using ImageFunction = void (*)(ImTextureRef, const ImVec2&, const ImVec2&, const ImVec2&);
ImageFunction volatile image_function = static_cast<ImageFunction>(&ImGui::Image);
} // namespace

int main()
{
    static_assert(std::is_integral<ImTextureID>::value, "system imgui should provide the ImTextureID ABI");

    ImGui::CreateContext();
    ImPlot::CreateContext();

    auto handler = vsgImGui::SendEventsToImGui::create();
    const ImTextureID texture_id{};
    const ImTextureRef texture_ref{texture_id};
    const bool ok = static_cast<bool>(handler) && image_function != nullptr && texture_ref.GetTexID() == texture_id;

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return ok ? 0 : 1;
}
