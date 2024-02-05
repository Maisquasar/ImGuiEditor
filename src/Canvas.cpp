#include "Canvas.h"
#include "Object/IObject.h"

#include "Editor.h"
#include "Hierarchy.h"
#include "Inspector.h"

void Canvas::Initialize()
{
}

void Canvas::Draw() const
{
	static float pos = 0;
	static Hierarchy* hierarchy = Editor::Get()->GetHierarchy();
	//ImGui::ShowStyleEditor();
	//ImGui::ShowMetricsWindow();
	if (ImGui::Begin("Canvas", nullptr))
	{
		size_t index = 0;
		for (const auto& weakObject : hierarchy->GetRoot()->p_children)
		{
			DisplayObject(weakObject.lock(), ++index);
		}
	}
	ImGui::End();

	ImGui::Begin("dEBUGGGG");

	//TabBar
	ImGui::PushID(2068073198);
	if (ImGui::BeginTabBar("TabBar"))
	{
		//Tab 1
		ImGui::PushID(1155343973);
		if (ImGui::BeginTabItem("Tab 1"))
		{
			//Shopping list
			ImGui::PushID(543289989);
			if (ImGui::TreeNodeEx("Shopping list", 0))
			{
				//Text
				ImGui::PushID(496575351);
				ImGui::TextUnformatted("Apple");
				ImGui::PopID();
				//Text
				ImGui::PushID(788791217);
				ImGui::TextUnformatted("Pear");
				ImGui::PopID();
				//Text
				ImGui::PushID(825674460);
				ImGui::TextUnformatted("Banana");
				ImGui::PopID();
				ImGui::TreePop();
			}
			ImGui::PopID();
			//Empty
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.480000, 0.263529, 0.160000, 0.540000));
			//Drag
			ImGui::PushID(527898738);
			int variable527898738 = 0;
			ImGui::DragInt("Drag", &variable527898738, 1.000000, 0, 0);
			ImGui::PopID();
			//Drag
			ImGui::PushID(79414360);
			int variable79414360 = 0;
			ImGui::DragInt("Drag", &variable79414360, 1.000000, 0, 0);
			ImGui::PopID();
			ImGui::PopStyleColor(1);
			ImGui::EndTabItem();
		}
		ImGui::PopID();
		//Tab 2
		ImGui::PushID(612745087);
		if (ImGui::BeginTabItem("Tab 2"))
		{
			//ComboBox
			ImGui::PushID(384558373);
			if (ImGui::BeginCombo("ComboBox", "Preview Text"))
			{
				//Preview Text
				ImGui::PushID(491695825);
				ImGui::TextUnformatted("A");
				ImGui::PopID();
				//Text 2
				ImGui::PushID(1363185373);
				ImGui::TextUnformatted("B");
				ImGui::PopID();
				ImGui::EndCombo();
			}
			ImGui::PopID();
			//Slider Example
			ImGui::PushID(1424070549);
			int variable1424070549 = 0;
			ImGui::SliderInt("Slider Example", &variable1424070549, 0, 100, "%d", 0);
			ImGui::PopID();
			//Button
			ImGui::PushID(975429984);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.000000, 0.151961, 0.151961, 0.400000));
			ImGui::Button("Button");
			ImGui::PopStyleColor(1);
			ImGui::PopID();
			//Group
			ImGui::PushID(1990026100);
			ImGui::BeginGroup();
			{
				//Drag
				ImGui::PushID(925083771);
				int variable925083771 = 0;
				ImGui::DragInt("Drag", &variable925083771, 1.000000, 0, 0);
				ImGui::PopID();
				//Input
				ImGui::PushID(1413070171);
				std::string variable1413070171 = "";
				ImGui::InputText("Input", &variable1413070171, 0);
				ImGui::PopID();
				//Checkbox
				ImGui::PushID(1817489435);
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.000000, 1.000000, 1.000000, 1.000000));
				bool variable1817489435 = 0;
				ImGui::Checkbox("Checkbox", &variable1817489435);
				ImGui::PopStyleColor(1);
				ImGui::PopID();
			}
			ImGui::EndGroup();
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()
				, 4294967295, 0.000000
				, ImDrawFlags_None, 0.000000);
			ImGui::PopID();
			ImGui::EndTabItem();
		}
		ImGui::PopID();
	}
	ImGui::PopID();
	ImGui::End();
}

void Canvas::DisplayObject(std::shared_ptr<Object> object, size_t& index) const
{
	if (!object->p_enable)
		return;
	object->p_id = index;
	if (!m_isDynamic) {
		const Vec2f anchorPosition = (Vec2f)ImGui::GetWindowContentRegionMin() + object->p_anchorPosition *
			((Vec2f)ImGui::GetWindowContentRegionMax() + object->GetPosition() - object->p_realSize - (Vec2f)ImGui::GetWindowContentRegionMin());
		const Vec2f value = object->GetPosition() + anchorPosition;
		object->p_realPos = value;
	}
	else
	{
		const Vec2f anchorPosition = (Vec2f)ImGui::GetCursorPos() + object->p_anchorPosition *
			((Vec2f)ImGui::GetWindowContentRegionMax() + object->GetPosition() - object->p_realSize - (Vec2f)ImGui::GetCursorPos());
		object->p_realPos = object->GetPosition() + anchorPosition;
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

