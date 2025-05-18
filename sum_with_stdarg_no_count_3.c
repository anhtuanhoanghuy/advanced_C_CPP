// Chương trình này tính tổng các số có độ dài không cố định dựa vào thư viện stdarg và macro variadic sử dụng chuỗi "end" báo hiệu kết thúc
// Lưu ý: phải gọi va_start trước va_copy
#include <stdio.h>
#include <stdarg.h>
#define tong(...) sum(__VA_ARGS__, "end")
int sum(int first_number, ...)
{
    va_list args;
    va_list check;
    va_start(args, first_number);
    va_copy(check, args);
    int result = first_number;
    while (va_arg(check, char *) != "end")
    {
        result += va_arg(args, int);
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(1, 2, 3, 4, 5);
}