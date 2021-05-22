#include "wrapper.h"

void add_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct hotel_node hotel_temp;
	char str[MAX_LENGTH];
	char errmsg[256];
	long len;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [���ݱ��3λ����]\n\n");

	//������ݱ��
	printf("\n                                                 > ���ݱ�ţ�");
	fgets(hotel_temp.hotel_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_number, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_number, "E") == 0)
		return;

	//�����������
	printf("\n                                                 > �������ƣ�");
	fgets(hotel_temp.hotel_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_name, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_name, "E") == 0)
		return;

	//�������ڳ���
	printf("\n                                                 > ���ڳ��У�");
	fgets(hotel_temp.hotel_city, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_city, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_city, "E") == 0)
		return;

	//�����Ǽ�
	printf("\n                                                 > �����Ǽ���");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	hotel_temp.hotel_level = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//�����׼����
	printf("\n                                                 > ��׼���ۣ�");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	hotel_temp.hotel_price = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//������ϵ��
	printf("\n                                                 > �� ϵ �ˣ�");
	fgets(hotel_temp.hotel_contact, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_contact, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_contact, "E") == 0)
		return;

	//������ϵ��ְ��
	printf("\n                                                 > ְ    ��");
	fgets(hotel_temp.contact_duty, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.contact_duty, MAX_LENGTH);

	if (strcmp(hotel_temp.contact_duty, "E") == 0)
		return;

	//������ϵ��ַ
	printf("\n                                                 > ��ϵ��ַ��");
	fgets(hotel_temp.hotel_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_addr, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_addr, "E") == 0)
		return;

	//������ϵ�绰
	printf("\n                                                 > ��ϵ�绰��");
	fgets(hotel_temp.hotel_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_tel, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_tel, "E") == 0)
		return;

	//���봫��
	printf("\n                                                 > ��    �棺");
	fgets(hotel_temp.hotel_fax, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_fax, MAX_LENGTH);;

	if (strcmp(hotel_temp.hotel_fax, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Hotel VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		SQLBindParameter(dbhstmt, 1,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_number,  0, NULL);
		SQLBindParameter(dbhstmt, 2,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_name,    0, NULL);
		SQLBindParameter(dbhstmt, 3,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_city,    0, NULL);
		SQLBindParameter(dbhstmt, 4,  SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0,          0, &hotel_temp.hotel_level,  0, NULL);
		SQLBindParameter(dbhstmt, 5,  SQL_PARAM_INPUT, SQL_C_LONG,  SQL_INTEGER,  0,          0, &hotel_temp.hotel_price,  0, NULL);
		SQLBindParameter(dbhstmt, 6,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_contact, 0, NULL);
		SQLBindParameter(dbhstmt, 7,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.contact_duty,  0, NULL);
		SQLBindParameter(dbhstmt, 8,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_addr,    0, NULL);
		SQLBindParameter(dbhstmt, 9,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_tel,     0, NULL);
		SQLBindParameter(dbhstmt, 10, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_fax,     0, NULL);
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

void delete_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct hotel_node hotel_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [���ݱ��3λ����]\n\n");

	//������ݱ��
	printf("\n                                                 > ���ݱ�ţ�");
	fgets(hotel_temp.hotel_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_number, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_number, "E") == 0)
		return;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Hotel WHERE hotel_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, hotel_temp.hotel_number, 0, NULL);
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

void query_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	long len;
	struct hotel_node hotel_temp;

	system("cls");
	title();
	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Hotel;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, hotel_temp.hotel_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, hotel_temp.hotel_name, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, hotel_temp.hotel_city, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_SHORT, &hotel_temp.hotel_level, 0, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_LONG, &hotel_temp.hotel_price, 0, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_CHAR, hotel_temp.hotel_contact, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 7, SQL_C_CHAR, hotel_temp.contact_duty, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 8, SQL_C_CHAR, hotel_temp.hotel_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 9, SQL_C_CHAR, hotel_temp.hotel_tel, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 10, SQL_C_CHAR, hotel_temp.hotel_fax, MAX_LENGTH, &len);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);

	/*��ȡ���*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s  ", hotel_temp.hotel_number);
		printf("%s", hotel_temp.hotel_name);
		printf("%s", hotel_temp.hotel_city);
		printf("%d   ", hotel_temp.hotel_level);
		printf("%d   ", hotel_temp.hotel_price);
		printf("%s", hotel_temp.hotel_contact);
		printf("%s   ", hotel_temp.hotel_tel);
		printf("%s", hotel_temp.contact_duty);	
		printf("%s   ", hotel_temp.hotel_fax);
		printf("%s\n\n", hotel_temp.hotel_addr);
		ret = SQLFetch(dbhstmt);
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void hotel(){
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
		hotel_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> ��ѡ��Ҫִ�еĹ���: ");
		else
			printf("                               -> ������������ȷѡ��Ҫִ�еĹ���: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_hotel(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_hotel(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_hotel(&dbhenv, &dbhdbc);
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