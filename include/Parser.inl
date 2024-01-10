#pragma once
#include "Parser.h"

	void Serializer::AddLine(const std::string& key, const std::string& value)
	{
		m_content << m_tab << "[" << key << "] : " << value << '\n';
	}

	void Serializer::AddLine(const std::string& line)
	{
		m_content << m_tab << line << '\n';
	}

	void Serializer::PushTab()
	{
		m_tab.push_back(' ');
	}

	void Serializer::PopTab()
	{
		m_tab.pop_back();
	}
