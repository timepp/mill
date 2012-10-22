#include "stdafx.h"
#include "medicinemgr.h"
#include "pathmgr.h"
#include <excelformat/ExcelFormat.h>
#include <tplib/include/pinyin.h>
#include "hlp.h"

MedicineMgr::MedicineMgr()
{
	m_path = tp::servicemgr::get<PathMgr>()->GetDataDir() + L"\\medicine.xls";
	LoadMedicineInfo();
}

MedicineMgr::~MedicineMgr()
{
	SaveMedicineInfo();
	Clear();
}

void MedicineMgr::Clear()
{
	m_map.clear();
	m_medicines.clear();
}

const Medicine* MedicineMgr::GetMedicine(const std::wstring& name) const
{
	auto it = m_map.find(name);
	if (it == m_map.end())
	{
		return NULL;
	}
	return it->second;
}

std::vector<const Medicine*>  MedicineMgr::Search(const std::wstring& str) const 
{
	std::vector<const Medicine*> ret;

	for (auto it = m_medicines.begin(); it != m_medicines.end(); ++it)
	{
		const Medicine* m = &(*it);
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

void MedicineMgr::LoadMedicineInfo()
{
	Clear();

	tp::pinyintool pyt;

	ExcelFormat::BasicExcel excel;
	hlp::ExcelLoad(excel, m_path);
	ExcelFormat::BasicExcelWorksheet* sheet = excel.GetWorksheet(0);

	/// XLS文件里的第一行是标题，不读取
	for (int i = 1; i < sheet->GetTotalRows(); i++)
	{
		Medicine m;
		hlp::SafeAssign(m.name, sheet->Cell(i, 0));
		m.price = sheet->Cell(i, 1)->GetDouble();
		m.stock = sheet->Cell(i, 2)->GetDouble();
		hlp::SafeAssign(m.pinyin, sheet->Cell(i, 3));
		hlp::SafeAssign(m.tags, sheet->Cell(i, 4));
		hlp::SafeAssign(m.description, sheet->Cell(i, 5));
		m.cost = sheet->Cell(i, 6)->GetDouble();
		hlp::SafeAssign(m.related, sheet->Cell(i, 7));

		if (m.pinyin.empty())
		{
			m.pinyin = pyt.pinyin_of_string(m.name.c_str());
		}

		m_medicines.push_back(m);
	}

	// 构造map
	for (auto it = m_medicines.begin(); it != m_medicines.end(); ++it)
	{
		const Medicine* m = &(*it);
		m_map[m->name] = m;
	}
}

void MedicineMgr::SaveMedicineInfo()
{
	// 目前不会在程序中更改medicine信息，所以不会保存
}

void MedicineMgr::ShellEditMedicineData()
{
	hlp::ShellExecuteAndWait(m_path.c_str(), NULL, NULL);
	LoadMedicineInfo();
}
