# lua_example (Bazel + Lua/C example)

这个仓库包含最小的示例，展示如何使用 Bazel 构建：

- 一个 C 程序嵌入 Lua (`//:embed`)。
- 一个 C 写的 Lua 模块（共享对象）通过 genrule 构建 (`//:mylib_so`) 并由 `scripts/require_module.lua` 使用。

注意：构建 Lua C 模块需要系统安装 Lua 开发头和库（例如 Debian/Ubuntu 上的 `liblua5.3-dev`）。

快速测试（在容器或主机上）：

```bash
sudo apt-get update
sudo apt-get install -y build-essential liblua5.3-dev lua5.3
bazel build //:embed //:mylib_so
./bazel-bin/embed
# 把生成的 mylib.so 放到 LUA_CPATH 可见位置或当前目录，再运行 lua 脚本
cp bazel-bin/mylib.so .
lua5.3 scripts/require_module.lua
```
# lua_example