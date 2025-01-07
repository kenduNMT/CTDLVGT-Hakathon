#include <stdio.h>
#include <stdlib.h>
//HCM_ENG_KS23A_NguyenMinhThuan_01
// Định nghĩa cấu trúc Node
typedef struct Node
{
    int data;            
    struct Node *next;   
} Node;

// Tạo một node mới với giá trị cho trước
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) // Kiểm tra việc cấp phát bộ nhớ
    {
        printf("Khong the cap phat bo nho!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Khởi tạo danh sách liên kết (đặt head là NULL)
void initializeList(Node **head)
{
    *head = NULL;
}

// Thêm một phần tử vào đầu danh sách
void addFirst(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head; // Liên kết node mới với danh sách hiện tại
    *head = newNode;       // Cập nhật head trỏ tới node mới
}

// Thêm một phần tử vào cuối danh sách
void addLast(Node **head, int data)
{
    Node *newNode = createNode(data);
    if (*head == NULL) 
    {
        *head = newNode; // Node mới trở thành node đầu tiên
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode; // Thêm node mới vào cuối
}

// Chèn phần tử vào vị trí cụ thể trong danh sách
void insertAtPosition(Node **head, int data, int position)
{
    if (position < 0) // Kiểm tra vị trí hợp lệ
    {
        printf("Vi tri khong hop le!\n");
        return;
    }
    if (position == 0) // Nếu vị trí là đầu danh sách
    {
        addFirst(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *temp = *head;
    // Duyệt tới vị trí cần chèn
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL) // Nếu vị trí vượt quá độ dài danh sách
    {
        printf("Vi tri vuot qua danh sach!\n");
        free(newNode); // Giải phóng bộ nhớ cho node mới
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode; // Chèn node mới vào danh sách
}

// Xóa phần tử đầu tiên trong danh sách
void deleteFirst(Node **head)
{
    if (*head == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }
    Node *temp = *head;
    *head = (*head)->next; // Cập nhật head tới node kế tiếp
    free(temp);            // Giải phóng node đầu tiên
}

// Xóa phần tử cuối cùng trong danh sách
void deleteLast(Node **head)
{
    if (*head == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }
    if ((*head)->next == NULL) // Nếu danh sách chỉ có một phần tử
    {
        free(*head);
        *head = NULL;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != NULL) // Duyệt đến phần tử kế cuối
    {
        temp = temp->next;
    }
    free(temp->next);    // Giải phóng node cuối cùng
    temp->next = NULL;   // Đặt node kế cuối trỏ tới NULL
}

// Xóa tất cả các phần tử có giá trị cho trước trong danh sách
void deleteByValue(Node **head, int value)
{
    if (*head == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }
    
    // Xử lý các nút đầu có giá trị bằng value
    while (*head != NULL && (*head)->data == value)
    {
        Node *temp = *head;
        *head = (*head)->next; // Cập nhật head tới node kế tiếp
        free(temp);            // Giải phóng node có giá trị trùng
    }
    
    Node *current = *head;
    while (current != NULL && current->next != NULL)
    {
        if (current->next->data == value) // Nếu tìm thấy giá trị trùng
        {
            Node *temp = current->next;
            current->next = current->next->next; // Bỏ qua node bị xóa
            free(temp);                          // Giải phóng node bị xóa
        }
        else
        {
            current = current->next; // Tiếp tục duyệt danh sách
        }
    }
}

// Tìm kiếm tất cả các vị trí của phần tử có giá trị cho trước
void searchAll(Node *head, int value)
{
    Node *current = head;
    int position = 0;
    int found = 0;

    while (current != NULL)
    {
        if (current->data == value)
        {
            printf("Phan tu %d da duoc tim thay o vi tri %d.\n", value, position);
            found = 1; // Đánh dấu đã tìm thấy
        }
        current = current->next;
        position++;
    }

    if (!found) // Nếu không tìm thấy giá trị
    {
        printf("Phan tu %d khong ton tai trong danh sach.\n", value);
    }
}

// In danh sách ra màn hình
void printList(Node *head)
{
    if (head == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }
    printf("Cac phan tu trong danh sach: ");
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data); // In dữ liệu của từng node
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    Node *head = NULL; // Khởi tạo danh sách
    int choice, data, position;

    do
    {
        printf("\n==================MENU=================\n");
        printf("1. Them phan tu vao dau danh sach\n");
        printf("2. Them phan tu vao cuoi danh sach\n");
        printf("3. Chen phan tu vao vi tri cu the\n");
        printf("4. Xoa phan tu dau danh sach\n");
        printf("5. Xoa phan tu cuoi danh sach\n");
        printf("6. Xoa phan tu theo gia tri\n");
        printf("7. Tim kiem phan tu theo gia tri\n");
        printf("8. In danh sach cac gia tri ra man hinh\n");
        printf("9. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Nhap gia tri: ");
            scanf("%d", &data);
            addFirst(&head, data);
            break;
        case 2:
            printf("Nhap gia tri: ");
            scanf("%d", &data);
            addLast(&head, data);
            break;
        case 3:
            printf("Nhap gia tri: ");
            scanf("%d", &data);
            printf("Nhap vi tri: ");
            scanf("%d", &position);
            insertAtPosition(&head, data, position);
            break;
        case 4:
            deleteFirst(&head);
            break;
        case 5:
            deleteLast(&head);
            break;
        case 6:
            printf("Nhap gia tri can xoa: ");
            scanf("%d", &data);
            deleteByValue(&head, data);
            break;
        case 7:
            printf("Nhap gia tri can tim: ");
            scanf("%d", &data);
            searchAll(head, data);
            break;
        case 8:
            printList(head);
            break;
        case 9:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 9);

    return 0;
}
