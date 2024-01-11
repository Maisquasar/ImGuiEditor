#pragma once
#include "pch.h"

class Object;
class Inspector
{
public:
	Inspector() = default;

	void Draw();

	void CopyObject();
	void PasteObject() const;

	bool HasSelected() const { return m_selectedObject.lock() != nullptr; }
	void SetSelected(Object* object);
	Object* GetSelected() const { return m_selectedObject.lock().get(); }

	void DrawSelected() const;
private:
	std::weak_ptr<Object> m_selectedObject;

	std::string m_clipBoard;

};
