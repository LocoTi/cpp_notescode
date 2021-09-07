#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>      // std::accumulate

/**
 * 37. 使用 accumulate 或者 for_each 进行区间统计
 */

// 接受当前的长度总和值和新的字符串，然后返回更新之后的总和值
std::string::size_type stringLengthSum(std::string::size_type sumSoFar, const std::string &s) {
    return sumSoFar + s.size();
}

struct Point {
    Point(double initX, double initY): x(initX), y(initY) { }
    double x, y;
};

class PointAverage{
public:
    PointAverage(): xSum(0), ySum(0), numPoints(0) { }
    void operator()(const Point &p) {
        ++numPoints;
        xSum += p.x;
		ySum += p.y;
    }

    Point result() const {
        return Point(xSum / numPoints, ySum / numPoints);
    }
private:
	size_t numPoints;
	double xSum, ySum;
};

void test_item_37() {
    std::vector<double> v{ 1.0f, 2.2f, 3.3f, 4.5f };
    double sum = std::accumulate(v.cbegin(), v.cend(), 0.0); // 注意：初始值被指定为0.0,而不是简单的0
    fprintf(stdout, "vaule: %f\n", sum); // 11.000000

    sum = std::accumulate(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), 0); // 输入非整数值结束,如字母
    fprintf(stdout, "sum of the ints: %f\n", sum);

    std::set<std::string> st{ "abc", "cde", "xyzw" };
    // 计算一个容器中字符串的长度总和 binary_op接受两个参数，第一个
    std::string::size_type lenthSum = std::accumulate(st.cbegin(), st.cend(), static_cast<std::string::size_type>(0), stringLengthSum);
    fprintf(stdout, "lenth sum: %d\n", lenthSum); // 10

    // 计算一个区间中数值的乘积
    std::vector<float> vf{ 1.f, 2.f, 3.f, 1.5f };
    float product = std::accumulate(vf.cbegin(), vf.cend(), 1.f, std::multiplies<float>());
    fprintf(stdout, "product: %f\n", product); // 9.000000

    // 计算出一个区间中所有点的平均值
    std::list<Point> lp{ { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
    Point avg = std::for_each(lp.cbegin(), lp.cend(), PointAverage()).result();
}

int main() {
    test_item_37();

    return 0;
}