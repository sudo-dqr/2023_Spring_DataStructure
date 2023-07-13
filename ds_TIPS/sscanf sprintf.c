
/*
�ַ���ת��������sprintf
printf����ͬ�����������Ļ�ϣ���Ļ����ı��ʾ����ַ���
sprintf���ֱ�ӱ��浽�ַ�����
��printf���˵�һ����������Ҫ�洢���ַ�������
int sprintf(char *buf,char *format[argument...]);

int main()
{
	int m;
	double x;
	char format[32];
	scanf("%lf%d", &x, &m);
	sprintf(format, "%%.%df", m);//�����ʽ�ַ�����������ַ����У�����%����ʾΪһ��
	printf(format, sin(x));
	return 0;
}
ͨ��������ӿ���֪��printf("%d",a);�ȵ�ǰ�����ʵ����һ���ַ�������Ϊ��ʽ�ַ���

sscanf
scanf�Ӽ��̶���һ�����ţ����뵽��ͬ������
sscanf�ǴӸ������ַ����ж���,ͨ����ʽ�ַ������ƶ��뷽ʽ
��scanf��һ��������Ҫ��ȡ���ַ���
char buf[] = "17/APR/2018:10:28:28 +0800";
	sscanf(buf,"%d/%3c/%d:%d:%d:%d %s", &day, mon, &year, &h, &m,&s, zone);
	��ȡ��ͨ����ʱ��&��������ַ���ʱҪ��ĩβ����'\0';����������������
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
int main()
{
	int day, year, h, m, s;
	char mon[4], zone[6];
	char buf[] = "17/APR/2018:10:28:28 +0800";
	sscanf(buf,"%d/%3c/%d:%d:%d:%d %s", &day, mon, &year, &h, &m,&s, zone);
	mon[3] = '\0';
	printf("%d\n%s\n%d\n%d\n%d\n%d\n%s", day, mon, year, h,m, s, zone);
	return 0;
}