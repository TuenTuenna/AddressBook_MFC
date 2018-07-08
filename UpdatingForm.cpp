//UpdatingForm.cpp
#include "UpdatingForm.h"
#include "AddressBook.h"
#include "FindingForm.h"
#include <afxcmn.h>
#include <afxdb.h>
#include <stdlib.h>



BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


UpdatingForm::UpdatingForm(CWnd *parent)
	:CDialog(UpdatingForm::IDD, parent) {
	this->addressBook = NULL;

}

// 1. �����찡 ������ ��
BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog(); // �ڵ� ���뼺
	 // 1.1. �ּҷ��� �غ��Ѵ�.
	this->addressBook = new AddressBook;

	// 1.2. �ּҷϿ� �����Ѵ�.
	this->Load();

	// 1.3. ����Ʈ�信 ����� �����.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(0, "��ȣ", LVCFMT_CENTER, 50);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(1, "����", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(2, "�ּ�", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(4, "�̸����ּ�", LVCFMT_CENTER, 100);

	// 1.4. ����Ʈ �信 �׸���� �߰��Ѵ�.
	Long length = this->addressBook->GetLength();
	Long index = 0;
	CString number;
	while (index < length) {
		number.Format("%d", index + 1);
		Personal personal = this->addressBook->GetAt(index);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertItem(index, number);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 1, personal.GetName().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 2, personal.GetAddress().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
		index++;
	}

	// 1.5. ���� �� �޺��ڽ��� ������ ����� �����.
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("naver.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("nate.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("daum.net");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("google.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("�����Է�");

	return FALSE;
}

// 2. �����ϱ� ��ư�� Ŭ������ ��
void UpdatingForm::OnRecordButtonClicked() {

	// 2.1. ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �д´�.
	CString name;
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	CString address;
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	CString telephoneNumber;
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	CString emailAddress;
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	CString domain;
	this->GetDlgItem(IDC_COMBO_DOMAIN)->GetWindowText(domain);
	emailAddress.Format("%s@%s", emailAddress, domain);

	// 2.2. �ּҷϿ� �����Ѵ�.
	Long index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);

	// 2.3. �����ͺ��̽��� �����Ѵ�.
	this->Insert(index);

	// 2.3. ����Ʈ�信 �׸��� �߰��Ѵ�.
	Personal personal = this->addressBook->GetAt(index);
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertItem(index, number);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}

// 3. ã�� ��ư�� Ŭ������ ��
void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

// 4. ��ġ�� ��ư�� Ŭ������ ��
void UpdatingForm::OnCorrectButtonClicked() {
	// 4.1. ������ �д´�.
	CString address;
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	CString telephoneNumber;
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	CString emailAddress;
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	CString domain;
	this->GetDlgItem(IDC_COMBO_DOMAIN)->GetWindowText(domain);

	// 4.2. ����Ʈ ���� ���õ� �׸��� ��ġ�� �д´�.
	Long index = (Long)(((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark());

	// 4.3. �ּҷ��� ��ģ��.
	emailAddress.Format("%s@%s", emailAddress, domain);
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
	Personal personal = this->addressBook->GetAt(index);

	// 4.4. ������ ���̽����� �����Ѵ�.
	this->Update(index);

	// 4.5. ����Ʈ�信�� �׸��� �������´�.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}

// 5. ����� ��ư�� Ŭ������ ��
void UpdatingForm::OnEraseButtonClicked() {
	// 5.1. ����Ʈ �信�� ���õ� ��ġ�� �д´�.
	Long lvIndex = (Long)(((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark());

	// 5.2. �ּҷϿ��� �����.
	Long index = this->addressBook->Erase(lvIndex);

	// 5.3. ������ ���̽����� �����.
	this->Delete(index);

	// 5.4. ����Ʈ �信 �ش� �׸��� �����.
	if (index == -1) {
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->DeleteItem(lvIndex);
	}
	// 5.5. �ش� �׸� ���� ��ȣ���� �����Ѵ�.
	CString number;
	while (lvIndex < this->addressBook->GetLength()) {
		number.Format("%d", lvIndex + 1);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(lvIndex, 0, number);
		lvIndex++;
	}
}

// 6. �����ϱ� ��ư�� Ŭ������ ��
void UpdatingForm::OnArrangeButtonClicked() {
	// 6.1. �ּҷ��� �����Ѵ�.
	this->addressBook->Arrange();

	// 6.2. ����Ʈ ���� ��� �׸��� �����.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->DeleteAllItems();

	// 6.3. ����Ʈ �信 �ּҷ��� �߰��Ѵ�.
	Long length = this->addressBook->GetLength();
	Long index = 0;
	CString number;
	while (index < length) {
		number.Format("%d", index + 1);
		Personal personal = this->addressBook->GetAt(index);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertItem(index, number);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 1, personal.GetName().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 2, personal.GetAddress().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
		index++;
	}
}

// 7. ����Ʈ ���� �׸���� ���� Ŭ������ ��
void UpdatingForm::OnListViewItemButtonClicked(NMHDR* pNotifyStructure, LRESULT *result) {
	// 7.1. ����Ʈ �信 ���õ� ��ġ�� �д´�.
	Long lvIndex = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark();
	// 7.2. ����Ʈ �信 ���õ� �׸��� �д´�.
	CString name = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 1);
	CString address = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 2);
	CString telephoneNumber = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 3);
	CString emailAddress = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 4);
	// 7.3. ���ο� ���� �׸��� ���´�.
	this->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	this->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString standard("");
	Long length;
	Long i = 0;
	while (standard != "@") {
		standard = emailAddress.Mid(i, 1);
		i++;
	}
	length = emailAddress.GetLength();
	CString domain = emailAddress.Right(length - i);
	emailAddress = emailAddress.Left(i-1);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	this->GetDlgItem(IDC_COMBO_DOMAIN)->SetWindowText(domain);
}

// 8. �ݱ� ��ư�� Ŭ������ ��
void UpdatingForm::OnClose() {
	// 8.1. �ּҷ��� ������ ���̽��� �����Ѵ�.
	// 8.2. �ּҷ��� �����.
	if (this->addressBook != NULL) {
		this->Save();
		delete this->addressBook;
	}
	// 8.3. �����츦 �ݴ´�.
	this->EndDialog(0);
}


// ����Ʈ ���̽� �Լ�����
CString UpdatingForm::GetCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=mysql"); // Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); // Request
	CString code("P0000");
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
	}
	code = code.Right(4);
	int number = _ttoi(code);
	code.Format("P%04d",number+1);
	rs.Close();
	db.Close();
	return code;
}

void UpdatingForm::Load() {
	CDatabase db;
	CRecordset rs(&db); // SELECT �� ���� ���
	CString sql = "SELECT Personal.name, Personal.address, Personal.telephoneNumber, Personal.emailAddress FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=mysql"); // Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); // Request/ Response
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
		rs.MoveNext();
	}
	rs.Close();  // Disconnection
	db.Close(); // Disconnection
}

void UpdatingForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	CString sql = "SELECT Personal.code FROM Personal;"; // Connection
	db.OpenEx("DSN=AddressBook;UID=root;PWD=mysql"); // Request / Response
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql); // Request
	Long i = 0;
	Personal personal;
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		rs.GetFieldValue((short)0, code);
		sql.Format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, personal.GetName().c_str(), personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
		db.ExecuteSQL(sql);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}

void UpdatingForm::Insert(Long index) {
	CDatabase db;
	CString sql;
	Personal personal = this->addressBook->GetAt(index);
	sql.Format("INSERT INTO Personal(code,name,address, telephoneNumber, emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)this->GetCode(), personal.GetName().c_str(), personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
	db.OpenEx("DSN=AddressBook;UID=root;PWD=mysql");
	db.ExecuteSQL(sql);
	db.Close();
}

void UpdatingForm::Delete(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=mysql");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	Long number = 0;
	while (!rs.IsEOF() && number <= index) {
		rs.GetFieldValue((short)0, code);
		number++;
		rs.MoveNext();
	}
	sql.Format("DELETE FROM Personal WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

void UpdatingForm::Update(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=mysql");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	Long number = 0;
	while (!rs.IsEOF() && number <= index) {
		rs.GetFieldValue((short)0, code);
		number++;
		rs.MoveNext();
	}
	Personal personal = this->addressBook->GetAt(index);
	sql.Format("UPDATE Personal SET address='%s', telephoneNumber='%s', emailAddress='%s' WHERE code='%s';", personal.GetAddress().c_str(), personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}