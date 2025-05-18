// Chương trình này tính tổng các số có độ dài không cố định dựa vào thư viện stdarg và macro variadic sử dụng số 0 báo hiệu kết thúc
// Nhược điểm: nếu trong dãy số có số 0 thì sẽ tính sai do bị kết thúc khi chưa duyệt hết dãy số
#include <stdio.h>
#include <stdarg.h>
#define sum(...) tong(__VA_ARGS__, 0)
int tong(int first_number, ...)
{
    va_list args;
    va_start(args, first_number);
    int result = first_number;
    int current_value = 0;
    while ((current_value = va_arg(args, int)) != 0)
    {
        result += current_value;
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(1, 2, 3, 4, 5, 6); // Hàm này chạy đúng
    sum(1, 2, 3, 0, 5, 6); // Hàm này chạy sai do có số 0 trong dãy số
}