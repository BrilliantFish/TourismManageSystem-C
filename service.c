#include "wrapper.h"

void add_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct service_node service_temp;
	char str[MAX_LENGTH];
	char errmsg[256];
	long len;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                           [��α��5λ���֣�������нض�]\n\n");

	//����·�߱��
	printf("\n                                                 > ��α�ţ�");
	fgets(service_temp.service_number, 6, stdin);
	fflush(stdin);
	process_string(service_temp.service_number, 6);

	if (strcmp(service_temp.service_number, "E") == 0)
		return;

	//�������
	printf("\n                                                 > �������ڣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &service_temp.start_time);

	if (strcmp(str, "E") == 0)
		return;

	//�����յ�
	printf("\n                                                 > �س����ڣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &service_temp.end_time);

	if (strcmp(str, "E") == 0)
		return;

	//�������α�׼
	printf("\n                                                 > ���α�׼��");
	fgets(service_temp.travel_standard, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(service_temp.travel_standard, MAX_LENGTH);

	if (strcmp(service_temp.travel_standard, "E") == 0)
		return;

	//���뱨��
	printf("\n                                                 > ��    �ۣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	service_temp.price = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//�����ۿ���
	printf("\n                                                 > �� �� �ʣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	service_temp.discount = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Service VALUES(?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_temp.service_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)(&service_temp.start_time), 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)(&service_temp.end_time), 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_temp.travel_standard, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &service_temp.price, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 6, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &service_temp.discount, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}
	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > �����ӳɹ���\n");
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
		printf("\n                                                 > ������ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct service_node service_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                           [��α��5λ���֣�������нض�]\n\n");

	//�����α��
	printf("\n                                                 > ��α�ţ�");
	fgets(service_temp.service_number, 6, stdin);
	fflush(stdin);
	process_string(service_temp.service_number, 6);

	if (strcmp(service_temp.service_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Service WHERE service_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_temp.service_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ���ɾ���ɹ���\n");
	else
		printf("\n                                                 > ���ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	long len;
	struct service_node service_temp;

	system("cls");
	title();
	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Service;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, service_temp.service_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_TYPE_TIMESTAMP, &service_temp.start_time, 0, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_TYPE_TIMESTAMP, &service_temp.end_time, 0, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_CHAR, service_temp.travel_standard, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_LONG, &service_temp.price, 0, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_SHORT, &service_temp.discount, 0, &len);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);

	/*��ȡ���*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s\t", service_temp.service_number);
		printf("%d-%d-%d\t", service_temp.start_time.year, service_temp.start_time.month, service_temp.start_time.day);
		printf("%d-%d-%d\t", service_temp.end_time.year, service_temp.end_time.month, service_temp.end_time.day);
		printf("%s\t", service_temp.travel_standard);
		printf("%d\t", service_temp.price);
		printf("%d\n\n", service_temp.discount);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void service(){
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
		service_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_service(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_service(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_service(&dbhenv, &dbhdbc);
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