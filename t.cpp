#include <stdlib.h>
#include <iostream>
#include "t.h"
using namespace std;

int main()
{
 CList w(8);
 w.Show();
w.AddEnd(7); w.AddEnd(5); w.AddEnd(3); w.AddEnd(4);
w.AddEnd(9); w.AddEnd(1); w.AddEnd(2); w.AddEnd(8);
w.Show();
w.AddEnd(6); w.AddEnd(10); w.AddEnd(11);
w.Show();
w.DelPos(0);
w.Show();
w.AddPos(0,7);
w.Show();

int count;w.GetCount(count);cout<<"count="<<count<<endl;

double *x; x=w.GetCur(0);
*x=9;w.Show();
*x=7;w.Show();

int z=w.BinSearch(5);
if (z == -1)cout << "NON" << endl;
return 0;
}