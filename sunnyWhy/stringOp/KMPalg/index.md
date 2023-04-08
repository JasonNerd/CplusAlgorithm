---
title: "字符串专题(2)-字符串 KMP算法"
date: 2023-04-08T15:21:15+08:00
draft: false
tags: ["字符串", "KMP算法"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---
本节主要讨论字符串的匹配问题，也就是说，如果给出两个字符串 text和 pattern，需要判断字符串 pattern 是否是字符串 text 的子串。一般把**字符串 text 为文本串，而把字符串pattern称为模式串**。例如，给定文本串text="caniwaitforyourheart”，那么模式串pattern="wait"是它的子串，而模式串pattern="sorry"则不是它的子串。

暴力的解法非常简单，只要枚举文本串的起始位置i，然后从该位开始逐位与模式串进行匹配，如果匹配过程中每一位都相同，则匹配成功:否则，只要出现某位不同，就让文本串的起始位置变为i+1，并从头开始模式串的匹配。这种做法的时间复杂度为 O(nm)，其中n和m分别是文本串与模式串的长度。显然，当n和m都达到10级别的时候完全无法承受。下面介绍KMP算法时间复杂度为O(n+m)。它是由Knuth、Morris、Pratt这3位科学家共同发现的，这也是其名字的由来。


## next 数组
假设有一个字符串s(下标从0开始)，那么它以i号位作为结尾的子串就是 `s[0...i]` 对该子串来说，长度为 k+1 的前缀和后缀分别是 `s[0...k]` 与 `s[i-k...i]` 。现在定义一个int 型数组 next (请先不要在意名字)，其中next[i]表示使子串 `s[0...i]` 的前缀 `s[0...k]` 等于后缀 `s[i-k...i]` 的最大的k(注意前缀跟后缀可以部分重叠，但不能是 `s[0...i]` 本身); 如果找不到相等的前后缀，那么就令next[i] = -1。

例如, s="ababaab", next[] = {-1, -1, 0, 1, 2, 0, 1}

下面总结next数组的求解过程，并给出代码，读者可以结合上面的例子理解:
1. 初始化next数组，令j=next[0]=-1;
2. 让i在1~len-1范围遍历，对每个i，执行3&4, 以求解next[i];
3. 不断令j=next[i]，直到j回退为-1，或是si]=si+1]成立;
4. 如果s[i]==s[j+1]，则next[i]=j+1;否则next[i]=j.

```c++
void fillnext(string str, int next[]){
    next[0] = -1;
    int n = str.length();
    int j = -1;
    for(int i=1; i<n; i++){
        // 1. 失配则回退
        while(j != -1 && s[i] != s[j+1])
            j = next[j];
        // 2. 适配则前进
        if(s[j+1] == s[i])
            ++j;
        next[i] = j;
    }
}
```

由此, KMP算法的一般思路是:
1. 初始化j=-1，表示pattemn 当前已被匹配的最后位。
2. 让i遍历文本串text，对每个i，执行3&4来试图匹配`text[i]`和`pattern[i+1]`。
3. 不断令j=next[i]，直到j回退为-1，或是text[i]=pattern[j+1]成立。
4. 如果text[i]=pattern[j+1]，则令j++。如果j达到m-1,说明pattern 是 text的子串

```c++
bool KMP(string text, string pattern){
    int n = text.length(), m = pattern.length();
    // 1. 计算pattern的next 数组
    int *next = new int [m];
    fillnext(pattern, next);
    int j = -1;
    for(int i=1; i<n; i++){
        while(j!=-1 && text[i]!=pattern[j]) // text[i] 匹配失败则回退
            j = next[j];
        if(text[i]==pattern[j])
            ++j;
        if (j == m-1) return true;
    }
    return false;
}
```