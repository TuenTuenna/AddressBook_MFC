// FindingForm.cpp
#include"FindingForm.h"
#include<afxcmn.h>
#include"UpdatingForm.h"
#include"AddressBook.h"

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// 생성자
FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}

// 1. 윈도우가 생성될 때
BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	// 1.1. 리스트 뷰 헤더를 만든다.
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(0, "번호", LVCFMT_CENTER, 50);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(2, "주소", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 100);
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 100);
	return FALSE;
}

// 2. 찾기 버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked() {
	CString name;
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "주소록");
	if (indexes != NULL) {
		delete[] indexes;
	}
	updatingForm->addressBook->Find((LPCTSTR)name, &indexes, &count);
	
	((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->DeleteAllItems();
	Long i = 0;
	while (i < count) {
		Personal personal = updatingForm->addressBook->GetAt(indexes[i]);
		CString number;
		number.Format("%d", i + 1);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->InsertItem(i, number);
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		i++;
	}
}

// 3. 리스트 뷰 항목을 더블클릭 했을 때
void FindingForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStructure, LRESULT *result) {
	//리스트뷰에 있는 개인을 읽는다
	int index = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetSelectionMark();
	CString name = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(index, 1);
	CString address = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(index, 2);
	CString telephoneNumber = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(index, 3);
	CString emailAddress = ((CListCtrl*)(this->GetDlgItem(IDC_LIST_PERSONALS)))->GetItemText(index, 4);
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "주소록");
	((updatingForm->GetDlgItem(IDC_EDIT_NAME)))->SetWindowText(name);
	((updatingForm->GetDlgItem(IDC_EDIT_ADDRESS)))->SetWindowText(address);
	((updatingForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)))->SetWindowText(telephoneNumber);
	CString standard("");
	Long length;
	Long i = 0;
	while (standard != "@") {
		standard = emailAddress.Mid(i, 1);
		i++;
	}
	length = emailAddress.GetLength();
	CString domain = emailAddress.Right(length - i);
	emailAddress = emailAddress.Left(i - 1);
	((updatingForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)))->SetWindowText(emailAddress);
	((updatingForm->GetDlgItem(IDC_COMBO_DOMAIN)))->SetWindowText(domain);
	((CListCtrl*)(updatingForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetSelectionMark(this->indexes[index]);
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	this->EndDialog(0);
}

// 4. 닫기 버튼을 클릭했을 때
void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] indexes;
	}this->EndDialog(0);
}