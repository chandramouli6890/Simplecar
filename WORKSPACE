load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip"],
  strip_prefix = "googletest-1.14.0",
  sha256 = "1f357c27ca988c3f7c6b4bf68a9395005ac6761f034046e9dde0896e3aba00e4",
)


http_archive(
  name = "eigen",
  build_file_content = """
package(default_visibility= ["//visibility:public"])

cc_library(
    name = "eigen",
    hdrs = glob(
        ["Eigen/**"],
        exclude = [
            "Eigen/src/OrderingMethods/Amd.h",
            "Eigen/src/SparseCholesky/**",
            "Eigen/Eigen",
            "Eigen/IterativeLinearSolvers",
            "Eigen/MetisSupport",
            "Eigen/Sparse",
            "Eigen/SparseCholesky",
            "Eigen/SparseLU",
        ],
    ),
    defines = [
        "EIGEN_MPL_ONLY",
        "EIGEN_NO_DEBUG",
    ],
    includes = [
        ".",
        ],
    visibility = ["//visibility:public"],
)
""",
  urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip"],
  strip_prefix = "eigen-3.4.0",
  sha256 = "1ccaabbfe870f60af3d6a519c53e09f3dcf630207321dffa553564a8e75c4fc8",
)

# http_archive(
#   name = "pooya",
#   urls = ["https://github.com/modjtabaf/pooya/archive/21f3aeffee1f1a40d0f4b2067d7ab0dc92e2ea9f.zip"],
#   strip_prefix = "pooya-21f3aeffee1f1a40d0f4b2067d7ab0dc92e2ea9f",
#   sha256 = "40d836303d641edbd172a0607dd448abfe26f4a64bf702a1645d5548c5057edf",
# )

http_archive(
  name = "pooya",
  urls = ["https://github.com/modjtabaf/pooya/archive/086aa681b567c4263a363b9be7ebc69bc9bdc417.zip"],
  strip_prefix = "pooya-086aa681b567c4263a363b9be7ebc69bc9bdc417",
)
