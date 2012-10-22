#include "stdafx.h"
#include "peoplemgr.h"
#include "pathmgr.h"
#include <excelformat/ExcelFormat.h>
#include <tplib/include/pinyin.h>
#include "hlp.h"

PeopleMgr::PeopleMgr()
{
	LOG_FUNCTION();

	m_path = tp::servicemgr::get<PathMgr>()->GetDataDir() + L"\\people.xls";
	LoadPeopleInfo();
}

PeopleMgr::~PeopleMgr()
{
	SavePeopleInfo();
	Clear();
}

void PeopleMgr::Clear()
{
	m_map.clear();
	m_peoples.clear();
}

People* PeopleMgr::GetPeople(const std::wstring& name, bool create_new_if_not_exist)
{
	auto it = m_map.find(name);
	if (it == m_map.end())
	{
		if (create_new_if_not_exist) return AddPeople(name);
		return NULL;
	}
	return it->second;
}

People* PeopleMgr::AddPeople(const std::wstring& name)
{
	People p;
	p.birthday = 0;
	m_peoples.push_back(p);
	People* pp = &m_peoples.back();
	m_map[name] = pp;
	return pp;
}

std::vector<const People*>  PeopleMgr::Search(const std::wstring& str) const 
{
	std::vector<const People*> ret;

	for (auto it = m_peoples.begin(); it != m_peoples.end(); ++it)
	{
		const People* m = &(*it);
		if (tp::pinyintool::fuzzy_match(m->pinyin.c_str(), str.c_str()))
		{
			ret.push_back(m);
			continue;
		}
		if (m->name.length() >= str.length() &&
			m->name.compare(0, str.length(), str.c_str(), str.length()) == 0)
		{
			ret.push_back(m);
			continue;
		}
	}

	return ret;
}

void PeopleMgr::LoadPeopleInfo()
{
	LOG_FUNCTION();

	Clear();

	tp::pinyintool pyt;

	ExcelFormat::BasicExcel excel;

	if (!hlp::FileExists(m_path))
	{
		Log(LL_EVENT, TAG_DEFAULT, L"文件[%s]不存在，新建", m_path.c_str());
		excel.New(1);
		hlp::ExcelSave(excel, m_path);
	}
	else
	{
		hlp::ExcelLoad(excel, m_path);
	}

	ExcelFormat::BasicExcelWorksheet* sheet = excel.GetWorksheet(0);

	for (int i = 1; i < sheet->GetTotalRows(); i++)
	{
		People m;
		int col = 0;
		hlp::SafeAssign(m.name, sheet->Cell(i, 0));
		hlp::SafeAssign(m.gender, sheet->Cell(i, 1));
		hlp::SafeAssign(m.contact, sheet->Cell(i, 2));
		hlp::SafeAssign(m.pinyin, sheet->Cell(i, 3));
		std::wstring datestr;
		hlp::SafeAssign(datestr, sheet->Cell(i, 4));
		m.birthday = 0; //sheet->Cell(i, 4);
		hlp::SafeAssign(m.idnumber, sheet->Cell(i, 5));
		hlp::SafeAssign(m.address, sheet->Cell(i, 6));
		hlp::SafeAssign(m.comment, sheet->Cell(i, 7));

		if (m.pinyin.empty())
		{
			m.pinyin = pyt.pinyin_of_string(m.name.c_str());
		}

		m_peoples.push_back(m);
	}

	// 构造map
	for (auto it = m_peoples.begin(); it != m_peoples.end(); ++it)
	{
		People* m = &(*it);
		m_map[m->name] = m;
	}
}

void PeopleMgr::SavePeopleInfo()
{
	LOG_FUNCTION();

	ExcelFormat::BasicExcel excel;
	hlp::ExcelLoad(excel, m_path);
	ExcelFormat::BasicExcelWorksheet* sheet = excel.GetWorksheet(0);

	int i = 1; /// XLS文件里的第一行是标题，不读取
	for (int j = 0; j < (int)m_peoples.size(); j++, i++)
	{
		const People& p = m_peoples[j];
		sheet->Cell(i, 0)->SetWString(p.name.c_str());
		sheet->Cell(i, 1)->SetWString(p.gender.c_str());
		sheet->Cell(i, 2)->SetWString(p.contact.c_str());
		sheet->Cell(i, 3)->SetWString(p.pinyin.c_str());
		sheet->Cell(i, 4)->SetWString(L"");
		sheet->Cell(i, 5)->SetWString(p.idnumber.c_str());
		sheet->Cell(i, 6)->SetWString(p.address.c_str());
		sheet->Cell(i, 7)->SetWString(p.comment.c_str());
	}

	for (; i < sheet->GetTotalRows(); i++)
	{
		for (int j = 0; j < sheet->GetTotalCols(); j++)
		{
			sheet->EraseCell(i, j);
		}
	}

	hlp::ExcelSave(excel);
}

void PeopleMgr::ShellEditPeopleData()
{
	SavePeopleInfo();
	hlp::ShellExecuteAndWait(m_path.c_str(), NULL, NULL);
	LoadPeopleInfo();
}

std::vector<std::wstring> PeopleMgr::GetSuggestion(const std::wstring& input)
{
	strlist_t ret;
	auto lst = Search(input);
	for (size_t i = 0; i < lst.size(); i++)
	{
		ret.push_back(lst[i]->name);
	}
	return ret;
}
