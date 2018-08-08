/*
归并排序的一个很简洁的版本
关键是利用辅助空间与原数据空间进行交换
*/
class Solution
{
private:
	void merge_sort_core(vector<int> &data, int s, int e, vector<int> &copy)
	{
		if (s >= e) return;
		int mid = (e - s) / 2 + s, i, j, k = s;
		merge_sort_core(copy, s, mid, data);
		merge_sort_core(copy, mid + 1, e, data);
		for (i = s, j = mid + 1; i <= mid && j <= e;)
		{
			if (copy[i] < copy[j])
				data[k++] = copy[i++];
			else
				data[k++] = copy[j++];
		}
		while (i <= mid)
			data[k++] = copy[i++];
		while (j <= e)
			data[k++] = copy[j++];
	}
public:
	void merge_sort(vector<int> &v)
	{
		vector<int> copy(v);
		merge_sort_core(v, 0, v.size() - 1, copy);
	}
};
