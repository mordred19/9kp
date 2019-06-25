#include <stdio.h>
#include <malloc.h>
#include <locale.h>

typedef enum alp {
  A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z 
} alp;

struct Node {
  alp data;
  struct Node *next;
  struct Node *prev;
};
typedef struct Node *PNode; //тип данных: указатель на узел

PNode CreateNode(alp);
PNode AddHead (PNode, PNode);
void AddAfter(PNode, PNode, PNode);
void AddLast(PNode, PNode, PNode);
void menu();
void PrintList(PNode, PNode);
int LengthCalculation(PNode, PNode);
PNode DeleteNode(PNode, alp, PNode);
int Fuck(PNode, PNode);

int main() {
  setlocale(LC_ALL, "Rus");
  int c, flag = 0;
  PNode Head = NULL;
  PNode terminator = (PNode) malloc(sizeof(struct Node));
  terminator->next = NULL;
  menu();
  char x[20];
  int sex;

  while (c != 7) {
    printf("Выберите: ");
    scanf("%d", &c);
    switch(c) {
      case 1:
        if (Head != NULL)
        {
          PrintList(Head, terminator);
          printf("\n");
        }else{
          printf("Ошибка, список пуст!\n");
        }
       
        break;
      case 2:
        printf("Введите букву алфавита: "); 
        scanf("%s", x);
        if((x[0] >= 'A' && x[0] <= 'Z') || (x[0] >= 'a' && x[0] <= 'z')) 
        {
          if (flag == 0 || Head == terminator) 
          {
            Head = AddHead(terminator, CreateNode(x[0]));
            flag = 1;
          } else {
          AddLast(Head, CreateNode(x[0]), terminator);
          }
        }
        break;
      case 3:
        printf("Введите букву алфавита: "); 
        scanf("%s", x);
        Head = DeleteNode(Head, x[0], terminator);
        break;
      case 4:
        printf("Длина списка = %d\n\n", LengthCalculation(Head, terminator));
        break;
      case 5:
        sex = Fuck(Head, terminator);
        if(sex == 1) printf("Список не упорядочен.\n");
        else if(sex == 0) printf("Список упорядочен.\n");
        break;
      case 6:
        menu();
      default:
        break;
    }
  }

  return 0;
}

int LengthCalculation(PNode Head, PNode terminator)
{
  PNode z = Head;
  int counter = 0;
  while (z != terminator) {
    counter++;
    z = z->next;
  }

  return counter;
}

void PrintList(PNode Head, PNode terminator)
{
    PNode p = Head;
    if (p != NULL) {
      //printf("\n");
      while (p != terminator) {
          printf("%c->", p->data);
          p = p->next;
      }
    }
    printf("terminator->NULL");
}

PNode CreateNode (alp newData) {
  PNode NewNode = (PNode) malloc(sizeof(struct Node));
  NewNode->data = newData;
  NewNode->prev = NULL;
  NewNode->next = NULL;
  return NewNode; //возвращается адрес узла
}

PNode AddHead (PNode terminator, PNode head) {
  head->next = terminator;
  terminator->prev = head;
  return head;
}

void AddAfter (PNode p, PNode NewNode, PNode t)
{
  NewNode->prev = p;
  NewNode->next = t;
  p->next = NewNode;
  t->prev = NewNode;
}

void AddLast(PNode Head, PNode NewNode, PNode terminator)
{
  PNode q = Head;
  if (Head == NULL) { // если список пуст,
    AddHead(terminator, NewNode); // вставляем первый элемент
    return;
  }
  while (q->next != terminator) {
    q = q->next; // ищем последний элемент
  }
  AddAfter(q, NewNode, q->next); //q->next --- terminator 
}

PNode DeleteNode(PNode Head, alp OldNode, PNode terminator)
{
  PNode q = Head, t;
  if (q->data == OldNode) {
    t = q;
    q = q->next; // удаление первого элемента
    free(t);
    return q;
  } else {
    while (q != terminator && q->next->data != OldNode) //поиск элемента
    {
      q = q->next;
    }
    if (q == terminator) {
      printf("Такой элемент не найден\n");
      return Head;
    }
    t = q->next;
    q->next = q->next->next;
    free(t);
  }
  return Head;
}

int Fuck(PNode a, PNode b) {
  int ab = 0;
  while(a->next != b) {
    if(a->data <= a->next->data) ab = 0;
    else ab = 1;
    if(ab == 1) return 1;
    a = a->next;
  }
  return ab;
}

void menu()
{
  printf("1. Печать списка.\n2. Вставка нового элемента в список.\n3. Удаление элемента из списка.\n"
"4. Подсчет длины списка.\n5. Проверить упорядоченность элементов списка.\n"
"6. Вывести меню.\n7. Выход.\n");
}
