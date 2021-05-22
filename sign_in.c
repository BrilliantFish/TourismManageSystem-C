#include "wrapper.h"

int sign_in(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*�������ͱ���*/
	SQLHSTMT dbhstmt;       //�����
	SQLRETURN ret;          //����ֵ
	long len;
	long consumer_level = -1;

	system("cls");
	title();
	printf("                                                     ���� E �˳�\n");
	printf("                           ----------------------------------------------------------------\n\n");

	//�����û��˺�
	printf("\n                                                 > �û��˺ţ�");
	fgets(consumer_node.consumer_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(consumer_node.consumer_id, MAX_LENGTH);

	if (strcmp(consumer_node.consumer_id, "E") == 0)
		return -1;

	//�����û�����
	printf("\n                                                 > �û����룺");
	fgets(consumer_node.pass_word, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(consumer_node.pass_word, MAX_LENGTH);

	if (strcmp(consumer_node.pass_word, "E") == 0)
		return -1;

	/*���������������ʼ�������*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*Ԥ�����������SQL��䣬�����в�����*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT consumer_level FROM Consumer WHERE consumer_id = ? and pass_word = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_node.consumer_id, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_node.pass_word, 0, NULL);
	}
	else{
		printf("������ʧ�ܣ�\n");
		exit(0);
	}
	ret = SQLBindCol(dbhstmt, 1, SQL_C_LONG, &consumer_level, 0, &len);

	/*ִ��������е�SQL���*/
	ret = SQLExecute(dbhstmt);

	/*��ȡ���*/
	ret = SQLFetch(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > ��½�ɹ���\n");
	else{
		printf("\n                                                 > ��½ʧ��,�û��������ڣ�\n");
		consumer_level = -1;
	}

	/*�ͷ������*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");

	return consumer_level;
}