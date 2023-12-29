#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

/*
https://www.lintcode.com/problem/1070/?utm_source=sc-cheatsheet-cyc

给定一个帐户列表，每个元素accounts [i]是一个字符串列表，其中第一个元素accounts [i] [0]是账户名称，其余元素是这个帐户的电子邮件。
现在，我们想合并这些帐户。
如果两个帐户有相同的电子邮件地址，则这两个帐户肯定属于同一个人。
请注意，即使两个帐户具有相同的名称，它们也可能属于不同的人，因为两个不同的人可能会使用相同的名称。
一个人可以拥有任意数量的账户，但他的所有帐户肯定具有相同的名称。
合并帐户后，按以下格式返回帐户：每个帐户的第一个元素是名称，其余元素是按字典序排序后的电子邮件。
帐户本身可以按任何顺序返回。

样例 1:
	输入:
	[
		["John", "johnsmith@mail.com", "john00@mail.com"],
		["John", "johnnybravo@mail.com"],
		["John", "johnsmith@mail.com", "john_newyork@mail.com"],
		["Mary", "mary@mail.com"]
	]
	
	输出: 
	[
		["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],
		["John", "johnnybravo@mail.com"],
		["Mary", "mary@mail.com"]
	]

	解释: 
	第一个第三个John是同一个人的账户，因为这两个账户有相同的邮箱："johnsmith@mail.com".
	剩下的两个账户分别是不同的人。因为他们没有和别的账户有相同的邮箱。

	你可以以任意顺序返回结果。比如：
	
	[
		['Mary', 'mary@mail.com'],
		['John', 'johnnybravo@mail.com'],
		['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']
	]
	也是可以的。


解决思路：

1. 先对accounts进行解析，形成两个map：email2Account[邮件， 账户]  parent[邮件，父节点邮件] 
2. 对parent进行归并，知道每个邮件属于哪个连通分量，即每个邮件属于哪个父节点
3. 轮询每个邮件，查找邮件所属的父节点，定位此父节点邮件对应的账户；对于相同账户的邮件放入到vector，最终形成result[account, <email>]结果
4. 放入result之前vector排序，最终结果返回



*/

class Solution {
public:
    /**
     * @param accounts: List[List[str]]
     * @return: return a List[List[str]]
     *          we will sort your return value in output
     */
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        // write your code here

        vector<vector<string>> result;
        if (accounts.size() <= 0) {
            return result;
        }

        for (const auto &account :accounts) {
            for (size_t i = 0; i < account.size(); ++i) {
                if (i == 0) {
                    continue;
                }
                email2Account[account[i]] = account[0];
                parent[account[i]] = account[i];
            }
        }

        // 以accounts的用户拥有的邮件列表和parent，进行归并
        for (const auto &account :accounts) {
            if (account.size() <= 2) {
                continue;
            }
            string firstEmail = account[1];
            for (size_t i = 2; i < account.size(); ++i) {
                merge(firstEmail, account[i]);
            }
        }

        // for(const auto &elem : parent) {
        //     cout << "first: " << elem.first << " second: " <<  elem.second << endl;
        // }

        // 遍历每个email，将其聚合某个相同的father邮件下
        unordered_map<string, vector<string>> tmp;
        for(const auto &elem : email2Account) {
            string father = findParent(elem.first);
            // string accountName = email2Account[father];

            if (tmp.find(father) == tmp.end()) {
                tmp[father] = vector<string>();
            }
            tmp[father].push_back(elem.first);
        }

        //  形成结果
        for (const auto &elem : tmp) {
            vector<string> oneAccount;
            oneAccount.insert(oneAccount.end(), elem.second.begin(), elem.second.end());
            sort(oneAccount.begin(), oneAccount.end());
            oneAccount.insert(oneAccount.begin(), email2Account[elem.first]);
            result.push_back(oneAccount);
        }

        return result;
        
    }

private:
    void merge(string firstEmail, string otherEmail) {

        string firstEmailFather = findParent(firstEmail);
        string otherEmailFather = findParent(otherEmail);

        if (firstEmailFather != otherEmailFather) {
            parent[firstEmailFather] = otherEmailFather;
        }
        return;
    }

    string findParent(string email) {
        string oriEamil = email;
        // email.compare(parent[email], std::locale::tolower)
        while (email != parent[email]) {
            email = parent[email];
        }
        parent[oriEamil] = email;
        return email;
    }

private:
    unordered_map<string, string> parent;
    unordered_map<string, string> email2Account;
};

void TestBuildBinaryTree()
{
    std::cout << "----begin to TestBuildBinaryTree ---" << std::endl;
    std::cout << "----finished TestBuildBinaryTree ---" << std::endl;
}
