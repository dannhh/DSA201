#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;
/* --------------------------------- PROBLEM DESCRIPTION ------------------------------------ *
 * TASK:  Given a set of n segments{[a0, b0],[a1, b1], . . . ,[an−1, bn−1]}                   *
 *        with integer coordinates on a line, findthe minimum number m of points such that    *
 *        each segment contains at least one point. That is, find aset of integers X of the   *
 *        minimum size such that for any segment[ai, bi]there is a point x∈X such that 𝑎𝑖≤𝑥≤𝑏𝑖.*
 *                                                                                            *
 * Input Format: The first line of the input contains the number𝑛of segments.                 *
 *               Each of the following n linescontains two integers ai and bi                 *
 *               (separated by a space) defining the coordinates of endpoints of              *
 *               the i-th segment                                                             *
 *                                                                                            *
 * Constraints:  1 <= n <= 100; 0 <= ai <= bi <= 10^9 for all 0 <= i < n.                     *
 * ----------------------------------------------------------------------------------------   */
struct Segment {
    int start, end;
};

bool sortFunction(Segment i, Segment j) { return (i.end < j.end); }

vector<int> optimal_points(vector <Segment> &segments) {

    std::sort(segments.begin(), segments.end(), sortFunction);

    vector<int> points;
    int point = segments[0].end;
    points.push_back(point);

    for (size_t i = 1; i < segments.size(); ++i) {
        if (point < segments[i].start || point > segments[i].end) {
            point = segments[i].end;
            points.push_back(point);
        }
    }
    return points;
}

/*------------------- SAMPLE TEST ---------------------- *
 * 3                       |    4                        *   
 * 1 3                     |    4 7                      *     
 * 2 5                     |    1 3                      *  
 * 3 6                     |    2 5                      *   
 * Result: 1               |    5 6                      * 
 *         3               |    Result: 2                *
 *                         |            3 6              * 
 *-------------------------------------------------------*/ 

int main() {
    int n;
    std::cin >> n;
    vector <Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
