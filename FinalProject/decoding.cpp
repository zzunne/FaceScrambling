#include <fstream>
#include <iostream>
using namespace std;

/*
	---------- 전처리문 ----------
	MAX_ROW : 원본 이미지의 ROW SIZE 256
	MAX_COL : 원본 이미지의 COLUMN SIZE 256
	ROI_ROW : ROI(Region of Interest)의 ROW SIZE 80
	ROI_COL : ROI(Region of Interest)의 COLUMN SIZE 80
	ROI_BEGIN_ROW : ROI(Region of Interest)의 시작점(80, 84)의 ROW 80
	ROI_BEGIN_COL : ROI(Region of Interest)의 시작점(80, 84)의 COLUMN 84
*/
#define MAX_ROW 256
#define MAX_COL 256
#define ROI_ROW 80
#define ROI_COL 80
#define ROI_BEGIN_ROW 80
#define ROI_BEGIN_COL 84

/*
	---------- 전역 변수(Global variable) ----------
	input_data : input이미지(원본 이미지)를 저장
*/
char **input_data;

/*
	---------- 함수선언부 ----------
	loadImage() : 이미지를 불러오는 함수
	encoding(char**) : 얼굴영역을 scramble하는 함수
	generateRandomNumbers() : key에 의해 random numbers를 만드는 함수
	saveImage(char**) : scramble된 이미지를 저장하는 함수
*/
void loadImage(string);
void decoding(char**);
void generateRandomNumbers(int*, int);
void saveImage(char**, string);

void main() {
	// inputFilename / outputFilename : input/output image의 경로 및 파일명
	string inputFilename = "../GIRL/girl_scrambled.gray";
	string outputFilename = "../GIRL/girl_descrambled.gray";

	loadImage(inputFilename);				// 이미지 불러오기
	decoding(input_data);					// decoding(descrambling)
	saveImage(input_data, outputFilename);	// 이미지 저장하기
}

void loadImage(string filename) {
	// new를 이용하여 256x256 크기로 동적할당
	input_data = new char*[MAX_ROW];
	for (int i = 0; i < MAX_ROW; i++) input_data[i] = new char[MAX_COL];

	// 파일 입력 스트림 변수 선언
	ifstream in(filename, ios::in | ios::binary);
	for (int i = 0; i<MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++) {
			char ch;
			in.get(ch);				// char 하나를 파일로부터 읽기
			input_data[i][j] = ch;	// input_data에 저장
		}
}
void decoding(char** encoded) {
	// new를 이용하여 80x80 크기로 동적할당
	char** roi_data = new char*[ROI_ROW];
	char **temp_data = new char*[ROI_ROW];
	for (int i = 0; i < ROI_ROW; i++) {
		roi_data[i] = new char[ROI_COL];
		temp_data[i] = new char[ROI_COL];
	}

	// input_data에서 얼굴 영역만 roi_data, temp_data에 저장
	for (int i = 0; i<ROI_ROW; i++)
		for (int j = 0; j < ROI_COL; j++) {
			roi_data[i][j] = input_data[i + ROI_BEGIN_ROW][j + ROI_BEGIN_COL];
			temp_data[i][j] = 0;
		}

	// key에 의한 random numbers를 담기 위해 6400(80*80)크기로 동적할당
	int* key_arr = new int[ROI_ROW*ROI_COL];
	int key = 12121603;
	generateRandomNumbers(key_arr, key);	// random number 생성 후 key_arr에 저장

	// Face Descrambling
	for (int i = 0; i < 6400; i++)
		temp_data[key_arr[i] / ROI_ROW][key_arr[i] % ROI_COL] = roi_data[i / ROI_ROW][i%ROI_COL];
	
	// roi_data, key_arr 메모리 해제
	for (int i = 0; i < ROI_ROW; i++) delete roi_data[i];
	delete roi_data, key_arr;

	// input_data(원본)에 descramble된 얼굴 추가
	for (int i = 0; i < ROI_ROW; i++)
		for (int j = 0; j < ROI_COL; j++)
			input_data[i + 80][j + 84] = temp_data[i][j];

	// temp_data 메모리 해제
	for (int i = 0; i < ROI_ROW; i++) delete temp_data[i];
	delete temp_data;
}
void generateRandomNumbers(int* key_arr, int key) {
	srand(key);
	for (int i = 0; i < ROI_ROW*ROI_COL; i++) key_arr[i] = i;	// 초기화

	for (int i = 0; i<ROI_ROW*ROI_COL; i++)
	{
		int n = rand() % (ROI_ROW*ROI_COL); // 0~6399
		// 마지막 index와 나온 index swap하기
		int temp = key_arr[n];
		key_arr[n] = key_arr[ROI_ROW*ROI_COL - 1];
		key_arr[ROI_ROW*ROI_COL - 1] = temp;
	}
}
void saveImage(char** decoded, string filename) {
	// 파일 출력 스트림 변수 선언
	ofstream out(filename, ios::out | ios::binary);
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			out.put(input_data[i][j]);
	
	// input_data 메모리 해제
	for (int i = 0; i < MAX_ROW; i++) delete input_data[i];
	delete input_data;
}