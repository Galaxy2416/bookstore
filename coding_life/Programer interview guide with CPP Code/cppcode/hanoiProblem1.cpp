#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*
汉诺塔问题比较经典，这里修改一下游戏规则：现在限制不能从最左侧的塔直接移动到最
右侧，也不能从最右侧直接移动到最左侧，而是必须经过中间。求当塔有 N 层的时候，打印最
优移动过程和最优移动总步数。
例如，当塔数为两层时，最上层的塔记为 1，最下层的塔记为 2，则打印：
Move 1 from left to mid
Move 1 from mid to right
Move 2 from left to mid
Move 1 from right to mid
Move 1 from mid to left
Move 2 from mid to right
Move 1 from left to mid
Move 1 from mid to right
It will move 8 steps
注意：关于汉诺塔游戏的更多讨论，将在本书递归与动态规划的章节中继续。
*/

using namespace std;

int process(int, string , string );

int hanoiProblem(int num)
{
    if (num < 1) 
    {
        return 0;
    }
    return process(num, "left", "right");
}

int process(int num, string from, string to) 
{
    if(1 == num)
    {
        if("mid" == to || "mid" == from)
        {
            cout << "move 1 from " << from << " to " << to << endl;
            return 1;
        }
        else
        {
            cout << "move 1 from " << from << " to " << "mid" << endl; 
            cout << "move 1 from " << "mid" << " to " << to << endl; 
            return 2;
        }
    }
    else
    {
        if("mid" == to  || "mid" == from)
        {
            string another = ("left" == from || "left" == to) ? "right" : "left";
            int p1 = process(num - 1, from, another);
            // 1
            cout << "move " << num << " from " << from << " to " << to << endl;
            int p2 = process(num - 1, another, to);
            return p1 + p2 + 1;
        }

        else
        {
            // 1. Left n-1 to right
            int p1 = process(num - 1, from, to);
            // 2. Left n to mid
            cout << "move " << num << " from " << from << " to " << "mid" << endl;
            // 3. Right n -1 to left 
            int p2 = process(num - 1, to, from);
            // 4. Mid n to right
            cout << "move " << num << " from " << "mid" << " to " << to << endl;
            // 5. Mid n to right
            int p3 = process(num - 1, from, to);
            return p1 + p2 + p3 + 2;
        }
    }
}


int main()
{
    cout << hanoiProblem(2);
}
