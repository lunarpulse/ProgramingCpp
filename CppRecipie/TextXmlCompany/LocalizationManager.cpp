#include "LocalizationManager.h"
#include "rapidxml.hpp"
//#include <iostream>

namespace Localization
{
	Manager::Manager()
	{
		std::ifstream xmlStringFile{ "xmlFile.xml"s };
		xmlStringFile.seekg(0, std::ios::end);
		uint32_t size{ static_cast<uint32_t>(xmlStringFile.tellg()) + 1 };
		char* buffer{ new char[size]{} };
		xmlStringFile.seekg(0, std::ios::beg);
		xmlStringFile.read(buffer, size);
		xmlStringFile.close();
		 //These two lines are responsible for initializing the XML data structure from the contents of the file.
		rapidxml::xml_document<> document;
		document.parse<0>(buffer);
		 //those string literals can be dynamically assigned.
		rapidxml::xml_node<>* workbook{ document.first_node("Workbook") };
		if (workbook != nullptr)
		{
			rapidxml::xml_node<>* worksheet{ workbook->first_node("ss:Worksheet") };
			if (worksheet != nullptr)
			{
				rapidxml::xml_node<>* table{ worksheet->first_node("Table") };
				if (table != nullptr)
				{
					rapidxml::xml_node<>* row{ table->first_node("Row") };
					while (row != nullptr)
					{
						uint32_t stringId{ UINT32_MAX };
						 
						rapidxml::xml_node<>* cell{ row->first_node("Cell") };
						if (cell != nullptr)
						{
							rapidxml::xml_node<>* data{ cell->first_node("Data") };
							if (data != nullptr)
							{
								stringId = static_cast<uint32_t>(atoi(data->value()));
								x++;
							}
						}
								 
						if (stringId != UINT32_MAX)
						{
							uint32_t languageIndex{ 0 };
							 
							cell = cell->next_sibling("Cell");
							while (cell != nullptr)
							{
								rapidxml::xml_node<>* data = cell->first_node("Data");
								if (data != nullptr)
								{
									
									m_StringPacks[languageIndex++][stringId] = data->value();
									y++;
									//std::cout <<  stringId <<", "<< m_StringPacks[languageIndex-1][stringId] << std::endl;
								}
									cell = cell->next_sibling("Cell");
							}
						}
					 
						row = row->next_sibling("Row");
					}
				}
			}
		}
	}
	
	void Manager::SetColumn(Column column)
	{
		m_CurrentStringPack = &(m_StringPacks[static_cast<uint32_t>(column)]);
	}

	std::string Manager::GetString(StringID stringId) const
	{
		std::stringstream resultStream;
		resultStream << "!!!"s;
		resultStream << stringId;
		resultStream << "!!!"s;
		std::string result{ resultStream.str() };
		 
		auto iter = m_CurrentStringPack->find(stringId);
		if (iter != m_CurrentStringPack->end())
		{
		result = iter->second;
		}
		
		return result;
	}
}