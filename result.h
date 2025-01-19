#pragma once

typedef enum {
    NIL,
    ERR_INTERNAL,
    ERR_VALIDATION,
    ERR_UNAUTHORIZED,
    ERR_NOT_IMPLEMENTED,
    ERR_NOT_FOUND,
} ErrorCode;

typedef struct {
    ErrorCode code;
    const char* message;
} Error;

static Error NoError(){
    return (Error){.code=NIL};
}

static Error InternalError(const char* message){
    return (Error){.code=ERR_INTERNAL, .message=message};
}

static Error ValidationError(const char* message){
    return (Error){.code=ERR_VALIDATION, .message=message};
}

static Error UnauthorizedError(const char* message){
    return (Error){.code=ERR_UNAUTHORIZED, .message=message};
}

static Error NotImplementedError(const char* message){
    return (Error){.code=ERR_NOT_IMPLEMENTED, .message=message};
}

static Error NotFoundError(const char* message){
    return (Error){.code=ERR_NOT_FOUND, .message=message};
}


#ifndef __cplusplus
#define auto __auto_type
#endif

#define __CONCATE(x,y) x ## y
#define _CONCATE(x,y) __CONCATE(x,y)
#define _ _CONCATE(__tmp_ignore_var_, __LINE__)
#define _DESTRUCT_RESULT _CONCATE(__tmp_destruct_result_, __LINE__)

#define GEN_RESULT(T) typedef struct {T val; Error err;} Res_##T
#define GEN_RESULT_DEF(T,Name) typedef struct {T val; Error err;} Res_##Name

#define DESTRUCT(Value, Err, Result) auto _DESTRUCT_RESULT = Result; auto Err = _DESTRUCT_RESULT.err; auto Value = _DESTRUCT_RESULT.val
#define DESTRUCT_CP(Value, Err, Result) auto _DESTRUCT_RESULT = Result; Err = _DESTRUCT_RESULT.err; Value = _DESTRUCT_RESULT.val
#define DESTRUCT_VAL(Value, Err, Result) auto _DESTRUCT_RESULT = Result; Err = _DESTRUCT_RESULT.err; auto Value = _DESTRUCT_RESULT.val
#define DESTRUCT_ERR(Value, Err, Result) auto _DESTRUCT_RESULT = Result; auto Err = _DESTRUCT_RESULT.err; Value = _DESTRUCT_RESULT.val

GEN_RESULT(int);
GEN_RESULT(float);
GEN_RESULT(double);
GEN_RESULT(char);
GEN_RESULT_DEF(char*, String);
