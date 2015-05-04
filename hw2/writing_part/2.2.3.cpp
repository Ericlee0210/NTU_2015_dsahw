first, counting both numbers of nodes in L and M, if number of nodes are not same, L and M are not same. second, If the numbers of nodes are same, then make sure the content of nodes in L is totally as orderly same as M. 
//evenpos defualt 輸入為0
//oddpos default 輸入最後一個元素的位置
void sort(int ary[], int evenpos, int oddpos)
{
	while(ary[evenpos]%2==0)
		evenpos++;
	while(ary[oddpos]%2==1)
		oddpos--;
	if(evenodd >= oddpos)
		return;
	else
	{
		int tmp = ary[evenpos];
		ary[evenpos] = ary[oddpos];
		ary[oddpos] = tmp;
		sort(ary, evenpos++, oddpos--);
	}
}