
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
  + 
# Bài 4: Pointer
## 4.1. Khái niệm và cách sử dụng
- Trong ngôn ngữ lập trình C, con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một đối tượng khác (biến, mảng, hàm). 
- Cách khai báo: data_type * data_name;
```c
    int *ptr_int;
    char *ptr_char;
    float *ptr_float;
```
- Lấy địa chỉ của một biến:
```c
    int x = 10;
    int *ptr_int = &x;
    int *ptr_int2;
    ptr_int2 = &x;
```
- Truy cập giá trị (giải tham chiếu):
```c
    int x = 10;
    int *ptr_int = &x;
    int y = *ptr_int //(y = 10);
```
- Kích thước của con trỏ: Kích thước của con trỏ không phụ thuộc vào kiểu dữ liệu mà con trỏ trỏ đến. Kích thước của con trỏ phụ thuộc vào kiến trúc của vi xử lý và trình biên dịch. Ví dụ với kiến trúc x64 thì kích thước của con trỏ là 8 bytes, x32 là 4 bytes.
## 4.2. Các loại con trỏ đặc biệt
### 4.2.1. Con trỏ Void
- Con trỏ Void là con trỏ không trỏ có thể trỏ đến bất kì kiểu dữ liệu nào
- Để giải tham chiếu với con trỏ Void, cần ép kiểu cho con trỏ Void thành kiểu dữ liệu xác đinh.
VD:
```c
    int x = 3;
    double y = 3.5;
    void *ptr = &x;
    printf("%d\n",*(int*)ptr);
    ptr = &y;
    printf("%f\n",*(double*)ptr);
```
### 4.2.2. Con trỏ NULL
- Con trỏ NULL là con trỏ không trỏ đến bất kỳ đối tượng hoặc vùng nhớ cụ thể nào. 
- Cú pháp: data_type *data_name = NULL;
- Sử dụng null pointer thường hữu ích để kiểm tra xem một con trỏ đã được khởi tạo và có trỏ đến một vùng nhớ hợp lệ chưa. Tránh dereferencing (sử dụng giá trị mà con trỏ trỏ đến) một null pointer là quan trọng để tránh lỗi chương trình.
### 4.2.3. Con trỏ trỏ tới hằng
- Là con trỏ trỏ tới 1 biến là hằng số hoặc biến thông thường, không thể thay đổi được giá trị của biến đó nhưng có thể thay đổi được địa chỉ mà con trỏ trỏ đến.
VD:
```c
    int x = 5;
    int y =10;
    const int *ptr = &x;
    ptr = &y; // Câu lệnh này thực hiện đúng vì con trỏ hằng có thể thay đổi địa chỉ mà nó trỏ tới
   *ptr = 10; // Câu lệnh này sai vì con trỏ hằng không thể thay đổi giá trị mà ở địa chỉ mà nó trỏ đến
    printf("%d",*ptr);
```
### 4.2.4. Hằng con trỏ
- Là con trỏ kiẻu hằng số, nó không thể thay đổi được địa chỉ mà nó trỏ đến nhưng có thể thay đổi được giá trị ở địa chỉ mà nó trỏ đến.
  VD:
```c
    int x = 5;
    int y =10;
    int *const ptr = &x;
    ptr = &y; // Câu lệnh này sai vì con trỏ hằng không thể thay đổi địa chỉ mà nó trỏ tới
   *ptr = 10; // Câu lệnh này đúng vì con trỏ hằng có thể thay đổi giá trị mà ở địa chỉ mà nó trỏ đến
    printf("%d",*ptr);
```
### 4.2.5. Hằng con trỏ hằng
- Là con trỏ vừa không thể thay đổi được địa chỉ mà con trỏ trỏ đến vừa không thay đổi được giá trị ửo địa chỉ mà con trỏ trỏ đến.
VD:
```c
    int x = 5;
    int y =10;
    int *const ptr = &x;
    ptr = &y; // Câu lệnh này sai vì con trỏ hằng không thể thay đổi địa chỉ mà nó trỏ tới
   *ptr = 10; // Câu lệnh này sai vì con trỏ hằng không thể thay đổi giá trị mà ở địa chỉ mà nó trỏ đến
```
### 4.2.6. Con trỏ hàm
- Là một biến mà giữ địa chỉ của một hàm. Có nghĩa là, nó trỏ đến vùng nhớ trong bộ nhớ chứa mã máy của hàm được định nghĩa trong chương trình.
- Trong ngôn ngữ lập trình C, con trỏ hàm cho phép bạn truyền một hàm như là một đối số cho một hàm khác, lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu, hoặc thậm chí truyền hàm như một giá trị trả về từ một hàm khác.
- Cú pháp: return_type (*function_name)(param);
VD:
```c
int tong(int a, int b) {
    return a+b;
}

int main()
{
  int (*tinh)(int, int);
  tinh = tong;
  return  tinh(3,4);
}
```
VD: Sử dụng mảng con trỏ hàm:
```c
int tong(int a, int b) {
    return a+b;
}

int hieu(int a, int b) {
    return a-b;
}

int main()
{
    int (*calculate[])(int, int) = {tong, hieu};
    return calculate[1](5,4);
}
```
VD: Sử dụng Call back để gọi hàm
```c
int tong(int a, int b) {
    return a+b;
}

int hieu(int a, int b) {
    return a-b;
}

int calculate(int (*pheptoan)(int, int), int a, int b) {
    pheptoan(a,b);
}

int main()
{
  return calculate(hieu,6,5);
}
```
### 4.2.7. Con trỏ trỏ đến con trỏ (con trỏ lồng nhau)
- Là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ khác.
VD:
```c
int a = 5;
int *b = &a;
int **c = &b;
```
## 4.2. Endianness
- Thứ tự lưu giá trị phụ thuộc vào kiến trúc của vi xử lý. 2 kiểu lưu thứ tự phổ biến là Little Endian và Big Endian.
- Little Endian: Byte thấp nhất sẽ được lưu ở địa chỉ cao nhất.
|Address:|0x04|0x03|0x02|0x01|
|Value:0x|12|34|56|78|

- Big Endian: Byte cao nhất sẽ được lưu ở địa chỉ thấp nhất.
|Address:|0x01|0x02|0x03|0x04|
|Value:0x|12|34|56|78|

## 4.3. Mảng
- Mảng là 1 nhóm các ô nhớ liền kề nhau dùng để lưu trữ các phần tử cùng kiểu
- Tên mảng thực chất là 1 con trỏ, luôn trỏ đến địa chỉ đầu tiên của mảng
- Để gán địa chỉ của mảng cho một con trỏ chỉ cần viết tên của mảng không cần & 
- Nếu không gán giá trị trước cho mảng thì phải khai báo số lượng phần tử trong mảng
- Có thể gán giá trị riêng lẻ cho từng phần tử
- Truyền mảng vào hàm trong C là truyền tham chiếu (truyền địa chỉ phần tử đầu tiên của mảng vào hàm) arr = &arr = &arr[0]
- Khi truyền mảng vào hàm thì truyền như biến, không cần &
- Để trả về mảng từ hàm: cần khai báo kiểu hàm là con trỏ, khai báo mảng static và biến con trỏ để gán mảng trả về

# Bài 5: Storage Class Specifier
## 5.1. Extern
- Extern trong ngôn ngữ lập trình C/C++ là từ khóa được sử dụng để thông báo rằng một biến hoặc hàm đã được khai báo ở một nơi khác trong chương trình hoặc trong một file nguồn khác. 
- Điều này giúp chương trình hiểu rằng biến hoặc hàm đã được định nghĩa và sẽ được sử dụng từ một vị trí khác, giúp quản lý sự liên kết giữa các phần khác nhau của chương trình hoặc giữa các file nguồn.
## 5.2. Static
### 5.2.1. Local static
- Khi static được sử dụng với biến cục bộ (khai báo biến trong một hàm):
    + Giữ phạm vi của biến chỉ trong hàm đó.
    + Giữ giá trị của biến qua các lần gọi hàm.
    + Để thay đổi giá trị của biến static trong hàm, cần sử dụng con trỏ toàn cục để trỏ đến địa chỉ của biến static này.
```c
void exampleFunction()
{
    static int count = 0;  // Biến static giữ giá trị qua các lần gọi hàm
    count++;
    printf("Count: %d\n", count);
}

int main()
{
    exampleFunction();  // In ra "Count: 1"
    exampleFunction();  // In ra "Count: 2"
    exampleFunction();  // In ra "Count: 3"
    return 0;
}
```
### 5.2.2. Global static
- Khi static được sử dụng với biến, hàm toàn cục, nó hạn chế phạm vi của biến, hàm đó chỉ trong file nguồn hiện tại.
- Ứng dụng: dùng để thiết kế các file thư viện.

### 5.3. Volatile
- Từ khóa volatile trong ngôn ngữ lập trình C/C++ được sử dụng để báo hiệu cho trình biên dịch rằng một biến có thể thay đổi ngẫu nhiên, ngoài sự kiểm soát của chương trình. Ví dụ:
    + Bị thay đổi bởi phần cứng (thanh ghi)
    + Bị thay đổi bởi một luồng khác (đa luồng)
    + Bị thay đổi bởi ngắt (interrupt handler)
- Volatile giúp ngăn chặn trình biên dịch tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.

### 5.4. Register
- Chỉ sử dụng cho biến local
- Từ khóa register được sử dụng để chỉ ra một biến được sử dụng thường xuyên và có thể được lưu trữ trong một thanh ghi máy tính, chứ không phải trong bộ nhớ stack trong RAM, sử dụng để bỏ qua quá trình load dữ liệu từ bộ nhớ. Việc này nhằm tăng tốc độ truy cập.
- Nếu không đủ thanh ghi, compiler vẫn có thể lưu vào RAM như bình thường.
- Không có địa chỉ bộ nhớ cụ thể nên không dùng được con trỏ để trỏ tới.
