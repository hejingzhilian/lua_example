cc_binary(
    name = "embed",
    srcs = ["src/embed.c"],
    copts = ["-I/usr/include/lua5.3"],
    linkopts = ["-llua5.3"],
    visibility = ["//visibility:public"],
)

# Build a Lua C module as a shared object using gcc via genrule.
# This avoids needing to vendor Lua into the workspace; it requires the
# system to have lua headers and lib (e.g. `liblua5.3-dev`).
genrule(
    name = "mylib_so",
    srcs = ["src/myluamodule.c"],
    outs = ["mylib.so"],
    cmd = "gcc -fPIC -shared -I/usr/include/lua5.3 $(SRCS) -o $@ -llua5.3",
    visibility = ["//visibility:public"],
)

filegroup(
    name = "examples",
    srcs = ["scripts/require_module.lua"],
)
