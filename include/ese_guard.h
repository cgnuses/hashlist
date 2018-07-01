#ifndef HL_ESE_GUARD_H
#define HL_ESE_GUARD_H

/**
 * В данном файле собранны предопределения упрощающие понимание вызовов
 * API Jet Blue.
 * 
 * Каждый вызов возвращает код ошибки и мы просто убераем нагромаждение кода
 * проверки вызова и детектирования ошибки.  
 */


#define ese_guard_start() {int __guard_count__=0;JET_ERR __hl_ese_guard_var__

#define ese_guard(__jet_call__, __error_string__) \
++__guard_count__;__hl_ese_guard_var__ = __jet_call__; \
if (__hl_ese_guard_var__ != JET_errSuccess){ \
	error_out("\n[%d] %s\n", __hl_ese_guard_var__); \
	return -__guard_count__; \
}

#define ese_guard_end(__terminate__) if(__terminate__){JetTerm(0);}}

#endif
