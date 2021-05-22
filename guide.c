#include "wrapper.h"

void add_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct guide_node guide_temp;
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                  [���α��6λ����]\n\n");

	//���뵼�α��
	printf("\n                                                 > ���α�ţ�");
	fgets(guide_temp.guide_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_number, MAX_LENGTH);

	if (strcmp(guide_temp.guide_number, "E") == 0)
		return;

	//�������֤��
	printf("\n                                                 > ���֤�ţ�");
	fgets(guide_temp.guide_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_id, MAX_LENGTH);

	if (strcmp(guide_temp.guide_id, "E") == 0)
		return;

	//��������
	printf("\n                                                 > ��    ����");
	fgets(guide_temp.guide_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_name, MAX_LENGTH);

	if (strcmp(guide_temp.guide_name, "E") == 0)
		return;

	//�����Ա� 
	printf("\n                                                 > ��    ��");
	fgets(guide_temp.guide_sex, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_sex, MAX_LENGTH);

	if (strcmp(guide_temp.guide_sex, "E") == 0)
		return;

	//�����������
	printf("\n                                                 > �������ڣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &guide_temp.guide_birth);

	if (strcmp(str, "E") == 0)
		return;

	//����סַ
	printf("\n                                                 > ס    ַ��");
	fgets(guide_temp.guide_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_addr, MAX_LENGTH);

	if (strcmp(guide_temp.guide_addr, "E") == 0)
		return;

	//������ϵ�绰
	printf("\n                                                 > ��ϵ�绰��");
	fgets(guide_temp.guide_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_tel, MAX_LENGTH);

	if (strcmp(guide_temp.guide_tel, "E") == 0)
		return;

	//��������
	printf("\n                                                 > ��    �֣�");
	fgets(guide_temp.guide_language, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_language, MAX_LENGTH);

	if (strcmp(guide_temp.guide_language, "E") == 0)
		return;

	//����ȼ�
	printf("\n                                                 > ��    ����");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	guide_temp.guide_level = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Guide VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_id, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_name, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_sex, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &guide_temp.guide_birth, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_tel, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_language, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 9, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &guide_temp.guide_level, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}
	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ������ӳɹ���\n");
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
		printf("\n                                                 > �������ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct guide_node guide_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [���α��6λ����]\n\n");

	//���뵼�α��
	printf("\n                                                 > ���α�ţ�");
	fgets(guide_temp.guide_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_number, MAX_LENGTH);

	if (strcmp(guide_temp.guide_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Guide WHERE guide_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_number, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ����ɾ���ɹ���\n");
	else
		printf("\n                                                 > ����ɾ��ʧ�ܣ�\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	long len;
	struct guide_node guide_temp;

	system("cls");
	title();
	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Guide;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, guide_temp.guide_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, guide_temp.guide_id, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, guide_temp.guide_name, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_CHAR, guide_temp.guide_sex, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_TYPE_TIMESTAMP, &guide_temp.guide_birth, 0, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_CHAR, guide_temp.guide_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 7, SQL_C_CHAR, guide_temp.guide_tel, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 8, SQL_C_CHAR, guide_temp.guide_language, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 9, SQL_C_SHORT, &guide_temp.guide_level, MAX_LENGTH, &len);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);

	/*��ȡ���*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s  ", guide_temp.guide_number);
		printf("%s  ", guide_temp.guide_id);
		printf("%s  ", guide_temp.guide_name);
		printf("%s  ", guide_temp.guide_sex);
		printf("%d-%d-%d\t", guide_temp.guide_birth.year, guide_temp.guide_birth.month, guide_temp.guide_birth.day);
		printf("%s  ", guide_temp.guide_tel);
		printf("%s  ", guide_temp.guide_language);
		printf("%d    ", guide_temp.guide_level);
		printf("%s\n\n", guide_temp.guide_addr);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void guide(){
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
		guide_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_guide(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_guide(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_guide(&dbhenv, &dbhdbc);
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