#pragma once
#define L 4
using namespace std;
/*
1. Создать массив заданной начальной длины     !     
2. Добавить элемент в конец масива       !
3. Вставить элемент так , чтобы он имел указанный индекс(Сдвиг)   !
4. Получить указатель (или ссылку) элемента с заданным индексом для прямого доступа к значению  !
5. Удалить элемент по указанному индексу    !  
6. Получить количество элементов в масиве   !
7. Установить новую длину масива            !  
8. Искать заданное значение в масиве            !
9. Сортировать	 масив по возр или убыванию 	 !
*/
class CListNode
{
 public:
 double *v; CListNode *prev, *next;
 int size; //n- кол во элементов в ячейке
 CListNode(){v=new double[L];size=0;for(int i =0;i<L;i++)v[i]=0;next=prev=NULL;}  // Надо убрать for после отладки 
 ~CListNode(){prev=next=NULL; delete v;}
};

class CList                                     
{                                               //к-количество ячеек 
 CListNode *first, *cur,  *last;                  
 int k;
public:
 CList(){cur=first=last=NULL; k=0;}
 CList(const int length);
 ~CList(){Clean();}
 void Clean(){GoToBegin();if(cur==NULL)return; ;while(cur->next!=NULL){GoToNext(); delete cur->prev;} cur=last=first=NULL;}
 void GoToBegin(){cur=first;}
 void GoToEnd(){cur=last;}
 int GoToNext(){if(cur==NULL) return -1;  cur=cur->next; return 0;}
 int GoToPrev(){if(cur==NULL) return -1;  cur=cur->prev; return 0;}
 void AddEnd(const double &x);//В конце масива
 int AddCur(int k,const double &x);// В конец выбранной ячейки 
 int AddPos(int j,const double &x);
 int DelPos(int j);
 int GetCount(int &x){x=0;CListNode *t=first; if(t==NULL){x=0;return 0;} while(t!=NULL){x+=(t->size);t=t->next;}; return 0;}
 int resize(const int length);
 double* GetCur(const int j);
 int Sort();
 int BinSearch(const double &x);
 void Show(){CListNode *t=first;if(t==NULL)return; while(t!=NULL){for(int j=0;j<t->size;j++){cout<<t->v[j]<<" ";}t=t->next;}cout<<endl;}
};

CList::CList(const int length)
{
 k=(length%L==0)?length/L:length/L+1;
 CListNode *t;
 for(int i=0;i<k;i++)
 { 
  t=new CListNode;
  if(i==0){cur=first=t;continue;} 
  t->prev=cur; cur->next=t; cur=t;
          
 }
 last=cur;
 last->next=NULL;
 cur=first;

}


int CList::resize(const int length)     // Не делает меньше 
{int nk=(length%L==0)?length/L:length/L+1;
 if(length<(L*k)){return -1;}
 GoToEnd();
 CListNode *t;
 for(int i=k;i<nk;i++)
 {
  t=new CListNode;
  t->prev=cur; cur->next=t; cur=t;
 }
 last=cur;
 last->next=NULL;
 cur=first;
 k=nk;
 return 0; 
}




int CList::AddCur(int k,const double &x)
{
  if(k>this->k)return -1;
  GoToBegin();
  for(int i=0;i<k;i++)GoToNext();//cur-ячейка в которую нужно вставить элемент(в конец ячейки)
  if(cur->size<L){cur->v[cur->size]=x;cur->size++;return 0;} 
    
  //if(cur->next==NULL){CListNode *t =new CListNode; last->next=t; t->prev=last; last=t;this->k++;last->v[0]=x;last->size=1;return 0;}//Добавили ячейку если в последней нет места 
  
  CListNode *t=cur->next;
  while(t!=NULL){if(t->size<L)break; t=t->next;}// t-первая ячейка в которой есть место(или новая пустая) после текущей(-в которую нужно вставить)
  if(t==NULL) {t=new CListNode; t->prev=last;last->next=t; last=t;this->k++;}//КОгда все переполнены создали новую ячейку 
//-------------Это обрабатывается последнаяя ячейка
   for(int i=t->size;i>0;i--){t->v[i]=t->v[i-1];} 
   t->v[0]=t->prev->v[t->prev->size-1];
   t->size++;
   t=t->prev;
//------------------------------------------------

   while(t!=cur)//Обрабатывает ячейки с предпоследней, так как последняя обработана выше
   {
     for(int i=t->size-1;i>0;i--)
      {t->v[i]=t->v[i-1];}
     t->v[0]=t->prev->v[t->prev->size-1];
     t=t->prev;
   }
   t->next->v[0]=x;
   return 0;
}

int CList::AddPos(int j,const double &x)
{
 int cell=j/L;//Номер нужной ячейки(считая с нуля)
 int pos=j%L; //Позиция нужного элемента внутри ячейки
 if(cell>=k){return -1;} 
 GoToBegin();
 for(int i=0;i<cell;i++)GoToNext();//cur-ячейка внутрь которой нужно вставить x
 if(cur->size==pos){cur->v[cur->size]=x; cur->size++; return 0;}//Если в нужной ячейке не занята необх позиция просто вставить 

 CListNode *t=cur->next;
 while(t!=NULL){if(t->size<L)break; t=t->next;}//Первая ячейка в которой есть место
 if(t==NULL){t=new CListNode; t->prev=last;last->next=t; last=t;k++;}//Если свободной не нашлось создали новую
//----Последняя ячейка
 for(int i=t->size;i>0;i--){t->v[i]=t->v[i-1];}//Если пустая не зайдет 
   t->v[0]=t->prev->v[t->prev->size-1];
   t->size++;
   t=t->prev;
//-------------------- 
 while(t!=cur)//Обрабатываем все до текущей
 {                                                                       //      . <-.
  for(int i=t->size-1;i>0;i--){t->v[i]=t->v[i-1];}                        // [1 2 3] [4 5 6]
  t->v[0]=t->prev->v[t->prev->size-1];
  t=t->prev;
 }
 for(int i=t->size-1;i>pos;i--){t->v[i]=t->v[i-1];}
 t->v[pos]=x;
 return 0;

}


 
int CList::DelPos(int j)//НУжно ли уменьшать число ячеек
{
 int cell=j/L;//Номер нужной ячейки(считая с нуля)
 int pos=j%L; //Позиция нужного элемента внутри ячейки
 if(cell>=k){return -1;} 
 GoToBegin();
 for(int i=0;i<cell;i++)GoToNext();//cur-ячейка в которой удаляем элемент 

 CListNode *t;
 t=cur;
 //----Первая ячейка
 for(int i=pos;i<t->size-1;i++){t->v[i]=t->v[i+1];}//Если пустая не зайдет 
   if(t==last){t->v[t->size-1]=0;t->size--; return 0;}// Если последняя, то сдвинет элементы внутри и все
   t->v[t->size-1]=t->next->v[0]; 
   t=t->next;
//-------------------- 
 while(t!=last)//Сдвигаем влево до последней ячейки 
 {                                                                       //      . <-.
  for(int i=0;i<t->size-1;i++){t->v[i]=t->v[i+1];}                        // [1 2 3] [4 5 6]
  t->v[t->size-1]=t->next->v[0];
  t=t->next;
 }
//---последняя ячейка
 for(int i=0;i<t->size-1;i++){t->v[i]=t->v[i+1];}
 t->v[t->size]=0;
//---------------
CListNode*p;                                              //К 
p=last;                                                    //Надо уменьшить размер какой то ячейке после сдвига;
while(p!=NULL){if(p->size!=0)break; p=p->prev;}
p->size--;
//---------------
 return 0;
}


double* CList::GetCur(const int j)
{
 if(j<0){cout<<"not exist"<<endl;return 0;}
 int cell=j/L;//Номер нужной ячейки(считая с нуля)
 int pos=j%L; //Позиция нужного элемента внутри ячейки
 if(cell>k){cout<<"not exist"<<endl; return 0;}
 GoToBegin();
 for(int i=0;i<cell;i++)GoToNext();
 return  &(cur->v[pos]);
}
                                                                 

          
void CList::AddEnd(const double &x)//Вставить в конец массива(Динамического )
{
 if(cur==NULL){first=last=cur=new CListNode; cur->v[0]=x;(cur->size)++;k++;return;}
 CListNode *p =first;while(p!=NULL){if(p->size<L)break; p=p->next;}
 if(p==NULL)
 {
 p= new CListNode;
 p->v[0]=x;p->size=1;p->prev=last;
 last->next=p; last=p;return;
 }
 p->v[p->size]=x;
 p->size++;
 return;
}


int CList::Sort()
{ 
 CListNode *t=first;
 double *max=&(t->v[0]);
 int p;GetCount(p);int y=0;
 int m=0; 
for(;;)
 { 
  for(;;)
  {
   for(int i=0;i<t->size&&y<p;i++,y++){if(t->v[i]>*max){max=&(t->v[i]);}}
   if(t->next==NULL||t->next->size==0)break;
   if(y < p) { t = t->next; m++;} 
   else break;
  }
  double tmp=t->v[p-m*L-1];
  t->v[p-m*L-1]=*max;
  *max=tmp;
//---------------------
  max=&(first->v[0]);
  p--;y=0;
  if(p==0)break;
  t=first;
  m=0;
 }
 return 0;  
}



int CList::BinSearch(const double &x)
{
  Sort();
 int left=0,right,p;GetCount(right);
 Show();
 p=right-left; // p позиция элемента локально 
 CListNode *t=first;
 int m=0;
 for(int i=0;i<(p/2)/L;i++){t=t->next;m++;}
 for(;;)
 { 
  if(x<t->v[0])
  {
    if(t->prev==NULL)return -1; 
    right=m*L;
    p=right-left;
    t=t->prev;m--;
   for(int i=0;i<(p/2)/L;i++){t=t->prev; m--;}
   continue;
  }
  else
  {
   if(x>t->v[t->size-1])
   {
   if(t->next==NULL)return -1;
   left=(m+1)*L;
   p=right-left;
   t=t->next;m++;
   for(int i=0;i<(p/2)/L;i++){t=t->next;m++;}
   continue;
   }
 break;
  }
 } 
 for(int i=0;i<t->size;i++){if(x==t->v[i]){cout<<t->v[i]<<endl;return m*L+i;}}
 return -1;
}
