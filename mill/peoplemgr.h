#pragma once

#include "serviceid.h"
#include <tplib/include/service.h>
#include <string>
#include <vector>
#include <map>
#include "mill.h"

struct People
{
	std::wstring name;
	std::wstring gender;
	std::wstring contact;
	std::wstring pinyin;
	time_t birthday;
	std::wstring idnumber;
	std::wstring address;
	std::wstring comment;
};

struct Prescription /// 处方
{
	struct MedicineItem
	{
		std::wstring name;
		double dosage;
	};

	std::vector<MedicineItem> medicines;
	int timePerDay;                              // 每天服几次
	int dose;                                    // 每次用量
	std::wstring note;                           // 关于如何服药的建议
};

struct MedicalRecord /// 医疗记录
{
	time_t datetime;                             // 日期
	std::wstring description;                    // 病情描述
	std::wstring diagnose;                       // 诊断结果
	Prescription ps;                             // 处方
};

class PeopleMgr : public tp::service_impl<SID_PeopleMgr>, public SuggestionProvider
{
public:
	/// 通过名字获取人员信息
	People* GetPeople(const std::wstring& name, bool create_new_if_not_exist = false);

	/// 检索人员信息
	std::vector<const People*> Search(const std::wstring& str) const;
	/// 调用excel编辑
	void ShellEditPeopleData();

	virtual std::vector<std::wstring> GetSuggestion(const std::wstring& input);

	PeopleMgr();
	~PeopleMgr();

private:
	std::vector<People> m_peoples;
	std::map<std::wstring, People*> m_map;
	std::wstring m_path;

private:
	void LoadPeopleInfo();
	void SavePeopleInfo();
	void Clear();
	People* AddPeople(const std::wstring& name);
};

DEFINE_SERVICE(PeopleMgr, L"人员信息管理器");
