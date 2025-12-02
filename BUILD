cc_binary(
    name = "embed",
    srcs = ["src/embed.c"],
    deps = ["@lua_src_with_build//:lua"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "mylib_so",
    srcs = ["src/myluamodule.c"],
    deps = ["@lua_src_with_build//:lua"],
    linkshared = 1,
    visibility = ["//visibility:public"],
)

filegroup(
    name = "examples",
    srcs = ["scripts/require_module.lua"],
)
