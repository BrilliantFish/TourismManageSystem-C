#include "wrapper.h"

//�����ַ���
void process_string(char *str, int length){
	for (int i = 0; i < length; i++){
		if (str[i] == '\n'){
			str[i] = '\0';
		}
	}
}

//��������
int calculate_string(char *str){
	int count = 0;
	int i = 0;

	for (; str[i] != '\0'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			count = count * 10 + (str[i] - '0');
		}
		else{
			count = -1;
			break;
		}
	}

	if (i == 0){
		count = -1;
	}

	return count;
}

//��������
void process_date_string(char *str, TIMESTAMP_STRUCT *date){
	int i = 0;
	date->year = 0;
	date->month = 0;
	date->day = 0;
	date->hour = 0;
	date->minute = 0;
	date->second = 0;
	date->fraction = 0;

	//������
	for (; str[i] != '-'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			date->year = (date->year) * 10 + (str[i] - '0');
		}
		else{
			date->year = 1970;
			date->month = 1;
			date->day = 1;
			return;
		}
	}
	//������
	for (i++; str[i] != '-'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			date->month = (date->month) * 10 + (str[i] - '0');
		}
		else{
			date->year = 1970;
			date->month = 1;
			date->day = 1;
			return;
		}
	}
	//������
	for (i++; str[i] != '\0'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			date->day = (date->day) * 10 + (str[i] - '0');
		}
		else{
			date->year = 1970;
			date->month = 1;
			date->day = 1;
			return;
		}
	}
}

//�˳�
void ending(){
	system("cls");

	printf("\n\n\n\n\n\n\n");
	printf("                                          |-------------------------------|\n");
	printf("                                          |  ��   ��   ��   ��   ϵ   ͳ  |\n");
	printf("                                          |-------------------------------|\n\n\n");
	printf("            --------------------------------------------------------------------------------------------\n\n\n");
	printf("                                              -> ������");
}

int write_choice(){
	int choice;
	char str[MAX_LENGTH];

	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	choice = calculate_string(str);

	return choice;
}
