# LECTURE 19
## `std::string`
- It's a type of dynamic array and a container class.
- Usually it consists of three `char` pointers. One points to the start of the allocated memory, one points to the current last
    element and the last one points to the end of the allocated memory. It is also possible to get this done by using one `char`
    pointer and two integers or `size_t` members, thanks to the pointer arithmetic.

#### Different Types of Strings
- Null Terminated Byte Stream (`CString`) e.g. this_is_a_ntbs\0
- An object of `std::string`
- A string literal that is known at the compile time, which also has a `null` character at the end. e.g. "thisi_a_string_literal"

##### ###REMARK###
> There is a thing called Small String Optimization. Because allocating and reallocating dynamic arrays are expensive
> operations, if the contents of the string is too small, compiler decides to keep the contents directly in the object instead of
> using three pointers. Because of this some compilers include a buffer inside the object and sometimes even can decide to use
> the space of two of the pointers as part of the buffer if the buffer is not enough.<br>
> Therefore,
> ```cpp
> int main() { std::cout << "sizeof(std::string) = " << sizeof(std::string) << '\n'; }
> ```
> can have the output of just three times the size of a char pointer or, slightly bigger, because of the buffer.

- It has the nested type of `size_type`.
    ##### ###REMARK###
    > `std::string::size_type` is not always `size_t` but for `char` specialization of `std::string`, it's always `size_t`.
    > Following parameters and expression types are `size_type`
    > 1. Index storing type
    > 2. Length storing type
    > 3. Amount type

#### Some member functions of std::string
- `length()` and `size()`<br>
    They do the same thing. They both exists because `size()` comes from the generic side of `std::string` and it's usable with
    every container type. `length()` is specific to `std::string`. They both return `size_type`.
- `empty()`<br>
    Does not empty the container, it checks if it is empty or not. Returns `bool`. Can also be achieved by checking if the `size()`
    returns 0, but using `empty()` is more readible and idiomatically better.
- `capacity()`
    Returns the capacity of the string. It's return type is `size_type`.

##### ###REMARK###
> REALLOCATION TAKES TIME.<br>
> REALLOCATION INVALIDATES POINTERS.

#### Typical Constructors of std::string
- `CString` Constructor (`char const*`)
    ```cpp
    char s[] = "asd\0"; // It must contain null terminator at the end. If not, it's an Undefined Behaviour.
    std::string str(s);
    std::cout << '|' << str << '|'; // Outputs |asd|
    ```

- Data Constructor (`char const*`, `size_t`)
    ```cpp
    char        s = "tycakmak1";
    std::string str(s, 5);
    std::cout << '|' << str << '|'; // Outputs |tycak|
    ```

- Fill Constructor (`size_t`, `char`)
    ```cpp
    std::string str(5, 'A');
    std::cout << '|' << str << '|'; // Outputs |AAAAA|
    ```

- `std::initializer_list` Constructor {'a', 'b', 'c'}
    ```cpp
    std::string str{'a', 'b', 'c'};
    std::cout << '|' << str << '|'; // Outputs |abc|
    ```
    ##### ###REMARK###
    > e.g. for initializer_list Constructor
    > ```cpp
    > class Myclass {
    > public:
    >     Myclass(int){ std::cout << "int" << '\n'; }
    >
    >     Myclass(std::initializer_list<int>){
    >         std::cout << "std::initializer_list<int>" << '\n';
    >     }
    > }; // class Myclass
    >
    > int main(){
    >     Myclass a(5);       // Outputs int
    >     Myclass b{ 5 };     // Outputs std::initializer_list<int>
    > }
    > ```

- range Constructor (pos1, pos2)
    Requires two positions, they don't have to be pointers. First position is inclusive, second is not.

- `std::string` Constructor (`std::string`)
    ```cpp
    std::string str1{"tyc"};
    std::string str2(str1);
    std::cout << '|' << str2 << '|'; // Outputs |tyc|
    ```

- Sub-String Constructor (`std::string`, `size_t` idx)
    ```cpp
    std::string str1{"tycakmak1"};
    std::string str2(str1, 2);
    std::cout << '|' << str2 << '|'; // Outputs |cakmak1|
    ```

- Sub-String Constructor (`std::string`, `size_t` idx1, `size_t` idx2)
    ```cpp
    std::string str1{"tycakmak1"};
    std::string str2(str1, 2, 3);
    std::cout << '|' << str2 << '|'; // Outputs |cak|
    ```

##### ###REMARK###
> `std::string` does not have a char Constructor.
> ```cpp
> std::string s1('A');  // Invalid
> std::string s2 = 'A'; // Invalid
> ```

##### ###REMARK###
> `std::string` has a `static constexpr` variable called `npos`. It stores the highest possible value for `size()` function of string.
> This variable is used as to denote a failure.<br>
> ##### `string::size_type find(char) const`;<br>
> This function searches a character in a string. If it can find the character then it returns the position of that character in that
> string. If it can't find it, it returns `string::npos` because that value can't be a position.
> ```cpp
> int main() {
>     std::string str{"tycakmak1"};
>     std::cout << str.find('t') << '\n'; // Outputs 0
>     std::cout << str.find('b') << '\n'; // Outputs the value of std::string::npos
>
>     return 0;
> }
> ```
