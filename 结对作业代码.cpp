#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void show()
{
    int num1, num2, result;
    char oper;
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;

    // ���ѡ�������
    switch (rand() % 4) {
    case 0:
        oper = '+';
        result = num1 + num2;
        break;
    case 1:
        oper = '-';
        result = num1 - num2;
        break;
    case 2:
        oper = '*';
        result = num1 * num2;
        break;
    case 3:
        oper = '/';
        result = num1 / num2;
        break;
    }

    // �����Ŀ�ͽ��
    printf("%d %c %d = ?\n", num1, oper, num2);
}
int main() {
    int n;
    // �������������
    srand(time(NULL));
    printf("��������Ҫ���ɵ���Ŀ������");
    scanf("%d" ,& n);
    for (int i = 0; i < n; i++)
    {
        show();
    }
    return 0;
}