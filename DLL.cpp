#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class DLL {
	private:
		class DLL_Node {
			public:
				int num;
				DLL_Node* preNode;
				DLL_Node* NextNode;

				DLL_Node(int data);
				~DLL_Node();
		};
		DLL_Node* first;
		DLL_Node* last;
	public:
		void DLL_AppendBackNode(int data);
		void DLL_AppendFrontNode(int data);
		int DLL_AppendNextNode(int search, int data);
		int DLL_RemoveNode(int data);
		bool Is_Empty();
		int DLL_ReverseNode();
		int DLL_PrintNode();
		DLL();
		~DLL();
};

class StrTok {
	public:
		string str;
		string* tmp;
		void StringSplit(string);
		StrTok();
		~StrTok();
};

int main () {
	DLL test;
	StrTok st;

	while(getline(cin, st.str)) {
		st.StringSplit(" ");
		if(st.tmp[0] == "I") {
			int temp1 = 0, temp2 = 0;
			int minus_flag=0;
			int i = 0;
			if(st.tmp[1][0] == '-') {
				minus_flag=1;
				i++;
			}
			for(i; i< st.tmp[1].length(); i++) {
				temp1 *= 10;
				temp1 += st.tmp[1][i]-'0';
			}
			if(minus_flag) {
				temp1 *= -1;
			}
			minus_flag=0, i=0;

			if(st.tmp[2][0] == '-') {
				minus_flag=1;
				i++;
			}
			for(i; i< st.tmp[2].length(); i++) {
				temp2 *= 10;
				temp2 += st.tmp[2][i]-'0';
			}
			if(minus_flag) {
				temp2 *= -1;
			}
			minus_flag=0;
			if(!test.DLL_AppendNextNode(temp1, temp2)) {
				cout << "error" <<endl;
			}
			else {
				cout<< "done"<<endl;
			}
		}
		else if (st.tmp[0] == "IB") {
			for(int i =1; st.tmp[i] != ""; i++) {
				int minus_flag = 0;
				int j = 0, temp1 =0;
				if(st.tmp[i][0] == '-') {
					minus_flag =1;
					j++;
				}
				for(j; j< st.tmp[i].length(); j++) {
					temp1 *= 10;
					temp1+=st.tmp[i][j]-'0';
				}
				if(minus_flag) {
					temp1 *= -1;
				}
				test.DLL_AppendBackNode(temp1);
			}
			cout << "done" <<endl;
		}
		else if(st.tmp[0] == "IF") {
			int i =0;
			while(st.tmp[i] != "") {
				i++;
			}

			for(--i; i >= 1; i--) {
				int minus_flag = 0;
				int j = 0, temp1 =0;
				if(st.tmp[i][0] == '-') {
					minus_flag =1;
					j++;
				}
				for(j; j< st.tmp[i].length(); j++) {
					temp1 *= 10;
					temp1+=st.tmp[i][j]-'0';
				}
				if(minus_flag) {
					temp1 *= -1;
				}
				test.DLL_AppendFrontNode(temp1);
			}
			cout << "done" <<endl;
		}
		else if(st.tmp[0] == "P") {
			if(test.Is_Empty()) {
				cout << "error" << endl;
			}
			else {
				test.DLL_PrintNode();
			}
		}
		else if(st.tmp[0] == "D") {
			int temp1 = 0;
			int minus_flag=0;
			int i = 0;
			if(st.tmp[1][0] == '-') {
				minus_flag=1;
				i++;
			}
			for(i; i< st.tmp[1].length(); i++) {
				temp1 *= 10;
				temp1 += st.tmp[1][i]-'0';
			}
			if(minus_flag) {
				temp1 *= -1;
			}
			if(!test.DLL_RemoveNode(temp1)){
				cout << "error" <<endl;
			}
			else {
				cout << "done" <<endl;
			}
		}
		else if(st.tmp[0] == "R") {
			if(!test.DLL_ReverseNode()) {
				cout << "error" <<endl;
			}
			else {
				cout << "done" << endl;
			}
		}
	}
	return 0;
}

DLL::DLL_Node::DLL_Node(int data) {
	this->num = data;
	preNode = NULL;
	NextNode = NULL;
}

DLL::DLL() {
	first = new DLL_Node(0);
	last = first;
}

DLL::~DLL() {
	while(!Is_Empty() && last->preNode != first) {
		DLL_Node* remove = last;
		last = last->preNode;
		delete remove;
	}
	if(!Is_Empty()) {
		delete last;
	}
	delete first;
}

DLL::DLL_Node::~DLL_Node() {
	preNode= NULL;
	NextNode= NULL;
}

void DLL::DLL_AppendBackNode(int data){
	DLL_Node* NewNode = new DLL_Node(data);
	last->NextNode = NewNode;
	NewNode->preNode = last;
	last = NewNode;
}

bool DLL::Is_Empty() {
	if (first->NextNode == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void DLL::DLL_AppendFrontNode(int data) {
	DLL_Node* NewNode = new DLL_Node(data);
	NewNode->preNode = first;
	NewNode->NextNode = first->NextNode;
	if(!Is_Empty()) {
		first->NextNode->preNode = NewNode;
	}

	if(Is_Empty()) {
		last = NewNode;
	}

	first->NextNode = NewNode;
}

int DLL::DLL_AppendNextNode(int search, int data) {
	DLL_Node* current = first;

	while(current->NextNode != NULL && current->NextNode->num != search) {
		current = current->NextNode;
	}
	current = current->NextNode; // search가 있는 노드!
	if(current == NULL) {
		return 0;
	}

	DLL_Node* NewNode = new DLL_Node(data);
	NewNode->NextNode = current->NextNode;
	NewNode->preNode = current;

	if( current->NextNode != NULL) {
		current->NextNode->preNode = NewNode;
	}
	current->NextNode = NewNode;
	
	if( last->NextNode == NewNode) {
		last = NewNode;
	}
	return 1;
}

int DLL::DLL_RemoveNode(int data) {
	DLL_Node* current = first;

	while(current->NextNode != NULL && current->NextNode->num != data) {
		current = current->NextNode;
	}
	current = current->NextNode;

	if(current == NULL) {
		return 0;
	}
	
	if(current->NextNode == NULL) {
		last = current->preNode;
	}

	current->preNode->NextNode = current->NextNode;
	if(current->NextNode != NULL) {
		current->NextNode->preNode = current->preNode;
	}
	delete current;

	return 1;
}

int DLL::DLL_ReverseNode() {
	DLL_Node* current = first;

	if(Is_Empty()) {
		return 0;
	}
	else {
		while(last->preNode!=first) {
			current->NextNode = last;
			last = last->preNode;
			last->NextNode->preNode = current;
			last->NextNode = NULL;
			current = current->NextNode;
		}
		current->NextNode = last;
		last->preNode = current;
	}
	return 1;
}

int DLL::DLL_PrintNode() {
	DLL_Node* current = first;

	if(Is_Empty()) {
		return 0;
	}

	else {
		while(current != last) {
			cout << current->NextNode->num;
			if(current->NextNode != last) {
				cout << " ";
			}
			current=current->NextNode;
		}
	}
	cout << endl;
	return 1;
}

void StrTok::StringSplit(string strTok) {
	int cutAt;
	int index=0;
	string* strResult = new string[1002];
	string strOrigin = str;

	while((cutAt=strOrigin.find_first_of(strTok)) != strOrigin.npos) {
		if(cutAt>0) {
			strResult[index++] = strOrigin.substr(0, cutAt);
		}
		strOrigin = strOrigin.substr(cutAt+1);
	}

	if(strOrigin.length() > 0) {
		strResult[index++] = strOrigin.substr(0, cutAt);
	}
	tmp = strResult;
}

StrTok::StrTok() {
	str = "";
	tmp = NULL;
}

StrTok::~StrTok() {
	delete[] tmp;
}
