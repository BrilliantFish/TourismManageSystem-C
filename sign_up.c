#include "wrapper.h"

//�û�ע�ᣬע��ɹ�Ϊ1��ע��ʧ��Ϊ0���˳�-1
int sign_up(SQLHENV *dbhenv, SQLHDBC *dbhdbc, long consumer_level){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	struct consumer consumer_temp;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                            [�˺�8λ�����벻�ɳ���15λ]\n\n");

	//�����û��˺�
	printf("\n                                                 > �û��˺ţ�");
	fgets(consumer_temp.consumer_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(consumer_temp.consumer_id, MAX_LENGTH);
	
	if (strcmp(consumer_temp.consumer_id, "E") == 0)
		return -1;

	//�����û�����
	printf("\n                                                 > �û����룺");
	fgets(consumer_temp.pass_word, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(consumer_temp.pass_word, MAX_LENGTH);
	
	if (strcmp(consumer_temp.pass_word, "E") == 0)
		return -1;
	
	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Consumer VALUES(?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_temp.consumer_id, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_temp.pass_word, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &consumer_level, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ע��ɹ���\n");
	else
		printf("\n                                                 > ע��ʧ��,�û����ظ����ʽ���淶��\n");

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");

	return 0;
}

