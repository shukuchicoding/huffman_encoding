#include <bits/stdc++.h>

using namespace std;

//variable for task 1
int base; //co so cua ma huffman
unordered_map <string, double> Source; //nguon ban dau, gom cac tin va phan bo xac suat
unordered_map <string, string> Code; //ma Huffman cua nguon
unordered_map <string, string> Code1; //ma Huffman cua nguon
unordered_map <string, bool> exist;//Luu tru su ton tai cua nguon tin

//-----------------------------TASK_1-----------------------------
//cau truc so sanh xac suat trong hang doi uu tien
struct CustomComparator {
    bool operator()(const pair <string, double> &p, const pair <string, double> &q) {
        return p.second > q.second;
    }
};
//dat lai du lieu
void reset_data(){
	base = 0;
	unordered_map<string, double>().swap(Source);
	unordered_map<string, string>().swap(Code);
}
//tinh tong xac suat
double sum_probs(unordered_map <string, double> Source){
	double sum = 0;
	for (auto pair : Source) {
		sum += pair.second;
	}
	return sum;
}
//hien thi nguon
void show_info_source(){
	cout << "Total probability is 1. You have finished inputting. Your source is below:\n";
	cout << "+--------------------------+\n";
	cout << " Information	Probability\n";
	cout << "+--------------------------+\n";
	for (auto pair : Source) {
		cout << " " << pair.first << "\t\t" << pair.second << '\n';	
		cout << "+--------------------------+\n";
	}
}
//kiem tra tong xac suat
void check_input(string Info, double Prob){
	if (sum_probs(Source) + Prob > 1){
		cout << "Total probability of informations is greater than 1. Try again:\n";
	}
	else {
		Source[Info] = Prob;
		Code[Info] = "";
	}	
}
//nhap nguon
void input_source(){
	reset_data();
	cout << "Input your information source\n";
	while (sum_probs(Source) != 1) {
		cout << "\tInformation " << Source.size() + 1 << ": ";
		string info;
		cin >> info;
		exist[info] = true;
		cout << "\tProbability " << Source.size() + 1 << ": ";
		double prob;
		cin >> prob;
		check_input(info, prob);
	}
	show_info_source();
}
//tao ma huffman
void generate_huffman_code(){
	priority_queue <pair <string, double>, vector <pair <string, double>>, CustomComparator> source; 
	for (auto pair : Source) {
		source.push({pair.first, pair.second});
	}
	
	unordered_map <string, vector <pair <string, string>>> adj;	
	int num_r_info = Source.size();
	cout << "Base of Huffman code: ";
	cin >> base;
	int a = (num_r_info-base)/(base-1);
	if ((num_r_info-base) % (base-1)) a++;
	int num_newsource = base + a*(base-1);
	int num_i_info = num_newsource - num_r_info;
	for (int i = 1; i <= num_i_info; i++) {
		source.push({"i" + to_string(i+1), 0});
	}

	while (source.size() > 1) {
		double tmp_prob = 0;
		string tmp_info = "";
		for (int i = 0; i < base; i++) {
			tmp_info += source.top().first;
			tmp_prob += source.top().second;
		}
		for (int i = 0; i < base; i++) {
			adj[source.top().first].push_back({tmp_info, to_string(i)});
			source.pop();
		}
		source.push({tmp_info, tmp_prob});
	}
	
	for (auto pair : Source) {
		string p = pair.first;
		while (adj[p].size()) {
			Code[pair.first] = adj[p].front().second + Code[pair.first];
			p = adj[p].front().first;
		}
	}
	
	cout << "Huffman code has been generated!\n";
	cout << "+---------------------------+\n";
	cout << " Information	Huffman code\n";
	cout << "+---------------------------+\n";
	for (auto pair : Code) {
		Code1[pair.second]=pair.first;
		cout << " " << pair.first << "\t\t" << pair.second << '\n';
		cout << "+---------------------------+\n";
	}
}

void show_huffman_code(){
	if (!Source.size()) cout << "Huffman code does not exist! Try again!\n";
	else {
		cout << "The Huffman code of your source is below:\n";
		cout << "+---------------------------+\n";
		cout << " Information	Huffman code\n";
		cout << "+---------------------------+\n";
		for (auto pair : Code) {
			cout << " " << pair.first << "\t\t" << pair.second << '\n';
			cout << "+---------------------------+\n";
		}
	}
}
void input_processor(){
	input_source();
	generate_huffman_code();
}
//---------------------------END_TASK_1---------------------------

//-------------------------BEGIN_TASK_2---------------------------

string sequence; // bản tin cần mã hóa
string huffman_sequence;// bản tin sau khi mã hóa

void input_sequence(){
	cout << "Input sequence is: ";
	getline(cin,sequence);
	
}

//Kiểm tra sự tồn tại của các tin trong chuỗi tin được nhập vào 
bool check(string sequence){
	for (int i =0;i<sequence.length();i++){
		if (exist[sequence.substr(i,1)] == false)
			return false;
	}
	return true;
}

void sequence_process(){
	input_sequence();
	while (!check(sequence)){
		cout<<"Your sequence contains (an) unidentified character(s). Please check again!\n";
		input_sequence();
	}

	huffman_sequence="";
	for (int i=0;i< sequence.length(); i++){
		string tmp = sequence.substr(i,1);
		huffman_sequence += Code[tmp];
	}
	cout<<"Ma hufman la:" << huffman_sequence<<endl;
}

//---------------------------END_TASK_2---------------------------

//-------------------------BEGIN_TASK_3---------------------------
string mahuffman;//luu tru ma huffman
void input(){//ham nhap ma huffman
	cout<<"Nhap ma huffman: ";
//	cin.ignore();
	getline(cin,mahuffman);
	
}
//giai ma huffman
void decodeMessage(string code) {
    string decodedMessage = "";
    int d=code.length();
    string str="";
    for(int i=0;i<d;++i){
    	
    	
    		str=str+code[i];
    		auto it= Code1.find(str);
    		
    		if(it!=Code1.end()){
    			decodedMessage=decodedMessage+it->second;
    			str="";
			}
		
		//cout<<decodedMessage<<" ";
		
	}
    cout<<"Giai ma huffman: "<<decodedMessage<<endl;
    
}
//---------------------------END_TASK_3---------------------------


int main(){
	input_processor();
	show_huffman_code();

	cin.ignore();//tránh trôi lệnh
	sequence_process();
	
	
	decodeMessage(huffman_sequence);
	

	
	
	return 0;
}

