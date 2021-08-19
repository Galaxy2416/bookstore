#include <vector>
int trap_water(const vector<int> &heights)
{
    int left_max = 0;
    int right_max = 0;
    int ans = 0;
    int left = 0, right = heights.size() - 1;
    while(left < right)
    {
        if(heights[left] < heights[right])
        {
            heights[left] >= left_max ? (left_max = heights[left]) : ans += left_max - heights[left]; 
            left++;

        }
        else{
            right--;
        }
    }
    return ans;
}