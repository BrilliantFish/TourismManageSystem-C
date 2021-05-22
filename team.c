#include "wrapper.h"

void add_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct team_node team_temp;
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                 [�����ź�5λ����]\n\n");

	//�����ź�
	printf("\n                                                 > �����źţ�");
	fgets(team_temp.team_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_temp.team_number, MAX_LENGTH);

	if (strcmp(team_temp.team_number, "E") == 0)
		return;

	//��������
	printf("\n                                                 > ����������");
	fgets(team_temp.team_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_temp.team_name, MAX_LENGTH);

	if (strcmp(team_temp.team_name, "E") == 0)
		return;

	//����ʵ������
	printf("\n                                                 > ʵ��������");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	team_temp.people_count = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//������ϵ��
	printf("\n                                                 > �� ϵ �ˣ�");
	fgets(team_temp.team_contact, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_temp.team_contact, MAX_LENGTH);

	if (strcmp(team_temp.team_contact, "E") == 0)
		return;

	//����סַ
	printf("\n                                                 > ס    ַ��");
	fgets(team_temp.contact_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_temp.contact_addr, MAX_LENGTH);

	if (strcmp(team_temp.contact_addr, "E") == 0)
		return;

	//������ϵ�绰
	printf("\n                                                 > ��ϵ�绰��");
	fgets(team_temp.contact_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_temp.contact_tel, MAX_LENGTH);

	if (strcmp(team_temp.contact_tel, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Team VALUES(?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_temp.team_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_temp.team_name, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &team_temp.people_count, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_temp.team_contact, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_temp.contact_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_temp.contact_tel, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}
	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ��������ӳɹ���\n");
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
		printf("\n                                                 > ���������ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct team_node team_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                 [�����ź�5λ����]\n\n");

	//���������ź�
	printf("\n                                                 > �����źţ�");
	fgets(team_temp.team_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(team_temp.team_number, MAX_LENGTH);

	if (strcmp(team_temp.team_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Team WHERE team_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, team_temp.team_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ������ɾ���ɹ���\n");
	else
		printf("\n                                                 > ������ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	long len;
	struct team_node team_temp;

	system("cls");
	title();
	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Team;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, team_temp.team_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, team_temp.team_name, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_SHORT, &team_temp.people_count, 0, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_CHAR, team_temp.team_contact, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_CHAR, team_temp.contact_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_CHAR, team_temp.contact_tel, MAX_LENGTH, &len);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);

	/*��ȡ���*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s\t", team_temp.team_number);
		printf("%s\t", team_temp.team_name);
		printf("%d\t", team_temp.people_count);
		printf("%s\t", team_temp.team_contact);
		printf("%s\t", team_temp.contact_tel);
		printf("%s\n\n", team_temp.contact_addr);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void team(){
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
		team_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_team(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_team(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_team(&dbhenv, &dbhdbc);
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