#pragma once

#include "serviceid.h"
#include <tplib/include/service.h>
#include <string>
#include <vector>
#include <map>

struct Medicine
{
	std::wstring name;
	double price;
	double stock;               // 存货
	std::wstring pinyin;
	std::wstring tags;
	std::wstring description;
	double cost;                // 成本
	std::wstring related;
};

class MedicineMgr : public tp::service_impl<SID_MedicineMgr>
{
public:
	/// 通过名字获取药品信息
	const Medicine* GetMedicine(const std::wstring& name) const;
	/// 检索药品信息
	std::vector<const Medicine*> Search(const std::wstring& str) const;
	/// 调用excel编辑
	void ShellEditMedicineData();

	MedicineMgr();
	~MedicineMgr();

private:
	std::vector<Medicine> m_medicines;
	std::map<std::wstring, const Medicine*> m_map;
	
	std::wstring m_path;

private:
	void LoadMedicineInfo();
	void SaveMedicineInfo();
	void Clear();
};

DEFINE_SERVICE(MedicineMgr, L"药物管理器");

