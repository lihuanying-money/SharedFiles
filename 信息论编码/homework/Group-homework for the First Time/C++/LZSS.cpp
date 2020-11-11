//#include<iostream>
//#include<string>
//#include<vector>
//#include <fstream> 
//#include<algorithm>
//#include "time.h"
//using namespace std;
//#define _for(i,j) for(int i=0;i<j;i++)
//
//bool readFileToString(string file_name, string& fileData);
//void input(int& search_buffer_size, string& s);
//void encoding(const int search_buffer_size, const string& s_ori);
//void writeToFile(const string& s_encoded);
//void decoding(string&, const string& ori_s);
//void adjust_parameter();
//
//int main() {
//	adjust_parameter();
//	//int a = 127;
//	//char c =  char(a);
//	//string s = string(1, c);
//	//cout << c << endl;
//	//cout << s << endl;
//	//char cs = s[0];
//	//cout << s.length() << endl;
//	//cout << int(cs) << endl;1000
//	//cout << (cs == c) << endl;
//
//	return 0;
//}
//
//bool readFileToString(string file_name, string& fileData)
//{
//	ifstream file(file_name.c_str(), std::ifstream::binary);
//	if (file)
//	{
//		// Calculate the file's size, and allocate a buffer of that size.
//		file.seekg(0, file.end); // ����ַΪ�ļ���������ƫ��Ϊ0��ָ�붨λ���ļ�������
//		const int file_size = int(file.tellg());
//		char* file_buf = new char[file_size + 1];
//		//make sure the end tag \0 of string.
//		memset(file_buf, 0, file_size + 1);
//		// Read the entire file into the buffer.
//		file.seekg(0, ios::beg);  //����ַΪ�ļ�ͷ��ƫ����Ϊ0����λ���ļ�ͷ
//		file.read(file_buf, file_size);
//		fileData = "";
//		fileData.append(file_buf);
//		if (!file)
//		{
//			cout << "error: only " << file.gcount() << " could be read";
//			file.close();
//			delete[]file_buf;
//			return false;
//		}
//		file.close();
//		delete[]file_buf;
//		return true;
//	}
//	else
//	{
//		cout << "error: File open failed.\n";
//		return false;
//	}
//}
//
//void input(int& search_buffer_size, string& s) {
//	cout << "search buffer size = ";
//	cin >> search_buffer_size;
//
//	if (!readFileToString("./data_base.txt", s))
//		cout << "Failed to open the file, please check the file path." << endl;
//	cout << endl;
//}
//
//void encoding(const int search_buffer_size, const string& s_ori) {
//	clock_t encode_start, encode_finish;
//	encode_start = clock();
//	double  encode_duration;
//	int code_num = 0, sbi = 4, lai = 5, sLen = s_ori.length(); // LZSS�����ܶ�ǰ5���ַ�����
//	int max_match_num = 0;                                     // ��¼���б��������һ��ƥ����ַ�����
//	string s_encoded = s_ori.substr(0, 5);                     // ֱ�ӱ��뵽�ַ�����
//	while (lai < sLen) {                                       // look_ahead_buffer�������lai��lai=sbj+1
//		int sbj = sbi, max_reduce_length = 0;                  // ��search_buffer�����һλsbj��ǰ����
//		int sb_min = max(-1, sbi - search_buffer_size);        // �������½�
//		string best_code = string(1, s_ori[lai]);              // ��¼search_buffer����ѵ�һ������
//		while (sbj > sb_min) {                                 // ����search_buffer
//			if (s_ori[sbj] == s_ori[lai]) { // search_buffer��jλ��ƥ�䵽look_ahead_buffer��iλ�ã���ʼһ��ƥ��
//				int j_match = sbj + 1, laj_match = lai + 1;
//				while (j_match <= sbi && laj_match < sLen && s_ori[j_match] == s_ori[laj_match])
//				{
//					j_match++; laj_match++;
//				}
//				if (j_match == sbi + 1) {                      // ɨ��search_bufferβ����ѭ�� sbj->sbi
//					j_match = sbj;
//					while (laj_match < sLen && s_ori[j_match] == s_ori[laj_match]) {
//						j_match++;
//						laj_match++;
//						if (j_match == sbi) j_match = sbj;     // �Կɼ���ѭ��
//					}
//				}
//				int match_num = laj_match - lai, ahead_num = lai - sbj;
//				// ֱ�Ӱ�����תΪstring̫����
//				//string wish_code = "$" + to_string(ahead_num) + "," + to_string(match_num) + "$";
//			/*	if (lai > 9820) {
//					cout << s_encoded.substr(s_encoded.length() - 20, 20) << endl;
//					cout << s_ori.substr(s_ori.length() - 20, 22) << endl;
//				}*/
//				string aheads = "";
//				if (ahead_num < 127) aheads = string(1, char(ahead_num));// ����Сʱ��һ��char�洢��תΪstring
//				else aheads = string(1, char(ahead_num / 127)) + string(1, char(ahead_num % 127));
//
//				char matchc = char(match_num);                           // ������126, 127���ڱ������ұ߽��ַ�
//				string matchs = string(1, matchc);
//				string boundary = string(1, char(127));
//				//  matchsֻ����һ���ַ��������м�Ķ��ſ���ʡ����
//				string wish_code = boundary + aheads + matchs + boundary;// ��������search�����ı���  
//
//				int reduce_length = match_num - wish_code.length();      // ����������������˶���
//				if (reduce_length > max_reduce_length) {                 // ��������˸��࣬�ͼ�¼��
//					best_code = wish_code;
//					max_reduce_length = reduce_length;
//				}
//			}
//			sbj--;
//		}
//		if (best_code.length() > 1) code_num++;                          // ��¼���̴��������������
//		s_encoded += best_code;
//		sbi += max_reduce_length + int(best_code.length());              // ���ƻ���
//		max_match_num = max(max_match_num, max_reduce_length + int(best_code.length()));
//		lai = sbi + 1;
//	}
//	encode_finish = clock();
//	encode_duration = (double)(encode_finish - encode_start) / CLOCKS_PER_SEC;
//
//
//	if (s_ori.length() == 0) {
//		cout << "null string.\n\n";
//		return;
//	}
//	double compression_rate = double(s_ori.length() - s_encoded.length()) / double(s_ori.length());
//	cout << "Encoding Run time: " << encode_duration << "s" << endl;
//	cout << "max match number: " << max_match_num << endl;
//	cout << "code num(ѹ������): " << code_num << endl;
//	cout << "Compressed Length: " << s_encoded.length() << "B\nOriginal Length: " << s_ori.length()
//		<< "B\nCompression Rate: " << compression_rate << "\n\n";
//
//	writeToFile(s_encoded);
//	decoding(s_encoded, s_ori);
//}
//
//void writeToFile(const string& s_encoded) {
//	ofstream out("./LZSS_output.txt");
//	if (out.is_open())
//	{
//		out << s_encoded;
//		out.close();
//	}
//	else cout << "OpenFileFailed.\n";
//}
//
//// ���ڴ浽�ı��ļ���Ȼ��ȡ����ʱ '\r\n'����'\r\r\n'������ֱ�Ӵ���ѹ�����string��ԭʼstring�����ٴ��ı��ļ�����ѹ�����string
//void decoding(string& s_encoded, const string& s_ori) {  // �����ַ�����ԭʼ�ַ���
//	clock_t decode_start, decode_finish;
//	decode_start = clock();
//	double  decode_duration;
//	string s_decoded = "";								 // �����ַ���
//	char boundary = char(127);							 // �߽��ַ�
//	int s_en_len = s_encoded.length();
//	//readFileToString("./LZSS_output.txt", s_encoded);
//	_for(i, s_en_len - 3) {                               // ���3���ַ������ܱ��룬ͬʱҪ��ֹ����ifԽ��
//		if (s_encoded[i] != boundary)                    // ��λ��δ����ѹ��
//			s_decoded += s_encoded[i];
//		else {
//			int lai = s_decoded.length();                // look_ahead��ʼλ���±�
//			int ahead_num = 0, match_num = 0;            // ��ǰ���ַ�����
//			i++;
//			//while (s_encoded[i] != ',') ahead_num = ahead_num * 10 + s_encoded[i++] - '0';
//			//while (s_encoded[++i] != '$') match_num = match_num * 10 + s_encoded[i] - '0';
//			// �ö������ָ�������ahead������������ţ�����
//			//while (s_encoded[i] != ',')   ahead_num = ahead_num * 128 + int(char(s_encoded[i++]));
//			if (s_encoded[i + 2] == boundary)            // ���ڱ������ж�+2������+3��λ����!!! (֮ǰ�������ж�+3)
//				ahead_num = int(char(s_encoded[i++]));   // ahead_num��1λ127������
//			else {                                       // ����ahead_num��2λ127������
//				ahead_num = int(char(s_encoded[i])) * 127 + int(char(s_encoded[i + 1]));
//				i += 2;
//			}
//
//			char c = s_encoded[i]; i++;                  // ��ʱs_encoded[i] == boundary
//			match_num = int(c);                          // ƥ����ַ��������ᳬ��127��ʵ����һ�붼������
//
//			if (s_encoded[i] != boundary) {              // ������
//				cerr <<"Error Occurred: "<< s_encoded.substr(i - 20, 22) << endl;
//				break;
//			}
//
//			const int sb_begin = lai - ahead_num;        // ��sb_begin��ʼ��ȡ�������ַ�
//			int  sbi = sb_begin;  
//			_for(j, match_num) {                         // �ɼ���ѭ������search_buffer��ƥ���Ӵ�
//				s_decoded += s_decoded[sbi];
//				sbi++;
//				if (sbi == lai) sbi = sb_begin;          // ѭ��
//			}
//
//		}                
//		if (s_decoded != s_ori.substr(0, s_decoded.length())) { 
//			cerr << s_encoded.substr(i - 20, 22) << endl;
//			cerr << s_decoded.substr(s_decoded.length() - 20, 22) << endl;
//			cerr << s_ori.substr(s_decoded.length() - 20, 22) << endl;
//			break;
//		}
//	}
//	s_decoded += s_encoded.substr(max(0, s_en_len - 3), min(3, s_en_len));
//
//	decode_finish = clock();
//	decode_duration = (double)(decode_finish - decode_start) / CLOCKS_PER_SEC;
//	cout << "Decoding Run time: " << decode_duration << "s\n";
//	if (s_ori == s_decoded) cout << "\nCorrect decoding !\n\n";
//	else cout << "\nWrong decoding !\n\n";
//}
//
//void adjust_parameter() {
//	while (1) {
//		int search_buffer_size = 7, look_ahead_size = 6;
//		string s_ori = "aaaaaaaaaaaaa";
//		input(search_buffer_size, s_ori);
//		encoding(search_buffer_size, s_ori);
//		//decoding(search_buffer_size, s_ori);
//	}
//}