#include <fstream>
#include <iostream>
using namespace std;

#define MAX_X 256
#define MAX_Y 256
#define ROI_ROW 80
#define ROI_COL 80
char ch;
void main() {
	// new 사용하며 메모리 공간 할당
	char** in_data = new char*[256];
	for (int i = 0; i < 256; i++) in_data[i] = new char[256];
	char** roi_data = new char*[ROI_ROW];
	for (int i = 0; i < ROI_ROW; i++) roi_data[i] = new char[ROI_COL];
	char** temp_data = new char*[ROI_ROW];
	for (int i = 0; i < ROI_ROW; i++) temp_data[i] = new char[ROI_COL];
	ifstream in("../GIRL/GIRL.gray", ios::in | ios::binary);
	ofstream out("../GIRL/GIRL_half.gray", ios::out | ios::binary);

	for (int i = 0; i<MAX_Y; i++)
		for (int j = 0; j < MAX_X; j++) {
			in.get(ch);
			in_data[i][j] = ch;
		}


	for (int i = 0; i<ROI_ROW; i++)
		for (int j = 0; j < ROI_COL; j++) {
			roi_data[i][j] = in_data[i + 80][j + 84];
			temp_data[i][j] = in_data[i + 80][j + 84];
		}



	int key = 5;
	srand(key);
	int* temp_arr = new int[6400];
	for (int i = 0; i < 6400; i++)temp_arr[i] = i;
	for (int i = 0; i<6400; i++)
	{
		int n = rand() % 6400; // 0~6399

							   // 마지막 index와 나온 index swap하기
		int temp = temp_arr[n];
		temp_arr[n] = temp_arr[6399];
		temp_arr[6399] = temp;
	}

	//for (int i = 0; i < 6400; i++) {
	//	roi_data[i / ROI_ROW][i % ROI_COL] = temp_data[temp_arr[i] / ROI_ROW][temp_arr[i] % ROI_COL];
	//	/*
	//	roi[0][0] = temp[31][52]
	//	roi[0][1] = temp[0][7]
	//	roi[0][2] = temp[1][25]
	//	*/
	//}
	//for (int i = 0; i < ROI_ROW; i++) {
	//	for (int j = 0; j < ROI_COL; j++) {
	//		in_data[i + 80][j + 84] = roi_data[i][j];
	//	}
	//}

	//for (int i = 0; i < 6400; i++) {
	//	temp_data[temp_arr[i] / ROI_ROW][temp_arr[i] % ROI_COL] = roi_data[i / ROI_ROW][i%ROI_COL];
	//	/*
	//	temp[31][52] = roi[0][0]
	//	temp[0][7] = roi[0][1]
	//	temp[0][2] = roi[1][25]
	//	*/
	//}
	//for (int i = 0; i < ROI_ROW; i++) {
	//	for (int j = 0; j < ROI_COL; j++) {
	//		in_data[i + 80][j + 84] = temp_data[i][j];
	//	}
	//}
	//for (int i = 0; i < 256; i++)
	//	for (int j = 0; j < 256; j++)
	//		out.put(in_data[i][j]);


}