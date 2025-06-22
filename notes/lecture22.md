# LECTURE 22
### Runtime Polymorphism

##### ###REMARK###
> - If a `class` has a `virtual` or a pure `virtual` function, it's a polymorphic class.
> - If a `class` has or inherits a pure `virtual` function but does not define an implementation for
it, then that class is an abstract `class`. If a `class` is not abstract, then it is a concrete `class`.
Difference between abstract and concrete classes is, that creating an instance from an abstract `class`
is not permitted. Trying to do so is a syntax error.

#### Static (Early) Binding and Dynamic (Late) Binding
If the compiler decides which function to call during the compile time (called Static Dispatch),
then it is Static Binding.<br>
If it is decided during runtime (called Dynamic Dispatch), then it is Dynamic Binding.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;e.g. Function Overloading is an example for Static Binding.
Function Overriding is an example for Dynamic Binding.
37:52
