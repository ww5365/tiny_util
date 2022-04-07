#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>

#include <unordered_map>


using namespace std;

/*

开发一个船票预定系统，该船包含的多个船舱信息存于 cabins 数组，数组下标为 cabin_id
，值为该船舱包含的座位数。该系统需要满足以下几个功能：

book(id, cabin_id, num) 表示订单号为 id 的客人想要在 cabin_id 的船舱里预定 num 个座位，这里订单号 id
全局唯一，并且如果该船舱余票数多于乘客预定数 num, 则以 最小连续座位分配规则分配 num 个座位给该乘客，返回
True；如果余票不足，则进入该船舱的预订队列进行排队等候，返回 False. cancel（id): 订单号为 id 的乘客
想要取消订单。若该乘客已订票成功，则将已经分配好的座位重置为未分配，并完成退票操作；若该乘客在预订队列中，从预订队列中取消，不影响其它排队的人；取消成功后返回
True，若该乘客已取消或者没有标识为 id 的订单号，则返回 False query (id) : 查询订单号为 id
的订单。如果订票成功，则返回分配的最小座位编号；其它情况返回 -1。 最小连续座位分配规则：若该船舱还存在连续 num
个座位，则分配起始 index最小的 num 个座位给该乘客；否则根据空的 index 从小到大分配 num
个座位给该乘客。简单来说就是：有连续 num 个座位则优先分配连续的座位（遵循最小连续规则），若没有则按座位号从小到大分配
num 个空的座位给该乘客。


*/

// class TicketSystem {
// public:
//     explicit TicketSystem(const vector<int> &cabins)

//     {
//         int n = cabins.size();

//         Cabins.resize(n);

//         Waiting.resize(n);

//         for (int i = 0; i < n; ++i) {
//             Cabins[i] = {cabins[i], cabins[i], bitset<1000>(0)};
//         }
//     }


//     bool Book(int id, int cabinId, int num)

//     {
//         if (Waiting[cabinId].size() != 0 || get<1>(Cabins[cabinId]) < num) {
//             Waiting[cabinId].emplace_back(id, num);

//             return false;
//         }

//         Request(id, cabinId, num);

//         return true;
//     }


//     bool Cancel(int id)

//     {
//         if (auto it = Booked.find(id); it != Booked.end()) {
//             const auto &[cabinId, num, book] = it->second;

//             get<1>(Cabins[cabinId]) += num;

//             get<2>(Cabins[cabinId]) ^= book;

//             Waitline(cabinId);

//             Booked.erase(it);

//             return true;
//         }

//         for (int cid = 0; cid < Waiting.size(); ++cid) {
//             for (auto it = Waiting[cid].begin(); it != Waiting[cid].end(); ++it) {
//                 if (it->first == id) {
//                     Waiting[cid].erase(it);

//                     Waitline(cid);

//                     return true;
//                 }
//             }
//         }

//         return false;
//     }


//     int Query(int id)

//     {
//         if (auto it = Booked.find(id); it != Booked.end()) {
//             int i = 0;

//             while (i < 1000 && !get<2>(it->second)[i]) {
//                 ++i;
//             }

//             return i;
//         }

//         return -1;
//     }


// private:
//     void Request(int id, int cabinId, int num)

//     {
//         if (num > get<1>(Cabins[cabinId])) {
//             return;
//         }

//         get<1>(Cabins[cabinId]) -= num;

//         bitset<1000> book(0);

//         for (int l = -1, r = 0; r < get<0>(Cabins[cabinId]);) {
//             while (++l < get<0>(Cabins[cabinId]) && get<2>(Cabins[cabinId])[l]) {
//             }

//             r = l;

//             while (++r < get<0>(Cabins[cabinId]) && !get<2>(Cabins[cabinId])[r]) {
//             }

//             if (r - l >= num) {
//                 for (int i = l; i < l + num; ++i) {
//                     get<2>(Cabins[cabinId])[i] = true;

//                     book[i] = true;
//                 }

//                 Booked[id] = {cabinId, num, std::move(book)};

//                 return;
//             }

//             l = r;
//         }


//         for (int i = 0, t = num; i < get<0>(Cabins[cabinId]) && t > 0; ++i) {
//             if (!get<2>(Cabins[cabinId])[i]) {
//                 --t;

//                 get<2>(Cabins[cabinId])[i] = true;

//                 book[i] = true;
//             }
//         }

//         Booked[id] = {cabinId, num, std::move(book)};
//     }


//     void Waitline(int cabinId)

//     {
//         auto it = Waiting[cabinId].begin();

//         while (it != Waiting[cabinId].end() && it->second <= get<1>(Cabins[cabinId])) {
//             Request(it->first, cabinId, it->second);

//             it = Waiting[cabinId].erase(it);
//         }
//     }


//     vector<tuple<int, int, bitset<1000>>> Cabins;

//     vector<list<pair<int, int>>> Waiting;

//     unordered_map<int, tuple<int, int, bitset<1000>>> Booked;
// };
