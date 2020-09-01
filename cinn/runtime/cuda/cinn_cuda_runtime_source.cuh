/**
 * \file This file contains all the intrisics available to be used in CUDA code generated by CodeGen.
 */

#define FN(x) cinn_nvgpu_ ## x ## _fp32
// NOTE Due to function override, we don't need to use type (such as '_fp32') as the suffix of function's name.
__device__ inline float FN(sin)(float x) { return sin(x); }
__device__ inline float FN(cos)(float x) { return cos(x); }
__device__ inline float FN(cosh)(float x) { return cosh(x); }
__device__ inline float FN(tanh)(float x) { return tanh(x); }

__device__ inline float FN(asin)(float x) { return asin(x); }
__device__ inline float FN(acos)(float x) { return acos(x); }
__device__ inline float FN(acosh)(float x) { return acosh(x); }
__device__ inline float FN(atanh)(float x) { return atanh(x); }

__device__ inline float FN(ceil)(float x) { return ceil(x); }
__device__ inline float FN(round)(float x) { return round(x); }
__device__ inline float FN(trunc)(float x) { return trunc(x); }
__device__ inline float FN(abs)(float x) { return abs(x); }
__device__ inline float FN(floor)(float x) { return floor(x); }
__device__ inline float FN(log)(float x) { return log(x); }
__device__ inline float FN(log2)(float x) { return log2(x); }
__device__ inline float FN(log10)(float x) { return log10(x); }
__device__ inline float FN(exp)(float x) { return exp(x); }
__device__ inline float FN(erf)(float x) { return erf(x); }
__device__ inline float FN(sigmoid)(float x) { return 1. / (1 + exp(-x)); }
__device__ inline float FN(sqrt)(float x) { return sqrt(x); }

__device__ inline bool FN(isfinite)(float x) { return isfinite(x); }
__device__ inline bool FN(isinf)(float x) { return isinf(x); }
__device__ inline bool FN(isnan)(float x) { return isnan(x); }

__device__ inline float FN(max)(float a, float b) { return max(a, b); }
__device__ inline float FN(min)(float a, float b) { return min(a, b); }
#undef FN