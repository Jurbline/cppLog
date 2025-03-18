class Solution {
public:
    int minSwaps(string s) {
        int tempL = 0;//暂时没有消除的左括号
        int permR = 0;//永远不能消除的右括号，即pairs
        for(char ch : s)
        {
            if(ch == '[') 
                tempL++;
            else 
                tempL--;//匹配到了成对的右括号
            if(tempL < 0)
            {
                permR++;//出现了永远不能消除的右括号（pairs）
                tempL = 0;//重置
            }
        }
        return (permR + 1) / 2;
    }
};
/*已经匹配的或者暂时没有匹配的未来可以消除
遍历完后，栈只留下永远不能被匹配的pairs
][ --> 1
]][[ --> 1
]]][[[ --> 2
]]]][[[[ --> 2
5pairs --> 3
6pairs --> 3
result = (npairs + 1) / 2
*/
