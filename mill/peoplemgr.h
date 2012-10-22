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

struct Prescription /// ����
{
	struct MedicineItem
	{
		std::wstring name;
		double dosage;
	};

	std::vector<MedicineItem> medicines;
	int timePerDay;                              // ÿ�������
	int dose;                                    // ÿ������
	std::wstring note;                           // ������η�ҩ�Ľ���
};

struct MedicalRecord /// ҽ�Ƽ�¼
{
	time_t datetime;                             // ����
	std::wstring description;                    // ��������
	std::wstring diagnose;                       // ��Ͻ��
	Prescription ps;                             // ����
};

class PeopleMgr : public tp::service_impl<SID_PeopleMgr>, public SuggestionProvider
{
public:
	/// ͨ�����ֻ�ȡ��Ա��Ϣ
	People* GetPeople(const std::wstring& name, bool create_new_if_not_exist = false);

	/// ������Ա��Ϣ
	std::vector<const People*> Search(const std::wstring& str) const;
	/// ����excel�༭
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

DEFINE_SERVICE(PeopleMgr, L"��Ա��Ϣ������");
