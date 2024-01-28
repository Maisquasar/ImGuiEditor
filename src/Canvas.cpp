#include "Canvas.h"
#include "Object/IObject.h"

#include "Editor.h"
#include "Hierarchy.h"
#include "Inspector.h"

void Canvas::Initialize()
{
	m_objects = &Editor::Get()->GetHierarchy()->m_objects;
}

void Canvas::Draw() const
{
	static float pos = 0;
	static Hierarchy* hierarchy = Editor::Get()->GetHierarchy();
	ImGui::ShowStyleEditor();
	//ImGui::ShowMetricsWindow();
	if (ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar))
	{
		size_t index = 0;
		for (const auto& weakObject : hierarchy->GetRoot()->p_children)
		{
			DisplayObject(weakObject.lock(), ++index);
		}
#if 0
		int j = 0;
		int y = 0;
		static bool thumbnailClicked = false;
		static bool thumbnailHovered = false;

		static float thumbnailSize = 1.f;
		if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
			thumbnailSize += ImGui::GetIO().MouseWheel * 0.1f;

		Vec2f windowSize = ImGui::GetWindowSize();
		Vec2f windowPos = ImGui::GetWindowPos();
		Vec2f regMin = ImGui::GetWindowContentRegionMin();
		Vec2f thumbnailOffset = Vec2f(150, 225) * thumbnailSize;

		// Common offsets and sizes
		const Vec2f shadowOffset = Vec2f(6.0f, 5.5f);
		const Vec2f imageSize = Vec2f(128.f);
		const Vec2f shadowSize = Vec2f(134.0f, 210.5f);
		constexpr float bottomRectHeight = 204.5f;
		float lineHeight = 1.5f;

		constexpr float cornerRounding = 7.5f;
		ImU32 clickedColor = ImGui::ColorConvertFloat4ToU32(Vec4f(0.2, 0.4f, 1.f, 1.f));
		constexpr ImU32 hoveredColor = 4281742902;

		std::cout << "Thumbnail size: " << thumbnailSize << std::endl;
		for (int i = 0; i < 1; i++) {
			// Common positions
			Vec2f currentPos = Vec2f(j, y) * thumbnailOffset;
			Vec2f contentMin = regMin + currentPos;
			const Vec2f rectSize = imageSize * thumbnailSize;
			if (contentMin.x >= windowSize.x - thumbnailOffset.x + 25.f) {
				y++;
				j = 0;

				currentPos = Vec2f(j, y) * thumbnailOffset;
				contentMin.x = regMin.x;
				contentMin.y += thumbnailOffset.y;
			}

			Vec2f contentRegionStart = windowPos + contentMin;
			// Draw list pointer
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			// Shadow behind the thumbnail
			Vec2f shadowMin = contentRegionStart + shadowOffset;
			Vec2f shadowMax = contentRegionStart + shadowSize * thumbnailSize;
			drawList->AddRectFilled(shadowMin, shadowMax, 1677721600, cornerRounding, 240);

			// Thumbnail image with rounded corners
			Vec2f thumbnailMin = contentRegionStart;
			Vec2f thumbnailMax = contentRegionStart + imageSize * thumbnailSize;
			drawList->AddImageRounded(nullptr, thumbnailMin, thumbnailMax, Vec2f(0, 0), Vec2f(1, 1), IM_COL32_WHITE, cornerRounding, 48);
			drawList->AddRectFilled(thumbnailMin, thumbnailMax, thumbnailClicked ? clickedColor : thumbnailHovered ? hoveredColor : IM_COL32_BLACK, cornerRounding, 48);

			// Line under the thumbnail
			Vec2f lineMin = contentRegionStart + Vec2f(0, imageSize.y * thumbnailSize);
			Vec2f lineMax = contentRegionStart + Vec2f(imageSize.x, imageSize.y + lineHeight) * thumbnailSize;
			drawList->AddRectFilled(lineMin, lineMax, IM_COL32_WHITE, 0.0f, 0); // No rounding

			// Bottom rectangle under the thumbnail
			Vec2f bottomRectMin = contentRegionStart + Vec2f(0, (imageSize.y + lineHeight) * thumbnailSize);
			Vec2f bottomRectMax = contentRegionStart + Vec2f(imageSize.x, bottomRectHeight) * thumbnailSize;
			drawList->AddRectFilled(bottomRectMin, bottomRectMax, thumbnailClicked ? clickedColor : thumbnailHovered ? hoveredColor : 4279834905, cornerRounding, 192);

			static bool clicked = false;
			//Content
			//Resource Name
			std::string name = "AAAAAAAAAAAAA";
			const Vec2f textSize = ImGui::CalcTextSize(name.c_str());
			if (!clicked)
			{
				ImGui::PushID(779144781);
				Vec2f textPos = currentPos + Vec2f((rectSize.x - textSize.x) * 0.5f, rectSize.y + textSize.y * 3.f);
				ImGui::SetCursorPos(textPos);
				ImGui::TextUnformatted(name.c_str());
				if (ImGui::IsItemClicked())
					clicked = true;
				ImGui::PopID();
			}

			//Resource Type
			ImGui::PushID(705220297);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.622549f, 0.622549f, 0.622549f, 1.000000));
			std::string type = "Type";
			Vec2f typePos = currentPos + Vec2f(15, 205.f) * thumbnailSize;
			ImGui::SetCursorPos(typePos);
			ImGui::TextUnformatted(type.c_str());
			ImGui::PopStyleColor(1);
			ImGui::PopID();

			if (clicked) {
				//##Input
				ImGui::PushID(579442659);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.000000, 1.000000, 1.000000, 0.540000));
				Vec2f inputPos = currentPos + Vec2f(8.f * thumbnailSize, rectSize.y + textSize.y * 3.f);
				ImGui::SetCursorPos(inputPos);
				ImGui::SetNextItemWidth(rectSize.x - 8 * thumbnailSize);
				std::string variable579442659 = "";
				ImGui::InputText("##Input", &variable579442659, 0);
				if (!ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
					clicked = false;
				ImGui::PopStyleColor(1);
				ImGui::PopID();
			}
			thumbnailHovered = !clicked && ImGui::IsMouseHoveringRect(contentRegionStart, contentRegionStart + shadowSize * thumbnailSize);
			if (thumbnailHovered)
			{
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
					thumbnailClicked = true;
			}
			j++;
		}
		ImGui::SetCursorPosY(2000.f);
		ImGui::Button("##");
	}
	ImGui::End();
	ImGui::Begin("Debug");
	ImGui::DragFloat("pos", &pos);
	ImGui::End();
#endif
}

void Canvas::DisplayObject(std::shared_ptr<Object> object, size_t& index) const
{
	if (!object->p_enable)
		return;
	object->p_id = index;
	if (!m_isStatic) {
		const Vec2f value = object->GetPosition() + ImGui::GetWindowContentRegionMin();
		object->p_realPos = value;
	}
	else
	{
		object->p_realPos = ImGui::GetCursorPos() + object->GetPosition();
	}
	ImGui::SetCursorPos(object->p_realPos);

	int styleColorCount = 0;
	for (const auto& style : object->p_styleColors)
	{
		style.Use(styleColorCount);
	}
	int styleVarCount = 0;
	for (const auto& p_styleVar : object->p_styleVars)
	{
		p_styleVar->ApplyStyle(styleVarCount);
	}

	ImGui::BeginDisabled(object->p_disabled);
	ImGui::PushID(object->p_uuid);
	object->Draw();
	ImGui::PopID();
	object->PostDraw(Editor::IsUserMode());

	if (object->Begin())
	{
		for (auto& child : object->p_children)
		{
			DisplayObject(child.lock(), ++index);
		}
		object->End();
	}
	object->PostEnd();

	ImGui::PopStyleColor(styleColorCount);
	ImGui::PopStyleVar(styleVarCount);
	ImGui::EndDisabled();
}

void Canvas::Update() const
{
	if (Editor::IsUserMode())
		return;
	if (m_hoveredObject && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		m_hoveredObject->p_position = m_hoveredObject->p_position + ImGui::GetIO().MouseDelta;
	}
}

