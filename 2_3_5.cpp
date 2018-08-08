#include<iostream>
#include<algorithm>
#include<set>
#include<queue>
typedef unsigned long long ll;
using namespace std;

/*
 * 编写程序找第n个这样的数，这个数的特征是只包含质因子 2,3,5的正整数。
 * 例如 1,2,3,4,5,6,8,9,10,12就是前10个这样的数。
 * 注意:1也被当做这种数
 *
 * 假设这样的数中最大的小于10^18。
 *====================================================================================================
 * 思路有很多
 * 1. 第一种思路是初始化一个优先队列和一个set，优先队列中有一个元素1，然后set中为空（优先队列中的元素有没有在set中使用过）。每次从优先队列中选取最小的元素，添加到数组的尾部。
 *    然后乘上2, 3, 5判断乘上之后的是否在set中，不在set中将这个元素加入set，同时将该元素插入优先队列。直到数组中元素的个数达到k个
 * 2. 将小于10^18的这样的满足要求的数都生成出来（这样的数的个数肯定不多，因为10^18 <= 2^60，就算全都是2的因子也只有60个，3和5这两个因此每个最多也60个，所以满足条件的数个数 < 60*60*60）
 *    存放在数组中，然后对数组排序，输出第k个。
 */

//方法1的实现
const int N = 60 * 60 * 60;
const double INF = 1e18;
ll arr[N];
int cnt = 0;
void init()
{
	int num;
	priority_queue<ll, vector<ll>, greater<ll>> q;
	set<ll> s;
	q.push(1);

	while (cnt < N)
	{
		arr[cnt++] = q.top();
		num = q.top();
		q.pop();
		if (num * 2 >= INF)
			break;
		if (!s.count(num * 2))
		{
			s.insert(num * 2);
			q.push(num * 2);
		}
		if (!s.count(num * 3))
		{
			s.insert(num * 3);
			q.push(num * 3);
		}
		if (!s.count(num * 5))
		{
			s.insert(num * 5);
			q.push(num * 5);
		}
	}
}
int main()
{
	int k;
	init();
	while (cin>>k)
	{
		cout<<arr[k-1]<<endl;
	}
	return 0;
}



//方法2的实现
const int N = 60 * 60 * 60;
const double INF = 1e18;
ll arr[N];// 存放满足条件的数的集合
int cnt = 0;
void init()
{
	ll a, b, c;
	for (a = 1; a < INF; a *= 2)
		for (b = 1; a * b < INF; b *= 3)
			for (c = 1; a * b * c < INF; c *= 5)
				arr[cnt++] = a * b * c;
}
int main()
{
	int k;
	init();
	sort(arr, arr + cnt);
	while (cin>>k)
	{
		cout<<arr[k-1]<<endl;
	}
    return 0;
}




