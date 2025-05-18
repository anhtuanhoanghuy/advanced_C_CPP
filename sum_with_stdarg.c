// Chương trình này tính tổng các số có độ dài không cố định dựa vào tham số đầu tiên chỉ định độ dài của dãy số
// Nhược điểm: khi truyền đối số cần phải truyền vào độ dài của dãy số
// Nếu truyền vào độ dài count của dãy số bé hơn số phần tử của dãy số thì chương trình tính tổng sẽ chỉ tính đến số phần tử thứ count
// Nếu truyền vào độ dài count của dãy số lớn hơn số phần tử của dãy số thì chương trình tính tổng sẽ có thể bị sai do giá trị bên ngoài có thể là 0 hoặcoặc là giá trị rácrác
#include <stdio.h>
#include <stdarg.h>
int sum(int count, ...)
{
    va_list args;
    va_start(args, count);
    int result = 0;
    for (int i = 0; i < count; i++)
    {
        result += va_arg(args, int);
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(5, 1, 2, 3, 4, 5);       // Hàm này chạy đúng
    sum(5, 1, 2, 3, 4, 5, 6, 7); // Hàm này chạy sai do tính thiếu giá trịtrị
    sum(7, 1, 2, 3, 4, 5);       // Hàm này chạy sai do truyền thừa số phần tử
}