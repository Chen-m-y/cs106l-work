#include "spellcheck.h"

#include <algorithm>
#include <bits/ranges_algo.h>
#include <cctype>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

// using Corpus = std::set<Token>
Corpus tokenize(std::string& source) {
  auto all_it = find_all(source.begin(), source.end(), 
    [](unsigned char c){
    return std::isspace(c);
  });
  std::set<Token> tokens; // set没有大小构造--而vector有顺序有位置
  // 红黑树没有固定位置，是按排序方式动态插入节点
  std::transform(all_it.begin(), all_it.end()-1,
                 all_it.begin()+1,
                 std::inserter(tokens, tokens.end()), //输出迭代器适配器
                 [&](auto begin, auto end){
                  return Token(source, begin, end);
  });
  std::erase_if(tokens,[](const Token& x){return x.content.empty();});
  // Corpus()：空语料库
  return tokens;
}

// using Dictionary = std::unordered_set<std::string>;
namespace rv = std::ranges::views;
std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  // 遍历才真正触发计算,迭代器从 source 里取元素，套用 lambda 过滤
  auto misspelled_tokens_view = rv::all(source) 
    | rv::filter([&dictionary](const Token& t)
      {return dictionary.find(t.content) == dictionary.end();}
  );
  auto misspellings_view = misspelled_tokens_view | rv::transform([&dictionary](const Token& t){
    auto suggestions_view = rv::all(dictionary) | rv::filter([&t](const std::string& dic){
      return levenshtein(t.content, dic) == 1;
    });
    std::set<std::string> suggestions(suggestions_view.begin(), suggestions_view.end());
    return Misspelling{t, suggestions};
  });
  auto misspellings = misspellings_view | rv::filter([](Misspelling mis){
    return !mis.suggestions.empty();
  });
  
  std::set<Misspelling> result(misspellings.begin(), misspellings.end());
  return result;
};

/* Helper methods */

#include "utils.cpp"