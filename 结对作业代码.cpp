#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void show()
{
    int num1, num2, result;
    char oper;
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;

    // 随机选择运算符
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

    // 输出题目和结果
    printf("%d %c %d = ?\n", num1, oper, num2);
}
int main() {
    int n;
    // 设置随机数种子
    srand(time(NULL));
    printf("请输入需要生成的题目个数：");
    scanf("%d" ,& n);
    for (int i = 0; i < n; i++)
    {
        show();
    }
    return 0;
}