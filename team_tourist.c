#include "wrapper.h"

void add_team_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	char team_number[MAX_LENGTH];
	char tourist_number[MAX_LENGTH];
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                          [�����ź�5λ���֣��οͱ��8λ����]\n\n");

	//���������ź�
	printf("\n                                                 > �����źţ�");
	fgets(team_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_number, MAX_LENGTH);

	if (strcmp(team_number, "E") == 0)
		return;

	//�����οͱ��
	printf("\n                                                 > �οͱ�ţ�");
	fgets(tourist_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_number, MAX_LENGTH);

	if (strcmp(tourist_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Team_Tourist VALUES(?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_number, 0, NULL);
		SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ������-�ο���ӳɹ���\n");
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
		printf("\n                                                 > ������-�ο����ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_team_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	char team_number[MAX_LENGTH];
	char tourist_number[MAX_LENGTH];
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                          [�����ź�5λ���֣��οͱ��8λ����]\n\n");

	//���������ź�
	printf("\n                                                 > �����źţ�");
	fgets(team_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_number, MAX_LENGTH);

	if (strcmp(team_number, "E") == 0)
		return;

	//�����οͱ��
	printf("\n                                                 > �οͱ�ţ�");
	fgets(tourist_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_number, MAX_LENGTH);

	if (strcmp(tourist_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Team_Tourist WHERE team_number = ? AND tourist_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ������-�ο�ɾ���ɹ���\n");
	else
		printf("\n                                                 > ������-�ο�ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_team_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	char team_number[MAX_LENGTH];
	char tourist_number[MAX_LENGTH];
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                          [�����ź�5λ���֣��οͱ��8λ����]\n\n");

	//���������ź�
	printf("\n                                                 > �����źţ�");
	fgets(team_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_number, MAX_LENGTH);

	if (strcmp(team_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT tourist_number FROM Team_Tourist WHERE team_number = ?;", SQL_NTS);
	SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_number, 0, NULL);
	SQLBindCol(dbhstmt, 1, SQL_C_CHAR, tourist_number, MAX_LENGTH, NULL);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("\n                                                 > �οͱ�ţ�%s\n", tourist_number);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void team_tourist(){
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
		team_tourist_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_team_tourist(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_team_tourist(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_team_tourist(&dbhenv, &dbhdbc);
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