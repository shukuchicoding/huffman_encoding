#include <bits/stdc++.h>
#include <chrono> //added for timer
using namespace std;
using namespace chrono;

//global variables
int base; //co so cua ma huffman
unordered_map <string, string> Code; //ma Huffman cua nguon

//variable for task 1
unordered_map <string, double> Source; //nguon ban dau, gom cac tin va phan bo xac suat

//variables for task 2, 3
unordered_map <string, string> reverseCode; //ma Huffman cua nguon
unordered_map <string, bool> exist; //luu tru su ton tai cua nguon tin

//-------------------------BEGIN_TASK_1---------------------------
//cau truc so sanh xac suat trong hang doi uu tien
struct CustomComparator
{
    bool operator()(const pair <string, double> &p, const pair <string, double> &q)
    {
        return p.second > q.second;
    }
};
//tinh tong base so nho nhat trong hang doi uu tien
double base_min_sum(priority_queue <pair <string, double>, vector <pair <string, double>>, CustomComparator> q)
{
	priority_queue <pair <string, double>, vector <pair <string, double>>, CustomComparator> qq = q;
	double sum = 0;
	for (int i = 1; i <= base; i++)
	{
		sum += qq.top().second;
		qq.pop();
	}
	return sum;
}
//gan nhan cho base so nho nhat trong hang doi uu tien
string base_min_label(priority_queue <pair <string, double>, vector <pair <string, double>>, CustomComparator> q)
{
	priority_queue <pair <string, double>, vector <pair <string, double>>, CustomComparator> qq = q;
	string label = "";
	for (int i = 1; i <= base; i++)
	{
		label += qq.top().first;
		qq.pop();
	}
	return label;
}
//dat lai du lieu
void reset_data()
{
    base = 0;
    unordered_map<string, double>().swap(Source);
    unordered_map<string, string>().swap(Code);
}
//tinh tong xac suat
double sum_probs(unordered_map <string, double> Source)
{
    double sum = 0;
    for (auto pair : Source)
    {
        sum += pair.second;
    }
    return sum;
}
//hien thi nguon
void show_info_source()
{
    cout << "Total probability is 1. You have finished inputing. Your source is below:\n";
    cout << "+--------------------------+\n";
    cout << " Information	Probability\n";
    cout << "+--------------------------+\n";
    for (auto pair : Source)
    {
        cout << " " << pair.first << "\t\t" << pair.second << '\n';
        cout << "+--------------------------+\n";
    }
}
//kiem tra tong xac suat
void check_input(string Info, double Prob)
{
    if (Prob < 0 || Prob > 1)
        cout << "Invalid probability. Try again:\n";
    else
    {
        if(sum_probs(Source) + Prob > 1.0001)
            cout << "Total probability of informations is greater than 1. Try again:\n";
        else
        {
            Source[Info] = Prob;
            Code[Info] = "";
        }
    }
}

//input from file
void read_source_from_file(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    reset_data();  // Clear previous data

    string info;
    double prob;

    while (file >> info >> prob) {
        exist[info] = true;
        check_input(info, prob);
    }

    file.close();
    show_info_source();
}

//input from keyboard
void input_source()
{
    reset_data();
    cout << "Input your information source\n";
    while (sum_probs(Source) <=0.9999)
    {
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
void generate_huffman_code()
{
    priority_queue <pair <string, double>, vector <pair <string, double>>, CustomComparator> source;
    for (auto pair : Source)
    {
        source.push({pair.first, pair.second});
    }
	//danh sach dinh ke cua cac node trong cay base_phan, chi gom 1 node duy nhat hoac khong co node nao
    unordered_map <string, vector <pair <string, string>>> adj;
    int num_r_info = Source.size();
    cout << "Base of Huffman code: ";
    cin >> base;
    int a = (num_r_info-base)/(base-1);
    if ((num_r_info-base) % (base-1)) a++;
    int num_newsource = base + a*(base-1);
    int num_i_info = num_newsource - num_r_info;
    
	for (int i = 1; i <= num_i_info; i++)
    {
        source.push({"i" + to_string(i+1), 0});
    }
	//tao cay base_phan day du
    while (source.size() > 1)
    {
        string tmp_info = base_min_label(source);
		double tmp_prob = base_min_sum(source);
        
        for (int i = 0; i < base; i++)
        {
			adj[source.top().first].push_back({tmp_info, to_string(i)});
            source.pop();
        }
        source.push({tmp_info, tmp_prob});
    }
	//doc tu goc xuong la de tim ma huffman cho la
    for (auto pair : Source)
    {
        string p = pair.first;
        while (adj[p].size())
        {
            Code[pair.first] = adj[p].front().second + Code[pair.first];
            p = adj[p].front().first;
        }
    }

    cout << "Huffman code has been generated!\n";
    cout << "+---------------------------+\n";
    cout << " Information	Huffman code\n";
    cout << "+---------------------------+\n";
    for (auto pair : Code)
    {
        reverseCode[pair.second]=pair.first;
        cout << " " << pair.first << "\t\t" << pair.second << '\n';
        cout << "+---------------------------+\n";
    }
}

void show_huffman_code()
{
    if (!Source.size()) cout << "Huffman code does not exist! Try again!\n";
    else
    {
        cout << "The Huffman code of your source is below:\n";
        cout << "+---------------------------+\n";
        cout << " Information	Huffman code\n";
        cout << "+---------------------------+\n";
        for (auto pair : Code)
        {
            cout << " " << pair.first << "\t\t" << pair.second << '\n';
            cout << "+---------------------------+\n";
        }
    }
}
void input_processor()
{
    input_source();
    auto start_time = high_resolution_clock::now();
    generate_huffman_code();
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    cout << "\nHuffman code generated in " << duration.count() << " milliseconds.\n";
}
//---------------------------END_TASK_1---------------------------

//-------------------------BEGIN_TASK_2---------------------------

string sequence; //ban tin can ma hoa
string huffman_sequence; //ban tin sau khi ma hoa

void input_sequence()
{
    cout << "\nInput sequence is: ";
    cin.ignore();
    getline(cin,sequence);
}

//kiem tra
bool check(string sequence)
{
    for (int i =0; i<sequence.length(); i++)
    {
        if (exist[sequence.substr(i,1)] == false)
            return false;
    }
    return true;
}

void sequence_process()
{
    input_sequence();
    while (!check(sequence))
    {
        cout<< "Your sequence contains (an) unidentified character(s). Please check again!\n";
        cout << "Input sequence is: ";
        getline(cin,sequence);
    }

    huffman_sequence="";
    for (int i=0; i< sequence.length(); i++)
    {
        string tmp = sequence.substr(i,1);
        huffman_sequence += Code[tmp];
    }
    cout<< "Huffman Code:" << huffman_sequence<<endl<<"\n";
}

//---------------------------END_TASK_2---------------------------

//-------------------------BEGIN_TASK_3---------------------------
string mahuffman; //luu tru ma huffman
void input() //ham nhap ma huffman
{
    cout<< "\nEnter Huffman Code: ";

	cin.ignore();
    getline(cin,mahuffman);

}
//giai ma huffman
int  decodeMessage(string code)
{
    string decodedMessage = "";
    int d=code.length();
    string str= "";
    for(int i=0; i<d; ++i)
    {
        str=str+code[i];
        auto it= reverseCode.find(str);

        if(it!=reverseCode.end())
        {
            decodedMessage=decodedMessage+it->second;
            str="";
        }
    }
    if(str=="") {
    	
		cout<< "Huffman decode: "<<decodedMessage<<endl<<"\n";
		return 1;
	}
    else cout<<"Nhap lai ma huffman:\n";
    return 0;

}
//---------------------------END_TASK_3---------------------------

void displaymenu()
{
    cout << "Choose an option:\n";
    cout << "1. Generate Huffman Code\n";
    cout << "2. Encode\n";
    cout << "3. Decode\n";
    cout << "4. Exit\n";
}

void inputmenu()
{
    cout << "\nChoose an option\n";
    cout << "1. Input from keyboard\n";
    cout << "2. Input from file\n";
    cout << "3. Back\n";
}

int main()
{
    int option;
    string filename;
    int choice;
    bool Back;
    while(cin)
    {
        displaymenu();
        cout << "Enter your choice: ";
        cin >> option;
        int q;
        switch (option)
        {
        case 1:
            while(cin)
            {
                inputmenu();
                Back=false;
                cout << "Enter your choice: ";
                cin>>choice;
                switch(choice)
                {
                case 1:
                    input_processor();
                    cout << "\nGenerating Huffman Code...\n";
                    show_huffman_code();
                    break;
                case 2:
                    cout<<"Enter file name: ";
                    cin>>filename;
                    read_source_from_file(filename);
                    cout << "\nGenerating Huffman Code...\n";
                    generate_huffman_code();
                    show_huffman_code();
                    break;
                case 3:
                    Back=true;
                    break;
                default:
                    cout << "\nInvalid option. Try again.\n";
                }
                if(Back)
                    break;
            }
            break;
        case 2:
            sequence_process();
            break;
        case 3:
            input();
			 q=decodeMessage(mahuffman);
            while(q==0){
            	input();
            	q=decodeMessage(mahuffman);
            	cin.ignore();
			}
            break;
        case 4:
            cout << "Exiting...\n";
            exit(0);
        default:
            cout << "\nInvalid option. Try again.\n";
        }
    }
    return 0;
}
