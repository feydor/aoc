load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
  name = "silver",
  srcs = ["silver.cc"],
  hdrs = ["silver.h"],
)

cc_library(
  name = "gold",
  srcs = ["gold.cc"],
  hdrs = ["gold.h"],
)

cc_test(
  name = "silver-test",
  size = "small",
  srcs = ["silver-test.cc"],
  deps = [
    ":silver",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_binary(
    name = "silver-main",
    srcs = ["silver-main.cc"],
    deps = [
        ":silver",
    ],
)

cc_binary(
    name = "gold-main",
    srcs = ["gold-main.cc"],
    deps = [
        ":gold",
    ],
)
