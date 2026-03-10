1、两数之和
关键是使用哈希表，key是目标值，value是当前值的index。那么key + mp[key] = target.

2、字母易位词分组
["abc", "cba", "abd"],分为两组，["abc", "cba"]分为一组,["abd"]为一组。跟顺序无关的，哈希表最为合适, unordered_map<string, vector<string>> mp, 值得注意的是后续字符串拷贝的过程中，可以使用move。 

3、最长连续序列，给定未排序的数组，返回最大的连续子序列的长度。
要求使用O(n)，只能使用哈希表，不然排序最少也是O(nlogn),最最关键的点是找起点，减少迭代次数。同时学到了stl的初始化方法
```
vector<int> nums = {xxxxx};
unordered_set<int> st(nums.begin(), nums.end());
```

4、移动零，将所有的非零数字按照顺序移动到最左边。
核心思路是双指针交换，每次都将非零移到左边就行。最开始用了O(n2)的暴力算法。
