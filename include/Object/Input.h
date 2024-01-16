#pragma once
#include "Object/IObject.h"

#include <any>

enum class InputType
{
	Text,
	Double,
	Int,
	Int2,
	Int3,
	Int4,
	Float,
	Float2,
	Float3,
	Float4,
};

static const char* InputTypeEnumToString()
{
	return "Text\0Double\0Int\0Int2\0Int3\0Int4\0Float\0Float2\0Float3\0Float4\0";
}

class Input : public IObject<Input>
{
public:
	Input() = default;
	Input& operator=(const Input& other) = default;
	Input(const Input&) = default;
	Input(Input&&) noexcept = default;
	~Input() override = default;

	void Initialize() override;
	void Draw() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;

	std::string GetTypeName() const override { return "Input"; }
private:
	InputType m_inputType = InputType::Text;
	std::any m_value = std::string("");
	ImGuiInputTextFlags m_flags;

	bool m_textMultiline = false;

};