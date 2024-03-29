#include "Object/IObject.h"

class Tree : public ScopeObject<Tree>
{
public:
	Tree() = default;
	Tree& operator=(const Tree& other) = default;
	Tree(const Tree&) = default;
	Tree(Tree&&) noexcept = default;
	~Tree() override = default;

	void Initialize() override;
	bool Begin() override;
	void End() override;
	void PostEnd() override;
	void DisplayOnInspector() override;
	void Serialize(std::string& content) const override;
	void Serialize(Serializer& serializer) const override;
	void Deserialize(Parser& parser) override;
	void InternalSerialize(std::string& content) const override;

	std::string GetTypeName() const override { return "Tree"; }
private:
	ImGuiTreeNodeFlags m_flags = 0;
};