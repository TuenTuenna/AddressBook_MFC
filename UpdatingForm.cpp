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

// 1. 윈도우가 생성될 때
BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog(); // 코드 재사용성
	 // 1.1. 주소록을 준비한다.
	this->addressBook = new AddressBook;

	// 1.2. 주소록에 적재한다.
	this->Load();

	// 1.3. 리스트뷰에 헤더를 만든다.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(0, "번호", LVCFMT_CENTER, 50);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(2, "주소", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 100);

	// 1.4. 리스트 뷰에 항목들을 추가한다.
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

	// 1.5. 도메 인 콤보박스에 도메인 목록을 만든다.
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("naver.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("nate.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("daum.net");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("google.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_DOMAIN)))->AddString("직접입력");

	return FALSE;
}

// 2. 기재하기 버튼을 클릭했을 때
void UpdatingForm::OnRecordButtonClicked() {

	// 2.1. 성명, 주소, 전화번호, 이메일주소를 읽는다.
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

	// 2.2. 주소록에 기재한다.
	Long index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);

	// 2.3. 데이터베이스에 삽입한다.
	this->Insert(index);

	// 2.3. 리스트뷰에 항목을 추가한다.
	Personal personal = this->addressBook->GetAt(index);
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertItem(index, number);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}

// 3. 찾기 버튼을 클릭했을 때
void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

// 4. 고치기 버튼을 클릭했을 때
void UpdatingForm::OnCorrectButtonClicked() {
	// 4.1. 개인을 읽는다.
	CString address;
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	CString telephoneNumber;
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	CString emailAddress;
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	CString domain;
	this->GetDlgItem(IDC_COMBO_DOMAIN)->GetWindowText(domain);

	// 4.2. 리스트 뷰의 선택된 항목의 위치를 읽는다.
	Long index = (Long)(((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark());

	// 4.3. 주소록을 고친다.
	emailAddress.Format("%s@%s", emailAddress, domain);
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
	Personal personal = this->addressBook->GetAt(index);

	// 4.4. 데이터 베이스에서 갱신한다.
	this->Update(index);

	// 4.5. 리스트뷰에서 항목을 고쳐적는다.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}

// 5. 지우기 버튼을 클릭했을 때
void UpdatingForm::OnEraseButtonClicked() {
	// 5.1. 리스트 뷰에서 선택된 위치를 읽는다.
	Long lvIndex = (Long)(((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark());

	// 5.2. 주소록에서 지운다.
	Long index = this->addressBook->Erase(lvIndex);

	// 5.3. 데이터 베이스에서 지운다.
	this->Delete(index);

	// 5.4. 리스트 뷰에 해당 항목을 지운다.
	if (index == -1) {
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->DeleteItem(lvIndex);
	}
	// 5.5. 해당 항목 이후 번호들을 수정한다.
	CString number;
	while (lvIndex < this->addressBook->GetLength()) {
		number.Format("%d", lvIndex + 1);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(lvIndex, 0, number);
		lvIndex++;
	}
}

// 6. 정리하기 버튼을 클릭했을 때
void UpdatingForm::OnArrangeButtonClicked() {
	// 6.1. 주소록을 정리한다.
	this->addressBook->Arrange();

	// 6.2. 리스트 뷰의 모든 항목을 지운다.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->DeleteAllItems();

	// 6.3. 리스트 뷰에 주소록을 추가한다.
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

// 7. 리스트 뷰의 항목들을 더블 클릭했을 때
void UpdatingForm::OnListViewItemButtonClicked(NMHDR* pNotifyStructure, LRESULT *result) {
	// 7.1. 리스트 뷰에 선택된 위치를 읽는다.
	Long lvIndex = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark();
	// 7.2. 리스트 뷰에 선택된 항목을 읽는다.
	CString name = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 1);
	CString address = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 2);
	CString telephoneNumber = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 3);
	CString emailAddress = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(lvIndex, 4);
	// 7.3. 개인에 읽은 항목을 적는다.
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

// 8. 닫기 버튼을 클릭했을 때
void UpdatingForm::OnClose() {
	// 8.1. 주소록을 데이터 베이스에 저장한다.
	// 8.2. 주소록을 지운다.
	if (this->addressBook != NULL) {
		this->Save();
		delete this->addressBook;
	}
	// 8.3. 윈도우를 닫는다.
	this->EndDialog(0);
}


// 데이트 베이스 함수정의
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
	CRecordset rs(&db); // SELECT 할 때만 사용
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