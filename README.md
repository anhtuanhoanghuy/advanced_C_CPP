
# BÀI 1: Compiler - Macros
## 1.1. Compiler
Quá trình biên dịch chương trình:
- Bước 1: Pre-processor: tiền xử lý
    Chương trình C khi qua quá trình tiền xử lý sẽ build các file .h sang .i : loại bỏ chú thích, copy code từ các file include sang, thay thế các macro

- Bước 2: Compiler:
    Chương trình sau khi qua quá trình tiền xử lý sẽ được dịch sang mã Assembly, build từ file .i sang .s

- Bước 3: Assembler
    Chương trình tiép tục build từ file.s sang .o. Ở quá trình này, mã nguồn sẽ được chuyển sang mã nhị phân để máy tính có thể hiểu được.

- Bước 4: Linker
    Giai đoạn này trình biên dịch sẽ liên kết các file .o lại với nhau để tạo thành một file thực thi cuối cùng .exe. Từ đây chương tình đã có thể chạy được.

## 1.2. Macros

- Macros là từ hay chỉ thị dùng để chỉ những thông tin được xử lý ở quá trình tiền xử lý.

### Các loại Macros:
- `#include`: liên kết các thư viện, các file mã nguồn khác  
  + `#include <>`: dùng cho thư viện chuẩn, tìm trong thư mục hệ thống  
  + `#include ""`: tìm kiếm trong thư mục hiện tại hoặc do người dùng định nghĩa
- `#define`: macro định nghĩa giá trị, hàm; không kiểm tra lỗi hay kiểu dữ liệu
- `##`: dùng để nối chuỗi token
- `#`: chuẩn hóa tham số thành chuỗi văn bản
- `...`: khai báo tham số không xác định (variadic)
- `__VA_ARGS__`: đại diện cho danh sách tham số truyền vào
- `#undef`: hủy định nghĩa macro
- `#if`, `#ifdef`, `#ifndef`, `#endif`: dùng để kiểm tra điều kiện biên dịch theo macro

# BÀI 2: STDARG - ASSERT
## 2.1. Định nghĩa:
Thư viện stdarg cung cấp các phương thức để làm việc với các hàm số có số lượng tham sô đầu vào không cố định
## 2.2. Các hàm thường dùng:
- va_list: kiểu struct, khia báo một biến để chức các tham số có độ dài không xác định
- va_start: bắt buộc để khởi tạo va_list và cho phép bạn truy cập các đối số biến đổi (sau đối số cố định) trong hàm. Nếu bạn không gọi va_start, thì việc gọi va_arg sẽ truy cập vào vùng nhớ rác (undefined behavior).
- va_arg: lấy ra lần lượt giá trị của tham số sau mỗi lần gọi và ép kiểu cho tham số đó
- va_end: thu hồi, kết thúc truy cập danh sách tham số không xác định
- va_copy: Sao chép dữ liệu giữa 2 biến cùng kiểu va_list.
## 2.3. Các ví dụ với __VAR_ARGS__ và thư viện stdarg
```c
// Chương trình này tính tổng các số có độ dài không cố định dựa vào macro variadic
// Nguyên lý: Sử dụng một mảng để lưu các đối số truyền vào, tính độ dài của mảng bằng công thức sizeof(array)/ sizeof(aray[0]) sau đó duyệt từ đầu đến cuối mảng
#include <stdio.h>
#define sum(...)                                                 \
    int array[] = {__VA_ARGS__};                                 \
    int result = 0;                                              \
    for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) \
    {                                                            \
        result += array[i];                                      \
    }                                                            \
    printf("Tong: %d", result);

void main()
{
    sum(1, 2, 3, 4, 5, 6);
}
```

```c
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
```

```c
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
```

```c
// Chương trình này tính tổng các số có độ dài không cố định dựa vào thư viện stdarg và macro variadic sử dụng kí tự '0' báo hiệu kết thúc
// Nhược điểm: nếu trong dãy số có số là mã ascii của kí tự '0' (48) thì sẽ tính sai do bị kết thúc khi chưa duyệt hết dãy số
#include <stdio.h>
#include <stdarg.h>
#define sum(...) tong(__VA_ARGS__, '0')
int tong(int first_number, ...)
{
    va_list args;
    va_start(args, first_number);
    int result = first_number;
    int current_value = 0;
    while ((current_value = (va_arg(args, int))) != '0')
    {
        result += current_value;
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(1, 2, 3, 4);  // Hàm này chạy đúng
    sum(1, 2, 48, 5); // Hàm này chạy sai do có số 48 là mã ascii của kí tụ '0'
}
```

```c
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
```

```c
// Chương tình này sử dụng macro variadic để in ra một menu
#include <stdio.h>
#define print_menu(...)                                          \
    char *array[] = {__VA_ARGS__};                               \
    for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) \
    {                                                            \
        printf("%d. %s\n", i + 1, array[i]);                     \
    }

void main()
{
    print_menu("Trang chủ", "Giới thiệu", "Sản phẩm", "Liên hệ", "Cài đặt");
}
```

```c
// Chương trình này sử dụng macro variadic để thực hiện một chức năng được khi chọn option trong menu
#include <stdio.h>
#define print_menu(...)                                              \
    do                                                               \
    {                                                                \
        char *array[] = {__VA_ARGS__};                               \
        for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) \
        {                                                            \
            printf("%d. %s\n", i + 1, array[i]);                     \
        }                                                            \
    } while (0);

#define case_option(number, function) \
    case number:                      \
        function;                     \
        break;

#define switch_handle(option, ...) \
    switch (option)                \
    {                              \
        __VA_ARGS__;               \
    default:                       \
        break;                     \
    }
void feature1()
{
    printf("Đã mở Trang chủ\n");
}
void feature2()
{
    printf("Đã mở Giới thiệu\n");
}
void feature3()
{
    printf("Đã mở Sản phẩm\n");
}
void feature4()
{
    printf("Đã mở Liên hệ\n");
}
void feature5()
{
    printf("Đã mở Cài đặt\n");
}
int main()
{
    print_menu("Trang chủ", "Giới thiệu", "Sản phẩm", "Liên hệ", "Cài đặt");
    int item;
    printf("Chọn chức năng: ");
    scanf("%d", &item);
    switch_handle(item,
        case_option(1, feature1())
        case_option(2, feature2())
        case_option(3, feature3())
        case_option(4, feature4())
        case_option(5, feature5()));
    // switch (item)
    // {
    // case 1:
    //     feature1();
    //     break;
    // case 2:
    //     feature2();
    //     break;
    // case 3:
    //     feature3();
    //     break;
    // case 4:
    //     feature4();
    //     break;
    // case 5:
    //     feature5();
    //     break;
    // default:
    //     break;
    // }
    // return 0;
}
```

## 2.4. Assert
- Định nghĩa: thư viện assert cung cấp các macro dùng để kiểm tra một điều kiện. Nếu điều kiện đúng, không có gì xảy ra và chương trình tiếp tục được thực thi. Nếu điều kiện sai, chương trình sẽ dừng lại và thông báo một thông điệp lỗi.

## 2.5. Ví dụ sử dụng thư viện assert
```c
//Chương trình này sử dụng thư viện assert để kiểm tra điều kiện
#include <stdio.h>
#include <assert.h>
int divide(int a,int b){
  assert(b != 0 && "Không được chia cho 0");
    printf("result: %d",a/b);
}
void main(){
    divide(6,2); //hàm này chạy đúng và không thông báo lỗi
    divide(6,0); //hàm này chạy sai vì chia cho 0, dừng chương trình, in ra thông báo lỗi kèm dòng bị lỗi
}
```
# BÀI 3: BITMASK
## 3.1. Định nghĩa:
- Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái. Có thể sử dụng bitmask để đặt, xóa và kiểm tra trạng thái của các bit cụ thể.
- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.
## 3.2. Các phép toán thao tác với bit và bitmask
- Bật bit i: n|(1<<i)
- Tắt bit i: n & ~(1<<i)
- Kiểm tra bit thứ i: (n >> i) & 1 hoặc n & (1<<i)
- Đảo bit thứ i: n^ (1<<i)
- Kiểm tra bit cuối: n & 1
## 3.3. Độ ưu tiên của các toán tử
() ---> */ ---> +- ---> bitwise
## 3.4. Bit field
- Dùng để chia nhỏ các thành viên trong struct theo số lượng bit cụ thể, thay vì theo kiểu dữ liệu thông thường (byte) để tối ưu bộ nhớ
- Cú pháp: data_type data_name : bit_count
- Đặc điểm:
    + Không thể truy cập được địa chỉ của từng bit
    + Vị trí của bit field phụ thuộc vào Compiler
    + Thứ tự bit field tùy vào Endianess