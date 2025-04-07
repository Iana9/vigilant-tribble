// A. Интервью:
// 1. Записать себе заготовки обхода в ширину и глубину. Сделать их попроще чтобы окинуть взглядом и сразу вспомнилось.
// 2. Записать себе заготовку бинарного поиска.

#include <iostream>
#include <queue>
#include <vector>

struct node {
    int value;
    node* left;
    node* right;
    node(int value) : value(value), left(nullptr), right(nullptr) {};
    node(int value, node* left) : value(value), left(left), right(nullptr) {};
    node(int value, node* left, node* right) : value(value), left(left), right(right) {};
};

void dfs(node* root) {
    if (root != nullptr) {
        std::cout << root->value << std::endl;
    }
    if (root->left != nullptr) {
        dfs(root->left);
    }
    if (root->right!= nullptr) {
        dfs(root->right);
    }
}

void bfs(node* root) {
    std::queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* current = q.front();
        q.pop();
        if (current->left != nullptr) { q.push(current->left); }
        if (current->right != nullptr) { q.push(current->right); }
        std::cout << current->value << std::endl;
    }
}

template<typename Container, typename El>
int binarySearch(const Container& container, const El value) {
    int high = static_cast<int>(container.size());
    int low = 0;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (container[middle] == value) { return middle; }
        if (value > container[middle]) { low = middle + 1; }
        else if (value < container[middle]) { high = middle - 1; }
    }
}

class Solution {
    public:
        int removeElement(std::vector<int>& nums, int val) {
            int k = 0;
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] != val) {
                    std::swap(nums[k], nums[i]);
                    ++k;
                }
            }
            return k;
        }
    };

class Solution {
    public:
        int searchInsert(std::vector<int>& nums, int target) {
            int low, high, mid;
            low = 0;
            high = nums.size() - 1;
            while (low <= high) {
                mid = low + (high - low) / 2;
                if (nums[mid] == target) { return mid;}
                else if (nums[mid] < target) { low = mid + 1; }
                else { high = mid - 1; }
            }
            return low;
        }
    };

class Solution {
    public:
        int lengthOfLastWord(std::string s) {
            int countChar = 0;
            std::reverse(s.begin(), s.end());
            for (auto const& s : s) {
                if (countChar != 0 and s == ' ') { break; }
                if (s != ' ') { countChar++; }
            }
            return countChar;
        }
    };


class Solution {
    public:
        std::vector<int> plusOne(std::vector<int>& digits) {
            int digit, remainder;
            remainder = 0;
            for (int i = digits.size() - 1; i >= 0; --i) {
                digit = digits[i] + (digits.size() - 1 == i ? 1 : 0) + remainder;
                remainder = digit/10;
                digits[i] = digit%10;
                if (remainder == 0) break;
            }
            if (remainder != 0) {
                digits.insert(digits.begin(), remainder);
            }
            return digits;
        }
    };

    struct node {
        std::unordered_map<char, node*> children;
        bool isEndOfWord = false;
    };
    
class Solution {
    public:
        std::string longestCommonPrefix(std::vector<std::string>& strs) {
            if (strs.empty() || std::any_of(strs.begin(), strs.end(), [](const std::string& str) { return str.empty(); })) {
                return "";
            }

            for (const auto& str : strs) {
                this->insert(str);
            }

            node* currentNode = root;
            std::string resultPrefix{""};
            while (currentNode->children.size() == 1 and !currentNode->isEndOfWord) {
                resultPrefix += currentNode->children.begin()->first;
                currentNode = currentNode->children.begin()->second;
            }
            return resultPrefix;
        }
    private:
        node* root = new node();
        void insert(const std::string& word) {
            node* current_node = root;
            for (char c : word) {
                if (current_node->children.find(c) == current_node->children.end()) {
                    current_node->children[c] = new node();
                }
                current_node = current_node->children[c];
            }
            current_node->isEndOfWord = true;
        }


};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
        int maxDepth(TreeNode* root) {
            if (root == nullptr) { return 0; }
            int leftDepth = maxDepth(root->left);
            int rightDepth = maxDepth(root->right);
            return std::max(leftDepth, rightDepth) + 1;
        }
};

std::vector<std::vector<char>> multipleLineInput(int n) 
{
    std::vector<std::vector<char>> result;
    std::string line;
    result.resize(n);
    for (int i = 0; i < n; ++i) 
    {   
        std::getline(std::cin, line);
        for (const char& c : line) 
        {
            result[i].push_back(c);
        }
    }
    return result;
}

int main() 
{

    node* root = new node(5, new node(3, new node(1), new node(4)), new node(8, new node(6), new node(9)));

    bfs(root);

    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = binarySearch(values, 123);

    std::cout << "Binary search result: " << result << std::endl;

    return 0;
}