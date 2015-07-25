#pragma once
 
#include <array>
#include <cinttypes>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <assert.h>

namespace Localization
{
	using StringID = int32_t;
	using namespace std::literals;
	
	enum class Column
	{
		SYMBOL,
		COMPANYNAME,
		Number
	};
	 
	//const StringID STRING_COLOR{ 0 };
	 
	class Manager
	{
	private:
		
		using Strings = std::unordered_map<StringID, std::string>;
		using StringPacks =
		std::array<Strings, static_cast<size_t>(Column::Number)>;
		 
		StringPacks m_StringPacks;
		Strings* m_CurrentStringPack{ nullptr };
		 
		uint32_t m_LanguageIndex;
		
	public:
		static uint32_t  x;
		static uint32_t  y;
		Manager();
		 
		void SetColumn(Column column);
		 
		std::string GetString(StringID stringId) const;
	};

}