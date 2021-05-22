#include "wrapper.h"

void add_route_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	char route_number[MAX_LENGTH];
	char service_number[MAX_LENGTH];
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                          [·�߱��4λ���֣���α��5λ����]\n\n");

	//·�߱��
	printf("\n                                                 > ·�߱�ţ�");
	fgets(route_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_number, MAX_LENGTH);

	if (strcmp(route_number, "E") == 0)
		return;

	//�����α��
	printf("\n                                                 > ��α�ţ�");
	fgets(service_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(service_number, MAX_LENGTH);

	if (strcmp(service_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Route_Service VALUES(?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_number, 0, NULL);
		SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ·��-�����ӳɹ���\n");
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
		printf("\n                                                 > ·��-������ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_route_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	char route_number[MAX_LENGTH];
	char service_number[MAX_LENGTH];
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                          [·�߱��4λ���֣���α��5λ����]\n\n");

	//·�߱��
	printf("\n                                                 > ·�߱�ţ�");
	fgets(route_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_number, MAX_LENGTH);

	if (strcmp(route_number, "E") == 0)
		return;

	//�����α��
	printf("\n                                                 > ��α�ţ�");
	fgets(service_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(service_number, MAX_LENGTH);

	if (strcmp(service_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Route_Service WHERE route_number = ? AND service_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ·��-���ɾ���ɹ���\n");
	else
		printf("\n                                                 > ·��-���ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_route_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	char route_number[MAX_LENGTH];
	char service_number[MAX_LENGTH];
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                  [·�߱��4λ����]\n\n");

	//·�߱��
	printf("\n                                                 > ·�߱�ţ�");
	fgets(route_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_number, MAX_LENGTH);

	if (strcmp(route_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT service_number FROM Route_Service WHERE route_number = ?;", SQL_NTS);
	SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_number, 0, NULL);
	SQLBindCol(dbhstmt, 1, SQL_C_CHAR, service_number, MAX_LENGTH, NULL);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("\n                                                 > ���ΰ�Σ�%s\n", service_number);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void route_service(){
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
		route_service_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_route_service(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_route_service(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_route_service(&dbhenv, &dbhdbc);
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