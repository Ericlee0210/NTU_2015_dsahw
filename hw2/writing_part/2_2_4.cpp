#include <iostream>
#include <algorithm>
using namespace std;
void func(int [], int);
int main()
{
	int bbb[10] = {1,2,3,4,5,6,7,8,9,11};
	func(bbb, sizeof(bbb)/sizeof(int) -1);
	cout << "success" << endl;
	return 0;
}

void func(int ary[], int v)
{
	int i=0;
	cout << "size= " << v << endl;
	while(i<v)
	{
		if(ary[i]%2==0 && ary[v]%2==0)
		{
			//cout << "1" << endl;
			int tmp = ary[i+1];
			ary[i+1] = ary[v];
			ary[v] = tmp;
			i++;			
		}
		else if(ary[i]%2==0 && ary[v]%2==1)
		{
			//cout << "2" << endl;
			i++;
			v--;			
		}
		else if(ary[i]%2==1 && ary[v]%2==0)
		{
			//cout << "3" << endl;
			int tmp = ary[i];
			ary[i] = ary[v];
			ary[v] = tmp;
			i++;
			v--;			
		}
		else if(ary[i]%2==1 && ary[v-1]%2==1)
		{
			//cout << "4" << endl;
			int tmp = ary[i];
			ary[i] = ary[v-1];
			ary[v-1] = tmp;
			v-=2;	
		}
	}
	for(int i=0; i<10; i++)
		cout << ary[i] << " " << endl;
}