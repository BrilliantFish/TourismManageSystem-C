#include "wrapper.h"

void add_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct route_node route_temp;
	char str[MAX_LENGTH];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                         [·�߱��4λ���֣�������нض�]\n\n");

	//����·�߱��
	printf("\n                                                 > ·�߱�ţ�");
	fgets(route_temp.route_number, 5, stdin);
	fflush(stdin);
	process_string(route_temp.route_number, 5);

	if (strcmp(route_temp.route_number, "E") == 0)
		return;

	//�������
	printf("\n                                                 > ������㣺");
	fgets(route_temp.start_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_temp.start_addr, MAX_LENGTH);

	if (strcmp(route_temp.start_addr, "E") == 0)
		return;

	//�����յ�
	printf("\n                                                 > �����յ㣺");
	fgets(route_temp.end_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_temp.end_addr, MAX_LENGTH);

	if (strcmp(route_temp.end_addr, "E") == 0)
		return;

	//������������
	printf("\n                                                 > ����������");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	route_temp.days_count = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//������Ҫ����
	printf("\n                                                 > ��Ҫ���㣺");
	fgets(route_temp.main_attraction, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_temp.main_attraction, MAX_LENGTH);

	if (strcmp(route_temp.main_attraction, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Route VALUES(?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.route_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.start_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.end_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &route_temp.days_count, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.main_attraction, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ·����ӳɹ���\n");
	else
		printf("\n                                                 > ·�����ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct route_node route_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                         [·�߱��4λ���֣�������нض�]\n\n");

	//����·�߱��
	printf("\n                                                 > ·�߱�ţ�");
	fgets(route_temp.route_number, 5, stdin);
	fflush(stdin);
	process_string(route_temp.route_number, 5);

	if (strcmp(route_temp.route_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Route WHERE route_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.route_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ·��ɾ���ɹ���\n");
	else
		printf("\n                                                 > ·��ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	long len;
	struct route_node route_temp;

	system("cls");
	title();
	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Route;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, route_temp.route_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, route_temp.start_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, route_temp.end_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_SHORT, &route_temp.days_count, 0, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_CHAR, route_temp.main_attraction, MAX_LENGTH, &len);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);

	/*��ȡ���*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s\t%s\t%s\t%d\t%s\n\n", route_temp.route_number, route_temp.start_addr, route_temp.end_addr, route_temp.days_count, route_temp.main_attraction);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void route(){
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
		route_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
			case 1:
				add_route(&dbhenv, &dbhdbc);
				break;
			case 2:
				delete_route(&dbhenv, &dbhdbc);
				break;
			case 3:
				query_route(&dbhenv, &dbhdbc);
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