void test()
{
    vector<Person> per = {
        Person("A"),
        Person("B"),
        Person("C"),
        Person("D"),
        Person("E"),
    };
    vector<vector<int>> scr = {
        {81, 80, 83, 94, 82, 86, 82, 80, 95, 92},
        {92, 94, 91, 92, 88, 90, 85, 87, 83, 89},
        {88, 82, 84, 82, 89, 90, 97, 92, 91, 87},
        {77, 81, 82, 83, 82, 86, 85, 93, 81, 92},
        {81, 82, 81, 80, 82, 89, 91, 80, 90, 92}
    };

    for (size_t i = 0; i < per.size(); ++i)
    {
        per[i].getScore() = deque<int>(scr[i].begin(), scr[i].end());
    }

    for (size_t i = 0; i < per.size(); ++i)
    {
        deque<int> sortScore = per[i].getScore();
        
        // 使用冒泡排序对成绩进行排序
        bubbleSort(sortScore);  // 或者使用其他排序方法

        if (sortScore.size() > 2) {
            sortScore.pop_back(); // 去掉最高分
            sortScore.pop_front(); // 去掉最低分
        }

        int totalScore = 0;
        for (const auto &score : sortScore)
        {
            totalScore += score;
        }

        double averageScore = static_cast<double>(totalScore) / sortScore.size();
        cout << "Player: " << per[i].getName() << ", Score: " << averageScore << endl;
    }
}

