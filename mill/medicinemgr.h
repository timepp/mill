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
	double stock;               // ���
	std::wstring pinyin;
	std::wstring tags;
	std::wstring description;
	double cost;                // �ɱ�
	std::wstring related;
};

class MedicineMgr : public tp::service_impl<SID_MedicineMgr>
{
public:
	/// ͨ�����ֻ�ȡҩƷ��Ϣ
	const Medicine* GetMedicine(const std::wstring& name) const;
	/// ����ҩƷ��Ϣ
	std::vector<const Medicine*> Search(const std::wstring& str) const;
	/// ����excel�༭
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

DEFINE_SERVICE(MedicineMgr, L"ҩ�������");

