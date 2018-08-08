
#include<iostream>
#include<vector>
using namespace std;

/**
今天我们看到的阿里巴巴提供的任何一项服务后边都有着无数子系统和组件的支撑，子系统之间也互相依赖关联，

其中任意一个环节出现问题都可能对上游链路产生影响。小明做为新人接收到的第一个任务就是去梳理所有的依赖关系，

小明和每个系统的负责人确认了依赖关系，记录下调用对应系统的耗时，用这些数据分析端到端链路的数目和链路上最长的耗时。

输入： 小明搜集到的系统耗时和依赖列表

5 4 // 表示有5个系统和 4个依赖关系

3 // 调用1号系统耗时 3 ms

2 // 调用2号系统耗时 2 ms

10 // 调用3号系统耗时 10 ms

5 // 调用4号系统耗时 5 ms

7 // 调用5号系统耗时 7 ms

1 2 // 2号系统依赖1号系统

1 3 // 3号系统依赖1号系统

2 5 // 2号系统依赖5号系统

4 5 // 4号系统依赖5号系统

输出: 调用链路的数目 和最大的耗时， 这里有三条链路1->2
 */

vector<vector<int>> graph; //存储调用关系图, graph[i][j] == 1表示，i调用j
/**
 * @brief find_call_path 用来计算给定调用号码的所有调用路径
 * @param ans 所有调用结果
 * @param cur_path 当前调用路径
 * @param call_no 开始调用号
 */
void find_call_path(vector<vector<int>> &ans, vector<int> &cur_path, int call_no)
{
    int j, find = 0;
    cur_path.push_back(call_no);
    for (j = 0; j < graph[call_no].size(); ++j)
    {
        if (graph[call_no][j] == 0)
            continue;
        find = 1;
        find_call_path(ans, cur_path, j);
    }
    if (find == 0)
    {
        ans.push_back(cur_path);
    }
    cur_path.pop_back();
}
/**
 * @brief cal_cost 计算调用调用路径path的调用消耗
 * @param times 每个调用的耗时
 * @param path 调用路径
 * @return
 */
int cal_cost(vector<int> &times, vector<int> &path)
{
    int i, cost = 0;
    for (i = 0; i < path.size(); ++i)
        cost += times[path[i]];
    return cost;
}

int main()
{
    int n_calls, m_depend, i, j, a, b, max_cost = -1, tmp, total = 0;
    cin>>n_calls>>m_depend;
    vector<int> times(n_calls + 1), path, init_call(n_calls + 1, 1); //times表示每个调用的耗时，init_call表示能够作为调用链的头部
    vector<vector<int>> all_path;
    graph.push_back(vector<int>(n_calls + 1));
    for (i = 1; i <= n_calls; ++i)
    {
        cin>>times[i];
        graph.push_back(vector<int>(n_calls + 1));
    }
    for (i = 0; i < m_depend; ++i)
    {
        cin>>a>>b;
        init_call[b] = 0;
        graph[a][b] = 1;
    }
    for (i = 1; i <= n_calls; ++i)
    {
        if (!init_call[i])
            continue;
        all_path.clear();
        path.clear();
        find_call_path(all_path, path, i);
        total += all_path.size();
        for (j = 0; j < all_path.size(); ++j)
        {
            tmp = cal_cost(times, all_path[j]);
            if (max_cost < tmp)
                max_cost = tmp;
        }
    }
    cout<<total<<" "<<max_cost<<endl;
    return 0;
}
