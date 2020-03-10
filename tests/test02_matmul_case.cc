#include <gtest/gtest.h>

#include "cinn/runtime/cinn_runtime.h"
#include "tests/test02_matmul.h"

TEST(test02, basic) {
  const int M = 1000;
  const int N = 400;
  const int K = 500;

  auto* A        = cinn_buffer_t::new_(cinn_device_kind_t::cinn_x86_device, cinn_float32_t(), {M, K});
  auto* B        = cinn_buffer_t::new_(cinn_device_kind_t::cinn_x86_device, cinn_float32_t(), {K, N});
  auto* C        = cinn_buffer_t::new_(cinn_device_kind_t::cinn_x86_device, cinn_float32_t(), {M, N});
  auto* C_target = cinn_buffer_t::new_(cinn_device_kind_t::cinn_x86_device, cinn_float32_t(), {M, N});
  cinn_buffer_malloc(nullptr, A);
  cinn_buffer_malloc(nullptr, B);
  cinn_buffer_malloc(nullptr, C_target);
  cinn_buffer_malloc(nullptr, C);

  float* Ad        = reinterpret_cast<float*>(A->host_memory);
  float* Bd        = reinterpret_cast<float*>(B->host_memory);
  float* Cd_target = reinterpret_cast<float*>(C_target->host_memory);
  float* Cd        = reinterpret_cast<float*>(C->host_memory);

  for (int i = 0; i < M; i++) {
    for (int k = 0; k < K; k++) {
      Ad[i * K + k] = float(rand()) / RAND_MAX;  // NOLINT
    }
  }

  for (int j = 0; j < M; j++) {
    for (int k = 0; k < K; k++) {
      Bd[k * N + j] = float(rand()) / RAND_MAX;  // NOLINT
    }
  }

  // manulally set zero
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      Cd_target[i * N + j] = 0.f;
      Cd[i * N + j]        = 0.f;
    }
  }

  matmul(A, B, C);

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < K; k++) {
        Cd_target[i * N + j] += Ad[i * K + k] * Bd[k * N + j];
      }

      EXPECT_NEAR(Cd[i * N + j], Cd_target[i * N + j], 1e-5);
    }
  }
}