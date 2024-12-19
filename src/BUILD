load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "tireslib",
    hdrs = ["tires.hpp"],
    deps = [
        "@pooya//src/block",
        "@pooya//src/solver",
        "@pooya//src/signal",
        "@pooya//src/misc",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "tires",
    srcs = ["tires.cpp"],
    deps = [
        "tireslib",
    ],
)
