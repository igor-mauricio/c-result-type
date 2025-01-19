# Welcome to the c-result-type wiki!

This project aims to provide a Golang-like error as values experience in C. The main goal is to provide a way to handle errors in a more expressive way, without the need to use the errno variable, the return value of the function or argument pointers to check if it was successful.


## Quick Start

1. Copy result.h to your project
2. Make sure that result.h is in the include path of your project
3. Import the result.h file in your source code

```c
#include "result.h"

GEN_RESULT(int);

Res_int divide(int a, int b) {
    if (b == 0) {
        return (Res_int) {0, InternalError("cannot divide by zero!\n")};
    }
    return (Res_int) {a/b, NoError()};
}

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    DESTRUCT(res, err, divide(a, b));
    if (err.code != NIL) {
        printf("%s\n", err.message);
    }
    printf("%d / %d = %d\n", a, b, res);
}
```

## Available macros:

`GEN_RESULT(type)`

Generate a result type for the specified type, named Res_'type'

`GEN_RESULT_DEF(type,Name)`

Generate a result type for the specified type, named 'Name'

`auto`

Automatically infer the type of a variable

```c
auto a = divide(10, 2);
if (a.err.code != NIL) {
    printf("%s\n", a.err.message);
}
printf("%d %s\n", a.val, a.err.message);
```

`DESTRUCT(var_val, var_err, Result)`

Destructure from 'Result', defining and initializing 'var_val' and 'var_err'
```c
DESTRUCT(id, err, deleteUser(10));
```
`DESTRUCT_CP(var_val, var_err, Result)`

Destructure from 'Result', initializing 'var_val' and 'var_err'
```c
int id;
Error err;
DESTRUCT_CP(id, err, deleteUser(10));
```
`DESTRUCT_VAL(var_val, var_err, Result)`

Destructure from 'Result', defining 'val_val' and initializing 'var_val' and 'var_err'
```c
Error err;
DESTRUCT_VAL(id, err, deleteUser(10));
```
`DESTRUCT_ERR(var_val, var_err, Result)`

Destructure from 'Result', defining 'val_err' and initializing 'var_val' and 'var_err'
```c
int id;
DESTRUCT_ERR(id, err, deleteUser(10));
```

`_`

Ignores the result of a function
```c
DESTRUCT(_, err, deleteUser(10));
```
