#define MAX_LENGTH 100
struct consumer{
	char consumer_id[MAX_LENGTH];
	char pass_word[MAX_LENGTH];
};
struct consumer consumer_node;

struct route_node{
	char route_number[MAX_LENGTH];    //·�߱��
	char start_addr[MAX_LENGTH];      //���
	char end_addr[MAX_LENGTH];        //�յ�
	short days_count;                 //��������
	char main_attraction[MAX_LENGTH]; //��Ҫ����
};

struct service_node{
	char service_number[MAX_LENGTH];     //��α��
	TIMESTAMP_STRUCT start_time;         //��������
	TIMESTAMP_STRUCT end_time;           //�س�����
	char travel_standard[MAX_LENGTH];    //���α�׼, ��ѡ����Ա����ʯ���ʹ�
	long price;                          //����
	short discount;                      //�ۿ���
};

struct team_node{
	char team_number[MAX_LENGTH];    //�ź�
	char team_name[MAX_LENGTH];      //����	
	short people_count;              //ʵ������
	char team_contact[MAX_LENGTH];   //��ϵ��
	char contact_addr[MAX_LENGTH];   //סַ
	char contact_tel[MAX_LENGTH];    //��ϵ�绰
};

struct tourist_node{
	char tourist_number[MAX_LENGTH];     //�οͱ��
	char tourist_id[MAX_LENGTH];         //���֤��
	char tourist_name[MAX_LENGTH];       //����
	char tourist_sex[MAX_LENGTH];        //�Ա�
	TIMESTAMP_STRUCT tourist_birth;      //��������
	char tourist_addr[MAX_LENGTH];       //סַ
	char tourist_tel[MAX_LENGTH];        //��ϵ�绰
	char route_number[MAX_LENGTH];       //����·��, �����ֵ
	TIMESTAMP_STRUCT start_time;         //����ʱ��
	TIMESTAMP_STRUCT end_time;           //�س�ʱ��
	char consumer_number[MAX_LENGTH];    //�����û�
};

struct insure_node{
	char insure_number[MAX_LENGTH];         //���յ���
	long avg_price;             //�˾����շ�
	TIMESTAMP_STRUCT deadline;  //��������
};

struct hotel_node{
	char hotel_number[MAX_LENGTH];      //���ݱ��
	char hotel_name[MAX_LENGTH];        //��������
	char hotel_city[MAX_LENGTH];        //���ڳ���
	short hotel_level;                  //�Ǽ�
	long hotel_price;                   //��׼����
	char hotel_contact[MAX_LENGTH];     //��ϵ��
	char contact_duty[MAX_LENGTH];      //��ϵ��ְ��
	char hotel_addr[MAX_LENGTH];        //��ϵ��ַ
	char hotel_tel[MAX_LENGTH];         //��ϵ�绰
	char hotel_fax[MAX_LENGTH];         //����

};

struct guide_node{
	char guide_number[MAX_LENGTH];          //���α��
	char guide_id[MAX_LENGTH];              //���֤��
	char guide_name[MAX_LENGTH];            //����
	char guide_sex[MAX_LENGTH];             //�Ա�
	TIMESTAMP_STRUCT guide_birth;           //��������
	char guide_addr[MAX_LENGTH];            //סַ
	char guide_tel[MAX_LENGTH];             //��ϵ�绰
	char guide_language[MAX_LENGTH];        //����
	short guide_level;                      //�ȼ�
};