# LECTURE 20
## `std::string`
Another use for `std::string::npos` is for the substring functions.<br>
##### `std::string& some_function(std::string str, size_t idx, size_t n);`<br>
This function returns the substring of `n` many characters starting from `idx` in `str`.<br>
If `n` is greater then the remaining length of the `str`, then it includes all the remaining characters in `str`.<br>
If the aim is to return the substring starting from `idx` till the end, then `n` must be equal or greater then the number of
remaining characters. To ensure this `std::string::npos` can be used.

- `std::string::reserve()`
    This function reserves the space for the string, it doesn't increase it's size, but it's capacity.
##### ###REMARK###
> - Just because it is reserved, it doesn't mean that a position that lies in that capacity is accessible.<br>
>   This also applies for `std::vector` as well.
>   ```cpp
>   std::string str{"string with a size of 24"};
>   str.reserve(100);
>   str[25]; // Undefined Behaviour
>   ```
>
> - Compiler automatically expands the capacity when necessary but it won't shrink it.
> - Reallocation is an expensive operation, since there is no guarantee that that string won't expand again, compiler doesn't
>   shrink the capacity. It only enlarges it.
>   ```cpp
>   std::string str(300'000, 'A');
>   
>   std::cout << "len = " << str.length() << '\n';      // len = 300000
>   std::cout << "cap = " << str.capacity() << '\n';    // cap = 300000
>   
>   str.erase(1);       // will erase starting from index 1 till the end.
>   
>   std::cout << "len = " << str.length() << '\n';      // len = 1
>   std::cout << "cap = " << str.capacity() << '\n';    // cap = 300000
>   str = "hello world";
>   std::string::iterator iter = str.begin();
>   std::cout << *++iter << '\n';               // e
>   ```
> ##### ###REMARK###
> > - `begin()` returns the index to the first element.
> > - `end()` returns the index that comes after the last element. Values like these are typically named as `Sentinel` in programming.

##### ###REMARK###
> Some operations for strings, like reversing a string, are not part of the string class, but it is in the `algorithm` as global
> functions. Reason for this is that these kind of functions are used by other containers as well, vector, array, etc.

As said before, `std::string` is a container. Like all other containers it has `iterator` interfaces and it also has index interfaces.
That's why some `std::string` functions and functions that are used with `std::string` have index and some have iterator
parameters. Most member functions of `std::string` uses index interfaces.
e.g. `erase()` function has both of those possibilities.
```cpp
std::string str{"hello world"};

str.erase(str.begin());
std::cout << '|' << str << '|';           // |ello world| is the output

str = "hello world";
str.erase(0U, 1U);          
std::cout << '|' << str << '|';           // |ello world| is the output

str = "hello world";
str.erase(0U);
std::cout << '|' << str << '|';           // || is the output
```
`insert()` funtions is another example for this, it supports both iterators and indexes.<br>


`std::string::erase()` Can be used in three different ways;
1. `constexpr` since C++20<br>
    `basic_string& erase(size_type index = 0, size_type count = std::string::npos)`<br>
    ```cpp
    std::string str{"hello world"};
    str.erase();
    std::cout << '|' << str << '|'; // || is the output
    str{"hello world"};
    str.erase(1);
    std::cout << '|' << str << '|'; // |h| is the output
    ```

2. since C++11, `constexpr` since C++20<br>
    `iterator erase(const_iterator position)`<br>
    ```cpp
    std::string str{"hello world"};
    str.erase(str.begin());
    std::cout << '|' << str << '|'; // |ello world| is the output
    ```

3. since C++11, `constexpr` since C++20<br>
    `iterator erase(const_iterator first, const_iterator last)`
    ```cpp
    std::string str{"hello world"};
    str.erase(str.begin(), str.begin() + 2);
    std::cout << '|' << str << '|';           // |llo world| is the output
    ```

4. `noexcept` since C++11, `constexpr` since C++20<br>
        std::string str{"hello world"};
        str.clear();
        std::cout << '|' << str << '|';           // || is the output

5. other ways to empty a `std::string`<br>
    ```cpp
    std::string str{"hello world"};
    str.erase(str.begin(), str.end());
    str.erase();
    str.clear();
    str.resize(0);
    str = "";
    str = {};
    str = std::string{};
    ```

##### ###REMARK###
> While taking input for a string, `std::cin >> str;` will interpret spaces as separator.
> ```cpp
> std::string str;
> std::cin >> str;                // hello world is the input
> std::cout << '|' << str << '|'; // |hello| is the output
> ```
>
> BUT `std::getline()` considers new line characters as separators.
> ```cpp
> std::string str;
> std::getline(std::cin, str);    // hello world is the input
> std::cout << '|' << str << '|'; // |hello| is the output
> ```
>
> A distinct separator for `std::getline` can be declared by passing it as the third argument.
> ```cpp
> std::string str1, str2;
> std::getline(std::cin, str1);      // hello world is the input
> std::cout << '|' << str1 << '|';   // |hello world|
> std::getline(std::cin, str2, ','); // hello, is the input
> std::cout << '|' << str2 << '|';   // |hello|
> ```

##### ###REMARK###
> When a substring of any given `std::string` is needed, using `str.substr(pos1, pos2)` can be used but, this causes the
> copying of the whole substring. If the substring is too long, this operation gets expensive.<br>
> As an alternative, if the substring is only needed for read-only operations, then `string_view` can be used.<br>
> ```cpp
> std::string      str{"hello world"};
> std::string_view sv{&str.at(0U), 4U};
> ```
> Similar thing happens when we want to swap two strings. Doing
> ```cpp
> std::string s1(100'000, 'a');
> std::string s2(200'000, 'b');
>
> std::string temp = s1;
> s1 = s2;
> s2 = s1;
> ```
> would be unnecessarily wasteful because we don't need Deep Copy. Swapping the values of the pointers and the size
> values of the strings would be enough.
> ```cpp
> std::string s1(100'000, 'a');
> std::string s2(200'000, 'b');
> s1.swap(s2);
> // OR
> swap(s1, s2);
