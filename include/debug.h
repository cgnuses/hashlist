#ifndef HL_DEBUG_H
#define HL_DEBUG_H

/**
 * Набор сервисных предопределений для удобства включения выключения
 * отладочного или ошибочного вывода.
 * 
 * Поведение задаётся в файле config.h 
 */


#ifdef HL_DEBUG_OUT
# define debug_out(__format__, ...) fprintf(stdout, __format__, ##__VA_ARGS__)
#else 
# define debug_out(__format__, ...)
#endif

#ifdef HL_ERROR_OUT
# define error_out(__format__, ...) fprintf(stderr, __format__, ##__VA_ARGS__)
#else 
# define error_out(__format__, ...)
#endif

#endif
