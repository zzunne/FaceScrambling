#include <fstream>
#include <iostream>
using namespace std;

/*
	---------- ��ó���� ----------
	MAX_ROW : ���� �̹����� ROW SIZE 256
	MAX_COL : ���� �̹����� COLUMN SIZE 256
	ROI_ROW : ROI(Region of Interest)�� ROW SIZE 80
	ROI_COL : ROI(Region of Interest)�� COLUMN SIZE 80
	ROI_BEGIN_ROW : ROI(Region of Interest)�� ������(80, 84)�� ROW 80
	ROI_BEGIN_COL : ROI(Region of Interest)�� ������(80, 84)�� COLUMN 84
*/
#define MAX_ROW 256
#define MAX_COL 256
#define ROI_ROW 80
#define ROI_COL 80
#define ROI_BEGIN_ROW 80
#define ROI_BEGIN_COL 84

/*
	---------- ���� ����(Global variable) ----------
	input_data : input�̹���(���� �̹���)�� ����
*/
char **input_data;

/*
	---------- �Լ������ ----------
	loadImage() : �̹����� �ҷ����� �Լ�
	encoding(char**) : �󱼿����� scramble�ϴ� �Լ�
	generateRandomNumbers() : key�� ���� random numbers�� ����� �Լ�
	saveImage(char**) : scramble�� �̹����� �����ϴ� �Լ�
*/
void loadImage(string);
void decoding(char**);
void generateRandomNumbers(int*, int);
void saveImage(char**, string);

void main() {
	// inputFilename / outputFilename : input/output image�� ��� �� ���ϸ�
	string inputFilename = "../GIRL/girl_scrambled.gray";
	string outputFilename = "../GIRL/girl_descrambled.gray";

	loadImage(inputFilename);				// �̹��� �ҷ�����
	decoding(input_data);					// decoding(descrambling)
	saveImage(input_data, outputFilename);	// �̹��� �����ϱ�
}

void loadImage(string filename) {
	// new�� �̿��Ͽ� 256x256 ũ��� �����Ҵ�
	input_data = new char*[MAX_ROW];
	for (int i = 0; i < MAX_ROW; i++) input_data[i] = new char[MAX_COL];

	// ���� �Է� ��Ʈ�� ���� ����
	ifstream in(filename, ios::in | ios::binary);
	for (int i = 0; i<MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++) {
			char ch;
			in.get(ch);				// char �ϳ��� ���Ϸκ��� �б�
			input_data[i][j] = ch;	// input_data�� ����
		}
}
void decoding(char** encoded) {
	// new�� �̿��Ͽ� 80x80 ũ��� �����Ҵ�
	char** roi_data = new char*[ROI_ROW];
	char **temp_data = new char*[ROI_ROW];
	for (int i = 0; i < ROI_ROW; i++) {
		roi_data[i] = new char[ROI_COL];
		temp_data[i] = new char[ROI_COL];
	}

	// input_data���� �� ������ roi_data, temp_data�� ����
	for (int i = 0; i<ROI_ROW; i++)
		for (int j = 0; j < ROI_COL; j++) {
			roi_data[i][j] = input_data[i + ROI_BEGIN_ROW][j + ROI_BEGIN_COL];
			temp_data[i][j] = 0;
		}

	// key�� ���� random numbers�� ��� ���� 6400(80*80)ũ��� �����Ҵ�
	int* key_arr = new int[ROI_ROW*ROI_COL];
	int key = 12121603;
	generateRandomNumbers(key_arr, key);	// random number ���� �� key_arr�� ����

	// Face Descrambling
	for (int i = 0; i < 6400; i++)
		temp_data[key_arr[i] / ROI_ROW][key_arr[i] % ROI_COL] = roi_data[i / ROI_ROW][i%ROI_COL];
	
	// roi_data, key_arr �޸� ����
	for (int i = 0; i < ROI_ROW; i++) delete roi_data[i];
	delete roi_data, key_arr;

	// input_data(����)�� descramble�� �� �߰�
	for (int i = 0; i < ROI_ROW; i++)
		for (int j = 0; j < ROI_COL; j++)
			input_data[i + 80][j + 84] = temp_data[i][j];

	// temp_data �޸� ����
	for (int i = 0; i < ROI_ROW; i++) delete temp_data[i];
	delete temp_data;
}
void generateRandomNumbers(int* key_arr, int key) {
	srand(key);
	for (int i = 0; i < ROI_ROW*ROI_COL; i++) key_arr[i] = i;	// �ʱ�ȭ

	for (int i = 0; i<ROI_ROW*ROI_COL; i++)
	{
		int n = rand() % (ROI_ROW*ROI_COL); // 0~6399
		// ������ index�� ���� index swap�ϱ�
		int temp = key_arr[n];
		key_arr[n] = key_arr[ROI_ROW*ROI_COL - 1];
		key_arr[ROI_ROW*ROI_COL - 1] = temp;
	}
}
void saveImage(char** decoded, string filename) {
	// ���� ��� ��Ʈ�� ���� ����
	ofstream out(filename, ios::out | ios::binary);
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			out.put(input_data[i][j]);
	
	// input_data �޸� ����
	for (int i = 0; i < MAX_ROW; i++) delete input_data[i];
	delete input_data;
}