#include "wrapper.h"

void add_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct tourist_node tourist_temp;
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                  [�οͱ��8λ����]\n\n");

	//�οͱ��
	printf("\n                                                 > �οͱ�ţ�");
	fgets(tourist_temp.tourist_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_number, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_number, "E") == 0)
		return;

	//�������֤��
	printf("\n                                                 > ���֤�ţ�");
	fgets(tourist_temp.tourist_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_id, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_id, "E") == 0)
		return;

	//��������
	printf("\n                                                 > ��    ����");
	fgets(tourist_temp.tourist_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_name, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_name, "E") == 0)
		return;

	//�����Ա�
	printf("\n                                                 > ��    ��");
	fgets(tourist_temp.tourist_sex, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_sex, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_sex, "E") == 0)
		return;

	//�����������
	printf("\n                                                 > �������ڣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &tourist_temp.tourist_birth);

	if (strcmp(str, "E") == 0)
		return;

	//����סַ
	printf("\n                                                 > ס    ַ��");
	fgets(tourist_temp.tourist_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_addr, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_addr, "E") == 0)
		return;

	//������ϵ�绰
	printf("\n                                                 > ��ϵ�绰��");
	fgets(tourist_temp.tourist_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_tel, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_tel, "E") == 0)
		return;

	//��������·��
	printf("\n                                                 > ����·�ߣ�");
	fgets(tourist_temp.route_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.route_number, MAX_LENGTH);

	if (strcmp(tourist_temp.route_number, "E") == 0)
		return;

	//�������ʱ��
	printf("\n                                                 > ����ʱ�䣺");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &tourist_temp.start_time);

	if (strcmp(str, "E") == 0)
		return;

	//����س�ʱ��
	printf("\n                                                 > �س�ʱ�䣺");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &tourist_temp.end_time);

	if (strcmp(str, "E") == 0)
		return;

	//�����û�
	strcpy(tourist_temp.consumer_number, consumer_node.consumer_id);

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Tourist VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		SQLBindParameter(dbhstmt, 1,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_number,  0, NULL);
		SQLBindParameter(dbhstmt, 2,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_id,      0, NULL);
		SQLBindParameter(dbhstmt, 3,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_name,    0, NULL);
		SQLBindParameter(dbhstmt, 4,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_sex,     0, NULL);
		SQLBindParameter(dbhstmt, 5,  SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23,         3, &tourist_temp.tourist_birth,  0, NULL);
		SQLBindParameter(dbhstmt, 6,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_addr,    0, NULL);
		SQLBindParameter(dbhstmt, 7,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_tel,     0, NULL);
		SQLBindParameter(dbhstmt, 8,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.route_number,    0, NULL);
		SQLBindParameter(dbhstmt, 9, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23,         3, &tourist_temp.start_time,     0, NULL);
		SQLBindParameter(dbhstmt, 10, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23,         3, &tourist_temp.end_time,       0, NULL);
		SQLBindParameter(dbhstmt, 11, SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.consumer_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}
	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > �ο���ӳɹ���\n");
	else if (ret == SQL_NEED_DATA){
		printf("\n                                                 > SQL_NEED_DATA��\n");
		SQLError(*dbhenv, *dbhdbc, dbhstmt, NULL, NULL, errmsg, sizeof(errmsg), NULL);
		printf("\n                                                 > %s\n", errmsg);
	}
	else if (ret == SQL_ERROR){
		printf("\n                                                 > SQL_ERROR��\n");
		SQLError(*dbhenv, *dbhdbc, dbhstmt, NULL, NULL, errmsg, sizeof(errmsg), NULL);
		printf("\n                                                 > %s\n", errmsg);
	}
	else
		printf("\n                                                 > �ο����ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct tourist_node tourist_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                 [�οͱ��8λ����]\n\n");

	//�����οͱ��
	printf("\n                                                 > �οͱ�ţ�");
	fgets(tourist_temp.tourist_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_number, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Tourist WHERE tourist_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > �ο�ɾ���ɹ���\n");
	else
		printf("\n                                                 > �ο�ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

//��ѯ�ο���Ϣ
void query_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct tourist_node tourist_temp;
	char tourist_number[MAX_LENGTH];

	system("cls");
	title();

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Tourist", SQL_NTS);
	SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_number, 0, NULL);
	SQLBindCol(dbhstmt, 1,  SQL_C_CHAR,           tourist_temp.tourist_number,  MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 2,  SQL_C_CHAR,           tourist_temp.tourist_id,      MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 3,  SQL_C_CHAR,           tourist_temp.tourist_name,    MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 4,  SQL_C_CHAR,           tourist_temp.tourist_sex,     MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 5,  SQL_C_TYPE_TIMESTAMP, &tourist_temp.tourist_birth,  0,          NULL);
	SQLBindCol(dbhstmt, 6,  SQL_C_CHAR,           tourist_temp.tourist_addr,    MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 7,  SQL_C_CHAR,           tourist_temp.tourist_tel,     MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 8,  SQL_C_CHAR,           tourist_temp.route_number,    MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 9,  SQL_C_TYPE_TIMESTAMP, &tourist_temp.start_time,     0,          NULL);
	SQLBindCol(dbhstmt, 10, SQL_C_TYPE_TIMESTAMP, &tourist_temp.end_time,       0,          NULL);
	SQLBindCol(dbhstmt, 11, SQL_C_CHAR,           tourist_temp.consumer_number, MAX_LENGTH, NULL);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
		printf("#");
		printf("%s  ", tourist_temp.tourist_number);
		printf("%s  ", tourist_temp.tourist_id);
		printf("%s  ", tourist_temp.tourist_name);
		printf("%s  ", tourist_temp.tourist_sex);
		printf("%d-%d-%d\t", tourist_temp.tourist_birth.year, tourist_temp.tourist_birth.month, tourist_temp.tourist_birth.day);
		printf("%s  ", tourist_temp.tourist_addr);
		printf("%s  ", tourist_temp.tourist_tel);
		printf("%s  ", tourist_temp.route_number);
		printf("%d-%d-%d\t", tourist_temp.start_time.year, tourist_temp.start_time.month, tourist_temp.start_time.day);
		printf("%d-%d-%d\t", tourist_temp.end_time.year, tourist_temp.end_time.month, tourist_temp.end_time.day);
		printf("%s\n\n", tourist_temp.consumer_number);
		ret = SQLFetch(dbhstmt);
	}
	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);
	printf("\n                                                 > ");
	system("pause");
}

void tourist(){
	int choice = 0;

	/*�������ͱ���*/
	SQLHENV dbhenv;	     //�������
	SQLHDBC dbhdbc;      //���Ӿ��
	SQLRETURN ret;       //����ֵ

	/*���������������ʼ���������*/
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &dbhenv);
	ret = SQLSetEnvAttr(dbhenv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);

	/*�������Ӿ����������Դ��������*/
	ret = SQLAllocHandle(SQL_HANDLE_DBC, dbhenv, &dbhdbc);
	ret = SQLConnect(dbhdbc, (SQLCHAR *)"TCDB", SQL_NTS, (SQLCHAR *)"sa", SQL_NTS, (SQLCHAR *)"reply1988", SQL_NTS);
	if (!SQL_SUCCEEDED(ret)){  //�ж��Ƿ����ӳɹ��ĺ���
		printf("���ӳ���\n");
		exit(0);
	}

	do{
		tourist_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_tourist(&dbhenv, &dbhdbc, 1);
			break;
		case 2:
			delete_tourist(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_tourist(&dbhenv, &dbhdbc);
			break;
		case 0:
			break;
		}
	} while (choice);

	/*�Ͽ�����Դ�����Ӿ��������*/
	SQLDisconnect(dbhdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, dbhdbc);

	/*�ͷŻ������*/
	SQLFreeHandle(SQL_HANDLE_ENV, dbhenv);
} 