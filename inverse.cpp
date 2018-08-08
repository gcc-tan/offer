//使用nlogn的时间寻找数组中逆序对的数量
class Solution {
private:
	int left[100001];
	int right[100001];
	const int mod = 1000000007;
	long merge(vector<int> &data, int p, int q, int r)
	{
		int i, j, n1 = q - p + 1, n2 = r - q, k = p;
		long ans = 0;
		for(i = p; i <= q; ++i)
			left[i-p] = data[i];
		for(j = q + 1; j <= r; ++j)
			right[j-q-1] = data[j];

		for(i = 0, j = 0; i < n1 && j < n2;)
		{
			if(left[i] <= right[j])
				data[k++] = left[i++];
			else
			{
				ans += n1 - i;
				data[k++] = right[j++];
			}
		}
		while(i < n1)
			data[k++] = left[i++];
		while(j < n2)
			data[k++] = right[j++];
		return ans;
	}
	int merge_sort(vector<int> &data, int p, int r)
	{
		int mid, rev1, rev2;
		if(p >= r) return 0;
		mid = (p + r) / 2;
		rev1 = merge_sort(data, p, mid);
		rev2 = merge_sort(data, mid + 1, r);
		return (rev1 + rev2 + merge(data, p, mid, r)) % mod;
	}
public:
    int InversePairs(vector<int> data) 
	{
		return merge_sort(data, 0, data.size() - 1);
    }
};
